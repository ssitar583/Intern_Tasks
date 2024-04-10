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
#include <gst/gst.h>
#include "essos.h"
#include <list>
#include <string>
#include<thread>



namespace WPEFramework {
namespace Plugin {

    class GPlaybinImplementation : public Exchange::IGPlaybin {
    public:
        GPlaybinImplementation(const GPlaybinImplementation&) = delete;
        GPlaybinImplementation& operator=(const GPlaybinImplementation&) = delete;

        
        static GPlaybinImplementation *instance;
        public:
            GPlaybinImplementation()
                : _adminLock()
                , _servicePI(nullptr)
                , mUseWayland(false)
            {
                instance = this;
            }

            ~GPlaybinImplementation();


        BEGIN_INTERFACE_MAP(GPlaybinImplementation)
            INTERFACE_ENTRY(Exchange::IGPlaybin)
        END_INTERFACE_MAP


        // static GPlaybinImplementation* instance();
        void Register();
        void Unregister();
        bool seturl(string url);
        bool play();
        bool pause();
        bool ready();
        bool stop();
        bool fastforward();
        bool slow();
        bool reverseplay();
        bool playbackspeed(string input);
        void send_seek_event();
        string playbinurl;
        GstElement *pipeline;
        GstElement *westeros_sink;
        GstStateChangeReturn ret;
        gdouble playback_speed=1.0;
        std::thread mRenderThread;
        bool active = false;
        

        static void keyPressedCallback(void *userData, unsigned int key);
        static void keyReleasedCallback(void *userData, unsigned int key);
        EssCtx* mCtx; 
        EssKeyListener keyListener;

        virtual void Initialize();
        virtual void Deinitialize();

    private:
        // static GPlaybinImplementation* playbininstance;
        Core::CriticalSection _adminLock;
        PluginHost::IShell* _servicePI;
        bool mUseWayland;
    };

};  // namespace Plugin
}  // namespace WPEFramework
