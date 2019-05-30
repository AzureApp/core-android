/**
 ******************************************************************************
 * Azure : Open Source Multi-Target Memory Editor                             *
 * File  : main.cc                                                            *
 ******************************************************************************
 * Copyright 2018 Satori. All rights reserved.                                *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

#include <gflags/gflags.h>
#include <grpc++/grpc++.h>
#include <libazure/core.h>
#include <libazure/services/connection_service.h>
#include <linenoise.h>
#include <iostream>
#include <string>
#include <vector>

DEFINE_bool(daemon, true, "Run azure as a daemon");
DEFINE_string(ip, "127.0.0.1", "IP address for TCP server to connect to");
DEFINE_int32(port, 1248, "Port for TCP server to connect to");

namespace azure {

extern "C" int main(int argc, char **argv) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);

  if (FLAGS_daemon) {
    std::printf("This is a development executable. Please do not use\n");

    Core core("0.0.0.0");
    core.AddService(new ConnectionServiceImpl());
    core.Run();

    return 0;
  } else {
    // AZLog("Starting azure in command-line mode");
    char *line;
    while ((line = linenoise("azure> ")) != NULL) {
      if (!strcmp(line, "quit")) {
        break;
      }
      printf("You wrote: %s\n", line);
      linenoiseFree(line);
    }
  }

  // msgpack_main(argc, argv);
}

}  // namespace azure