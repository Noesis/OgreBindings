////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include "pch.h"
#include "OgreNsGuiResourceProvider.h"
#include "OgreRoot.h"
#include "OgreRenderWindow.h"

#include <OgreNsGuiBindings.h>

#include <d3d9.h>


using namespace Noesis;


namespace
{

    static Noesis::Key s_OISKeyMappings[] = 
    {
        Key_None,       //KC_UNASSIGNED  = 0x00,
        Key_Escape,     //KC_ESCAPE      = 0x01,
        Key_1,          //KC_1           = 0x02,
        Key_2,          //KC_2           = 0x03,
        Key_3,          //KC_3           = 0x04,
        Key_4,          //KC_4           = 0x05,
        Key_5,          //KC_5           = 0x06,
        Key_6,          //KC_6           = 0x07,
        Key_7,          //KC_7           = 0x08,
        Key_8,          //KC_8           = 0x09,
        Key_9,          //KC_9           = 0x0A,
        Key_0,          //KC_0           = 0x0B,
        Key_Subtract,   //KC_MINUS       = 0x0C,    // - on main keyboard
        Key_None,       //KC_EQUALS      = 0x0D,
        Key_Back,       //KC_BACK        = 0x0E,    // backspace
        Key_Tab,        //KC_TAB         = 0x0F,
        Key_Q,          //KC_Q           = 0x10,
        Key_W,          //KC_W           = 0x11,
        Key_E,          //KC_E           = 0x12,
        Key_R,          //KC_R           = 0x13,
        Key_T,          //KC_T           = 0x14,
        Key_Y,          //KC_Y           = 0x15,
        Key_U,          //KC_U           = 0x16,
        Key_I,          //KC_I           = 0x17,
        Key_O,          //KC_O           = 0x18,
        Key_P,          //KC_P           = 0x19,
        Key_None,       //KC_LBRACKET    = 0x1A,
        Key_None,       //KC_RBRACKET    = 0x1B,
        Key_Return,     //KC_RETURN      = 0x1C,    // Enter on main keyboard
        Key_Control,    //KC_LCONTROL    = 0x1D,
        Key_A,          //KC_A           = 0x1E,
        Key_S,          //KC_S           = 0x1F,
        Key_D,          //KC_D           = 0x20,
        Key_F,          //KC_F           = 0x21,
        Key_G,          //KC_G           = 0x22,
        Key_H,          //KC_H           = 0x23,
        Key_J,          //KC_J           = 0x24,
        Key_K,          //KC_K           = 0x25,
        Key_L,          //KC_L           = 0x26,
        Key_None,       //KC_SEMICOLON   = 0x27,
        Key_None,       //KC_APOSTROPHE  = 0x28,
        Key_None,       //KC_GRAVE       = 0x29,    // accent
        Key_Shift,      //KC_LSHIFT      = 0x2A,
        Key_None,       //KC_BACKSLASH   = 0x2B,
        Key_Z,          //KC_Z           = 0x2C,
        Key_X,          //KC_X           = 0x2D,
        Key_C,          //KC_C           = 0x2E,
        Key_V,          //KC_V           = 0x2F,
        Key_B,          //KC_B           = 0x30,
        Key_N,          //KC_N           = 0x31,
        Key_M,          //KC_M           = 0x32,
        Key_None,       //KC_COMMA       = 0x33,
        Key_None,       //KC_PERIOD      = 0x34,    // . on main keyboard
        Key_None,       //KC_SLASH       = 0x35,    // / on main keyboard
        Key_Shift,      //KC_RSHIFT      = 0x36,
        Key_None,       //KC_MULTIPLY    = 0x37,    // * on numeric keypad
        Key_Alt,        //KC_LMENU       = 0x38,    // left Alt
        Key_Space,      //KC_SPACE       = 0x39,
        Key_None,       //KC_CAPITAL     = 0x3A,
        Key_F1,         //KC_F1          = 0x3B,
        Key_F2,         //KC_F2          = 0x3C,
        Key_F3,         //KC_F3          = 0x3D,
        Key_F4,         //KC_F4          = 0x3E,
        Key_F5,         //KC_F5          = 0x3F,
        Key_F6,         //KC_F6          = 0x40,
        Key_F7,         //KC_F7          = 0x41,
        Key_F8,         //KC_F8          = 0x42,
        Key_F9,         //KC_F9          = 0x43,
        Key_F10,        //KC_F10         = 0x44,
        Key_NumLock,    //KC_NUMLOCK     = 0x45,
        Key_Scroll,     //KC_SCROLL      = 0x46,    // Scroll Lock
        Key_Pad7,       //KC_NUMPAD7     = 0x47,
        Key_Pad8,       //KC_NUMPAD8     = 0x48,
        Key_Pad9,       //KC_NUMPAD9     = 0x49,
        Key_Subtract,   //KC_SUBTRACT    = 0x4A,    // - on numeric keypad
        Key_Pad4,       //KC_NUMPAD4     = 0x4B,
        Key_Pad5,       //KC_NUMPAD5     = 0x4C,
        Key_Pad6,       //KC_NUMPAD6     = 0x4D,
        Key_Add,        //KC_ADD         = 0x4E,    // + on numeric keypad
        Key_Pad1,       //KC_NUMPAD1     = 0x4F,
        Key_Pad2,       //KC_NUMPAD2     = 0x50,
        Key_Pad3,       //KC_NUMPAD3     = 0x51,
        Key_Pad0,       //KC_NUMPAD0     = 0x52,
        Key_Decimal,    //KC_DECIMAL     = 0x53,    // . on numeric keypad
        Key_None,       // 0x54 - Gap
        Key_None,       // 0x55 - Gap
        Key_None,       //KC_OEM_102     = 0x56,    // < > | on UK/Germany keyboards
        Key_F11,        //KC_F11         = 0x57,
        Key_F12,        //KC_F12         = 0x58,
        Key_None,       // 0x59 - Gap
        Key_None,       // 0x5A - Gap
        Key_None,       // 0x5B - Gap
        Key_None,       // 0x5C - Gap
        Key_None,       // 0x5D - Gap
        Key_None,       // 0x5E - Gap
        Key_None,       // 0x5F - Gap
        Key_None,       // 0x60 - Gap
        Key_None,       // 0x61 - Gap
        Key_None,       // 0x62 - Gap
        Key_None,       // 0x63 - Gap
        Key_F13,        //KC_F13         = 0x64,    //                     (NEC PC98)
        Key_F14,        //KC_F14         = 0x65,    //                     (NEC PC98)
        Key_F15,        //KC_F15         = 0x66,    //                     (NEC PC98)
        Key_None,       // 0x67 - Gap
        Key_None,       // 0x68 - Gap
        Key_None,       // 0x69 - Gap
        Key_None,       // 0x6A - Gap
        Key_None,       // 0x6B - Gap
        Key_None,       // 0x6C - Gap
        Key_None,       // 0x6D - Gap
        Key_None,       // 0x6E - Gap
        Key_None,       // 0x6F - Gap
        Key_None,       //KC_KANA        = 0x70,    // (Japanese keyboard)
        Key_None,       // 0x71 - Gap
        Key_None,       // 0x72 - Gap
        Key_None,       //KC_ABNT_C1     = 0x73,    // / ? on Portugese (Brazilian) keyboards
        Key_None,       // 0x74 - Gap
        Key_None,       // 0x75 - Gap
        Key_None,       // 0x76 - Gap
        Key_None,       // 0x77 - Gap
        Key_None,       // 0x78 - Gap
        Key_None,       //KC_CONVERT     = 0x79,    // (Japanese keyboard)
        Key_None,       // 0x7A - Gap
        Key_None,       //KC_NOCONVERT   = 0x7B,    // (Japanese keyboard)
        Key_None,       // 0x7C - Gap
        Key_None,       //KC_YEN         = 0x7D,    // (Japanese keyboard)
        Key_None,       //KC_ABNT_C2     = 0x7E,    // Numpad . on Portugese (Brazilian) keyboards
        Key_None,       // 0x7F - Gap
        Key_None,       // 0x80 - Gap
        Key_None,       // 0x81 - Gap
        Key_None,       // 0x82 - Gap
        Key_None,       // 0x83 - Gap
        Key_None,       // 0x84 - Gap
        Key_None,       // 0x85 - Gap
        Key_None,       // 0x86 - Gap
        Key_None,       // 0x87 - Gap
        Key_None,       // 0x88 - Gap
        Key_None,       // 0x89 - Gap
        Key_None,       // 0x8A - Gap
        Key_None,       // 0x8B - Gap
        Key_None,       // 0x8C - Gap
        Key_None,       //KC_NUMPADEQUALS= 0x8D,    // = on numeric keypad (NEC PC98)
        Key_None,       // 0x8E - Gap
        Key_None,       // 0x8F - Gap
        Key_None,       //KC_PREVTRACK   = 0x90,    // Previous Track (KC_CIRCUMFLEX on Japanese keyboard)
        Key_None,       //KC_AT          = 0x91,    //                     (NEC PC98)
        Key_None,       //KC_COLON       = 0x92,    //                     (NEC PC98)
        Key_None,       //KC_UNDERLINE   = 0x93,    //                     (NEC PC98)
        Key_None,       //KC_KANJI       = 0x94,    // (Japanese keyboard)
        Key_None,       //KC_STOP        = 0x95,    //                     (NEC PC98)
        Key_None,       //KC_AX          = 0x96,    //                     (Japan AX)
        Key_None,       //KC_UNLABELED   = 0x97,    //                        (J3100)
        Key_None,       // 0x98 - Gap
        Key_None,       //KC_NEXTTRACK   = 0x99,    // Next Track
        Key_None,       // 0x9A - Gap
        Key_None,       // 0x9B - Gap
        Key_None,       //KC_NUMPADENTER = 0x9C,    // Enter on numeric keypad
        Key_Control,    //KC_RCONTROL    = 0x9D,
        Key_None,       // 0x9E - Gap
        Key_None,       // 0x9F - Gap
        Key_None,       //KC_MUTE        = 0xA0,    // Mute
        Key_None,       //KC_CALCULATOR  = 0xA1,    // Calculator
        Key_None,       //KC_PLAYPAUSE   = 0xA2,    // Play / Pause
        Key_None,       // 0xA3 - Gap
        Key_None,       //KC_MEDIASTOP   = 0xA4,    // Media Stop
        Key_None,       // 0xA5 - Gap
        Key_None,       // 0xA6 - Gap
        Key_None,       // 0xA7 - Gap
        Key_None,       // 0xA8 - Gap
        Key_None,       // 0xA9 - Gap
        Key_None,       // 0xAA - Gap
        Key_None,       // 0xAB - Gap
        Key_None,       // 0xAC - Gap
        Key_None,       // 0xAD - Gap
        Key_None,       //KC_VOLUMEDOWN  = 0xAE,    // Volume -
        Key_None,       // 0xAF - Gap
        Key_None,       //KC_VOLUMEUP    = 0xB0,    // Volume +
        Key_None,       // 0xB1 - Gap
        Key_None,       //KC_WEBHOME     = 0xB2,    // Web home
        Key_None,       //KC_NUMPADCOMMA = 0xB3,    // , on numeric keypad (NEC PC98)
        Key_None,       // 0xB4 - Gap
        Key_Divide,     //KC_DIVIDE      = 0xB5,    // / on numeric keypad
        Key_None,       // 0xB6 - Gap
        Key_None,       //KC_SYSRQ       = 0xB7,
        Key_Alt,        //KC_RMENU       = 0xB8,    // right Alt
        Key_None,       // 0xB9 - Gap
        Key_None,       // 0xBA - Gap
        Key_None,       // 0xBB - Gap
        Key_None,       // 0xBC - Gap
        Key_None,       // 0xBD - Gap
        Key_None,       // 0xBE - Gap
        Key_None,       // 0xBF - Gap
        Key_None,       // 0xC0 - Gap
        Key_None,       // 0xC1 - Gap
        Key_None,       // 0xC2 - Gap
        Key_None,       // 0xC3 - Gap
        Key_None,       // 0xC4 - Gap
        Key_Pause,      //KC_PAUSE       = 0xC5,    // Pause
        Key_None,       // 0xC6 - Gap
        Key_Home,       //KC_HOME        = 0xC7,    // Home on arrow keypad
        Key_Up,         //KC_UP          = 0xC8,    // UpArrow on arrow keypad
        Key_None,       //KC_PGUP        = 0xC9,    // PgUp on arrow keypad
        Key_None,       // 0xCA - Gap
        Key_Left,       //KC_LEFT        = 0xCB,    // LeftArrow on arrow keypad
        Key_None,       // 0xCC - Gap
        Key_Right,      //KC_RIGHT       = 0xCD,    // RightArrow on arrow keypad
        Key_None,       // 0xCE - Gap
        Key_End,        //KC_END         = 0xCF,    // End on arrow keypad
        Key_Down,       //KC_DOWN        = 0xD0,    // DownArrow on arrow keypad
        Key_None,       //KC_PGDOWN      = 0xD1,    // PgDn on arrow keypad
        Key_Insert,     //KC_INSERT      = 0xD2,    // Insert on arrow keypad
        Key_Delete,     //KC_DELETE      = 0xD3,    // Delete on arrow keypad
        Key_None,       // 0xD4 - Gap
        Key_None,       // 0xD5 - Gap
        Key_None,       // 0xD6 - Gap
        Key_None,       // 0xD7 - Gap
        Key_None,       // 0xD8 - Gap
        Key_None,       // 0xD9 - Gap
        Key_None,       // 0xDA - Gap
        Key_None,       //KC_LWIN        = 0xDB,    // Left Windows key
        Key_None,       //KC_RWIN        = 0xDC,    // Right Windows key
        Key_None,       //KC_APPS        = 0xDD,    // AppMenu key
        Key_None,       //KC_POWER       = 0xDE,    // System Power
        Key_None,       //KC_SLEEP       = 0xDF,    // System Sleep
        Key_None,       // 0xE0 - Gap
        Key_None,       // 0xE1 - Gap
        Key_None,       // 0xE2 - Gap
        Key_None,       //KC_WAKE        = 0xE3,    // System Wake
        Key_None,       // 0xE4 - Gap
        Key_None,       //KC_WEBSEARCH   = 0xE5,    // Web Search
        Key_None,       //KC_WEBFAVORITES= 0xE6,    // Web Favorites
        Key_None,       //KC_WEBREFRESH  = 0xE7,    // Web Refresh
        Key_None,       //KC_WEBSTOP     = 0xE8,    // Web Stop
        Key_None,       //KC_WEBFORWARD  = 0xE9,    // Web Forward
        Key_None,       //KC_WEBBACK     = 0xEA,    // Web Back
        Key_None,       //KC_MYCOMPUTER  = 0xEB,    // My Computer
        Key_None,       //KC_MAIL        = 0xEC,    // Mail
        Key_None        //KC_MEDIASELECT = 0xED     // Media Select
    };


    ////////////////////////////////////////////////////////////////////////////////////////////////////
    IDirect3DDevice9* gD3D9Device = 0;
    IDirect3DStateBlock9* gStateBlock = 0;
    IDirect3DSurface9* gRenderTarget = 0;
    IDirect3DSurface9* gDepthBuffer = 0;

    NsVector< Ptr<IRenderer> > gRenderers;

    struct RendererInfo
    {
        RenderCommands commands;
    };

    NsMap<IRenderer*, RendererInfo> gRenderersInfo;


    ////////////////////////////////////////////////////////////////////////////////////////////////////
    void NoesisErrorHandler(const NsChar* filename, NsInt line, const NsChar* desc)
    {
        throw std::exception(desc);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    class Listener: public Ogre::RenderSystem::Listener
    {
        void eventOccurred(const Ogre::String& eventName, const Ogre::NameValuePairList* parameters)
        {
            if (eventName == "DeviceLost")
            {
                if (gD3D9Device != 0 && gStateBlock != 0)
                {
                    if (gStateBlock != 0)
                    {
                        gStateBlock->Release();
                        gStateBlock = 0;
                    }

                    Noesis::GUI::OnLostDevice();
                }
            }
            else if(eventName == "DeviceRestored")
            {
                if (gD3D9Device != 0 && gStateBlock == 0)
                {
                    Noesis::GUI::OnResetDevice();
                    gD3D9Device->CreateStateBlock(D3DSBT_ALL, &gStateBlock);
                }
            }
        }
    } gListener;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    void InitDX9()
    {
        Ogre::RenderWindow* pWnd = Ogre::Root::getSingleton().getAutoCreatedWindow();
        if (pWnd != 0)
        {
            pWnd->getCustomAttribute("D3DDEVICE", &gD3D9Device);
        }
        else
        {
            NoesisErrorHandler("", 0, "No Autocreated RenderWindow found!");
        }

        gD3D9Device->CreateStateBlock(D3DSBT_ALL, &gStateBlock);
        Noesis::GUI::InitDirectX9(gD3D9Device, NoesisErrorHandler);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
#include <GL/GL.h>
#include <glext.h>

#pragma comment(lib, "opengl32.lib")

    PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer;
    PFNGLBINDBUFFERPROC glBindBuffer;
    PFNGLACTIVETEXTUREPROC glActiveTexture;
    PFNGLUSEPROGRAMPROC glUseProgram;
    PFNGLGETVERTEXATTRIBIVPROC glGetVertexAttribiv;
    PFNGLENABLEVERTEXATTRIBARRAYARBPROC glEnableVertexAttribArray;
    PFNGLDISABLEVERTEXATTRIBARRAYARBPROC glDisableVertexAttribArray;
    PFNGLBLENDEQUATIONPROC glBlendEquation;
    PFNGLBINDVERTEXARRAYPROC glBindVertexArray;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    void InitGL()
    {
#define GL_IMPORT(_proto, _func) \
        { \
        _func = (_proto)wglGetProcAddress(#_func); \
        if (_func == NULL) \
        { \
        NS_ERROR("wglGetProcAddress %s", #_func); \
    } \
    }

        GL_IMPORT(PFNGLBINDFRAMEBUFFERPROC, glBindFramebuffer);
        GL_IMPORT(PFNGLBINDBUFFERPROC, glBindBuffer);
        GL_IMPORT(PFNGLACTIVETEXTUREPROC, glActiveTexture);
        GL_IMPORT(PFNGLUSEPROGRAMPROC, glUseProgram);
        GL_IMPORT(PFNGLGETVERTEXATTRIBIVPROC, glGetVertexAttribiv);
        GL_IMPORT(PFNGLENABLEVERTEXATTRIBARRAYARBPROC, glEnableVertexAttribArray);
        GL_IMPORT(PFNGLDISABLEVERTEXATTRIBARRAYARBPROC, glDisableVertexAttribArray);
        GL_IMPORT(PFNGLBLENDEQUATIONPROC, glBlendEquation);
        GL_IMPORT(PFNGLBINDVERTEXARRAYPROC, glBindVertexArray);

        Noesis::GUI::InitOpenGL(NoesisErrorHandler);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    void StoreRenderStateDX9()
    {
        if (gStateBlock != 0)
        {
            gD3D9Device->GetRenderTarget(0, &gRenderTarget);
            if (gRenderTarget != 0)
            {
                gRenderTarget->Release();
            }

            gD3D9Device->GetDepthStencilSurface(&gDepthBuffer);
            if (gDepthBuffer != 0)
            {
                gDepthBuffer->Release();
            }

            gStateBlock->Capture();
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    void RestoreRenderStateDX9()
    {
        if (gStateBlock != 0)
        {
            gD3D9Device->SetRenderTarget(0, gRenderTarget);
            gD3D9Device->SetDepthStencilSurface(gDepthBuffer);
            gStateBlock->Apply();
        }
    }

    struct RenderStates
    {
        int             frameBuffer;
        int             viewport[4];
        float           clearColors[4];
        float           clearDepth;
        int             clearStencil;
        unsigned char   alphaTest;
        unsigned char   depthTest;
        unsigned char   depthWrite;
        int             depthFunc;
        unsigned char   stencilTest;
        int             stencilTestFailOp;
        int             stencilTestSPDF;
        int             stencilTestSPDP;
        int             stencilFunc;
        int             stencilRef;
        unsigned int    stencilMask;
        unsigned int    stencilWriteMask;
        unsigned char   scissorTest;
        unsigned char   cullFaceEnabled;
        int             cullFaceMode;
        unsigned char   dither;
        unsigned char   sampleAlphaToCoverage;
        unsigned char   sampleCoverage;
        unsigned char   blendEnabled;
        int             blendEquation;
        int             blendSource;
        int             blendDestination;
        unsigned char   colorWriteMask[4];
        unsigned int    arrayBuffer;
        int             vertexAttribsEnabled[6];
        int             activeTexture;
        unsigned int    elementArrayBuffer;
        unsigned int    vertexArrayBuffer;
        int             boundTexture[4];
        int             currentProgram;
        int             unpackAlignment;
    }
    gRenderStates;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    void StoreRenderStateGL()
    {
        glGetIntegerv(GL_UNPACK_ALIGNMENT, &gRenderStates.unpackAlignment);
        glGetIntegerv(GL_FRAMEBUFFER_BINDING, &gRenderStates.frameBuffer);
        glGetIntegerv(GL_VIEWPORT, gRenderStates.viewport);

        glGetFloatv(GL_COLOR_CLEAR_VALUE, gRenderStates.clearColors);
        glGetFloatv(GL_DEPTH_CLEAR_VALUE, &gRenderStates.clearDepth);
        glGetIntegerv(GL_STENCIL_CLEAR_VALUE, &gRenderStates.clearStencil);

        glGetBooleanv(GL_COLOR_WRITEMASK, gRenderStates.colorWriteMask);

        gRenderStates.dither = glIsEnabled(GL_DITHER);
        gRenderStates.sampleAlphaToCoverage = glIsEnabled(GL_SAMPLE_ALPHA_TO_COVERAGE);
        gRenderStates.sampleCoverage = glIsEnabled(GL_SAMPLE_COVERAGE);
        gRenderStates.alphaTest = glIsEnabled(GL_ALPHA_TEST);
        gRenderStates.depthTest = glIsEnabled(GL_DEPTH_TEST);
        glGetBooleanv(GL_DEPTH_WRITEMASK, &gRenderStates.depthWrite);
        glGetIntegerv(GL_DEPTH_FUNC, &gRenderStates.depthFunc);

        gRenderStates.stencilTest = glIsEnabled(GL_STENCIL_TEST);
        glGetIntegerv(GL_STENCIL_FAIL, &gRenderStates.stencilTestFailOp);
        glGetIntegerv(GL_STENCIL_PASS_DEPTH_FAIL, &gRenderStates.stencilTestSPDF);
        glGetIntegerv(GL_STENCIL_PASS_DEPTH_PASS, &gRenderStates.stencilTestSPDP);
        glGetIntegerv(GL_STENCIL_FUNC, &gRenderStates.stencilFunc);
        glGetIntegerv(GL_STENCIL_REF, &gRenderStates.stencilRef);
        glGetIntegerv(GL_STENCIL_VALUE_MASK, (int*)&gRenderStates.stencilMask);
        glGetIntegerv(GL_STENCIL_WRITEMASK, (int*)&gRenderStates.stencilWriteMask);

        gRenderStates.scissorTest = glIsEnabled(GL_SCISSOR_TEST);
        gRenderStates.cullFaceEnabled = glIsEnabled(GL_CULL_FACE);
        glGetIntegerv(GL_CULL_FACE_MODE, &gRenderStates.cullFaceMode);

        gRenderStates.blendEnabled = glIsEnabled(GL_BLEND);
        glGetIntegerv(GL_BLEND_EQUATION_RGB, &gRenderStates.blendEquation);
        glGetIntegerv(GL_BLEND_SRC_RGB, &gRenderStates.blendSource);
        glGetIntegerv(GL_BLEND_DST_RGB, &gRenderStates.blendDestination);

        glGetIntegerv(GL_ACTIVE_TEXTURE, &gRenderStates.activeTexture);

        for (NsSize i = 0; i < 4; i++)
        {
            glActiveTexture(GL_TEXTURE0 + i);
            glGetIntegerv(GL_TEXTURE_BINDING_2D, &(gRenderStates.boundTexture[i]));
        }

        glGetIntegerv(GL_CURRENT_PROGRAM, &gRenderStates.currentProgram);

        glGetIntegerv(GL_ARRAY_BUFFER_BINDING, (int*)&gRenderStates.arrayBuffer);
        for (NsSize i = 0; i < 6; i++)
        {
            glGetVertexAttribiv(i, GL_VERTEX_ATTRIB_ARRAY_ENABLED, 
                &(gRenderStates.vertexAttribsEnabled[i]));
        }

        glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, (int*)&gRenderStates.elementArrayBuffer);
        glGetIntegerv(GL_VERTEX_ARRAY_BINDING, (int*)&gRenderStates.vertexArrayBuffer);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    void RestoreRenderStateGL()
    {   
        glPixelStorei(GL_UNPACK_ALIGNMENT, gRenderStates.unpackAlignment);
        glBindFramebuffer(GL_FRAMEBUFFER, gRenderStates.frameBuffer);  
        glViewport(gRenderStates.viewport[0], gRenderStates.viewport[1], gRenderStates.viewport[2],
            gRenderStates.viewport[3]);

        glClearColor(gRenderStates.clearColors[0], gRenderStates.clearColors[1],
            gRenderStates.clearColors[2], gRenderStates.clearColors[3]);
        glClearDepth(gRenderStates.clearDepth);
        glClearStencil(gRenderStates.clearStencil);

        glColorMask(gRenderStates.colorWriteMask[0], gRenderStates.colorWriteMask[1],
            gRenderStates.colorWriteMask[2], gRenderStates.colorWriteMask[3]);

        gRenderStates.dither ? glEnable(GL_DITHER) : glDisable(GL_DITHER);
        gRenderStates.sampleAlphaToCoverage ? glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE) :
            glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
        gRenderStates.sampleCoverage ? glEnable(GL_SAMPLE_COVERAGE) : glDisable(GL_SAMPLE_COVERAGE);

        gRenderStates.alphaTest ? glEnable(GL_ALPHA_TEST) : glDisable(GL_ALPHA_TEST);
        gRenderStates.depthTest ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
        glDepthMask(gRenderStates.depthWrite);
        glDepthFunc(gRenderStates.depthFunc);

        gRenderStates.stencilTest ? glEnable(GL_STENCIL_TEST) : glDisable(GL_STENCIL_TEST);
        glStencilOp(gRenderStates.stencilTestFailOp, gRenderStates.stencilTestSPDF,
            gRenderStates.stencilTestSPDP);
        glStencilFunc(gRenderStates.stencilFunc, gRenderStates.stencilRef, gRenderStates.stencilMask);
        glStencilMask(gRenderStates.stencilWriteMask);

        gRenderStates.scissorTest ? glEnable(GL_SCISSOR_TEST) : glDisable(GL_SCISSOR_TEST);
        gRenderStates.cullFaceEnabled ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE);
        glCullFace(gRenderStates.cullFaceMode);

        gRenderStates.blendEnabled ? glEnable(GL_BLEND) : glDisable(GL_BLEND);
        glBlendEquation(gRenderStates.blendEquation);
        glBlendFunc(gRenderStates.blendSource, gRenderStates.blendDestination);

        for (NsSize i = 0; i < 4; i++)
        {
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, gRenderStates.boundTexture[i]);
        }

        glActiveTexture(gRenderStates.activeTexture);

        glUseProgram(gRenderStates.currentProgram);


        glBindVertexArray(gRenderStates.vertexArrayBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, gRenderStates.arrayBuffer);
        for (NsSize i = 0; i < 6; i++)
        {
            gRenderStates.vertexAttribsEnabled[i] ? 
                glEnableVertexAttribArray(i) : glDisableVertexAttribArray(i);
        }

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gRenderStates.elementArrayBuffer);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    void StoreRenderState()
    {
        if (gD3D9Device != 0)
        {
            StoreRenderStateDX9();
        }
        else
        {
            StoreRenderStateGL();
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    void RestoreRenderState()
    {
        if (gD3D9Device != 0)
        {
            RestoreRenderStateDX9();
        }
        else
        {
            RestoreRenderStateGL();
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    bool IsDeviceLost()
    {
        return (gD3D9Device != 0 && gStateBlock == 0);
    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" void Noesis_Init()
{
    Ogre::Root::getSingletonPtr()->getRenderSystem()->addListener(&gListener);

    Ogre::RenderSystem* renderSystem = Ogre::Root::getSingletonPtr()->getRenderSystem();
    if (renderSystem->getName() == "Direct3D9 Rendering Subsystem")
    {
        InitDX9();
        Ptr<OgreNsGuiResourceProvider> provider = *new OgreNsGuiResourceProvider("DX9");
        Noesis::GUI::AddResourceProvider(provider.GetPtr());
    }
    else if (renderSystem->getName() == "OpenGL Rendering Subsystem")
    {
        InitGL();
        Ptr<OgreNsGuiResourceProvider> provider = *new OgreNsGuiResourceProvider("GL");
        Noesis::GUI::AddResourceProvider(provider.GetPtr());
    }
    else
    {
        NS_ERROR("%s not supported", renderSystem->getName().c_str());
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" void Noesis_Shutdown()
{
    if (gD3D9Device != 0)
    {
        if (gStateBlock != 0)
        {
            gStateBlock->Release();
            gStateBlock = 0;
        }
    }

    gRenderers.set_capacity(0);
    gRenderersInfo.clear();

    Noesis::GUI::Shutdown();

    Ogre::Root::getSingletonPtr()->getRenderSystem()->removeListener(&gListener);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" void Noesis_Tick()
{
    Noesis::GUI::Tick();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" void Noesis_LoadXAML(void** root, void** uiRenderer, const char* xamlFile,
    const char* resourcesFile)
{
    Ptr<FrameworkElement> element = Noesis::GUI::LoadXaml<FrameworkElement>(xamlFile);

    if (!String::IsNullOrEmpty(resourcesFile))
    {
        Ptr<ResourceDictionary> resources = Noesis::GUI::LoadXaml<ResourceDictionary>(resourcesFile);
        element->GetResources()->GetMergedDictionaries()->Add(resources.GetPtr());
    }

    Ptr<IRenderer> renderer = Noesis::GUI::CreateRenderer(element.GetPtr());
    {
        gRenderers.push_back(renderer);
        gRenderersInfo.insert(nstl::make_pair_ref(renderer.GetPtr(), RendererInfo()));
    }

    *root = element.GetPtr();
    *uiRenderer = renderer.GetPtr();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" void Noesis_RendererAntialiasingMode(void* uiRenderer, int mode)
{
    IRenderer* renderer = static_cast<IRenderer*>(uiRenderer);
    renderer->SetAntialiasingMode((AntialiasingMode)mode);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" void Noesis_RendererTessMode(void* uiRenderer, int mode)
{
    IRenderer* renderer = static_cast<IRenderer*>(uiRenderer);
    renderer->SetTessellationMode((TessellationMode)mode);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" void Noesis_RendererTessQuality(void* uiRenderer, int quality)
{
    IRenderer* renderer = static_cast<IRenderer*>(uiRenderer);
    renderer->SetTessellationQuality((TessellationQuality)quality);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" void Noesis_RendererFlags(void* uiRenderer, int flags)
{
    IRenderer* renderer = static_cast<IRenderer*>(uiRenderer);
    renderer->SetFlags((NsUInt32)flags);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" void Noesis_Update(void* uiRenderer, double time, int width, int height)
{
    IRenderer* renderer = static_cast<IRenderer*>(uiRenderer);
    renderer->SetSize(width, height);
    renderer->Update(time);
    RendererInfo& ri = gRenderersInfo[renderer];
    ri.commands = renderer->WaitForUpdate();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" void Noesis_GPURenderOffscreen(void* uiRenderer)
{
    if (!IsDeviceLost())
    {
        IRenderer* renderer = static_cast<IRenderer*>(uiRenderer);
        RendererInfo& ri = gRenderersInfo[renderer];

        StoreRenderState();
        renderer->Render(ri.commands.offscreenCommands.GetPtr());
        RestoreRenderState();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" void Noesis_GPURender(void* uiRenderer)
{
    if (!IsDeviceLost())
    {
        IRenderer* renderer = static_cast<IRenderer*>(uiRenderer);
        RendererInfo& ri = gRenderersInfo[renderer];

        StoreRenderState();
        renderer->Render(ri.commands.commands.GetPtr());
        RestoreRenderState();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" bool Noesis_HitTest(void* root, float x, float y)
{
    Visual* visual = static_cast<Visual*>(root);
    Drawing::Point point(x, y);
    return VisualTreeHelper::HitTest(visual, point).visualHit != 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" void Noesis_MouseButtonDown(void* uiRenderer, float x, float y,
    int button)
{
    IRenderer* renderer = static_cast<IRenderer*>(uiRenderer);
    renderer->MouseButtonDown((NsInt)x, (NsInt)y, static_cast<MouseButton>(button));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" void Noesis_MouseButtonUp(void* uiRenderer, float x, float y, int button)
{
    IRenderer* renderer = static_cast<IRenderer*>(uiRenderer);
    renderer->MouseButtonUp((NsInt)x, (NsInt)y, static_cast<MouseButton>(button));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" void Noesis_MouseDoubleClick(void* uiRenderer, float x, float y,
    int button)
{
    IRenderer* renderer = static_cast<IRenderer*>(uiRenderer);
    renderer->MouseDoubleClick((NsInt)x, (NsInt)y, static_cast<MouseButton>(button));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" void Noesis_MouseMove(void* uiRenderer, float x, float y)
{
    IRenderer* renderer = static_cast<IRenderer*>(uiRenderer);
    renderer->MouseMove((NsInt)x, (NsInt)y);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" void Noesis_MouseWheel(void* uiRenderer, float x, float y,
    int wheelRotation)
{
    IRenderer* renderer = static_cast<IRenderer*>(uiRenderer);
    renderer->MouseWheel((NsInt)x, (NsInt)y, wheelRotation);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" void Noesis_KeyDown(void* uiRenderer, int key)
{
    IRenderer* renderer = static_cast<IRenderer*>(uiRenderer);

    Keyboard* keyboard = renderer->GetContent()->GetKeyboard();
    assert(keyboard != 0);

    NsUInt32 keyModifiers = keyboard->GetModifiers();
    NsBool isCtrlPressed = (keyModifiers & ModifierKeys_Control) != 0;
    NsBool isShiftPressed = (keyModifiers & ModifierKeys_Shift) != 0;

    Key nsKey = s_OISKeyMappings[key];
    renderer->KeyDown(nsKey);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" void Noesis_KeyUp(void* uiRenderer, int key)
{
    IRenderer* renderer = static_cast<IRenderer*>(uiRenderer);
    Key nsKey = s_OISKeyMappings[key];
    renderer->KeyUp(nsKey);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" void Noesis_Char(void* uiRenderer, int ch)
{
    IRenderer* renderer = static_cast<IRenderer*>(uiRenderer);
    renderer->Char(ch);
}

