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

#include "Addition.h"
#include "UtilsJsonRpc.h"

#include <glib.h>
#include <glib/gstdio.h>

#define API_VERSION_NUMBER_MAJOR 1
#define API_VERSION_NUMBER_MINOR 0
#define API_VERSION_NUMBER_PATCH 0

using namespace std;

namespace WPEFramework {

    namespace {

        static Plugin::Metadata<Plugin::Addition> metadata(
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

        SERVICE_REGISTRATION(Addition, API_VERSION_NUMBER_MAJOR, API_VERSION_NUMBER_MINOR, API_VERSION_NUMBER_PATCH);

        Addition* Addition::_instance = nullptr;

        Addition::Addition()
                : PluginHost::JSONRPC(), num1(0), num2(0)
        {
            LOGINFO("ctor");
            Addition::_instance = this;
            Register("gettwonumbers", &Addition::gettwonumbers, this);
            Register("addtwonumbers", &Addition::addtwonumbers, this);
        }

        Addition::~Addition()
        {
            //LOGINFO("dtor");
        }
        void Addition::Deinitialize(PluginHost::IShell* /* service */)
        {
            LOGINFO("Deinitialize");
            Addition::_instance = nullptr;
        }

        //Begin methods
        uint32_t Addition::gettwonumbers(const JsonObject& parameters, JsonObject& response)
        {
            LOGINFOMETHOD();

            // Assuming parameters contain the two numbers as strings
            std::string num1_str = parameters["num1"].String();
            std::string num2_str = parameters["num2"].String();

            // Convert the strings to integers
            try {
                num1 = std::stoi(num1_str);
                num2 = std::stoi(num2_str);
            } catch (...) {
                LOGERR("Error converting strings to numbers");
                returnResponse(false);
            }

            // Store the numbers in the response JsonObject
            response["num1"] = num1;
            response["num2"] = num2;
            JsonObject params;
            params["number1"]=num1;
            // LOGINFO("Get two numbers method called");

            sendNotify("ongetnumber",params);
            returnResponse(true);
        }

        // Function to calculate the sum of two numbers
        uint32_t Addition::addtwonumbers(const JsonObject& parameters, JsonObject& response)
        {
           LOGINFOMETHOD();

            // Calculate the sum using the numbers stored in the object's state
            uint32_t sum = num1 + num2;

            // Store the sum in the response JsonObject
            response["sum"] = sum;

            returnResponse(true);
        }
                //End methods

        //Begin events
        //End events

    } // namespace Plugin
} // namespace WPEFramework
