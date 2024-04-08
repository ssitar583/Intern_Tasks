#include<iostream>
#include<gst/gst.h>
#include<string>

using namespace std;

class CustomData{
    public:
    string file;
    GstElement* pipeline = nullptr;

    public:
    void setPath(CustomData *data,string file);
    void pause(CustomData *data);
    void exit(CustomData *data); 
};
