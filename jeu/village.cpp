#include "village.h"

Village::Village(QWidget* parent, QString pseudo, QProgressBar* pbNiveau, QLabel* lbNiveau, QProgressBar* pbOr, QProgressBar* pbNourriture) : QObject(parent)
{
    m_mainWindow = parent;

    //partie importante de irrlicht
    m_sceneManager = SceneManager::getSceneManager();
    m_driver = Driver::getDriver();
    m_collisionManager = m_sceneManager->getSceneCollisionManager();

    //stats
    m_pseudo = pseudo;
    m_nbMaxNourriture = m_nbMaxOr = 500;
    m_nbNourriture = m_nbOr = 0;
    m_nbXpMax = 100;
    m_nbXp = 1;
    m_pbNiveau = pbNiveau;
    m_pbOr = pbOr;
    m_pbNourriture = pbNourriture;
    m_lbNiveau = lbNiveau;
    m_niveau = 1;
    m_nbMaison = m_nbUsine = m_nbBanque = m_nbEntrepot
            = m_nbCamp = m_nbCaserne = m_nbPortail =
            m_nbCanon = m_nbTourelle = m_nbMortier = 0;

    //terrain
    //sol
    irr::scene::IMesh* plane = m_sceneManager->getGeometryCreator()->createPlaneMesh(irr::core::dimension2df(10,10), irr::core::dimension2du(100, 100));
    m_terrain = m_sceneManager->addMeshSceneNode(plane);
    m_terrain->setMaterialTexture(0, m_driver->getTexture("mesh/texture/sol.jpg"));
    m_terrainSelector = m_sceneManager->createTriangleSelector(m_terrain->getMesh(), m_terrain);
    m_terrain->setTriangleSelector(m_terrainSelector);

    //light
    irr::scene::ILightSceneNode* l = m_sceneManager->addLightSceneNode();
    l->setPosition(irr::core::vector3df(500,1000, -1000));
    l->setRadius(10000);

    //batiment du village
    genererVillage();

    //options bats widget
    m_WidgetOptionsBats = new WidgetOptionsBatiments(m_mainWindow);
    m_WidgetOptionsBats->setVisible(false);

    connect(m_WidgetOptionsBats->getBoutonDeplacer(), SIGNAL(clicked(bool)), this, SLOT(deplacerBatiment()));
    connect(m_WidgetOptionsBats->getBoutonVendre(), SIGNAL(clicked(bool)), this, SLOT(vendreBatiment()));
    connect(m_WidgetOptionsBats->getBoutonDroite(), SIGNAL(clicked(bool)), this, SLOT(pivoterDroite()));
    connect(m_WidgetOptionsBats->getBoutonGauche(), SIGNAL(clicked(bool)), this, SLOT(pivoterGauche()));
    connect(m_WidgetOptionsBats->getBoutonRetour(), SIGNAL(clicked(bool)), this, SLOT(quitterOptionBat()));

    //autre
    m_batimentADeplacer = NULL;
    m_batimentSelectionne = NULL;
    m_leBatimentEtaitDejaConstruit = false;
}

void Village::setNbOr(int nbOr)
{
    m_nbOr = nbOr;
    if(m_nbOr > m_nbMaxOr)
    {
        m_nbOr = m_nbMaxOr;
    }

    if(m_nbOr < 0) m_nbOr = 0;

    m_pbOr->setValue(m_nbOr);

    Bdd::getBdd()->majNbRessource(m_pseudo, m_nbOr, m_nbNourriture);
}

void Village::setNbNourriture(int nbNourriture)
{
    m_nbNourriture = nbNourriture;
    if(m_nbNourriture > m_nbMaxNourriture)
    {
        m_nbNourriture = m_nbMaxNourriture;
    }

    if(m_nbNourriture < 0) m_nbNourriture = 0;

    m_pbNourriture->setValue(m_nbNourriture);

    Bdd::getBdd()->majNbRessource(m_pseudo, m_nbOr, m_nbNourriture);
}

bool Village::PortailDansLeVillage()
{
    for(std::vector<Batiment*>::iterator it = m_listeBatiments.begin(); it != m_listeBatiments.end(); ++it)
    {
        if((*it)->getType() == portail && (*it)->isVisible())
        {
            return true;
        }
    }

    return false;
}

void Village::cacherBatiments()
{
    for(std::vector<Batiment*>::iterator it = m_listeBatiments.begin(); it != m_listeBatiments.end(); ++it)
    {
        (*it)->getMeshSceneNode()->setVisible(false);
    }
}

void Village::afficherBatiments()
{
    for(std::vector<Batiment*>::iterator it = m_listeBatiments.begin(); it != m_listeBatiments.end(); ++it)
    {
        (*it)->getMeshSceneNode()->setVisible(true);
    }
}

void Village::setArmee(Armee *armee)
{
    m_armee = armee;

    connect(this, SIGNAL(majNbCaserne(int)), m_armee, SLOT(majPlaceMax(int)));
    emit majNbCaserne(m_nbCaserne);
}

int Village::getNbOr()
{
    return m_nbOr;
}

int Village::getNbNourriture()
{
    return m_nbNourriture;
}

void Village::perdreRessource(cout nb)
{
    setNbOr(getNbOr() - nb.nbOr);
    setNbNourriture(getNbNourriture() - nb.nbNourriture);
}

std::vector<Travailleur*> Village::getListeTravailleur()
{
    std::vector<Travailleur*> listeTravailleur;

    for(std::vector<Batiment*>::iterator it = m_listeBatiments.begin(); it != m_listeBatiments.end(); ++it)
    {
        if((*it)->getType() == travailleurNourriture || (*it)->getType() == travailleurOr)
        {
            Travailleur* travailleur = (Travailleur*)(*it);
            listeTravailleur.push_back(travailleur);
        }
    }

    return listeTravailleur;
}

void Village::setNiveau(int niveau, int xp)
{
    m_niveau = niveau;
    m_lbNiveau->setText(QString("lvl " + QString::number(m_niveau)));

    m_nbXpMax = 100;
    for(int i = 0; i < niveau; ++i)
    {
        m_nbXpMax *= 1.5;
    }
    m_pbNiveau->setMaximum(m_nbXpMax);

    m_nbXp = xp;
    m_pbNiveau->setValue(m_nbXp);
}

bool Village::essayerConstruireBatiment(Batiment* batiment)
{
    cout coutDeConstruction = batiment->getCout();
    if(m_nbOr >= coutDeConstruction.nbOr && m_nbNourriture >= coutDeConstruction.nbNourriture)
    {
        m_batimentADeplacer = batiment;
        m_batimentADeplacer->afficherBatimentConstruit();

        return true;
    }

    else
    {
        delete batiment;
        return false;
    }
}

void Village::majPosBatimentAConstruire(irr::core::vector2di posMouse)
{
    emit onPlaceBatiment();

    irr::core::line3df line;
    line = m_collisionManager->getRayFromScreenCoordinates(posMouse);

    irr::core::vector3df pos(6,8,9);
    irr::core::triangle3df tri;
    irr::scene::ISceneNode* node;
    if(m_collisionManager->getCollisionPoint(line, m_terrainSelector, pos, tri, node))
    {
        irr::s32 x = pos.X, z = pos.Z;
        x = x / TAILLE_CASE * TAILLE_CASE;    z = z / TAILLE_CASE * TAILLE_CASE;
        pos.X = x;          pos.Z = z;
        pos.Y += 1;
        m_batimentADeplacer->setPosition(pos);
    }

    if(collisionEntreBatiment())
    {
        m_batimentADeplacer->getMeshSceneNode()->setMaterialTexture(0, Driver::getDriver()->getTexture("mesh/texture/rouge.jpg"));
    }

    else
    {
        m_batimentADeplacer->getMeshSceneNode()->setMaterialTexture(0, Driver::getDriver()->getTexture("mesh/texture/vert.jpg"));
    }
}

bool Village::collisionEntreBatiment()
{
    irr::core::aabbox3df bb_batimentAConstuire = m_batimentADeplacer->getMeshSceneNode()->getTransformedBoundingBox();
    irr::core::aabbox3df bb_autreBatiment;
    bool collision = false;

    for(unsigned int i = 0; i < m_listeBatiments.size(); i++)
    {
        if(m_batimentADeplacer->getId() != m_listeBatiments[i]->getId())
        {
            if(m_listeBatiments[i]->isVisible())
            {
                bb_autreBatiment =  m_listeBatiments[i]->getMeshSceneNode()->getTransformedBoundingBox();
                if(bb_autreBatiment.intersectsWithBox(bb_batimentAConstuire))
                {
                    collision = true;
                }
            }
        }
    }

   return collision;
}

void Village::ajouterBatiment()
{
    int typeBat = m_batimentADeplacer->getType();

    m_batimentADeplacer->setId(m_listeBatiments.size());
    m_batimentADeplacer->setIdFichierVillage(creerIdFichierVillage(typeBat));
    m_batimentADeplacer->setPseudo(m_pseudo);

    irr::scene::ITriangleSelector* selector;
    selector = m_sceneManager->createTriangleSelector(m_batimentADeplacer->getMeshSceneNode()->getMesh(), m_batimentADeplacer->getMeshSceneNode());
    m_batimentADeplacer->getMeshSceneNode()->setTriangleSelector(selector);
    m_batsSelectors.push_back(selector);

    m_listeBatiments.push_back(m_batimentADeplacer);

    if(typeBat == conteneurNourriture ||
                typeBat == travailleurNourriture)
    {
        Conteneur* conteneneur = (Conteneur*)m_batimentADeplacer;
        m_nbMaxNourriture += conteneneur->getContenanceMax();
        m_pbNourriture->setMaximum(m_nbMaxNourriture);
    }

    if(typeBat == conteneurOr ||
            typeBat == travailleurOr)
    {
        Conteneur* conteneneur = (Conteneur*)m_batimentADeplacer;
        m_nbMaxOr += conteneneur->getContenanceMax();
        m_pbOr->setMaximum(m_nbMaxOr);
    }

    if(typeBat == travailleurOr || typeBat == travailleurNourriture)
    {
        Travailleur* travailleur = (Travailleur*)m_batimentADeplacer;
        travailleur->verifierTiming();
    }

    if(typeBat == caserne)
    {
        emit majNbCaserne(m_nbCaserne);
    }
}

void Village::construireBatiment(bool gratuitement)
{
    if(gratuitement)
    {
        ajouterBatiment();

        m_batimentADeplacer->getMeshSceneNode()->setMaterialTexture(0, m_batimentADeplacer->getTexture());

        emit onArretePlacerBatiment();
    }

    else if(!collisionEntreBatiment())
    {
        if(!m_leBatimentEtaitDejaConstruit)
        {
            if(m_batimentADeplacer->getType() == travailleurOr)
            {
                Bdd::getBdd()->ajouterTimingBatiment(m_pseudo, m_batimentADeplacer->getType());
                Travailleur* travailleur = (Travailleur*)m_batimentADeplacer;
                connect(travailleur, SIGNAL(gagneDesRessources(int)), this, SLOT(gagneOr(int)));
            }

            if(m_batimentADeplacer->getType() == travailleurNourriture)
            {
                Bdd::getBdd()->ajouterTimingBatiment(m_pseudo, m_batimentADeplacer->getType());
                Travailleur* travailleur = (Travailleur*)m_batimentADeplacer;
                connect(travailleur, SIGNAL(gagneDesRessources(int)), this, SLOT(gagneNourriture(int)));
            }

            ajouterBatiment();

            cout coutDeConstruction = m_batimentADeplacer->getCout();

            setNbOr(getNbOr() - coutDeConstruction.nbOr);
            setNbNourriture(getNbNourriture() - coutDeConstruction.nbNourriture);

            gagneDeLXp(coutDeConstruction.nbXp);

            irr::s32 posX = m_batimentADeplacer->getPosition().X,
                posZ = m_batimentADeplacer->getPosition().Z;
            Bdd::getBdd()->majBatiment(m_pseudo, m_batimentADeplacer->getType(), irr::core::vector2di(posX, posZ), -1);
        }

        else
        {
            irr::s32 posX = m_batimentADeplacer->getPosition().X,
                posZ = m_batimentADeplacer->getPosition().Z;
            Bdd::getBdd()->majBatiment(m_pseudo, m_batimentADeplacer->getType(), irr::core::vector2di(posX, posZ), m_batimentADeplacer->getIdFichierVillage());
        }

        m_batimentADeplacer->getMeshSceneNode()->setMaterialTexture(0, m_batimentADeplacer->getTexture());

        emit onArretePlacerBatiment();

        m_batimentADeplacer = NULL;
    }
}

void Village::gagneDeLXp(int xp)
{
    m_nbXp += xp;

    if(m_nbXp >= m_nbXpMax)
    {
        int resteXp = m_nbXp - m_nbXpMax;

        m_nbXpMax *= 1.5;
        m_pbNiveau->setMaximum(m_nbXpMax);
        m_nbXp = resteXp;

        m_niveau++;
        m_lbNiveau->setText(QString("lvl " + QString::number(m_niveau)));
    }

    m_pbNiveau->setValue(m_nbXp);

    // on enregistre notre niveau
    Bdd* bdd = Bdd::getBdd();
    bdd->majNiveau(m_pseudo, m_niveau, m_nbXp);
}

bool Village::batimentVise(irr::core::vector2di posMouse)
{
    irr::core::line3df line;
    line = m_collisionManager->getRayFromScreenCoordinates(posMouse);

    irr::core::vector3df pos(6,8,9);
    irr::core::triangle3df tri;
    irr::scene::ISceneNode* node = NULL;

    for(unsigned int i = 0; i < m_batsSelectors.size(); i++)
    {
        if(m_collisionManager->getCollisionPoint(line, m_batsSelectors[i], pos, tri, node))
        {
            if(node->isVisible())
            {
                for(unsigned int i = 0; i < m_listeBatiments.size(); ++i)
                {
                    if(m_listeBatiments[i]->getMeshSceneNode() == node)
                    {
                        irr::core::vector2di posBat2d;
                        posBat2d = m_collisionManager->getScreenCoordinatesFrom3DPosition(node->getPosition());
                        m_WidgetOptionsBats->move(QPoint(posBat2d.X, posBat2d.Y));
                        m_WidgetOptionsBats->setVisible(true);

                        m_batimentSelectionne = m_listeBatiments[i];

                        m_batimentSelectionne->estVise();
                    }
                }
            }
        }
    }

    return false;
}

bool Village::eventFilter(QObject *obj, QEvent *event)
{
        QMouseEvent* mouseEvent = NULL;

            switch(event->type())
            {
            case QEvent::MouseButtonPress:
                mouseEvent = (QMouseEvent*)event;
                if(mouseEvent->button() == Qt::LeftButton)
                {
                    if(m_batimentADeplacer != NULL)
                    {
                        construireBatiment();
                        m_leBatimentEtaitDejaConstruit = false;
                    }
                }

                if(mouseEvent->button() == Qt::RightButton)
                {
                    if(m_batimentADeplacer != NULL && !m_leBatimentEtaitDejaConstruit)
                    {
                        m_batimentADeplacer->kill();
                        delete m_batimentADeplacer;
                        m_batimentADeplacer = NULL;
                    }

                    else batimentVise(irr::core::vector2di(mouseEvent->x(), mouseEvent->y()));

                    emit onArretePlacerBatiment();
                }
                break;

            case QEvent::MouseMove:
                mouseEvent = (QMouseEvent*)event;
                if(m_batimentADeplacer != NULL) majPosBatimentAConstruire(irr::core::vector2di(mouseEvent->x(), mouseEvent->y()));
                break;

            default : break;
            }

    return QObject::eventFilter(obj, event);
}

void Village::deplacerBatiment()
{
    m_batimentSelectionne->estPlusVise();
    m_batimentADeplacer = m_batimentSelectionne;
    m_leBatimentEtaitDejaConstruit = true;
}

void Village::vendreBatiment()
{
    m_batimentSelectionne->estPlusVise();
    if(m_batimentSelectionne->getType() != hdv)
    {
        if(m_batimentSelectionne->getType() == conteneurOr ||
                m_batimentSelectionne->getType() == travailleurOr)
        {
            m_nbMaxOr -= ((Conteneur*)m_batimentSelectionne)->getContenanceMax();
            m_pbOr->setMaximum(m_nbMaxOr);
        }

        if(m_batimentSelectionne->getType() == conteneurNourriture ||
                m_batimentSelectionne->getType() == travailleurNourriture)
        {
            m_nbMaxNourriture -= ((Conteneur*)m_batimentSelectionne)->getContenanceMax();
            m_pbNourriture->setMaximum(m_nbMaxNourriture);
        }

        gagneOr(m_batimentSelectionne->getCout().nbOr / 2);
        gagneNourriture(m_batimentSelectionne->getCout().nbNourriture / 2);

        Bdd::getBdd()->majNbRessource(m_pseudo, m_nbOr, m_nbNourriture);

        Bdd::getBdd()->supprimerBatiment(m_pseudo, m_batimentSelectionne->getType(), m_batimentSelectionne->getIdFichierVillage());
        if(m_batimentSelectionne->getType() == travailleurNourriture || m_batimentSelectionne->getType() == travailleurOr)
        {
            Bdd::getBdd()->supprimerTimingBatiment(m_pseudo, m_batimentSelectionne->getType(), m_batimentSelectionne->getIdFichierVillage());
        }
        supprimerIdFichierVillage(m_batimentSelectionne->getType(), m_batimentSelectionne->getIdFichierVillage());

        if(m_batimentSelectionne->getType() == caserne)
        {
            emit majNbCaserne(m_nbCaserne);
        }

        m_batimentSelectionne->kill();
    }

    else
    {
        QMessageBox::critical(m_mainWindow, "Erreur", "Il est impossible de vendre votre"
                                              " hotel de ville.");
    }
}

void Village::pivoterDroite()
{
    m_batimentSelectionne->estPlusVise();
    m_batimentSelectionne->setRotation(m_batimentSelectionne->getRotation() + irr::core::vector3df(0,90,0));
    Bdd::getBdd()->majRotationBatiment(m_pseudo, m_batimentSelectionne->getType(), m_batimentSelectionne->getRotation().Y, m_batimentSelectionne->getIdFichierVillage());
}

void Village::pivoterGauche()
{
    m_batimentSelectionne->estPlusVise();
    m_batimentSelectionne->setRotation(m_batimentSelectionne->getRotation() + irr::core::vector3df(0,-90,0));
    Bdd::getBdd()->majRotationBatiment(m_pseudo, m_batimentSelectionne->getType(), m_batimentSelectionne->getRotation().Y, m_batimentSelectionne->getIdFichierVillage());
}

void Village::gagneNourriture(int nbNourriture)
{
    setNbNourriture(getNbNourriture() + nbNourriture);
}

void Village::gagneOr(int nbOr)
{
    setNbOr(getNbOr() + nbOr);
}

void Village::quitterOptionBat()
{
    m_batimentSelectionne->estPlusVise();
}

irr::scene::ITriangleSelector* Village::getTerrainSelector()
{
    return m_terrainSelector;
}

Village::~Village()
{
    for(unsigned int i = 0; i < m_listeBatiments.size(); ++i)
    {
        delete m_listeBatiments[i];
        m_listeBatiments[i] = 0;
    }

    delete m_WidgetOptionsBats;
};
