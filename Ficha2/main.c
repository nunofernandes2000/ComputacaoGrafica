#include "form.h"
#include <stdlib.h>
#include <time.h>
#include <GL/glut.h>
#include <stdio.h>
#include "DBForms.h"


int counter = 0;

int windowX = 500;
int windowY = 500;

int drawArea = 60;

// state variable
int type = RECTANGLE;


// color state variables
float rState = 1.0;// initial color state
float gState = 1.0;// initial color state
float bState = 1.0;// initial color state
float deltaColor = 0.1; // increment for color change


//Form tempForm = NULL; // temporary form to be drawn while creating a form



int creatingForm = 0; // flag to indicate that we are creating a form --> 0 = false, 1 = true

Form selectedForm = NULL; // selected form to be moved

//FeedBack
Form activeColor;


// Save click past position --> ultima posição do click
int xLastClick = 0;
int yLastClick = 0;



//Color Palette
Form *palette;
int nPaletteColors;


// insert a random form in the database
void insertRandomForm(int x, int y) {
    Form f = createFormCLICK(type, x, y, windowX);
    setBackgroundColor(f, rState, gState, bState);
    if (!insertBDForm(f)) {
        printf("MEMORY FULL!!!\n");
        deleteForm(f);
    }
    else
        glutPostRedisplay();
}


// delete a form from the database
void deleteSomeForm(int x, int y) {
    Form f = pickDBForm(x, y);
    if (f != NULL) {
        printfForm(f);
        deleteFormDB(f);
        glutPostRedisplay();
    }
    else
        printf("No Form...\n");
}



// check if the mouse click is in the color palette
void mymouseTools(GLint button, GLint state, GLint x, GLint y) {
    int i;
    float color[3];

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        for (i = 0; i < nPaletteColors; i++) {
            if (pick(x, y, palette[i])) {
                getBGColor(palette[i], color);
                rState = color[0];
                gState = color[1];
                bState = color[2];
                setBackgroundColor(activeColor, rState, gState, bState);
                glutPostRedisplay();
                break;
            }
        }
    }
}


// check if the mouse click is in the canvas
void mymouseCanvas(GLint button, GLint state, GLint x, GLint y) {

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        printf("-> LEFT button pressed!\n");
/* Old vertion - create form on the second click
		if (type == RECTANGLE) {
			// ---> Example for creating fors with 2 clicks <---
			if (creatingForm) {
				Form f = newRectangle2Point(xLastClick, yLastClick, x, y);
				setBackgroundColor(f, rState, gState, bState);
				if (!insertDBForm(f)) {
					printf("MEMORY FULL!!!\n");
					deleteForm(f);
				}
				else
					glutPostRedisplay();
				creatingForm = 0;
			}
			else {
				xLastClick = x;
				yLastClick = y;
				creatingForm = 1;
			}
		}
		*/

        if (type == RECTANGLE) {
            if (creatingForm) {  // second click
                change2Point(selectedForm, x, y);
                creatingForm = 0;
                selectedForm = NULL;
                glutPostRedisplay();
            }
            else {  // first click
                selectedForm = newRectangle2Point(x, y, x, y);
                setBackgroundColor(selectedForm, rState, gState, bState);
                if (!insertBDForm(selectedForm)) {
                    printf("MEMORY FULL!!!\n");
                    deleteForm(selectedForm);
                    selectedForm = NULL;
                }
                else {
                    creatingForm = 1;
                    glutPostRedisplay();
                }
            }
        }
        else

            insertRandomForm(x, y);
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        printf("-> RIGHT button pressed!\n");
        deleteSomeForm(x, y);
    }


}




void mymouse(GLint button, GLint state, GLint x, GLint y) {
    y = windowY - y;

    if (y > windowY - drawArea) { // Adjusted to check the top 40 pixels
        mymouseTools(button, state, x, y);
    } else {
        mymouseCanvas(button, state, x, y);
    }
}


/*// Add the motion callback function ---> pergunta 7 da ficha 4
void mymotion(int x, int y) {
    y = windowY - y;

    if (creatingForm) {
        if (tempForm != NULL) {
            deleteForm(tempForm);
        }
        tempForm = newRectangle2Point(xLastClick, yLastClick, x, y);
        setBackgroundColor(tempForm, 1.0, 0.0, 0.0); // Set color to red
        glutPostRedisplay();
    }
}*/


// Callback function called when a key is pressed
void mykeyboard(unsigned char key, int x, int y)
{
    Form f;

    y = windowY - y;

    if (key == 'Q' | key == 'q')
        exit(0);

    switch (key) {
        case 'r':
        case 'R':
            type = RECTANGLE; break;
        case 't':
        case 'T':
            type = TRIANGLE_ISO; break;
        case 's':
        case 'S':
            type = SQUARE; break;
        case 'e':
        case 'E':
            type = EQUILATERAL_TRIANGLE; break;
        case 'h':
        case 'H':
            type = HEXAGON; break;
        case 'c':
        case 'C':
            type = CIRCUMFERENCE; break;
        case '1' :
            rState += deltaColor;
            if (rState > 1.0) rState = 1.0;
            break;
        case '2':
            gState += deltaColor;
            if (gState > 1.0) gState = 1.0;
            break;
        case '3':
            bState += deltaColor;
            if (bState > 1.0) bState = 1.0;
            break;

        case '4':
            rState -= deltaColor;
            if (rState < 0.0) rState = 0.0;
            break;
        case '5':
            gState -= deltaColor;
            if (gState < 0.0) gState = 0.0;
            break;
        case '6':
            bState -= deltaColor;
            if (bState < 0.0) bState = 0.0;
            break;

        case 'i':
        case 'I':
            insertRandomForm(x, y);
            break;
        case 'd':
        case 'D':
            deleteSomeForm(x, y);
            break;

    }
    setBackgroundColor(activeColor, rState, gState, bState);
    glutPostRedisplay();
}


void mouseMotion(int x, int y) {
    y = windowY - y;

    printf("Moving pressing some button... (%i, %i)\n", x, y);

}

//TODO:temos de ter um if para verificar o estado!
//TODO:Fazer maquina de estados onde vai estar por exemplo, o estado mover,inserir,apagar
void mousePassiveMotion(int x, int y) {
    y = windowY - y;

    printf("Moving without pressing any button... (%i, %i)\n", x, y);

    if (creatingForm) {
        change2Point(selectedForm, x, y);
        glutPostRedisplay();
    }
}





void mydisplay() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw X and Y axes for reference
    glBegin(GL_LINES);
    glVertex2f(-4.0, 0.0);
    glVertex2f(4.0, 0.0);
    glVertex2f(0.0, -4.0);
    glVertex2f(0.0, 4.0);
    glEnd();

    // Draw a line to separate the drawing area from the tools area
    glColor3f(1.0, 1.0, 1.0); // white color
    glBegin(GL_LINES);
    glVertex2f(0.0, windowY - drawArea); // Adjusted to the top 40 pixels
    glVertex2f(windowX, windowY - drawArea);
    glEnd();

    drawDBForms();

    drawForm(activeColor);

    // draw color palette
    for (int i = 0; i < nPaletteColors; ++i) {
        drawForm(palette[i]);
    }

    glFlush();

    printf("Counter: %i\n", ++counter);
}




void init() {
    int i;

    srand(time(NULL));

    initDBForms(50);

    printDBForms();

    // Adjust the y position of activeColor to be a bit lower
    activeColor = newSquare(10, windowY - 100, 40);
    setBackgroundColor(activeColor, rState, gState, bState);

    // Create array of palette colors with the first five in one row and the next five below them
    nPaletteColors = 10;
    palette = malloc(sizeof(Form) * nPaletteColors);
    palette[0] = newSquare(60, windowY - 50, 20);
    setBackgroundColor(palette[0], 1.0, 0.0, 0.0); // red
    palette[1] = newSquare(100, windowY - 50, 20);
    setBackgroundColor(palette[1], 0.0, 1.0, 0.0); // green
    palette[2] = newSquare(140, windowY - 50, 20);
    setBackgroundColor(palette[2], 0.0, 0.0, 1.0); // blue
    palette[3] = newSquare(180, windowY - 50, 20);
    setBackgroundColor(palette[3], 1.0, 1.0, 0.0); // yellow
    palette[4] = newSquare(220, windowY - 50, 20);
    setBackgroundColor(palette[4], 1.0, 0.0, 1.0); // magenta
    palette[5] = newSquare(60, windowY - 80, 20);
    setBackgroundColor(palette[5], 0.0, 1.0, 1.0); // cyan
    palette[6] = newSquare(100, windowY - 80, 20);
    setBackgroundColor(palette[6], 1.0, 0.5, 0.0); // orange
    palette[7] = newSquare(140, windowY - 80, 20);
    setBackgroundColor(palette[7], 0.5, 0.0, 0.5); // purple
    palette[8] = newSquare(180, windowY - 80, 20);
    setBackgroundColor(palette[8], 0.5, 0.5, 0.5); // gray
    palette[9] = newSquare(220, windowY - 80, 20);
    setBackgroundColor(palette[9], 0.0, 0.0, 0.0); // black

    glClearColor(0.0, 0.0, 0.0, 1.0);

    glColor3f(1.0, 1.0, 1.0);

    glViewport(0, 0, windowX, windowY);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, windowX, 0.0, windowY);
}


void myreshape(int w, int h) {
    windowX = w;
    windowY = h;

    // Update positions of active color and palette
    updateFormY(activeColor, windowY -50);

    for (int i = 0; i < nPaletteColors; ++i) {
        updateFormY(palette[i], windowY - 30);
    }

    glViewport(0, 0, windowX, windowY);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, windowX, 0.0, windowY);
}




void main(int argc, char** argv) {
    glutInit(&argc, argv);        /* Freeglut needs this line!*/
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(windowX, windowY);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("simple");
    glutDisplayFunc(mydisplay); /* function to be called whenever the window has to be painted */
    glutMouseFunc(mymouse); /* mouse callback function */
    glutKeyboardFunc(mykeyboard); /* keyboard callback function */
    glutReshapeFunc(myreshape); /* callback function for window resizing */
    //glutMotionFunc(mymotion); // Register the motion callback
    glutMotionFunc(mouseMotion); // Register the motion callback
    glutPassiveMotionFunc(mousePassiveMotion); // Register the passive motion callback

    init();
    glutMainLoop();
}