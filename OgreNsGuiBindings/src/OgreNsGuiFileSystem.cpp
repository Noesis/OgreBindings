////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include "OgreNsGuiFileSystem.h"
#include "OgreNsGuiStream.h"

#include <NsCore/IStream.h>
#include <NsCore/ITextReader.h>
#include <NsCore/Stream.h>
#include <NsCore/NJSON.h>
#include <NsCore/Parser.h>
#include <NsCore/ParserExpr.h>
#include <NsCore/NsFactory.h>
#include <NsFile/DiskFileSystem.h>
#include <NsResource/ResourceTools.h>
#include <NsCore/Ptr.h>
#include <OgreResourceGroupManager.h>


using namespace Noesis::Core;
using namespace Noesis::File;
using namespace Noesis::Resource;
using namespace Noesis::Gui;


////////////////////////////////////////////////////////////////////////////////////////////////////
OgreNsGuiFileSystem::OgreNsGuiFileSystem(const NsChar* root): mRoot(root)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
OgreNsGuiFileSystem::~OgreNsGuiFileSystem()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NsBool OgreNsGuiFileSystem::FileExists(const Noesis::File::FileId& filename) const
{
    Ogre::String fName = filename.GetDirectory().c_str();
    fName += filename.GetFileName().c_str();
    fName += filename.GetExtension().c_str();
	return Ogre::ResourceGroupManager::getSingleton().resourceExists(mRoot, fName);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Ptr<Noesis::Core::IStream> OgreNsGuiFileSystem::OpenRead(const FileId& filename) const
{			
    Ogre::String fName = filename.GetDirectory().c_str();
    fName += filename.GetFileName().c_str();
    fName += filename.GetExtension().c_str();
    return *new OgreNsGuiStream(Ogre::ResourceGroupManager::getSingleton().openResource(fName,
        mRoot, false));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_IMPLEMENT_REFLECTION_(OgreNsGuiFileSystem)
