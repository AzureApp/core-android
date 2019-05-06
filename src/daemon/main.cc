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
#include <libazure/services/connection_service.h>
#include <linenoise.h>
#include <iostream>
#include <string>
#include <vector>

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

DEFINE_bool(daemon, true, "Run azure as a daemon");
DEFINE_string(ip, "127.0.0.1", "IP address for TCP server to connect to");
DEFINE_int32(port, 1248, "Port for TCP server to connect to");

namespace azure {

extern "C" int main(int argc, char **argv) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);

  if (FLAGS_daemon) {
    std::printf("This is a development executable. Please do not use\n");

    std::string server_address("0.0.0.0:1248");
    azure::ConnectionServiceImpl connection_service;

    ServerBuilder builder;
    // Listen on the given address without any authentication mechanism.
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&connection_service);
    // Register "service" as the instance through which we'll communicate with
    // clients. In this case it corresponds to an *synchronous* service.
    // builder.RegisterService(&service);
    // Finally assemble the server.
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;

    // Wait for the server to shutdown. Note that some other thread must be
    // responsible for shutting down the server for this call to ever return.
    server->Wait();

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