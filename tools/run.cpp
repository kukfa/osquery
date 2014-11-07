// Copyright 2004-present Facebook. All Rights Reserved.

#include <gflags/gflags.h>
#include <glog/logging.h>

#include "osquery/core.h"

DEFINE_string(query, "", "query to execute");
DEFINE_int32(iterations, 1, "times to run the query in question");
DEFINE_int32(delay, 0, "delay before and after the query");

int main(int argc, char* argv[]) {
  osquery::initOsquery(argc, argv);

  if (FLAGS_query != "") {
    if (FLAGS_delay != 0) {
      ::sleep(FLAGS_delay);
    }

    for (int i = 0; i < FLAGS_iterations; ++i) {
      int err;
      LOG(INFO) << "Executing: " << FLAGS_query;
      osquery::query(FLAGS_query, err);
      if (err != 0) {
        LOG(ERROR) << "Query failed: " << err;
        return 1;
      }
      LOG(INFO) << "Query succedded";
    }

    if (FLAGS_delay != 0) {
      ::sleep(FLAGS_delay);
    }
  } else {
    LOG(ERROR) << "Usage: run --query=\"<query>\"";
    return 1;
  }

  return 0;
}
