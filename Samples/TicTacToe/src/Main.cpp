#include "pch.h"
#include "Sample.h"

int main( int argc, const char* argv[] ) {	
	try
	{
		Sample sample;
		sample.setupEngine();
		sample.setupScene();
		sample.startMainLoop();
        sample.Close();
	}
	catch (std::exception& e)
	{
		MessageBox(NULL, e.what(), "Exception...", MB_ICONERROR | MB_OK);
	}
	return 0;
}
