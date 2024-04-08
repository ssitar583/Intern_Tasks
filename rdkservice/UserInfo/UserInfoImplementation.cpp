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
 
#include "UserInfoImplementation.h"


namespace WPEFramework {
namespace Plugin {

    std::string UserName;

    SERVICE_REGISTRATION(UserInfoImplementation, 1, 0);

    UserInfoImplementation::~UserInfoImplementation()
    {
        _servicePI->Release();
        _servicePI = nullptr;
    }

    void UserInfoImplementation::Register()
    {
    }

    void UserInfoImplementation::Unregister()
    {
    }


    bool UserInfoImplementation::setname(std::string name)
    {
        UserName = name;
        return true;
    }

    string UserInfoImplementation::getname()
    {
        return UserName;
    }

   

}  // namespace Plugin
}  // namespace WPEFramework
