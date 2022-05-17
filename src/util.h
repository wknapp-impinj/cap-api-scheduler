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

#include <chrono>
#include <cstring>
#include <iostream>
#include <string>

namespace scheduler
{
    namespace util
    {
        template <typename... Args>
        void log(const char *format, Args... args)
        {
            std::string formatAsString = "[%s] ";
            formatAsString += format;
            formatAsString += "\n";

            const time_t currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            std::printf(formatAsString.c_str(), strtok(ctime(&currentTime), "\n"), args...);
        }

    }

}