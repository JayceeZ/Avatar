#ifndef SENSOR_H
#define SENSOR_H

#include "OpenNI.h"

enum EActiveStream {
    color_stream = 0,
    depth_stream = 1
};

class CSensor {
public:
    openni::Device m_device;

    openni::VideoStream m_colorStream;
    openni::VideoStream m_depthStream;
    EActiveStream active_stream;

public:
    CSensor();
    ~CSensor();

    bool OnInit(bool show_color_stream);
    void setColorDepthSync(bool value);
};

#endif // SENSOR_H
