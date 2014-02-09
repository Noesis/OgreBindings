OGRE bindings for noesisGUI
---------------------------

This code integrates the UI middleware noesisGUI (http://www.noesisengine.com/noesis_gui_features.htm) with Ogre3D (http://www.ogre3d.org/) graphics rendering engine.

Three projects are included:

* OgreNsGuiBindings: noesisGUI wrapped to be used in OGRE. This is the project you should integrate directly in your project.
* BasicOgreSample: minimal sample, showing a basic scene with a simple GUI on top.
* TicTacToe: a simple tic tac toe game implemented using noesisGUI

You need to get a copy of NoesisGUI SDK from http://forums.noesisengine.com/ and:

* Copy binaries to bin\debug and bin\release
* Include headers must be copied to Dependencies\include
* noesis.lib must be copied to Dependencies\lib

Known problems:

* Render to texture not working yet. The API of the Ogre bindings need to be expanded for this.
