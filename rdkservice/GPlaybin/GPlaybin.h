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
#include <interfaces/IGPlaybin.h>
// #include "essos.h"

namespace WPEFramework {
namespace Plugin {

    class GPlaybin : public PluginHost::IPlugin,public PluginHost::JSONRPC {
    public:
        GPlaybin(const GPlaybin&) = delete;
        GPlaybin& operator=(const GPlaybin&) = delete;

        GPlaybin()
            : _skipURL(0)
            , _connectionId(0)
            , _service(nullptr)
            , _implementation(nullptr) 
        {
             Register("seturl", &GPlaybin::seturlin, this);
             Register("play", &GPlaybin::playin, this);
             Register("pause", &GPlaybin::pausein, this);
             Register("ready", &GPlaybin::readyin, this);
             Register("stop", &GPlaybin::stopin, this);
             Register("playbackspeed", &GPlaybin::playbackspeedin, this);

        }

        ~GPlaybin() override
        {
            //  if (mCtx)
            // {
            //     EssContextDestroy(mCtx);
            // }
            // mCtx = NULL;
        }
    
        BEGIN_INTERFACE_MAP(GPlaybin)
            INTERFACE_ENTRY(PluginHost::IPlugin)
            INTERFACE_ENTRY(PluginHost::IDispatcher)
            INTERFACE_AGGREGATE(Exchange::IGPlaybin, _implementation)
        END_INTERFACE_MAP

        //   IPlugin methods
        const string Initialize(PluginHost::IShell* service);
        void Deinitialize(PluginHost::IShell* service);
        string Information() const ;



        // void handle_key_event(EssosInputContext* context, uint32_t key, uint32_t state, uint32_t time);
        uint32_t seturlin(const JsonObject& parameters, JsonObject& response);
        uint32_t playin(const JsonObject& parameters, JsonObject& response);
        uint32_t pausein(const JsonObject& parameters, JsonObject& response);
        uint32_t readyin(const JsonObject& parameters, JsonObject& response);
         uint32_t stopin(const JsonObject& parameters, JsonObject& response);
        uint32_t playbackspeedin(const JsonObject& parameters, JsonObject& response);
         uint32_t fastforwardin(const JsonObject& parameters, JsonObject& response);
          uint32_t slowin(const JsonObject& parameters, JsonObject& response);
           uint32_t reverseplayin(const JsonObject& parameters, JsonObject& response);
        // static void keyPressedCallback(void *userData, unsigned int key);
        // static void keyReleasedCallback(void *userData, unsigned int key);
        // EssCtx* mCtx; 
        // EssKeyListener keyListener;
        
    private:
        void Deactivated(RPC::IRemoteConnection* connection);
        uint8_t _skipURL;
        uint32_t _connectionId;
        PluginHost::IShell* _service;
        Exchange::IGPlaybin* _implementation;

    };

}  // namespace Plugin
}  // namespace WPEFramework
