#include "Device.h"
#include <iostream>

irr::IrrlichtDevice* Device::m_instance = NULL;

Device::Device(int WID)
{
    irr::SIrrlichtCreationParameters param = irr::SIrrlichtCreationParameters();
    param.DriverType = irr::video::EDT_OPENGL;
    param.WindowId = (void*)WID;
    m_instance = irr::createDeviceEx(param);
}

void Device::setDevice(irr::IrrlichtDevice *device)
{
    if(m_instance == NULL)
    {
        m_instance = device;
    }
}

irr::IrrlichtDevice* Device::getDevice()
{
        return m_instance;
}
