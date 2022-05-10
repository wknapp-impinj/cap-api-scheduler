/*****************************************************************************
 *                  IMPINJ CONFIDENTIAL AND PROPRIETARY                      *
 *                                                                           *
 * This source code is the property of Impinj, Inc. Your use of this source  *
 * code in whole or in part is subject to your applicable license terms      *
 * from Impinj.                                                              *
 * Contact support@impinj.com for a copy of the applicable Impinj license    *
 * terms.                                                                    *
 *                                                                           *
 * (c) Copyright 2022 Impinj, Inc. All rights reserved.                      *
 *                                                                           *
 *****************************************************************************/

#include <future>

#include <nlohmann/json.hpp>

#include "api_client.h"
#include "config.h"
#include "util.h"

using json = nlohmann::json;

std::mutex thread_mutex;
bool stop_thread{false};
std::condition_variable batch;

int main(void)
{
  scheduler::Config config("/cust/config.json");
  scheduler::util::log("Application Started (interval=%d, duration=%d)", config.getInterval(), config.getDuration());

  std::chrono::seconds cs_interval{config.getInterval()};
  std::chrono::seconds cs_duration{config.getDuration()};

  scheduler::ApiClient api("https://localhost", config.getUsername(), config.getPassword());

  std::unique_lock<std::mutex> lock(thread_mutex);
  while (!stop_thread)
  {
    scheduler::RestData response;
    batch.wait_for(lock, cs_interval, []()
                   { return stop_thread; });

    scheduler::util::log("Starting profile '%s', preset '%s'", config.getProfile().c_str(), config.getPreset().c_str());
    response = (&api)->StartPreset(config.getProfile(), config.getPreset());
    scheduler::util::log("result code= %d", response.res);

    if (!stop_thread)
    {
      batch.wait_for(lock, cs_duration, []()
                     { return stop_thread; });
    }

    scheduler::util::log("Stopping preset");
    response = (&api)->StopPreset();
    scheduler::util::log("result code= %d", response.res);
  }
}