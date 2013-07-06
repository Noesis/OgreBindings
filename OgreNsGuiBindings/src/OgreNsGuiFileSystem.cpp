////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include "OgreNsGuiStream.h"

#include <OgreNsGuiFileSystem.h>
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


namespace Noesis
{
	namespace Gui
	{
		////////////////////////////////////////////////////////////////////////////////////////////////////
		OgreNsGuiFileSystem::OgreNsGuiFileSystem()
		{
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		OgreNsGuiFileSystem::~OgreNsGuiFileSystem()
		{
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		NsBool OgreNsGuiFileSystem::FileExists(const Noesis::File::FileId& filename) const
		{
			Ogre::String fName = (filename.GetFileName() + filename.GetExtension()).c_str();
			return Ogre::ResourceGroupManager::getSingleton().resourceExistsInAnyGroup(fName);
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		Ptr<Noesis::Core::IStream> OgreNsGuiFileSystem::OpenRead(const Noesis::File::FileId& filename) const
		{			
			Ogre::String fName = (filename.GetFileName() + filename.GetExtension()).c_str();
			if (Ogre::ResourceGroupManager::getSingleton().resourceExistsInAnyGroup(fName))
			{
				return *new Noesis::Gui::OgreNsGuiStream(Ogre::ResourceGroupManager::getSingleton().openResource(fName));
			}
			else
			{
				NS_ERROR("File '%s' not found", filename.GetStr());
			}
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		NS_IMPLEMENT_REFLECTION_(OgreNsGuiFileSystem)
	}
}