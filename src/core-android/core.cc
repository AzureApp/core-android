/**
 ******************************************************************************
 * Azure : Open Source Multi-Target Memory Editor                             *
 * File  : core.cc                                                            *
 ******************************************************************************
 * Copyright 2018 Satori. All rights reserved.                                *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

#include "core.h"
#include <libazure/logging.h>
#include <thread>
#include "message_handlers/handshake_handler.h"

namespace azure {

Core::Core(std::string addr, int port) : server_(addr, port) {
  if (!server_.Setup()) {
    AZLogE("Could not setup TCP server [%s:%d]", addr.c_str(), port);
  }

  using namespace std::placeholders;

  auto func = std::bind(&Core::SpawnNewClient, this, _1);
  server_.AddCallback(func);
}

Core::~Core() {}

void Core::Run() { server_.AwaitConnections(); }

void Core::SpawnNewClient(int descriptor) {
  // start client agent on new thread
  std::thread t([this, descriptor]() {
    auto agent = std::make_unique<ClientAgent>(descriptor);
    // TODO: cleanup this code
    agent->RegisterMessageHandler(ObjectType::Handshake,
                                  std::make_unique<HandshakeHandler>(agent.get()));
    agent->Run();
    agents_.push_back(std::move(agent));
  });

  t.detach();
}

}  // namespace azure