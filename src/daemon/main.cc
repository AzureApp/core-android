/**
 ******************************************************************************
 * Azure : Open Source Multi-Target Memory Editor                             *
 * File  : main.cc                                                            *
 ******************************************************************************
 * Copyright 2018 Satori. All rights reserved.                                *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

#include <iostream>
#include <vector>

#include <gflags/gflags.h>
#include <linenoise.h>

#include <libazure/data_objects/meta_object.h>
#include <libazure/data_objects/search_object.h>
#include <libazure/daemon.h>
#include <libazure/logging.h>

DEFINE_bool(daemon, false, "Run azure as a daemon");
DEFINE_string(ip, "127.0.0.1", "IP address for TCP server to connect to");
DEFINE_int32(port, 1248, "Port for TCP server to connect to");

namespace azure {

extern "C" int main(int argc, char **argv) {
    gflags::ParseCommandLineFlags(&argc, &argv, true);

    if (FLAGS_daemon) {
        AZLog("Starting azure in daemon mode");
        Daemon daemon(argc, argv, FLAGS_ip, FLAGS_port);
        return daemon.Run();
    } else {
        AZLog("Starting azure in command-line mode");
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

} // namespace azure