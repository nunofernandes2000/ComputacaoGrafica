#include "form.h"
#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

// this struct is encapsulated
struct form {
    int type;
    float x, y;             // initial point of the form
    float xSize, ySize;     // sides
    float r, g, b;
};

Form newForm(int type, float x, float y, float xSize, float ySize) {
    Form f = (Form)malloc(sizeof(struct form));

    f->x = x;
    f->y = y;
    f->xSize = xSize;
    f->ySize = ySize;

    f->r = 1.0;
    f->g = 1.0;
    f->b = 1.0;

    f->type = type;

    return f;
}

Form newFormC(int type, float x, float y, float xSize, float ySize) {
    return newForm(type, x - (xSize / 2), y - (ySize / 2), xSize, ySize);
}

Form newRectangle(float x, float y, float xSize, float ySize) {
    return newForm(RECTANGLE, x, y, xSize, ySize);
}

Form newRectangleCenter(float x, float y, float xSize, float ySize) {
    return newFormC(RECTANGLE, x, y, xSize, ySize);
}

Form newSquare(float x, float y, float side) {
    return newForm(SQUARE, x, y, side, side);
}

Form newSquareCenter(float x, float y, float side) {
    return newFormC(SQUARE, x, y, side, side);
}

Form newTriangleIso(float x, float y, float xSize, float ySize) {
    return newForm(TRIANGLE_ISO, x, y, xSize, ySize);
}

Form newTriangleIsoCenter(float x, float y, float xSize, float ySize) {
    return newFormC(TRIANGLE_ISO, x, y, xSize, ySize);
}


Form newLine(float x, float y, float xSize, float ySize) {
    return newForm(LINE, x, y, xSize, ySize);
}

Form newLineCenter(float x, float y, float xSize, float ySize) {
    return newFormC(LINE, x, y, xSize, ySize);
}

Form newEquilateralTriangle(float x, float y, float xSize, float ySize) {
    return newForm(EQUILATERAL_TRIANGLE, x, y, xSize, ySize);
}

Form newEquilateralTriangleCenter(float x, float y, float xSize, float ySize) {
    return newFormC(EQUILATERAL_TRIANGLE, x, y, xSize, (sqrt(3) / 2) * xSize);
}

Form newHexagon(float x, float y, float xSize, float ySize) {
    return newForm(HEXAGON, x, y, xSize, ySize);
}

Form newHexagonCenter(float x, float y, float xSize, float ySize) {
    return newFormC(HEXAGON, x, y, xSize, ySize);
}

Form newCircumference(float x, float y, float xSize, float ySize) {
    return newForm(CIRCUMFERENCE, x, y, xSize, ySize);
}

Form newCircumferenceCenter(float x, float y, float xSize, float ySize) {
    return newFormC(CIRCUMFERENCE, x, y, xSize, ySize);
}


//Create forms 2 points
Form newRectangle2Point(float xi, float yi, float xf, float yf) {
    return newForm(RECTANGLE, xi, yi, xf - xi, yf - yi);
}



// check if XY is inside the form
int pick(float x, float y, Form f) {
    return (x <= f->x + f->xSize && x >= f->x && y <= f->y + f->ySize && y >= f->y);
}






Form createRandomForm(int maxSize) {
    Form f;
    switch (rand() % 7) {
        case 0:
            f = newRectangle(rand() % maxSize, rand() % maxSize, rand() % (maxSize / 4), rand() % (maxSize / 4));
            break;
        case 1:
            f = newSquare(rand() % maxSize, rand() % maxSize, rand() % (maxSize / 4));
            break;
        case 2:
            f = newTriangleIso(rand() % maxSize, rand() % maxSize, rand() % (maxSize / 4), rand() % (maxSize / 4));
            break;
        case 3:
            f = newLine(rand() % maxSize, rand() % maxSize, rand() % (maxSize / 4), rand() % (maxSize / 4));
            break;
        case 4:
            f = newEquilateralTriangle(rand() % maxSize, rand() % maxSize, rand() % (maxSize / 4), rand() % (maxSize / 4));
            break;
        case 5:
            f = newHexagon(rand() % maxSize, rand() % maxSize, rand() % (maxSize / 4), rand() % (maxSize / 4));
            break;
        case 6:
            f = newCircumference(rand() % maxSize, rand() % maxSize, rand() % (maxSize / 4), rand() % (maxSize / 4));
            break;
        default:
            f = newRectangle(rand() % maxSize, rand() % maxSize, rand() % (maxSize / 4), rand() % (maxSize / 4));
            break;
    }

    return f;
}


Form createFormCLICK(int type,int x, int y, int maxSize) {
    Form f;
    switch (type) {
        case RECTANGLE:
            f = newRectangleCenter(x, y, rand() % (maxSize / 4), rand() % (maxSize / 4));
            break;
        case SQUARE:
            f = newSquareCenter(x, y, rand() % (maxSize / 4));
            break;
        case TRIANGLE_ISO:
            f = newTriangleIsoCenter(x, y, rand() % (maxSize / 4), rand() % (maxSize / 4));
            break;
        case LINE:
            f = newLineCenter(x, y, rand() % (maxSize / 4), rand() % (maxSize / 4));
            break;
        case EQUILATERAL_TRIANGLE:
            f = newEquilateralTriangleCenter(x, y, rand() % (maxSize / 4), rand() % (maxSize / 4));
            break;
        case HEXAGON:
            f = newHexagon(x, y, rand() % (maxSize / 4), rand() % (maxSize / 4)); //usei o normal para central
            break;
        case CIRCUMFERENCE:
            f = newCircumference(x, y, rand() % (maxSize / 4), rand() % (maxSize / 4)); //usei o normal para central
            break;

        default:
            f = newRectangleCenter(x, y, rand() % (maxSize / 4), rand() % (maxSize / 4));
            break;
    }

    return f;
}







void deleteForm(Form f) {
    free(f);
}

void updateForm(Form f, float dx, float dy) {
    f->x += dx;
    f->y += dy;
}


void setBackgroundColor(Form f, float r, float g, float b)
{
    f->r = r;
    f->g = g;
    f->b = b;
}


void printfForm(Form f) {
    printf("Graphical Form BBox: (%.2f,%.2f), (%.2f, %.2f), (%.2f, %.2f), (%.2f, %.2f)\t",
           f->x, f->y,
           f->x, f->y + f->ySize,
           f->x + f->xSize, f->y + f->ySize,
           f->x + f->xSize, f->y);


    printf("Center(%.2f,%.2f) Size{%.2f,%.2f}\n",
           f->x + (f->xSize / 2), f->y + (f->ySize / 2),
           f->xSize, f->ySize);

}

void drawTriangleIso(Form f) {
    glColor3f(f->r, f->g, f->b);
    glBegin(GL_POLYGON);
    glVertex2f(f->x, f->y);
    glVertex2f(f->x + (f->xSize / 2.0), f->y + f->ySize);
    glVertex2f(f->x + f->xSize, f->y);
    glEnd();

    glColor3f(rand() / (RAND_MAX * 1.0), rand() / (RAND_MAX * 1.0), rand() / (RAND_MAX * 1.0));
    glBegin(GL_LINE_LOOP);
    glVertex2f(f->x, f->y);
    glVertex2f(f->x + (f->xSize / 2.0), f->y + f->ySize);
    glVertex2f(f->x + f->xSize, f->y);
    glEnd();
}

void drawBox(Form f) {
    glColor3f(f->r, f->g, f->b);
    glBegin(GL_POLYGON);
    glVertex2f(f->x, f->y);
    glVertex2f(f->x, f->y + f->ySize);
    glVertex2f(f->x + f->xSize, f->y + f->ySize);
    glVertex2f(f->x + f->xSize, f->y);
    glEnd();

    glColor3f(rand() / (RAND_MAX * 1.0), rand() / (RAND_MAX * 1.0), rand() / (RAND_MAX * 1.0));
    glBegin(GL_LINE_LOOP);
    glVertex2f(f->x, f->y);
    glVertex2f(f->x, f->y + f->ySize);
    glVertex2f(f->x + f->xSize, f->y + f->ySize);
    glVertex2f(f->x + f->xSize, f->y);
    glEnd();
}

void drawLine(Form f) {
    glColor3f(f->r, f->g, f->b);
    glBegin(GL_LINES);
    glVertex2f(f->x, f->y);
    glVertex2f(f->x + f->xSize, f->y + f->ySize);
    glEnd();
}


void drawEquilateralTriangle(Form f) {
    glColor3f(f->r, f->g, f->b);
    glBegin(GL_POLYGON);
    glVertex2f(f->x, f->y);
    glVertex2f(f->x + f->xSize / 2, f->y +(sqrt(3) / 2) * f->xSize);
    glVertex2f(f->x + f->xSize, f->y);
    glEnd();
}

void drawHexagon(Form f) {
    float radius = f->xSize / 2;
    glColor3f(f->r, f->g, f->b);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 6; ++i) {
        glVertex2f(f->x + radius * cos(i * M_PI / 3), f->y + radius * sin(i * M_PI / 3));
    }
    glEnd();
}

void drawCircumference(Form f) {
    float radius = f->xSize / 2;
    glColor3f(f->r, f->g, f->b);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; ++i) {
        glVertex2f(f->x + radius * cos(i * M_PI / 180), f->y + radius * sin(i * M_PI / 180));
    }
    glEnd();
}

void drawForm(Form f) {
    switch (f->type) {
        case TRIANGLE_ISO:
            drawTriangleIso(f); break;
        case RECTANGLE:
        case SQUARE:
            drawBox(f); break;
        case LINE:
            drawLine(f); break;
        case EQUILATERAL_TRIANGLE:
            drawEquilateralTriangle(f); break;
        case HEXAGON:
            drawHexagon(f); break;
        case CIRCUMFERENCE:
            drawCircumference(f); break;
    }
}
