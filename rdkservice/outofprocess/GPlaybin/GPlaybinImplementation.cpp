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
 
#include "GPlaybinImplementation.h"

#include <gst/gst.h>
#include <string>
#include <thread>
#include <cstdlib>
#include <iostream>


using namespace std;

int isstarted=0;
// WPEFramework::Plugin::GPlaybinImplementation *gPlaybin;
namespace WPEFramework {
namespace Plugin {

    SERVICE_REGISTRATION(GPlaybinImplementation, 1, 0);
    GPlaybinImplementation* GPlaybinImplementation::instance = nullptr;
    // GPlaybinImplementation *gobj = new GPlaybinImplementation();

    // GPlaybinImplementation* GPlaybinImplementation::playbininstance = NULL;
    GPlaybinImplementation::~GPlaybinImplementation()
    {
        _servicePI->Release();
        _servicePI = nullptr;
    }

    void GPlaybinImplementation::Register()
    {
    }

    void GPlaybinImplementation::Unregister()
    {
    }

     void GPlaybinImplementation::keyPressedCallback(void *userData, unsigned int key){
            std::cout<<"[sound-dbg]-Key Pressed soundaryaa"<<key<<"\n";
            if(!instance)
            {
                std::cout<<"[sound-dbg]-Instance not created";
            }
            if(key==28)
            {
                if(isstarted==0)
                {
                    GPlaybinImplementation::instance->play();
                    std::cout<<"[sound-dbg]-play"<<key;
                    isstarted=1;
                }
                else
                {
                    GPlaybinImplementation::instance->pause();
                    std::cout<<"[sound-dbg]-pause"<<key;
                    isstarted=0;
                }
            }
            else if(key==103)
            {
                GPlaybinImplementation::instance->stop();
                std::cout<<"[sound-dbg]-stop"<<key;
            }
            else if(key==106)
            {
                GPlaybinImplementation::instance->fastforward();
                std::cout<<"[sound-dbg]-fastforward"<<key;
            }
            else if(key==108)
            {
                GPlaybinImplementation::instance->slow();
                std::cout<<"[sound-dbg]-slow"<<key;
            }
            else if(key==105)
            {
                GPlaybinImplementation::instance->reverseplay();
                std::cout<<"[sound-dbg]-reverseplay"<<key;
            }
            // GPlaybinImplementation* instance = static_cast<GPlaybinImplementation*>(userData);

            // // Check if instance is valid
            // if (instance != nullptr) {
            //     // Call the pause method on the instance
            //     if(key==106)
            //     {
            //         instance->pause();
            //         std::cout << "[sound-dbg]-Key Pressed soundaryaa-pause key" << key << "\n";
            //     }
            // }
            // else
            // {
            //     std::cout<<"[sound-dbg]-Instance is null"<<key<<"\n";
            // }
            
            std::cout<<"[sound-dbg]-Key Pressed soundaryaa-exit"<<key<<"\n";
        }

        void GPlaybinImplementation::keyReleasedCallback(void *userData, unsigned int key){
            std::cout<<"[sound-dbg]-Key released soundaryaa"<<key<<"\n";
        }
    void GPlaybinImplementation::Initialize() {
    
        mRenderThread = std::thread([=]() {
        mCtx = EssContextCreate();
        
        keyListener.keyPressed = &GPlaybinImplementation::keyPressedCallback;
        keyListener.keyReleased = &GPlaybinImplementation::keyReleasedCallback;

        if ( !EssContextSetUseWayland( mCtx, mUseWayland ) )
        {
            std::cout<<"[sound-dbg]- set use wayland not set"<<"\n";
        }
        else
        {
             std::cout<<"[sound-dbg]- set use wayland set"<<"\n";
        }
        if(!EssContextSetKeyListener(mCtx, NULL, &keyListener))
        {
            std::cout<<"[sound-dbg]- key listener error"<<"\n";
        }
        else
        {
            std::cout<<"[sound-dbg]-Soundaryaa-Getting into key listener"<<"\n";
        }
       if(!EssContextStart(mCtx))
        {
            std::cout<<"Soundaryaa - Error Getting into Start"<<"\n";
        }
        else
        {
            std::cout<<"Soundaryaa - Getting into Start"<<"\n";
        }

        setenv("WAYLAND_DISPLAY","wst-GPlaybin",1);
                while (true) {
                    if (mCtx)
                    {
                        EssContextUpdateDisplay(mCtx);
                        EssContextRunEventLoopOnce(mCtx);
                    }
                    std::this_thread::sleep_for(std::chrono::milliseconds(30));
                }
            });
        
        // return (Core::ERROR_NONE);
    }

    // GPlaybinImplementation* GPlaybinImplementation::instance()
    // {
    //     if (playbininstance == NULL)
    //     {
    //         playbininstance = new GPlaybinImplementation();
    //     }
    //     return playbininstance;
    // }

    void GPlaybinImplementation::Deinitialize() {
            
            if(active==false)
            mRenderThread.join();
            // return (Core::ERROR_NONE);
    }



    bool GPlaybinImplementation::seturl(string url)
    {
        playbinurl = "playbin uri=" + url; 
        gst_init(NULL,NULL); 
        pipeline = gst_parse_launch(playbinurl.c_str(),nullptr);
        westeros_sink = gst_element_factory_make("westerossink", NULL);
        if (!westeros_sink) {
            g_printerr("Failed to create westerossink element. Exiting.\n");
            return false;
        }
        g_object_set(G_OBJECT(pipeline), "video-sink", westeros_sink, NULL); 
        ret=gst_element_set_state(pipeline, GST_STATE_NULL); 
        if(ret==GST_STATE_CHANGE_FAILURE)
        {
            cout<<"State Change failed";
            return false;
        }
        
        std::cout<<"[sound-dbg]-playbin url set"<<"\n";
        return true;
    }
    bool GPlaybinImplementation::play()
    {
        //pipeline = gst_parse_launch(playbinurl.c_str(),nullptr);
        ret=gst_element_set_state(pipeline, GST_STATE_PLAYING);
        std::cout<<"[sound-dbg]-play API"<<"\n";
        if(ret==GST_STATE_CHANGE_FAILURE)
        {
            return false;
        }
        return true;
    }
    bool GPlaybinImplementation::pause()
    {
        // pipeline = gst_parse_launch(playbinurl.c_str(),nullptr);
        ret=gst_element_set_state(pipeline, GST_STATE_PAUSED);
        std::cout<<"[sound-dbg]-pause API"<<"\n";
        if(ret==GST_STATE_CHANGE_FAILURE)
        {
            return false;
        }
        return true;
    }
    bool GPlaybinImplementation::ready()
    {
        // pipeline = gst_parse_launch(playbinurl.c_str(),nullptr);
        ret=gst_element_set_state(pipeline, GST_STATE_READY);
        std::cout<<"[sound-dbg]-ready API"<<"\n";
        if(ret==GST_STATE_CHANGE_FAILURE)
        {
            return false;
        }
        return true;
    }
    bool GPlaybinImplementation::stop()
    {
        // pipeline = gst_parse_launch(playbinurl.c_str(),nullptr);

        ret=gst_element_set_state(pipeline, GST_STATE_NULL);
        std::cout<<"[sound-dbg]-stop API"<<"\n";
        if(ret==GST_STATE_CHANGE_FAILURE)
        {
            return false;
        }
        return true;
    }
    bool GPlaybinImplementation::fastforward()
    {
        std::cout<<"[sound-dbg]-fastforward API"<<"\n";
        playback_speed*=2.0;
        send_seek_event();
        return true;
    }
      bool GPlaybinImplementation::slow()
    {
        std::cout<<"[sound-dbg]-slow API"<<"\n";
        playback_speed/=2.0;
        send_seek_event();
        return true;
    }
      bool GPlaybinImplementation::reverseplay()
    {
        std::cout<<"[sound-dbg]-reverseplay API"<<"\n";
        if(playback_speed>0)
        playback_speed*=-2.0;
        else
        playback_speed*=2.0;
        send_seek_event();
        return true;
    }

    void GPlaybinImplementation::send_seek_event ()
    {

        std::cout<<"[sound-dbg]-Entering into send_seek_event"<<"\n";
        // GPlaybinImplementation *gobj = this;
        gint64 position;

        GstEvent *seek_event;

        if (!gst_element_query_position (/*gobj->*/pipeline, GST_FORMAT_TIME, &position)) {

            g_printerr ("Unable to retrieve current position.\n");

            return;

        }
        else
        {
            std::cout<<"[sound-dbg]-Entering into query_position"<<"\n";
        }

        GstSeekFlags flags = static_cast<GstSeekFlags>(GST_SEEK_FLAG_FLUSH | GST_SEEK_FLAG_ACCURATE);

        if (playback_speed > 0) {

            std::cout<<"[sound-dbg]-Entering into forward speed"<<"\n";
            
            seek_event =

                gst_event_new_seek (playback_speed, GST_FORMAT_TIME,

               flags, GST_SEEK_TYPE_SET,

                position, GST_SEEK_TYPE_END, 0);

        } else {

            std::cout<<"[sound-dbg]-Entering into reverse speed"<<"\n";
            seek_event = gst_event_new_seek (playback_speed, GST_FORMAT_TIME,flags, GST_SEEK_TYPE_SET, 0,GST_SEEK_TYPE_SET, position);

        }



        if (/*gobj->*/westeros_sink == NULL) {
            std::cout<<"[sound-dbg]-westeros-sink in GPlaybinImpl";
            g_object_get (pipeline, "video-sink", &westeros_sink, NULL);
        }



        gst_element_send_event(westeros_sink, seek_event);

        g_print ("Current rate: %g\n", playback_speed);

    }
    bool GPlaybinImplementation::playbackspeed(string input)
    {
        //pipeline = gst_parse_launch(playbinurl.c_str(),nullptr);
        // ret=gst_element_set_state(pipeline, GST_STATE_PLAYING);
       
        std::cout<<"[sound-dbg]-TESTPLAYBACKSPEED"<<"\n";

        std::cout<<"[sound-dbg]-Input"<<input<<"\n";
        size_t colon_pos = input.find(':');
        std::cout<<"[sound-dbg]-Colon position"<<colon_pos<<"\n";
        std::string number_str = input.substr(colon_pos + 1);
        std::cout<<"[sound-dbg]-String number_str"<<number_str<<"\n";
        double speed = std::atof(number_str.c_str());
        std::cout<<"[sound-dbg]-Speed"<<speed<<"\n";
        if (g_ascii_isupper (input[0])) {

			playback_speed *= speed;

	    } else {

			playback_speed  /= speed;

	    }
        std::cout<<"[sound-dbg]-playbackspeed"<<playback_speed<<"\n";
	    send_seek_event();

        return true;
    }

   

}  // namespace Plugin
}  // namespace WPEFramework
