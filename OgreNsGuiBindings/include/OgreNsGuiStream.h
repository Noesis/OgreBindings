////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_OGRESTREAM_H__
#define __GUI_OGRESTREAM_H__

#include <Noesis.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/IStream.h>
#include <OgreDataStream.h>

namespace Noesis
{
	namespace Gui
	{
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// OgreStream
		////////////////////////////////////////////////////////////////////////////////////////////////////
		class OgreNsGuiStream : public Core::IStream
		{
		public:
			/// Constructor
			OgreNsGuiStream(Ogre::DataStreamPtr dataStream);

			/// Destructor
			virtual ~OgreNsGuiStream();

			/// @see Core::IStream
			virtual NsBool CanSeek() const;

			/// @see Core::IStream
			virtual void SetPosition(NsUInt64 pos);

			/// @see Core::IStream
			virtual NsUInt64 GetPosition() const;

			/// @see Core::IStream
			virtual void SetLength(NsUInt64 length);

			/// @see Core::IStream
			virtual NsUInt64 GetLength() const;

			/// @see Core::IStream
			virtual NsBool CanRead() const;

			/// @see Core::IStream
			virtual void Read(void* buffer, NsSize size);

			/// @see Core::IStream
			virtual NsBool CanWrite() const;

			/// @see Core::IStream
			virtual void Write(const void* buffer, NsSize size);

			/// @see Core::IStream
			virtual void Flush();

			/// @see Core::IStream
			virtual void Close();

		private:
			Ogre::DataStreamPtr mDataStream;

			NS_DECLARE_REFLECTION(OgreNsGuiStream, Core::IStream)
		};
	}
}

#endif