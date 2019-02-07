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
#include <libazure/logging.h>
#include "handshake_handler.h"

namespace azure {

int HandshakeHandler::HandleMessage(const MessageHandle& object_handle) {
  try {
    HandshakeObject handshake = object_handle.as<HandshakeObject>();

    AZLogD("Received handshake from OS %d with ACP version %s",
           (int)handshake.system, handshake.acp_version.c_str());

    return MessageHandler::Success;
  } catch (const msgpack::type_error& e) {
    AZLogE("Could not parse handshake object");
    return MessageHandler::InvalidObject;
  }
}

}  // namespace azure