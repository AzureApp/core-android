/**
 ******************************************************************************
 * Azure : Open Source Multi-Target Memory Editor                             *
 * File  : handshake_handler.cc                                               *
 ******************************************************************************
 * Copyright 2018 Satori. All rights reserved.                                *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

#include "handshake_handler.h"
#include <libazure/client_agent.h>
#include <libazure/logging.h>
#include "handshake_handler.h"
namespace azure {

HandshakeObject HandshakeHandler::HandshakeForCurrentDevice() {
  HandshakeObject obj;
  obj.acp_version = "1.0.0";  // TODO: don't hardcode this
  obj.system = OperatingSystem::Android;

  return obj;
}

int HandshakeHandler::HandleMessage(const MessageHandle& object_handle) {
  try {
    HandshakeObject handshake = object_handle.as<HandshakeObject>();

    AZLogD("Received handshake from OS %d with ACP version %s",
           (int)handshake.system, handshake.acp_version.c_str());

    HandshakeObject this_device = HandshakeForCurrentDevice();

    if (client_agent()->SendObject(this_device)) {
      return MessageHandler::Success;
    } else {
      return MessageHandler::SendFailure;
    }
  } catch (const msgpack::type_error& e) {
    AZLogE("Could not parse handshake object");
    return MessageHandler::InvalidObject;
  }
}

}  // namespace azure