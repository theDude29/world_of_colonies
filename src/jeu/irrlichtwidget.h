#ifndef IRRLICHTWIDGET_H
#define IRRLICHTWIDGET_H

#include <irrlicht/irrlicht.h>
#include <QWidget>
#include "Camera.h"

class IrrlichtWidget : public QWidget
{
    Q_OBJECT

public:
    explicit IrrlichtWidget(QWidget* parent = 0);
    ~IrrlichtWidget();
    void drawScene();
    virtual bool eventFilter(QObject* obj, QEvent *event);

    const CameraSTR* getCamera();

protected:
    //partie importante de irrlicht
    irr::IrrlichtDevice* m_device;
    irr::scene::ISceneManager* m_sceneManager;
    irr::video::IVideoDriver* m_driver;

    CameraSTR* m_camera;
};

#endif // IRRLICHTWIDGET_H
