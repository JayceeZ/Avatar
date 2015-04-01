#include "sensor.h"
#include <iostream>

CSensor::CSensor() {
}

CSensor::~CSensor() {
    m_colorStream.stop();
    m_colorStream.destroy();

    m_depthStream.stop();
    m_depthStream.destroy();

    openni::OpenNI::shutdown();
}

bool CSensor::OnInit(bool show_color_stream) {
    openni::OpenNI::initialize();

    if(m_device.open(openni::ANY_DEVICE) != openni::STATUS_OK) {
        std::cout << openni::OpenNI::getExtendedError();
        return false;
    }

    if(m_colorStream.create(m_device, openni::SENSOR_COLOR) == openni::STATUS_OK) {
        m_colorStream.start();
    } else {
        std::cout << openni::OpenNI::getExtendedError();
        return false;
    }

    if(m_depthStream.create(m_device, openni::SENSOR_DEPTH) == openni::STATUS_OK) {
        m_depthStream.start();
    } else {
        std::cout << openni::OpenNI::getExtendedError();
        return false;
    }

    if(m_colorStream.isValid() && m_depthStream.isValid()) {
        if(show_color_stream)
            active_stream = color_stream;
        else
            active_stream = depth_stream;
    } else {
        return false;
    }

    if(m_device.isImageRegistrationModeSupported(openni::IMAGE_REGISTRATION_DEPTH_TO_COLOR)) {
        m_device.setImageRegistrationMode(openni::IMAGE_REGISTRATION_DEPTH_TO_COLOR);
    }
    // à mettre si on veut synchroniser les images couleur et de profondeur
    //m_device.setDepthColorSyncEnabled(true);

    return true;
}
