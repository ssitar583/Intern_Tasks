/**
* If not stated otherwise in this file or this component's LICENSE
* file the following copyright and licenses apply:
*
* Copyright 2019 RDK Management
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
**/

#pragma once

#include "Module.h"

#define EVT_GETNUMBER "ongetnumber"

namespace WPEFramework {
    namespace Plugin {

        class Addition : public PluginHost::IPlugin, public PluginHost::JSONRPC {
        private:

            Addition(const Addition&) = delete;
            Addition& operator=(const Addition&) = delete;

            //Begin methods
            uint32_t gettwonumbers(const JsonObject& parameters, JsonObject& response);
            uint32_t addtwonumbers(const JsonObject& parameters, JsonObject& response);
            //End methods

            //Begin events
            //End events

        public:
            Addition();
            virtual ~Addition();
            virtual const string Initialize(PluginHost::IShell* shell) override { return {}; }
            virtual void Deinitialize(PluginHost::IShell* service) override;
            virtual string Information() const override { return {}; }

            BEGIN_INTERFACE_MAP(Addition)
            INTERFACE_ENTRY(PluginHost::IPlugin)
            INTERFACE_ENTRY(PluginHost::IDispatcher)
            END_INTERFACE_MAP

        public:
            static Addition* _instance;
        private:
            uint32_t num1;
            uint32_t num2;
        };
    } // namespace Plugin
} // namespace WPEFramework
