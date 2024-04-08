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
#include <interfaces/IDemo.h>

namespace WPEFramework {
namespace Plugin {

    class Demo : public PluginHost::IPlugin,public PluginHost::JSONRPC {
    public:
        Demo(const Demo&) = delete;
        Demo& operator=(const Demo&) = delete;

        Demo()
            : _skipURL(0)
            , _connectionId(0)
            , _service(nullptr)
            , _implementation(nullptr)
        {
             Register("setnumber", &Demo::setnumberin, this);
             Register("addtwonumbers", &Demo::addtwonumbersin, this);
        }

        ~Demo() override
        {

        }
    
        BEGIN_INTERFACE_MAP(Demo)
            INTERFACE_ENTRY(PluginHost::IPlugin)
            INTERFACE_ENTRY(PluginHost::IDispatcher)
            INTERFACE_AGGREGATE(Exchange::IDemo, _implementation)
        END_INTERFACE_MAP

        //   IPlugin methods
        const string Initialize(PluginHost::IShell* service);
        void Deinitialize(PluginHost::IShell* service);
        string Information() const ;

        uint32_t setnumberin(const JsonObject& parameters, JsonObject& response);
        uint32_t addtwonumbersin(const JsonObject& parameters, JsonObject& response);
        
    private:
        void Deactivated(RPC::IRemoteConnection* connection);
        uint8_t _skipURL;
        uint32_t _connectionId;
        PluginHost::IShell* _service;
        Exchange::IDemo* _implementation;

    };

}  // namespace Plugin
}  // namespace WPEFramework
