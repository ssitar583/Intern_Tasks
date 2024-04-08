#include<gst/gst.h>
typedef struct CustomData{
	//declare the variables of elements
	GstElement *pipeline;
	GstElement *source;
	GstElement *demux;
	GstElement *queue_video;
	//GstElement *h264parse;
	GstElement *avdec_h264;
	GstElement *autovideosink;
	GstElement *queue_audio;
	//GstElement *aacparse;
	GstElement *faad;
	GstElement *autoaudiosink;
} CustomData;


static void pad_handler(GstElement *src,GstPad *new_pad,CustomData *data);
int main(int argc,char *argv[]){
CustomData data;
GstBus *bus;
GstMessage *msg;
GstStateChangeReturn ret;
gboolean terminate=FALSE;

//Initialize Gstreamer
gst_init(&argc,&argv);

//initializing the elements
data.source=gst_element_factory_make("filesrc","file-source");
data.demux=gst_element_factory_make("qtdemux","demux");
data.queue_video=gst_element_factory_make("queue","queue-video");
//data.h264parse=gst_element_factory_make("h264parse","h264-parser");
data.avdec_h264=gst_element_factory_make("avdec_h264","h264-decoder");
data.autovideosink=gst_element_factory_make("autovideosink","video-sink");
data.queue_audio=gst_element_factory_make("queue","queue_audio");
//data.aacparse=gst_element_factory_make("aacparse","aac-parser");
data.faad=gst_element_factory_make("faad","faad-decoder");
data.autoaudiosink=gst_element_factory_make("autoaudiosink","audio-sink");


data.pipeline=gst_pipeline_new("video-pipeline");

if(!data.pipeline || !data.source ||!data.demux||
   !data.queue_video/*||!data.h264parse */|| !data.avdec_h264 || !data.autovideosink ||
   !data.queue_audio/*||!data.aacparse*/ || !data.faad ||!data.autoaudiosink){
	g_printerr("Some elements are not created");
    return 1;
}

//pipeline build
gst_bin_add_many(GST_BIN(data.pipeline),data.source,data.demux,data.queue_video,/*data.h264parse,*/data.avdec_h264,data.autovideosink,
	data.queue_audio,/*data.aacparse,*/data.faad,data.autoaudiosink,NULL);

//file src
g_object_set(data.source,"location","/home/soundaryaa/Documents/Gstreamer/Tom.mp4",NULL);

//Connect to pad_handler
g_signal_connect(data.demux,"pad-added",G_CALLBACK(pad_handler),&data);

//Linking the elements
if(!gst_element_link(data.source,data.demux)){
	g_printerr("source and demux not linked.\\n");
	gst_object_unref(data.pipeline);
	return 1;
}

if(!gst_element_link_many(data.queue_video/*,data.h264parse*/,data.avdec_h264,data.autovideosink,NULL)||
	!gst_element_link_many(data.queue_audio/*,data.aacparse*/,data.faad,data.autoaudiosink,NULL)){
	g_printerr("video or audio elements could not be linked.\\n");
    gst_object_unref(data.pipeline);
    return 1;
}


ret=gst_element_set_state(data.pipeline,GST_STATE_PLAYING);
if(ret == GST_STATE_CHANGE_FAILURE){
	g_printerr("Unable to set pipeline to playing state");
	return 1;
}



bus =gst_element_get_bus(data.pipeline);

do{
    msg = gst_bus_timed_pop_filtered(bus,GST_CLOCK_TIME_NONE, GST_MESSAGE_ERROR | GST_MESSAGE_EOS);

    if(msg!=NULL){
    	GError *err;
    	gchar *debug_info;

    	switch(GST_MESSAGE_TYPE(msg)){
	    	case GST_MESSAGE_ERROR:
	    		gst_message_parse_error(msg,&err,&debug_info);
	    		g_printerr("Error received from element %s :%s\\n",GST_OBJECT_NAME(msg->src),err->message);
	    		g_printerr("Debugging information :%s\\n",debug_info?debug_info:"none");
	    		g_clear_error(&err);
	    		g_free(debug_info);
	    		terminate=TRUE;
	    		break;
	    	case GST_MESSAGE_EOS:
	    		g_print("End of stream\\n");
	    		terminate =TRUE;
	    		break;
    	}
    gst_message_unref(msg);
    }

} while(!terminate);

gst_object_unref(bus);
gst_object_unref(data.pipeline);
return 0;
}
static void pad_handler(GstElement *src,GstPad *new_pad,CustomData *data){
gchar *new_pad_type=NULL;
GstPad *sink_pad=NULL;

g_print("Received new pad '%s' from '%s' :\\n",GST_PAD_NAME(new_pad),GST_ELEMENT_NAME(src));


GstCaps *new_pad_caps=gst_pad_get_current_caps(new_pad);
GstStructure *new_pad_struct=gst_caps_get_structure(new_pad_caps,0);
new_pad_type=g_strdup(gst_structure_get_name(new_pad_struct));

g_print("caps:%s \n",gst_caps_to_string(new_pad_caps));
g_print("Structure:%s \n",gst_structure_to_string(new_pad_struct));
g_print("Pad:%s\n",new_pad_type);



if(g_str_has_prefix(new_pad_type,"video/"))
	sink_pad=gst_element_get_static_pad(data->queue_video,"sink");

else if(g_str_has_prefix(new_pad_type,"audio/"))
	sink_pad=gst_element_get_static_pad(data->queue_audio,"sink");



GstPadLinkReturn ret=gst_pad_link(new_pad,sink_pad);
if(GST_PAD_LINK_FAILED(ret))
	g_print("Link failed");
else
	g_print("Link succeeded '%s'\\n",new_pad_type);

g_free(new_pad_type);
gst_caps_unref(new_pad_caps);
gst_object_unref(sink_pad);
}
