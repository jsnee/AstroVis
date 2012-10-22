/******************************************************************************
 *******************************************************************************
 **************                                                   **************
 *******     AUTHORS - THOMAS MARRINAN, TIMOTHY URNESS, JOSEPH SNEE     ********
 **************          Date last modified - 07/22/2009          **************
 **************   edited code from real-time-volume-graphics.org  **************
 **************                                                   **************
 *******************************************************************************
 ******************************************************************************/

#include "SimpleSlicerWindow.h"
#include "Camera.h"
#include "gluiVars.h"
#include <iostream>
#include <GLUT/glut.h>
#include <GLUI/glui.h>
#include <time.h>
#include "LoadConfig.cpp"

CGlutWindow *g_pMainWindow = 0;

void display(void)                              { g_pMainWindow->renderFrame();}
void idle(void)                                 { g_pMainWindow->idle();}
void reshape(int width, int height)             { g_pMainWindow->resize(width, height);}
void keyboard(unsigned char key, int x, int y)  { g_pMainWindow->keyEvent(key,x,y);}
void mouse(int button, int state, int x, int y) { g_pMainWindow->mouseButtonEvent(button, state,x,y);}
void move(int x, int y)                         { g_pMainWindow->mouseMoveEvent(x,y);}

int main(int argc, char* argv[])
{
    
	//GLUI variables
	GLUI_Listbox *box;
    GLUI_Listbox *box2;
	GLUI_Rollout *slitview_panel;
	GLUI_RadioGroup *radio;
	GLUI_Checkbox *check;
    GLUI_Checkbox *check2;
	GLUI_Spinner *spin;
	
	//window and function set-up
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    
	g_pMainWindow = new CSimpleSlicerWindow();
    
	glutDisplayFunc(display); 
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(move);
    
    printf(getRoot("/Desktop/data/shaders/fp_emis_abs_gradlightPhong.cg\n"));
    
	//create glui window
	GLUI *glui = GLUI_Master.create_glui("Control Panel",0,0,0);
    
	//create Transfer Function Panel
	GLUI_Panel *transfer_function_panel = glui->add_panel( "Transfer Function Display" );
	//add radio button group to panel
	radio = glui->add_radiogroup_to_panel(transfer_function_panel, &m_bDisplayTF);
	glui->add_radiobutton_to_group( radio, "None" );
	glui->add_radiobutton_to_group( radio, "Left" );
	glui->add_radiobutton_to_group( radio, "Right" );
	glui->add_radiobutton_to_group( radio, "Both" );
    
	//create Drop Down Panel
	GLUI_Panel *drop_down_panel = glui->add_panel( "Volume Rendering" );
    //add option to scale the color map
    check = glui->add_checkbox_to_panel(drop_down_panel, "Scale Color Map", &scaleColorMap);
	//add rollout to panel
	box = glui->add_listbox_to_panel(drop_down_panel, "Data Set 1", &vol_data1);
	box->add_item(0,"Gaussian");
	box->add_item(1,"cylv2gridi0");
	box->add_item(2,"cylv2gridi30");
	box->add_item(3,"cylv2gridi60");
	box->add_item(4,"cylv2gridi90");
	box->add_item(5,"cylv2randi0");
    box->add_item(6,"cylv2randi30");
	box->add_item(7,"cylv2randi60");
	box->add_item(8,"cylv2randi90");
    box->add_item(9,"cylgridi0");
    box->add_item(10,"cylgridi30");
    box->add_item(11,"cylgridi60");
    box->add_item(12,"cylgridi90");
    box->add_item(13,"radgridi0");
    box->add_item(14,"radgridi30");
    box->add_item(15,"radgridi60");
    box->add_item(16,"radgridi90");
    box->add_item(17,"cylrandi0");
    box->add_item(18,"cylrandi30");
    box->add_item(19,"cylrandi60");
    box->add_item(20,"cylrandi90");
    box->add_item(21,"radrandi0");
    box->add_item(22,"radrandi30");
    box->add_item(23,"radrandi60");
    box->add_item(24,"radrandi90");
    
    
	box2 = glui->add_listbox_to_panel(drop_down_panel, "Data Set 2", &vol_data2);
	box2->add_item(0,"Gaussian");
	box2->add_item(1,"cylv2gridi0");
	box2->add_item(2,"cylv2gridi30");
	box2->add_item(3,"cylv2gridi60");
	box2->add_item(4,"cylv2gridi90");
	box2->add_item(5,"cylv2randi0");
    box2->add_item(6,"cylv2randi30");
	box2->add_item(7,"cylv2randi60");
	box2->add_item(8,"cylv2randi90");
    box2->add_item(9,"cylgridi0");
    box2->add_item(10,"cylgridi30");
    box2->add_item(11,"cylgridi60");
    box2->add_item(12,"cylgridi90");
    box2->add_item(13,"radgridi0");
    box2->add_item(14,"radgridi30");
    box2->add_item(15,"radgridi60");
    box2->add_item(16,"radgridi90");
    box2->add_item(17,"cylrandi0");
    box2->add_item(18,"cylrandi30");
    box2->add_item(19,"cylrandi60");
    box2->add_item(20,"cylrandi90");
    box2->add_item(21,"radrandi0");
    box2->add_item(22,"radrandi30");
    box2->add_item(23,"radrandi60");
    box2->add_item(24,"radrandi90");
    
	//create Checkbox Panel
	GLUI_Panel *checkbox_panel = glui->add_panel( "Display Volumes" );
	//add checkboxes to panel
	check = glui->add_checkbox_to_panel(checkbox_panel, "Volume 1", &showVol1);
	check = glui->add_checkbox_to_panel(checkbox_panel, "Volume 2", &showVol2);
    
	// Create slit viewing panel
	slitview_panel = glui->add_rollout( "Slit Viewer" , 0);
    
	//create Checkbox Panel
	GLUI_Panel *checkbox_panel2 = glui->add_panel_to_panel(slitview_panel, "Volume 1" );
	//add checkboxes to panel
	check = glui->add_checkbox_to_panel(checkbox_panel2, "Slit 1", &Vol1Slit[0]);
	check = glui->add_checkbox_to_panel(checkbox_panel2, "Slit 2", &Vol1Slit[1]);
	check = glui->add_checkbox_to_panel(checkbox_panel2, "Slit 3", &Vol1Slit[2]);
	check = glui->add_checkbox_to_panel(checkbox_panel2, "Slit 4", &Vol1Slit[3]);
	check = glui->add_checkbox_to_panel(checkbox_panel2, "Slit 5", &Vol1Slit[4]);
	check = glui->add_checkbox_to_panel(checkbox_panel2, "Slit 6", &Vol1Slit[5]);
    
	glui->add_column_to_panel(slitview_panel);
    
	//create Checkbox Panel
	GLUI_Panel *checkbox_panel3 = glui->add_panel_to_panel(slitview_panel, "Volume 2" );
	//add checkboxes to panel
	check = glui->add_checkbox_to_panel(checkbox_panel3, "Slit 1", &Vol2Slit[0]);
	check = glui->add_checkbox_to_panel(checkbox_panel3, "Slit 2", &Vol2Slit[1]);
	check = glui->add_checkbox_to_panel(checkbox_panel3, "Slit 3", &Vol2Slit[2]);
	check = glui->add_checkbox_to_panel(checkbox_panel3, "Slit 4", &Vol2Slit[3]);
	check = glui->add_checkbox_to_panel(checkbox_panel3, "Slit 5", &Vol2Slit[4]);
	check = glui->add_checkbox_to_panel(checkbox_panel3, "Slit 6", &Vol2Slit[5]);
    
	//create Transfer Function Panel
	GLUI_Panel *transfer_function_panel2 = glui->add_panel( "Transfer Function Mode" );
	//add radio button group to panel
	radio = glui->add_radiogroup_to_panel(transfer_function_panel2, &m_nMode);
	glui->add_radiobutton_to_group( radio, "Emission-Absorbtion" );
	glui->add_radiobutton_to_group( radio, "Gradient Phong" );
	glui->add_radiobutton_to_group( radio, "Show Gradient" );

	//create Transfer Function Panel
	GLUI_Panel *stereo_panel = glui->add_panel( "Stereoscopic" );
	//add checkbox to panel
	check = glui->add_checkbox_to_panel(stereo_panel, "On/Off", &isStereo);
	//add spinner to panel
	spin = glui->add_spinner_to_panel(stereo_panel, "Offset", GLUI_SPINNER_FLOAT, &stereoDistance);
	spin->set_float_limits(0.0, 0.75);
    
	//create Checkbox Panel
	GLUI_Panel *checkbox_panel6 = glui->add_panel( "Displays" );
	//add checkboxes to panel
	check = glui->add_checkbox_to_panel(checkbox_panel6, "Bounding Box", &boundBox);
    
	GLUI_Master.set_glutIdleFunc(idle);
    
	int width = glutGet( GLUT_WINDOW_WIDTH );
	int height = glutGet( GLUT_WINDOW_HEIGHT );
	camera = new Camera(
                        width, height, 2, Point3( 0, 0, 0)
                        );
    
	glutMainLoop();
    
	return 0;
}
