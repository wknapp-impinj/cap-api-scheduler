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

#include "config.h"

#include <fstream>
#include <string>

#include <nlohmann/json.hpp>

namespace scheduler
{

    using json = nlohmann::json;

    Config::Config(std::string file_path)
    {
        std::ifstream source_ifs(file_path);
        source_ = json::parse(source_ifs);
    }

    Config::~Config() {}

    std::string Config::getUsername()
    {
        return source_.at("username").get<std::string>();
    }

    std::string Config::getPassword()
    {
        return source_.at("password").get<std::string>();
    }

    std::string Config::getProfile()
    {
        return source_.at("profile").get<std::string>();
    }

    std::string Config::getPreset()
    {
        return source_.at("preset").get<std::string>();
    }

    int Config::getInterval()
    {
        return source_.at("interval").get<int>();
    }

    int Config::getDuration()
    {
        return source_.at("duration").get<int>();
    }

}