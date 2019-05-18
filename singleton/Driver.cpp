#include "Device.h"
#include "Driver.h"
#include <iostream>

irr::video::IVideoDriver* Driver::m_instance = NULL;

Driver::Driver()
{
    m_instance = Device::getDevice()->getVideoDriver();
}

irr::video::IVideoDriver* Driver::getDriver()
{
        if(m_instance == NULL)
        {
            Driver();
        }

        return m_instance;
}

