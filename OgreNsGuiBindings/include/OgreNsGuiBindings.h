////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_GUIWRAPPER_H__
#define __GUI_GUIWRAPPER_H__


/// Indicates that the antialising algorithm that will be used rely on the multisampling that
/// is active in the target surface, if any
static const int NsAntialiasingMode_MSAA = 0;

/// Indicates that besides the multisampling in the target surface a per-primitive algorithm
/// will be used. PPA implements antialiasing by extruding the contours of the triangles
/// smoothing them
static const int NsAntialiasingMode_PPAA = 1;

/// Tessellation is done only the first time
static const int NsTessellationMode_Once = 0;

/// Tessellates geometry always
static const int NsTessellationMode_Always = 1;

/// Tessellates geometry when scale changes by a certain factor
static const int NsTessellationMode_Threshold = 2;

/// The lowest tessellation quality for curves
static const int NsTessellationQuality_Low = 0;

/// Medium tessellation quality for curves
static const int NsTessellationQuality_Medium = 1;

/// The highest tessellation quality for curves
static const int NsTessellationQuality_High = 2;

/// Toggles wireframe mode when rendering triangles
static const int NsRendererFlags_Wireframe = 1;

/// Each batch submitted to the GPU is given a unique solid color
static const int NsRendererFlags_ColorBatches = 2;

/// Display pixel overdraw using blending layers. Different colors are used for each type
/// of triangle. Green for normal, Red for opacities and Blue for clipping masks
static const int NsRendererFlags_Overdraw = 4;

/// Inverts the render vertically. Useful when rendering to OpenGL texture frame buffers
static const int NsRendererFlags_FlipY = 8;

/// By default the stencil buffer is cleared automatically. Use this flag to avoid it
static const int NsRendererFlags_DoNotClearStencil = 16;

/// Use this flag to clear the color buffer to transparent (#00000000) before rendering
static const int NsRendererFlags_ClearColor = 32;


////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis kernel management
////////////////////////////////////////////////////////////////////////////////////////////////////
//@{
extern "C" void Noesis_Init();
extern "C" void Noesis_Shutdown();
extern "C" void Noesis_Tick();
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Loads the specified XAML file and creates a Renderer for it using the given surface
////////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" void Noesis_LoadXAML(void** root, void** uiRenderer, const char* xamlFile,
    const char* resourcesFile = 0);

////////////////////////////////////////////////////////////////////////////////////////////////////
// Modifies renderer settings
////////////////////////////////////////////////////////////////////////////////////////////////////
//@{
extern "C" void Noesis_RendererAntialiasingMode(void* uiRenderer, int mode);
extern "C" void Noesis_RendererTessMode(void* uiRenderer, int mode);
extern "C" void Noesis_RendererTessQuality(void* uiRenderer, int quality);
extern "C" void Noesis_RendererFlags(void* uiRenderer, int flags);
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Updates and renders the specified renderer
////////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" void Noesis_Update(void* uiRenderer, double time, int width, int height);
extern "C" void Noesis_GPURenderOffscreen(void* uiRenderer);
extern "C" void Noesis_GPURender(void* uiRenderer);

////////////////////////////////////////////////////////////////////////////////////////////////////
// Tests if mouse is over any UI element
////////////////////////////////////////////////////////////////////////////////////////////////////
extern "C" bool Noesis_HitTest(void* root, float x, float y);

////////////////////////////////////////////////////////////////////////////////////////////////////
// Renderer input events
////////////////////////////////////////////////////////////////////////////////////////////////////
//@{
extern "C" void Noesis_MouseButtonDown(void* uiRenderer, float x, float y, int button);
extern "C" void Noesis_MouseButtonUp(void* uiRenderer, float x, float y, int button);
extern "C" void Noesis_MouseDoubleClick(void* uiRenderer, float x, float y, int button);
extern "C" void Noesis_MouseMove(void* uiRenderer, float x, float y);
extern "C" void Noesis_MouseWheel(void* uiRenderer, float x, float y, int wheelRotation);
extern "C" void Noesis_KeyDown(void* uiRenderer, int key);
extern "C" void Noesis_KeyUp(void* uiRenderer, int key);
extern "C" void Noesis_Char(void* uiRenderer, int ch);
//@}


#endif
