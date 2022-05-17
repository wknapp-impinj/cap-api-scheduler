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

#include <string>

#include <nlohmann/json.hpp>

namespace scheduler
{

    using json = nlohmann::json;

    class Config
    {
    private:
        json source_;

    public:
        Config(std::string file_path);
        ~Config();

        std::string getUsername();
        std::string getPassword();
        std::string getProfile();
        std::string getPreset();
        int getInterval();
        int getDuration();
    };
}