#ifndef DEVICE
#define DEVICE

#include <irrlicht/irrlicht.h>

class Device
{
public:
    static irr::IrrlichtDevice* getDevice();
    static void setDevice(irr::IrrlichtDevice* device);

private:
    Device(int WID);
    static irr::IrrlichtDevice* m_instance;
};
#endif // DEVICE
