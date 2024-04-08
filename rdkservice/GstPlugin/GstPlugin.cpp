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

#include "GstPlugin.h"
#include <string>
#include <iostream>
#include <plugins/System.h>

using namespace std;

namespace WPEFramework
{    
    namespace Plugin 
    {
    	SERVICE_REGISTRATION(GstPlugin,1,0);
    	
        GstPlugin::GstPlugin(): PluginHost::JSONRPC()
        {

            Register<JsonObject, JsonObject>(_T("test"),&GstPlugin::test,this);
            Register<JsonObject, JsonObject>(_T("setfile"),&GstPlugin::setfile,this);
            Register<JsonObject, JsonObject>(_T("pause"),&GstPlugin::pause,this);
            Register<JsonObject, JsonObject>(_T("exit"),&GstPlugin::exit,this);

        }

        GstPlugin::~GstPlugin()
        {
        }

        const string GstPlugin::Initialize(PluginHost::IShell* service )
        {
            cout<< "Initializing \n" ;
            cout<<" ------------- GstPlugin ---------------- \n";
            //shared pointer initialized
            //initialize external library
            return (string());
        }

        void GstPlugin::Deinitialize(PluginHost::IShell* service )
        {
            std::cout<< "Deinitializing \n" ;
            //shared pointer deinitialized
            //deinitialize external library 
        }


        /* virtual */ string GstPlugin::Information() const
        {
            return ((_T("The purpose of this plugin is provide ability to execute functional tests.\n")));
        }


        uint32_t GstPlugin::test(const JsonObject& request, JsonObject& response) 
        {
            uint32_t result= Core::ERROR_NONE;
            response["test"] = "Test Response";
            return result; 
        }


        uint32_t  GstPlugin::setfile( const JsonObject& request, JsonObject& response)
        {
            uint32_t result= Core::ERROR_NONE;
            string name = request["url"].String();
            data->setPath(data,name);
            response["message"] = "File path has been setted and video is playing"; 
            return result;
        }

        
        uint32_t GstPlugin::pause(const JsonObject& request, JsonObject& response) 
        {
            uint32_t result= Core::ERROR_NONE;
            data->pause(data);
            response["message"] = "video pause";
            return result;  
        }

        uint32_t GstPlugin::exit(const JsonObject& request, JsonObject& response) 
        {
            uint32_t result= Core::ERROR_NONE;
            data->exit(data);
            response["message"] = "player exit";
            return result;  
        }

    }  // namespace plugin  
}  // namespace framework