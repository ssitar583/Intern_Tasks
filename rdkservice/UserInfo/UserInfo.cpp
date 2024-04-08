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
 
#include "UserInfo.h"

#define API_VERSION_NUMBER_MAJOR 1
#define API_VERSION_NUMBER_MINOR 0
#define API_VERSION_NUMBER_PATCH 2

namespace WPEFramework {
    
namespace {

    static Plugin::Metadata<Plugin::UserInfo> metadata(
        // Version (Major, Minor, Patch)
        API_VERSION_NUMBER_MAJOR, API_VERSION_NUMBER_MINOR, API_VERSION_NUMBER_PATCH,
        // Preconditions
        {},
        // Terminations
        {},
        // Controls
        {}
    );
}

namespace Plugin {

    SERVICE_REGISTRATION(UserInfo, API_VERSION_NUMBER_MAJOR, API_VERSION_NUMBER_MINOR, API_VERSION_NUMBER_PATCH);

    const string UserInfo::Initialize(PluginHost::IShell* service) {
        ASSERT (_service == nullptr);
        ASSERT (service != nullptr);

        _service = service;
        _skipURL = static_cast<uint8_t>(service->WebPrefix().length());


         string result;
        _implementation = _service->Root<Exchange::IUserInfo>(_connectionId, 2000, _T("UserInfoImplementation"));
         if (_implementation == nullptr) {
            result = _T("Couldn't create UserInfo instance");

        } 
        return (result);
    }

    void UserInfo::Deinitialize(PluginHost::IShell* service)
    {
        ASSERT(_service == service);

        if (_implementation->Release() != Core::ERROR_DESTRUCTION_SUCCEEDED) {

            ASSERT(_connectionId != 0);

            RPC::IRemoteConnection* connection(_service->RemoteConnection(_connectionId));

            // The process can disappear in the meantime...
            if (connection != nullptr) {

                // But if it did not dissapear in the meantime, forcefully terminate it. Shoot to kill :-)
                connection->Terminate();
                connection->Release();
            }
        }

        _service = nullptr;
        _implementation = nullptr;
    }
        uint32_t UserInfo::setnamein(const JsonObject& parameters, JsonObject& response)
        {
            bool result = true;

            std::string name = parameters["username"].String();

            if (_implementation)
            {
                result = _implementation->setname(name);
            }
 
            if (!result)
            {
                response["message"] = "failed to setname";
            }
            response["message"]="Username has been updated";
            return Core::ERROR_NONE;
        }

          uint32_t UserInfo::getnamein(const JsonObject& parameters, JsonObject& response)
        {
            std::string gname; 

            if (_implementation)
            {
                gname = _implementation->getname();
            }
 
            if (gname.empty())
            {
                response["message"] = "failed to getname";
            }
            response["UserName"]=gname;
            return Core::ERROR_NONE;
        }

        string UserInfo::Information() const
        {
            return (string());
        }


    void UserInfo::Deactivated(RPC::IRemoteConnection* connection)
    {
        if (connection->Id() == _connectionId) {
            ASSERT(_service != nullptr);
            Core::IWorkerPool::Instance().Submit(PluginHost::IShell::Job::Create(_service,
                PluginHost::IShell::DEACTIVATED,
                PluginHost::IShell::FAILURE));
        }
    }
}  // namespace Plugin
}  // namespace WPEFramework
