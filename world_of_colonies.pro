QT += widgets

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle

SOURCES += main.cpp \
    singleton/Device.cpp \
    singleton/Driver.cpp \
    singleton/SceneManager.cpp \
    jeu/Camera.cpp \
    jeu/irrlichtwidget.cpp \
    mainwindow.cpp \
    gui/menuconstruire.cpp \
    jeu/batiments/ressource/conteneur_nourriture.cpp \
    jeu/batiments/ressource/conteneur_or.cpp \
    jeu/batiments/ressource/conteneur.cpp \
    jeu/batiments/ressource/travailleur_nourriture.cpp \
    jeu/batiments/ressource/travailleur_or.cpp \
    jeu/batiments/ressource/travailleur.cpp \
    jeu/batiments/hoteldeville.cpp \
    jeu/batiments/batiment.cpp \
    jeu/village.cpp \
    gui/widgetoptionsbatiments.cpp \
    utilitaire/getcss.cpp \
    utilitaire/sha1.cpp \
    bdd/widgetconnexion.cpp \
    bdd/bdd.cpp \
    bdd/village_bdd.cpp \
    jeu/batiments/armee/campentrainement.cpp \
    jeu/batiments/armee/caserne.cpp \
    jeu/batiments/armee/portail.cpp \
    jeu/batiments/defense/defense.cpp \
    jeu/batiments/defense/canon.cpp \
    jeu/batiments/defense/tourelle.cpp \
    jeu/batiments/defense/mortier.cpp \
    gui/widgetarmee.cpp \
    jeu/item.cpp \
    jeu/soldats/soldat.cpp \
    jeu/soldats/artilleur.cpp \
    jeu/soldats/tank.cpp

HEADERS += \
    singleton/Device.h \
    singleton/Driver.h \
    singleton/SceneManager.h \
    jeu/Camera.h \
    jeu/irrlichtwidget.h \
    mainwindow.h \
    gui/menuconstruire.h \
    jeu/batiments/ressource/conteneur_nourriture.h \
    jeu/batiments/ressource/conteneur_or.h \
    jeu/batiments/ressource/conteneur.h \
    jeu/batiments/ressource/travailleur_nourriture.h \
    jeu/batiments/ressource/travailleur_or.h \
    jeu/batiments/ressource/travailleur.h \
    jeu/batiments/hoteldeville.h \
    jeu/batiments/batiment.h \
    jeu/village.h \
    gui/widgetoptionsbatiments.h \
    utilitaire/getcss.h \
    utilitaire/sha1.h \
    bdd/widgetconnexion.h \
    bdd/bdd.h \
    jeu/batiments/armee/campentrainement.h \
    jeu/batiments/armee/caserne.h \
    jeu/batiments/armee/portail.h \
    jeu/batiments/defense/defense.h \
    jeu/batiments/defense/canon.h \
    jeu/batiments/defense/tourelle.h \
    jeu/batiments/defense/mortier.h \
    gui/widgetarmee.h \
    jeu/item.h \
    jeu/soldats/soldat.h \
    jeu/soldats/artilleur.h \
    jeu/soldats/tank.h


unix|win32: LIBS += -lIrrlicht
unix|win32: LIBS += -lmysqlcppconn

FORMS += \
    gui/mainwindow.ui \
    gui/menuconstruire.ui \
    gui/widgetoptionsbatiments.ui \
    bdd/widgetconnexion.ui \
    gui/widgetarmee.ui
