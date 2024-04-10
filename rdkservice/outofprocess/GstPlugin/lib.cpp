#include "lib.h"

void CustomData::setPath(CustomData *data,string path)
{
    gst_init(NULL,NULL);

    data->file = "playbin uri=" + path + "video-sink=westerossink";
    data->pipeline = gst_parse_launch(data->file.c_str(),nullptr);
    gst_element_set_state(data->pipeline,GST_STATE_PLAYING);

}


void CustomData::pause(CustomData *data)
{
    gst_element_set_state(data->pipeline,GST_STATE_PAUSED);
}


void CustomData::exit(CustomData *data)
{   
    gst_element_set_state(data->pipeline,GST_STATE_NULL);
    gst_object_unref (data->pipeline);
}

