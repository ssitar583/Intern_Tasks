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
 
#include "DemoImplementation.h"


namespace WPEFramework {
namespace Plugin {

    SERVICE_REGISTRATION(DemoImplementation, 1, 0);

    DemoImplementation::~DemoImplementation()
    {
        _servicePI->Release();
        _servicePI = nullptr;
    }

    void DemoImplementation::Register()
    {
    }

    void DemoImplementation::Unregister()
    {
    }


    bool DemoImplementation::setnumber(uint32_t num1,uint32_t num2)
    {
        // if(num1>0)
        // {
        //     return true;
        // }
        number1 = num1;
        number2 = num2;
        return true;
    }
    uint32_t DemoImplementation::addtwonumbers()
    {
        uint32_t sum = number1 + number2;
        return sum;
    }

   

}  // namespace Plugin
}  // namespace WPEFramework
