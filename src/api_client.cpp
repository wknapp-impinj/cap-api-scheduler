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

#include "api_client.h"

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string *)userp)->append((char *)contents, size * nmemb);
    return size * nmemb;
}

namespace scheduler
{
    ApiClient::ApiClient(std::string hostname, std::string username, std::string password) : hostname_(hostname), username_(username), password_(password)
    {
        // std::cout << "API Client Created" << std::endl;
    }

    ApiClient::~ApiClient()
    {
        // std::cout << "API Client Removed" << std::endl;
    }

    CURL *ApiClient::GetCurl(std::string path)
    {
        CURL *curl;

        curl = curl_easy_init();
        if (curl)
        {
            std::string url = hostname_ + "/api/v1/" + path;
            std::string userpwd = username_ + ":" + password_;

            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_USERPWD, userpwd.c_str());

            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
            curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
        }

        return curl;
    }

    scheduler::RestData ApiClient::GetProfiles()
    {
        scheduler::RestData results;

        CURL *curl = GetCurl("/profiles");
        if (curl)
        {
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &(results.readBuffer));

            results.res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
        }

        return results;
    }

    scheduler::RestData ApiClient::GetStatus()
    {
        scheduler::RestData results;

        CURL *curl = GetCurl("/status");
        if (curl)
        {
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &(results.readBuffer));

            results.res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
        }

        return results;
    }

    scheduler::RestData ApiClient::StartPreset(std::string profile, std::string preset)
    {
        scheduler::RestData results;

        CURL *curl = GetCurl("/profiles/" + profile + "/presets/" + preset + "/start");
        if (curl)
        {
            curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");

            struct curl_slist *headers = NULL;
            headers = curl_slist_append(headers, "Accept: application/json");
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

            results.res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
        }

        return results;
    }

    scheduler::RestData ApiClient::StopPreset()
    {
        scheduler::RestData results;

        CURL *curl = GetCurl("/profiles/stop");
        if (curl)
        {
            curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");

            struct curl_slist *headers = NULL;
            headers = curl_slist_append(headers, "Accept: application/json");
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

            results.res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
        }

        return results;
    }

}