/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2020 Metrological
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

namespace WPEFramework {
namespace Exchange {

    struct EXTERNAL IGPlaybin : virtual public Core::IUnknown {
        enum { ID = ID_GPLAYBIN };
        
        virtual void Register() = 0;
        virtual void Unregister() = 0;
        virtual void Initialize() = 0;
        virtual void Deinitialize() = 0;
        virtual bool seturl(string url) = 0;
        virtual bool play() = 0;
        virtual bool pause() = 0;
        virtual bool ready() = 0;
        virtual bool stop() = 0;
        virtual bool fastforward() = 0;
        // virtual bool slow() = 0;
        // virtual bool reverseplay() = 0;
        virtual bool playbackspeed(string input)=0;
        static void keyPressedCallback(void *userData, unsigned int key);
        static void keyReleasedCallback(void *userData, unsigned int key);
    };
}
}
