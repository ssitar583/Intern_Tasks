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

#include <list>
#include <string>



namespace WPEFramework {
namespace Plugin {

    class DemoImplementation : public Exchange::IDemo {
    public:
        DemoImplementation(const DemoImplementation&) = delete;
        DemoImplementation& operator=(const DemoImplementation&) = delete;

        
        public:
            DemoImplementation()
                : _adminLock()
                , _servicePI(nullptr)
            {
            }

            ~DemoImplementation();


        BEGIN_INTERFACE_MAP(DemoImplementation)
            INTERFACE_ENTRY(Exchange::IDemo)
        END_INTERFACE_MAP

        //   IPackager methods
        void Register();
        void Unregister();
        bool setnumber(uint32_t num1,uint32_t num2);
        uint32_t addtwonumbers();
        uint32_t number1,number2;

    private:
        Core::CriticalSection _adminLock;
        PluginHost::IShell* _servicePI;
        
    };

};  // namespace Plugin
}  // namespace WPEFramework
