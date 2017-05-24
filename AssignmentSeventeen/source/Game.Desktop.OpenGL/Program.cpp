#include "pch.h"
#include "SList.h"

void init();
void display(void);
void centerOnScreen();

int window_x;
int window_y;
int window_width = 480;
int window_height = 480;

char *window_title = "OpenGL";

int WINAPI WinMain(HINSTANCE instance, HINSTANCE previousInstance, LPSTR commandLine, int showCommand)
{
	UNREFERENCED_PARAMETER(instance);
	UNREFERENCED_PARAMETER(previousInstance);
	UNREFERENCED_PARAMETER(commandLine);
	UNREFERENCED_PARAMETER(showCommand);

	FieaGameEngine::SList<int> defaultList;

	//connects to the windowing system & creates a window with the specified dimensions & position, sets the display mode, & specifies window title
	glutInit(&__argc, __argv);
	centerOnScreen();
	glutInitWindowSize(window_width, window_height);
	glutInitWindowPosition(window_x, window_y);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutCreateWindow(window_title);

	init();

	glutDisplayFunc(display);

	glutMainLoop();
	}

	void init()
	{
		glClearColor(0.0, 0.0, 0.0, 0.0);
	}

	void display(void)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glutSwapBuffers();
	}

	void centerOnScreen()
	{
		window_x = (glutGet(GLUT_SCREEN_WIDTH) - window_width) / 2;
		window_y = (glutGet(GLUT_SCREEN_HEIGHT) - window_height) / 2;
	}