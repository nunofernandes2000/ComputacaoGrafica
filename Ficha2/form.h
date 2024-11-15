#ifndef __FORM_H__
#define __FORM_H__

#define RECTANGLE 0
#define SQUARE 1
#define TRIANGLE_ISO 2
#define LINE 3

#define EQUILATERAL_TRIANGLE 4
#define HEXAGON 5
#define CIRCUMFERENCE 6

/*
*  This interface provides clients with handles to form objects,
*  but does not give any information about the internal representation.
*  (The struct is specified only by its tag name.)
*/


// The tag name "Form" represents a pointer to a Graphical Form object
typedef struct form* Form;

//Form createRandomForm(int maxSize);
Form newRectangle(float x, float y, float xSize, float ySize);
Form newSquare(float x, float y, float side);
Form newTriangleIso(float x, float y, float xSize, float ySize);
Form newLine(float x, float y, float xSize, float ySize);


Form newEquilateralTriangle(float x, float y, float xSize, float ySize);
Form newHexagon(float x, float y, float xSize, float ySize);
Form newCircumference(float x, float y, float xSize, float ySize);



//Create forms Center
Form newRectangleCenter(float x, float y, float xSize, float ySize);
Form newSquareCenter(float x, float y, float side);
Form newTriangleIsoCenter(float x, float y, float xSize, float ySize);
Form newLineCenter(float x, float y, float xSize, float ySize);


Form newEquilateralTriangleCenter(float x, float y, float xSize, float ySize);
Form newHexagonCenter(float x, float y, float xSize, float ySize);
Form newCircumferenceCenter(float x, float y, float xSize, float ySize);


//Create forms 2 points
Form newRectangle2Point(float xi, float yi, float xf, float yf);





//check if XY is inside the form
int pick(float x, float y, Form f);


// delete form
void deleteForm(Form f);

// update a form position - moving by (dx,dy)
void updateForm(Form f, float dx, float dy);
void change2Point(Form f, float x, float y);


void setBackgroundColor(Form f, float r, float g, float b);

// print the content of the graphical form to console
void printfForm(Form f);

// draw a graphical form
void drawForm(Form f);



// draw a graphical form
Form createRandomForm(int maxSize);
Form createFormCLICK(int type,int x, int y, int maxSize);




// get the background color of the form
void getBGColor(Form f, float *c);


void updateFormY(Form f, float y);




#endif

