////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include "pch.h"
#include "OgreNsGuiResourceProvider.h"
#include "OgreNsGuiStream.h"

#include <OgreResourceGroupManager.h>


using namespace Noesis;


//////////////////////////////////////////////////////////////////////////////////////////////////////
OgreNsGuiResourceProvider::OgreNsGuiResourceProvider(const char* group): mGroup(group)
{
}


//////////////////////////////////////////////////////////////////////////////////////////////////////
Ptr<Noesis::IStream> OgreNsGuiResourceProvider::RequestFile(const NsChar* name)
{
    Ogre::ResourceGroupManager& manager = Ogre::ResourceGroupManager::getSingleton();

    if (manager.resourceExists(mGroup, name))
    {
        return *new OgreNsGuiStream(manager.openResource(name, mGroup, false));
    }
    else
    {
        return Ptr<Noesis::IStream>::Null();
    }
}
