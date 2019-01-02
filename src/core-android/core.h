/**
 ******************************************************************************
 * Azure : Open Source Multi-Target Memory Editor                             *
 * File  : core.h                                                             *
 ******************************************************************************
 * Copyright 2018 Satori. All rights reserved.                                *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

#ifndef CORE_ANDROID_CORE_H
#define CORE_ANDROID_CORE_H

#include <libazure/client_agent.h>
#include <libazure/tcp_server.h>
#include <memory>
#include <string>
#include <vector>

namespace azure {

// Currently this core is only configured for TCP use
// It reimplements what the (now deprecated) Daemon class did
class Core {
 public:
  explicit Core(std::string address, int port);
  ~Core();

  void Run();

 private:
  void SpawnNewClient(int descriptor);

  TCPServer server_;
  std::vector<std::unique_ptr<ClientAgent>> agents_;
};

}  // namespace azure

#endif  // CORE_ANDROID_CORE_H
