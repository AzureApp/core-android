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
}

Core::~Core() {}

void Core::Run() {
  // TODO: an alternative to busy waiting here
  while (true) {
    try {
      auto conn = server_.AwaitConnection(1000);  // timeout after 1 second

      if (conn) {
        // spawn new thread to run client agent
        std::thread thread(&Core::SpawnNewClient, this, conn);
        thread.detach();
      }
    } catch (const std::runtime_error& e) {
      AZLogW("Socket %s:%d disconnected", server_.address().c_str(),
             server_.port());

      break;
    }
  }
}

void Core::AddNewAgent(std::unique_ptr<ClientAgent>& agent) {
  agents_.push_back(std::move(agent));
}

void Core::SpawnNewClient(std::shared_ptr<TCPConn> conn) {
  auto agent = std::make_unique<ClientAgent>(conn);
  // TODO: cleanup this code
  agent->RegisterMessageHandler(
      ObjectType::Handshake, std::make_unique<HandshakeHandler>(agent.get()));
  agent->Run();
  AddNewAgent(agent);
}

}  // namespace azure