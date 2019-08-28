#include "Camera.h"
#include "../singleton/Device.h"
#include <QApplication>
#include <QWheelEvent>
#include <QMouseEvent>
#include "../mainwindow.h"

using namespace irr;

CameraSTR::CameraSTR(QObject *mainWindow) : QObject(mainWindow)
{
    m_camera = SceneManager::getSceneManager()->addCameraSceneNode(NULL, core::vector3df(0,600,-700));
    m_tarCamera = core::vector3df(0,0,0);
    m_camera->setTarget(m_tarCamera);

    m_pause = false;
    m_limite = core::dimension2d<s32>(300, 300);
    m_cliqueMilieuEnfonce = false;
    m_wheel = 0;
    m_vitesseWheel = 20;
    m_vitesse = 2.5;
    m_distanceMin = 100;
    m_distanceMax = 1000;
    m_hauteurCamera = 500;
    m_directionCamera_normalize = core::vector3df(0, 1, -1);

    mainWindow->installEventFilter(this);
}

void CameraSTR::majBoutonsCollecte()
{
    if(MainWindow::getMainWindow()->getVillage() != NULL)
    {
        std::vector<Travailleur*> listeTravailleur = MainWindow::getMainWindow()->getVillage()->getListeTravailleur();

        for(std::vector<Travailleur*>::iterator it = listeTravailleur.begin(); it != listeTravailleur.end(); ++it)
        {
            (*it)->majPosBoutonCollecte(m_hauteurCamera);
        }
    }
}

bool CameraSTR::eventFilter(QObject *obj, QEvent *event)
{
    QMouseEvent* mouseEvent = NULL;
    QWheelEvent* wheelEvent = NULL;

    if(!m_pause)
    {
        switch(event->type())
        {
        case QEvent::MouseButtonPress:
            mouseEvent = (QMouseEvent*)event;
            if(mouseEvent->button() == Qt::MidButton)
            {
                m_cliqueMilieuEnfonce = true;
            }
            break;

        case QEvent::MouseButtonRelease:
            mouseEvent = (QMouseEvent*)event;
            if(mouseEvent->button() == Qt::MidButton)
            {
                m_cliqueMilieuEnfonce = false;
            }
            break;

        case QEvent::MouseMove:
            mouseEvent = (QMouseEvent*)event;
            m_newPosMouse_X = mouseEvent->x();
            m_newPosMouse_Y = mouseEvent->y();
            break;

        case QEvent::Wheel:
            wheelEvent = (QWheelEvent*)event;
            m_wheel = wheelEvent->delta() / 120;
            break;

        default : break;
        }
    }

    return QObject::eventFilter(obj, event);
}

void CameraSTR::maj()
{
    m_direction.X = m_anciennePosMouse_X - m_newPosMouse_X;
    m_direction.Y = m_newPosMouse_Y - m_anciennePosMouse_Y;
    m_direction *= m_vitesse;

    m_anciennePosMouse_X = m_newPosMouse_X;
    m_anciennePosMouse_Y = m_newPosMouse_Y;

    if(m_cliqueMilieuEnfonce)
    {
        irr::core::vector3df posCameraTest = m_camera->getPosition();
        posCameraTest.X += m_direction.X;
        posCameraTest.Z += m_direction.Y;

        //si on ne depasse pas des limites on actualise la camera
        if(posCameraTest.X > -m_limite.Width && posCameraTest.X < m_limite.Width
           && posCameraTest.Z > (-m_limite.Height - 400) && posCameraTest.Z < m_limite.Height)
        {
            m_posCamera = posCameraTest;
            m_camera->setPosition(m_posCamera);

            m_tarCamera = m_camera->getTarget();
            m_tarCamera.X += m_direction.X;
            m_tarCamera.Z += m_direction.Y;
            m_camera->setTarget(m_tarCamera);
        }
    }

    if(m_wheel != 0)
    {
        irr::core::vector3df posCameraTest = m_camera->getPosition();
        posCameraTest += m_directionCamera_normalize * -m_wheel * m_vitesseWheel;
        if(posCameraTest.Y < 1000 && posCameraTest.Y > 100)
        {
            m_posCamera = posCameraTest;
            m_camera->setPosition(m_posCamera);
        }

        m_hauteurCamera = m_posCamera.Y;

        m_wheel = 0;
    }

    majBoutonsCollecte();
}

void CameraSTR::pause()
{
    m_pause = true;
}

void CameraSTR::reprendre()
{
    m_pause = false;
}
