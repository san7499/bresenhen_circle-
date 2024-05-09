#include <windows.h>
#include <iostream>
#include <GL/glut.h>
#include <GL/glu.h>
#include <cmath>

using namespace std;

GLint xi, yi, r;
GLint color[3] = {255, 0, 0}; // Red color by default

void setPixel(GLint x, GLint y) {
    glBegin(GL_POINTS);
    glColor3ub(color[0], color[1], color[2]); // Set the color
    glVertex2i(x, y);
    glEnd();
}

void drawCirclePoints(GLint x, GLint y) {
    setPixel(xi + x, yi + y);
    setPixel(xi - x, yi + y);
    setPixel(xi + x, yi - y);
    setPixel(xi - x, yi - y);
    setPixel(xi + y, yi + x);
    setPixel(xi - y, yi + x);
    setPixel(xi + y, yi - x);
    setPixel(xi - y, yi - x);
}

void drawCircle() {
    GLint x = 0;
    GLint y = r;
    GLint d = 3 - 2 * r;
    drawCirclePoints(x, y);
    while (y >= x) {
        x++;
        if (d > 0) {
            y--;
            d = d + 4 * (x - y) + 10;
        } else {
            d = d + 4 * x + 6;
        }
        drawCirclePoints(x, y);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawCircle();
    glFlush();
}

void initialize() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // Set background color to white
    gluOrtho2D(0, 800, 0, 600); // Set the coordinate system
}

void setColor(int r, int g, int b) {
    color[0] = r;
    color[1] = g;
    color[2] = b;
}

void menu(int choice) {
    switch (choice) {
        case 1:
            setColor(255, 0, 0); // Red
            break;
        case 2:
            setColor(0, 255, 0); // Green
            break;
        case 3:
            setColor(0, 0, 255); // Blue
            break;
        case 4:
            setColor(255, 255, 0); // Yellow
            break;
        case 5:
            setColor(255, 0, 255); // Magenta
            break;
        case 6:
            setColor(0, 255, 255); // Cyan
            break;
        default:
            break;
    }
    glutPostRedisplay(); // Redraw the circle with the new color
}

int main(int argc, char** argv) {
    cout << "Enter the center coordinates (x, y): ";
    cin >> xi >> yi;
    cout << "Enter the radius of the circle: ";
    cin >> r;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600); // Set the window size
    glutInitWindowPosition(100, 100); // Set the window position
    glutCreateWindow("Bresenham Circle Drawing");

    initialize();
    glutDisplayFunc(display); // Register display callback function

    // Create a menu for color selection
    glutCreateMenu(menu);
    glutAddMenuEntry("Red", 1);
    glutAddMenuEntry("Green", 2);
    glutAddMenuEntry("Blue", 3);
    glutAddMenuEntry("Yellow", 4);
    glutAddMenuEntry("Magenta", 5);
    glutAddMenuEntry("Cyan", 6);
    glutAttachMenu(GLUT_RIGHT_BUTTON); // Attach the menu to the right mouse button

    glutMainLoop(); // Enter the event-processing loop

    return 0;
}

