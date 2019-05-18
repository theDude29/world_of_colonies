#ifndef DRIVER
#define DRIVER

#include <irrlicht/irrlicht.h>

class Driver
{
public:
    static irr::video::IVideoDriver* getDriver();

private:
    Driver();
    static irr::video::IVideoDriver* m_instance;
};
#endif // Driver

