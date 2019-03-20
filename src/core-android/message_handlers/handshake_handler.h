/**
 ******************************************************************************
 * Azure : Open Source Multi-Target Memory Editor                             *
 * File  : handshake_handler.h                                                *
 ******************************************************************************
 * Copyright 2018 Satori. All rights reserved.                                *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

#ifndef AZURE_HANDSHAKE_HANDLER_H
#define AZURE_HANDSHAKE_HANDLER_H

#include <libazure/message_handler.h>

namespace azure {

class HandshakeHandler : public MessageHandler {
 public:
  HandshakeHandler(const ClientAgent* agent) : MessageHandler(agent) {}

  virtual int HandleMessage(const MessageHandle& object_handle) override;

 private:
  static HandshakeObject HandshakeForCurrentDevice();
};

}  // namespace azure

#endif