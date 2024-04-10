/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2020 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
 
#pragma once

#include "Module.h"
#include <interfaces/IUserInfo.h>

namespace WPEFramework {
namespace Plugin {

    class UserInfo : public PluginHost::IPlugin,public PluginHost::JSONRPC {
    public:
        UserInfo(const UserInfo&) = delete;
        UserInfo& operator=(const UserInfo&) = delete;

        UserInfo()
            : _skipURL(0)
            , _connectionId(0)
            , _service(nullptr)
            , _implementation(nullptr)
        {
             Register("setname", &UserInfo::setnamein, this);
             Register("getname", &UserInfo::getnamein, this);
        }

        ~UserInfo() override
        {

        }
    
        BEGIN_INTERFACE_MAP(UserInfo)
            INTERFACE_ENTRY(PluginHost::IPlugin)
            INTERFACE_ENTRY(PluginHost::IDispatcher)
            INTERFACE_AGGREGATE(Exchange::IUserInfo, _implementation)
        END_INTERFACE_MAP

        //   IPlugin methods
        const string Initialize(PluginHost::IShell* service);
        void Deinitialize(PluginHost::IShell* service);
        string Information() const ;

        uint32_t setnamein(const JsonObject& parameters, JsonObject& response);
        uint32_t getnamein(const JsonObject& parameters, JsonObject& response);
        
    private:
        void Deactivated(RPC::IRemoteConnection* connection);
        uint8_t _skipURL;
        uint32_t _connectionId;
        PluginHost::IShell* _service;
        Exchange::IUserInfo* _implementation;

    };

}  // namespace Plugin
}  // namespace WPEFramework
