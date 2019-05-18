#include "Device.h"
#include "SceneManager.h"
#include <iostream>

irr::scene::ISceneManager* SceneManager::m_instance = NULL;

SceneManager::SceneManager()
{
    m_instance = Device::getDevice()->getSceneManager();
}

irr::scene::ISceneManager* SceneManager::getSceneManager()
{
        if(m_instance == NULL)
        {
            SceneManager();
        }

        return m_instance;
}

