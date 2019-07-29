#include <QResizeEvent>
#include "jeu/irrlichtwidget.h"
#include "jeu/decor.h"
#include "singleton/Device.h"

using namespace irr;

IrrlichtWidget::IrrlichtWidget(QWidget *parent) : QWidget(parent)
{
    //setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_PaintOnScreen);
    setVisible(false);

    SIrrlichtCreationParameters createParams;
    createParams.WindowId = reinterpret_cast<void*>(parent->winId());
    createParams.DriverType = video::EDT_OPENGL;
    createParams.AntiAlias = true;
    createParams.Bits = 16;
    createParams.HighPrecisionFPU = false;
    createParams.Stencilbuffer = true;
    createParams.Vsync = true;

    m_device = createDeviceEx(createParams);
    Device::setDevice(m_device);
    m_driver = m_device->getVideoDriver();
    m_sceneManager = m_device->getSceneManager();

    //
    m_camera = new CameraSTR(parent);
}

void IrrlichtWidget::drawScene()
{
    m_driver->beginScene();
    m_sceneManager->drawAll();
    m_camera->maj();
    m_driver->endScene();
}

bool IrrlichtWidget::eventFilter(QObject* obj, QEvent *event)
{
    if(event->type() == QEvent::Resize)
    {
        QResizeEvent* resizeEvent = (QResizeEvent*)event;
        core::dimension2du tailleWidget = core::dimension2du(resizeEvent->size().width(), resizeEvent->size().height());
        if(tailleWidget.Width > 800)
        {
            m_driver->OnResize(tailleWidget);
        }
    }

    return QObject::eventFilter(obj, event);
}

const CameraSTR* IrrlichtWidget::getCamera()
{
    return m_camera;
}

IrrlichtWidget::~IrrlichtWidget()
{
    delete m_device->getTimer();
    delete m_camera;
    delete m_device;
}



