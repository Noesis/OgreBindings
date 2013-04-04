#include "Sample.h"
#include "OgreSceneManager.h"
#include "OgreNsGuiBindings.h"

#ifdef _DEBUG
#define PLUGIN_CFG "plugins_d.cfg"
#define RESOURCE_CFG "resources_d.cfg"
#else
#define PLUGIN_CFG "plugins.cfg"
#define RESOURCE_CFG "resources.cfg"
#endif

#define SAFE_DELETE(x) if(x){delete x;  x= NULL;}

Sample::Sample() 
	: mRoot(NULL), mWindow(NULL), mSceneMgr(NULL), mCamera(NULL), mExitMainLoop(false)
	, mUIRoot(NULL), mUIRenderer(NULL), mTicTac(NULL)
{
}

Sample::~Sample()
{
	SAFE_DELETE(mRoot)
}

void Sample::setupEngine()
{
	// Create root node and load plugins which are defined inside our plugin.cfg
	mRoot = new Ogre::Root(PLUGIN_CFG);
	if (!mRoot->restoreConfig()) { 
		mRoot->showConfigDialog();
	}

	// Create our main window
	mWindow = mRoot->initialise(true, "TicTacToe");

	// Parse resources
	parseResources();

	// start script parsing
	Ogre::ResourceGroupManager::getSingletonPtr()->initialiseResourceGroup(Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

	// Create the scenemanger
	mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);
	mCamera = mSceneMgr->createCamera("MyCam");

	// Setup NsGui
	Noesis_Init(mSceneMgr);
	Noesis_LoadXAML(&mUIRoot, &mUIRenderer, "Gui/TicTacToe/MainWindow.xaml");
	Noesis_RendererAntialiasingMode(mUIRenderer, 1); // PAA

	mTicTac = new TicTacToeLogic((Noesis::Gui::FrameworkElement*)mUIRoot);
	// Setup input
	setupInput();
}

void Sample::parseResources()
{
	// load resource paths from config file
	Ogre::ConfigFile resCfg;
	resCfg.load(RESOURCE_CFG);
	Ogre::ConfigFile::SectionIterator seci = resCfg.getSectionIterator();
	// go through all specified resource groups
	while (seci.hasMoreElements()) {
		Ogre::String sec = seci.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap* settings = seci.getNext();
		// go through all resource paths
		for (Ogre::ConfigFile::SettingsMultiMap::iterator i = settings->begin(); i != settings->end(); i++) {
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(i->second, i->first, sec);
		}
	}
}

void Sample::setupInput()
{
	size_t winHWND = 0;
	mWindow->getCustomAttribute( "WINDOW", &winHWND );

	OIS::ParamList paramList; 
	std::ostringstream windowHndStr;
	windowHndStr << winHWND;

	paramList.insert(std::make_pair( std::string("WINDOW"), windowHndStr.str()));
	paramList.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
	paramList.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND")));

	// Create input system
	mInputSystem = OIS::InputManager::createInputSystem( paramList );

	// If possible create a buffered mouse
	if( mInputSystem->getNumberOfDevices(OIS::OISMouse) > 0 ) {
		mMouse = static_cast<OIS::Mouse*>( mInputSystem->createInputObject( OIS::OISMouse, true ) );
		mMouse->setEventCallback( this );

		const OIS::MouseState &mouseState = mMouse->getMouseState();
		mouseState.width  = mWindow->getWidth();
		mouseState.height = mWindow->getHeight();
	}

	// If possible create a buffered keyboard
	if( mInputSystem->getNumberOfDevices(OIS::OISKeyboard) > 0 ) {
		mKeyboard = static_cast<OIS::Keyboard*>( mInputSystem->createInputObject( OIS::OISKeyboard, true ) );
		mKeyboard->setEventCallback( this );
	}
}


void Sample::setupScene()
{
	mSceneMgr->setSkyBox(true, "spaceSkyBox");

	Ogre::Entity* pEntity = mSceneMgr->createEntity("SinbadInstance", "Sinbad.mesh");
	Ogre::SceneNode* pNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	pNode->attachObject(pEntity);

	Ogre::Light* pDirLight = mSceneMgr->createLight();
	pDirLight->setDirection(Ogre::Vector3(0,-1,0));
	pDirLight->setType(Ogre::Light::LT_DIRECTIONAL);
	pNode->attachObject(pDirLight);

	mCamera->setNearClipDistance(1.0f);
	mCamera->setFarClipDistance(100000.0f);
	mCamera->setPosition(0,0,20.0f);
	mCamera->lookAt(0,0,0);
	mCamera->setAutoAspectRatio(true);

	Ogre::Viewport* vp = mWindow->addViewport(mCamera);
	vp->setBackgroundColour(Ogre::ColourValue(1,0,0));
}

bool Sample::keyPressed(const OIS::KeyEvent &e)
{
	if (e.key == OIS::KC_ESCAPE)
	{
		mExitMainLoop = true;
		return true; 
	}
	Noesis_KeyDown(mUIRenderer, e.key);
	Noesis_Char(mUIRenderer, e.text);
	return false;
}

bool Sample::keyReleased(const OIS::KeyEvent &e)
{
	Noesis_KeyUp(mUIRenderer, e.key);
	return false;
}

bool Sample::mouseMoved(const OIS::MouseEvent &e)
{
	Noesis_MouseMove(mUIRenderer, (float)e.state.X.abs, (float)e.state.Y.abs);
	Noesis_MouseWheel(mUIRenderer, (float)e.state.X.abs, (float)e.state.Y.abs, e.state.Z.abs);
	return false;
}

bool Sample::mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	Noesis_MouseButtonDown(mUIRenderer, (float)e.state.X.abs, (float)e.state.Y.abs, id);
	return false;
}

bool Sample::mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	Noesis_MouseButtonUp(mUIRenderer, (float)e.state.X.abs, (float)e.state.Y.abs, id);
	return false;
}

void Sample::startMainLoop()
{
	while(!mExitMainLoop) {
		Ogre::WindowEventUtilities::messagePump(); 

		if(mWindow->isClosed()) 
			return; 

		if(mMouse)
			mMouse->capture();

		if (mKeyboard)
			mKeyboard->capture();

		Noesis_Tick();
		Noesis_UpdateRenderer(mUIRenderer, ((double)mRoot->getTimer()->getMilliseconds() / 1000.0));

		if(!mRoot->renderOneFrame()) 
			return; 
	}
}