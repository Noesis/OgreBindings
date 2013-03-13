// Project Include
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "Sample.h"

int main( int argc, const char* argv[] ) {	
	try
	{
		Sample sample;
		sample.setupEngine();
		sample.setupScene();
		sample.startMainLoop();
	}
	catch (std::exception& e)
	{
		MessageBox(NULL, e.what(), "Exception...", MB_ICONERROR | MB_OK);
	}
	return 0;
}
