#include "GlutCgWindow.h"
#include <iostream>
#include <assert.h>
#include <Cg/cgGL.h>

CGcontext CGlutCgWindow::s_CgContext = 0;
CGprofile CGlutCgWindow::s_vertexProfile = CG_PROFILE_UNKNOWN;
CGprofile CGlutCgWindow::s_fragmentProfile = CG_PROFILE_UNKNOWN;

static void handleCgError() 
{
    fprintf(stderr, "Cg error: %s\n", cgGetErrorString(cgGetError()));
}

CGlutCgWindow::CGlutCgWindow(void)
{
	s_fragmentProfile = s_vertexProfile = CG_PROFILE_UNKNOWN;
	initializeCg();
}

CGlutCgWindow::~CGlutCgWindow(void)
{
}

void
CGlutCgWindow::initializeCg() {
    
	// Basic Cg setup; register a callback function for any errors
    // and create an initial context
    cgSetErrorCallback(handleCgError);
    s_CgContext = cgCreateContext();
    
}

void CGlutCgWindow::cgRenderGeometry() {
    
}

void CGlutCgWindow::renderGeometry() {
	static bool bInit = false;
	if (false == bInit) {
		chooseProfiles();
		bInit = true;
	}
    
    // Now make sure that the vertex and fragment programs, loaded
    // in LoadCgPrograms() are bound.
	cgRenderGeometry();
    
}

void CGlutCgWindow::cgDisplayTF() {
    
}

void CGlutCgWindow::displayTF() {
    
	cgDisplayTF();
    
}

void CGlutCgWindow::chooseProfiles()
{
    // Make sure that the appropriate profiles are available on the
    // user's system.
    if (cgGLIsProfileSupported(CG_PROFILE_ARBVP1))
        s_vertexProfile = CG_PROFILE_ARBVP1;
    else {
        // try VP30
        if (cgGLIsProfileSupported(CG_PROFILE_VP30))
            s_vertexProfile = CG_PROFILE_VP30;
        else {
            fprintf(stderr, "Neither arbvp1 or vp30 vertex profiles supported on this system.\n");
            exit(1);
        }
    }
	cgGLSetOptimalOptions(s_vertexProfile);
    
    if (cgGLIsProfileSupported(CG_PROFILE_ARBFP1))
        s_fragmentProfile = CG_PROFILE_ARBFP1;
    else {
        // try FP30
        if (cgGLIsProfileSupported(CG_PROFILE_FP30))
            s_fragmentProfile = CG_PROFILE_FP30;
        else {
            fprintf(stderr, "Neither arbfp1 or fp30 fragment profiles supported on this system.\n");
            exit(1);
        }
    }
	cgGLSetOptimalOptions(s_fragmentProfile);
}
