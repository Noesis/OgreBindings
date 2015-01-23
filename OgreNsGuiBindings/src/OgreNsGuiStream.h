////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_OGRESTREAM_H__
#define __GUI_OGRESTREAM_H__


#include <OgreDataStream.h>


////////////////////////////////////////////////////////////////////////////////////////////////////
/// OgreStream
////////////////////////////////////////////////////////////////////////////////////////////////////
class OgreNsGuiStream : public Noesis::BaseStream
{
public:
    /// Constructor
    OgreNsGuiStream(Ogre::DataStreamPtr dataStream);

    /// Destructor
    virtual ~OgreNsGuiStream();

    /// From Noesis::IStream
    NsBool CanSeek() const;
    void SetPosition(NsSize pos);
    NsSize GetPosition() const;
    void SetLength(NsSize length);
    NsSize GetLength() const;
    NsBool CanRead() const;
    void Read(void* buffer, NsSize size);
    void Close();

private:
    Ogre::DataStreamPtr mDataStream;
};


#endif