////////////////////////////////////////////////////////////////////////////////////////////////////
// Ogre Sample
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __SAMPLE_H__
#define __SAMPLE_H__

#include "Ogre.h"
#include "OIS.h"
#include "TicTacToeLogic.h"

class Sample : public OIS::KeyListener, public OIS::MouseListener
{
public:
	Sample();
	~Sample();

	void setupEngine();
	void setupScene();
	void startMainLoop();

private:
	Ogre::Root* mRoot;
	Ogre::RenderWindow* mWindow;
	Ogre::SceneManager* mSceneMgr;
	Ogre::Camera* mCamera;
	bool mExitMainLoop;

	OIS::InputManager* mInputSystem;
	OIS::Mouse* mMouse;
	OIS::Keyboard* mKeyboard;

	void parseResources();
	void setupInput();

	bool keyPressed(const OIS::KeyEvent &e);
	bool keyReleased(const OIS::KeyEvent &e);
	bool mouseMoved(const OIS::MouseEvent &e);
	bool mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id);
	bool mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id);

	// NsGui
	TicTacToeLogic* mTicTac;

	void* mUIRoot;
	void* mUIRenderer;
};
#endif