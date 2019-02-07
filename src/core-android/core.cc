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

Core::Core(const std::string& addr, int port) : server_(addr, port) {
  if (!server_.Setup()) {
    AZLogE("Could not setup TCP server [%s:%d]", addr.c_str(), port);
  }

  using namespace std::placeholders;

  auto func = std::bind(&Core::SpawnNewClient, this, _1);
  server_.AddCallback(func);
}

Core::~Core() {}

void Core::Run() {
  // TODO: an alternative to busy waiting here
  while (true) {
    // TODO: return new connection and spawn thread from here, not using
    // delegate callback
    if (!server_.AwaitConnections(1000)) {
      AZLogW("Socket %s:%d disconnected", server_.address().c_str(),
             server_.port());

      break;
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}

void Core::SpawnNewClient(int descriptor) {
  // start client agent on new thread
  std::thread t([this, descriptor]() {
    auto agent = std::make_unique<ClientAgent>(descriptor);
    // TODO: cleanup this code
    agent->RegisterMessageHandler(
        ObjectType::Handshake, std::make_unique<HandshakeHandler>(agent.get()));
    agent->Run();
    agents_.push_back(std::move(agent));
  });

  t.detach();
}

}  // namespace azure