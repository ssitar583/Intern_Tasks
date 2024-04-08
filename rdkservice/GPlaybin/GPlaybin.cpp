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

#include "GPlaybin.h"
#include "UtilsJsonRpc.h"

#include <glib.h>
#include <glib/gstdio.h>

#define API_VERSION_NUMBER_MAJOR 1
#define API_VERSION_NUMBER_MINOR 0
#define API_VERSION_NUMBER_PATCH 0

using namespace std;

namespace WPEFramework {

    namespace {

        static Plugin::Metadata<Plugin::GPlaybin> metadata(
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

        SERVICE_REGISTRATION(GPlaybin, API_VERSION_NUMBER_MAJOR, API_VERSION_NUMBER_MINOR, API_VERSION_NUMBER_PATCH);

        // void GPlaybin::keyPressedCallback(void *userData, unsigned int key){
        //     std::cout<<"[sound-dbg]-Key Pressed soundaryaa"<<key;
        // }

        // void GPlaybin::keyReleasedCallback(void *userData, unsigned int key){
        //     std::cout<<"[sound-dbg]-Key released soundaryaa"<<key;
        // }
        
		const string GPlaybin::Initialize(PluginHost::IShell* service) {
        ASSERT (_service == nullptr);
        ASSERT (service != nullptr);
        // mCtx = EssContextCreate();
        
        // keyListener.keyPressed = &GPlaybin::keyPressedCallback;
        // keyListener.keyReleased = &GPlaybin::keyReleasedCallback;

        // if(!EssContextStart(mCtx))
        // {
        //     std::cout<<"Soundaryaa - Error Getting into Start";
        // }
        // else
        // {
        //     std::cout<<"Soundaryaa - Getting into Start";
        // }
        // if(!EssContextSetKeyListener(mCtx, NULL, &keyListener))
        // {
        //     std::cout<<"[sound-dbg]- key listener error";
        // }
        // else
        // {
        //     std::cout<<"[sound-dbg]-Soundaryaa-Getting into key listener";
        // }
        // EssContextStart(mCtx);

        // setenv("WAYLAND_DISPLAY","wst-GPlaybin",1);

        _service = service;
        _skipURL = static_cast<uint8_t>(service->WebPrefix().length());


         string result;
        _implementation = _service->Root<Exchange::IGPlaybin>(_connectionId, 2000, _T("GPlaybinImplementation"));
         if (_implementation == nullptr) {
            result = _T("Couldn't create GPlaybin instance");

        } 
        _implementation->Initialize();
        return (result);
    }

    void GPlaybin::Deinitialize(PluginHost::IShell* service)
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
        _implementation->Deinitialize();
        _service = nullptr;
        _implementation = nullptr;
    }
        uint32_t GPlaybin::seturlin(const JsonObject& parameters, JsonObject& response)
        {
            bool result = true;

            std::string playbinurl = parameters["playbinurl"].String();

            if (_implementation)
            {
                result = _implementation->seturl(playbinurl);
            }
 
            if (!result)
            {
                response["message"] = "failed to set playbinurl";
            }
            response["message"]="Playbin url set";
            return Core::ERROR_NONE;
        }
		uint32_t GPlaybin::playin(const JsonObject& parameters, JsonObject& response)
		{
		    bool result = true;
			result = _implementation->play();
			if(!result)
			{
				response["message"] = "failed to set playbin to playing state";
			}
			response["playstate"]="playing";
            response["message"]="Video is playing using playbin";
			return Core::ERROR_NONE;
		}
        uint32_t GPlaybin::pausein(const JsonObject& parameters, JsonObject& response)
		{
		    bool result = true;
			result = _implementation->pause();
			if(!result)
			{
				response["message"] = "failed to set playbin to pause state";
			}
			response["playstate"]="paused";
            response["message"]="Video is paused";
			return Core::ERROR_NONE;
		}
        uint32_t GPlaybin::readyin(const JsonObject& parameters, JsonObject& response)
		{
		    bool result = true;
			result = _implementation->ready();
			if(!result)
			{
				response["message"] = "failed to set playbin to ready state";
			}
			response["playstate"]="Ready";
            response["message"]="Video is in ready state";
			return Core::ERROR_NONE;
		}
        uint32_t GPlaybin::stopin(const JsonObject& parameters, JsonObject& response)
		{
		    bool result = true;
			result = _implementation->stop();
			if(!result)
			{
				response["message"] = "failed to set playbin to null state";
			}
			response["playstate"]="NULL";
            response["message"]="Video is NULL State";
			return Core::ERROR_NONE;
		}
		uint32_t GPlaybin::playbackspeedin(const JsonObject& parameters, JsonObject& response)
		{
		    bool result = true;
            std::string playback_speed = parameters["speed"].String();
			result = _implementation->playbackspeed(playback_speed);
			if(!result)
			{
				response["message"] = "failed to set playbackspeed";
			}
            response["message"]="Playback speed set";
			return Core::ERROR_NONE;
		}

        uint32_t GPlaybin::fastforwardin(const JsonObject& parameters, JsonObject& response)
		{
		    bool result = true;
			result = _implementation->fastforward();
			if(!result)
			{
				response["message"] = "failed to set playback to fastforward";
			}
            response["message"]="Fastforward succeded";
			return Core::ERROR_NONE;
		}
         uint32_t GPlaybin::slowin(const JsonObject& parameters, JsonObject& response)
		{
		    bool result = true;
			result = _implementation->slow();
			if(!result)
			{
				response["message"] = "failed to set playback to slow";
			}
            response["message"]="slow forward succeded";
			return Core::ERROR_NONE;
		}
         uint32_t GPlaybin::reverseplayin(const JsonObject& parameters, JsonObject& response)
		{
		    bool result = true;
			result = _implementation->reverseplay();
			if(!result)
			{
				response["message"] = "failed to set playback to reverseplay";
			}
            response["message"]="reverseplay succeded";
			return Core::ERROR_NONE;
		}

        string GPlaybin::Information() const
        {
            return (string());
        }


    void GPlaybin::Deactivated(RPC::IRemoteConnection* connection)
    {
        if (connection->Id() == _connectionId) {
            ASSERT(_service != nullptr);
            Core::IWorkerPool::Instance().Submit(PluginHost::IShell::Job::Create(_service,
                PluginHost::IShell::DEACTIVATED,
                PluginHost::IShell::FAILURE));
        }
    
    }
	
	}
}
