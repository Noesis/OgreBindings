Ogre3D bindings for NoesisGUI
-----------------------------

This code integrates the UI middleware NoesisGUI (http://www.noesisengine.com/noesis_gui_features.htm) with Ogre3D (http://www.ogre3d.org/) graphics rendering engine.

You need to get a copy of NoesisGUI SDK from http://forums.noesisengine.com/ and:

* Copy noesis.dll to bin\debug and bin\release
* Include headers must be copied to Dependencies\include
* noesis.lib must be copied to Dependencies\lib

Known problems:

* For now only DX9 implementation is working. GL and mobile platform are pending.
* Render to texture not working yet. The API of the Ogre bindings need to be expanded for this.
