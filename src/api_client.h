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

#pragma once

#include <iostream>
#include <string>

#include <curl/curl.h>
#include <nlohmann/json.hpp>

namespace scheduler
{
    struct RestData
    {
        CURLcode res;
        std::string readBuffer;
    };

    class ApiClient
    {
    private:
        std::string hostname_;
        std::string username_;
        std::string password_;

        CURL *GetCurl(std::string path);

    public:
        ApiClient(std::string hostname, std::string username, std::string password);
        ~ApiClient();

        scheduler::RestData GetProfiles();
        scheduler::RestData GetStatus();
        scheduler::RestData StartPreset(std::string profile, std::string preset);
        scheduler::RestData StopPreset();
    };
}