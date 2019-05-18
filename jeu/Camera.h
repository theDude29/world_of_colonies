#ifndef CAMERA
#define CAMERA

#include <irrlicht/irrlicht.h>
#include <QObject>
#include <QEvent>
#include <vector>
#include "jeu/batiments/ressource/travailleur.h"

class CameraSTR : public QObject
{
    Q_OBJECT

public:
    CameraSTR(QObject* mainWindow);
    virtual bool eventFilter(QObject *obj, QEvent *event);
    void maj();
    void majBoutonsCollecte();

private:
    irr::scene::ICameraSceneNode* m_camera;

    //limites
    irr::core::dimension2d<irr::s32> m_limite;

    //mouvement de la camera (X et Z)
    bool m_cliqueMilieuEnfonce;
    irr::s32 m_newPosMouse_X, m_newPosMouse_Y, m_anciennePosMouse_X, m_anciennePosMouse_Y;
    irr::core::vector2d<irr::s32> m_direction;
    irr::core::vector3df m_posCamera;
    irr::core::vector3df m_tarCamera;
    irr::f32 m_vitesse;

    //mouvement de la camera (Y)
    irr::f32 m_wheel;
    irr::f32 m_vitesseWheel;
    irr::core::vector3df m_directionCamera_normalize;
    irr::s32 m_distanceMin, m_distanceMax;
    irr::f32 m_hauteurCamera;

    //autre
    bool m_pause;

public slots:
    void pause();
    void reprendre();
};
#endif // CAMERA
