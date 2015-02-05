//
//  assignment.c
//
//
//  Created by Shreya Rajani on 2/4/14.
//
//

#include <GLUT/glut.h>
#include <stdlib.h>

static int triangle = GL_FALSE;
static int line = GL_FALSE;
static int point = GL_FALSE;
static int polygon = GL_FALSE;
static int clear = GL_FALSE;
static int quad = GL_FALSE;
static int lineloop = GL_FALSE;
static int linestrip = GL_FALSE;
static int quadstrip = GL_FALSE;

GLdouble wx, wy, wz;  /*  returned world x, y, z coords  */
float xp[100]; //array of x coordinate
float yp[100]; //array of y coordinate
int ctr ;

/**
 Function to adjust the values when the window is reshaped
 */
void reshape(int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective (45.0, (GLfloat) w/(GLfloat) h, 0.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/**
 Function to draw point
 */
static void drawPoint(void){
    glPointSize(4.0);
    glBegin(GL_POINTS);
    for(int i=0;i<=ctr;i++) {
        glVertex2f(xp[i], yp[i]);
    }
    glEnd();
}

/**
 Function to draw line
 */
static void drawLine(void){
    glColor4f(1.0, 1.0, 0.0, 0.2);
    glBegin (GL_LINES);
    for(int i=0;i<=ctr-1;i=i+2){
        glVertex2f(xp[i], yp[i]);
        glVertex2f(xp[i+1], yp[i+1]);
    }
    glEnd();
}

/**
 Function to draw triangle
 */
static void drawTriangle(void){
    glColor4f(1.0, 1.0, 0.0, 0.2);
    
    glBegin (GL_TRIANGLES);
    for(int i=0;i<=ctr-2;i=i+3){
        glVertex2f(xp[i], yp[i]);
        glVertex2f(xp[i+1], yp[i+1]);
        glVertex2f(xp[i+2], yp[i+2]);
    }
    glEnd();
}

/**
 Function to draw polygon
 */
static void drawPolygon(void){
    glBegin(GL_POLYGON);
    glColor4f(0.0, 1.0, 1.0, 0.2);
    for(int i=0;i<=ctr;i++){
        glVertex2f(xp[i], yp[i]);
    }
    glEnd();
}

/**
 Function to draw Quadrilateral
 */
static void drawQuad(void){
    glPointSize(3.0);
    glColor4f(0.0, 1.0, 1.0, 0.2);
    glBegin (GL_QUADS);
    for(int i=0;i<=ctr-3;i=i+4){
        glVertex2f(xp[i], yp[i]);
        glVertex2f(xp[i+1], yp[i+1]);
        glVertex2f(xp[i+2], yp[i+2]);
        glVertex2f(xp[i+3], yp[i+3]);
    }
    glEnd();
}

/**
 Function to draw line strip
 */
static void drawLineStrip(void){
    glColor4f(1.0, 1.0, 0.0, 0.2);
    glBegin (GL_LINE_STRIP);
    for(int i=0;i<=ctr;i=i+2){
        glVertex2f(xp[i], yp[i]);
        glVertex2f(xp[i+1], yp[i+1]);
    }
    glEnd();
}

/**
 Function to draw line loop
 */
static void drawLineLoop(void){
    glColor4f(1.0, 1.0, 0.0, 0.2);
    glBegin (GL_LINE_LOOP);
    for(int i=0;i<=ctr;i=i+2){
        glVertex2f(xp[i], yp[i]);
        glVertex2f(xp[i+1], yp[i+1]);
    }
    glEnd();
}

/**
 Function to draw trianlge fan
 */
static void drawQuadStrip(void){
    glBegin (GL_TRIANGLE_FAN);
    for(int i=0;i<=ctr-1;i=i+2){
        glVertex2f(xp[i], yp[i]);
        glVertex2f(xp[i+1], yp[i+1]);
        glVertex2f(xp[i+2], yp[i+2]);
        //glVertex2f(xp[i+3], yp[i+3]);
    }
    glEnd();
}

/**
 Function to clear screen
 */
static void clear1(void){
    glClearColor (0.0, 0.0, 0.0, 0.0);
    for(int i=0; i<=ctr; i++){
        xp[i] = 0;
        yp[i]=0;
    }
}

/**
 Function to display the enabled option
 */
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    if (triangle) {
        drawTriangle();
    }
    
    if(quad){
        drawQuad();
    }
    
    if(point){
        drawPoint();
    }
    
    if(line){
        drawLine();
    }
    if(polygon){
        drawPolygon();
    }
    
    if(lineloop){
        drawLineLoop();
    }
    
    if(linestrip){
        drawLineStrip();
    }
    
    if(quadstrip){
        drawQuadStrip();
    }
    
    if(clear){
        clear1();
    }
    glFlush();
}

/**
 Function to associate each key with function
 */
void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
            //Draw a Point. Experiment with glPointSize() to vary the size of the displayed point.
        case 'p':
        case 'P':
            point = GL_TRUE;
            line = GL_FALSE;
            clear = GL_FALSE;
            polygon = GL_FALSE;
            triangle = GL_FALSE;
            quad = GL_FALSE;
            lineloop = GL_FALSE;
            linestrip = GL_FALSE;
            quadstrip = GL_FALSE;
            glutPostRedisplay();
            break;
            
            //Draw a Line. Experiment with glLineWidth() and glLineStipple() to vary the width and pattern of the drawn line.
        case 'l':
        case 'L':
            quad = GL_FALSE;
            polygon = GL_FALSE;
            clear = GL_FALSE;
            line = GL_TRUE;
            point = GL_FALSE;
            triangle = GL_FALSE;
            lineloop = GL_FALSE;
            linestrip = GL_FALSE;
            quadstrip = GL_FALSE;
            glutPostRedisplay();
            break;
            
            //Draw a Quadrilateral. The quadrilateral must be filled in with some color and opacity (glColor4f()).
        case 'q':
        case 'Q':
            quad = GL_TRUE;
            polygon = GL_FALSE;
            clear = GL_FALSE;
            line = GL_FALSE;
            point = GL_FALSE;
            triangle = GL_FALSE;
            lineloop = GL_FALSE;
            linestrip = GL_FALSE;
            quadstrip = GL_FALSE;
            glutPostRedisplay();
            break;
            
            //Draw a Polygon. The polygon must be filled in with some color.
        case 'o':
        case 'O':
            polygon = GL_TRUE;
            clear = GL_FALSE;
            line = GL_FALSE;
            point = GL_FALSE;
            triangle = GL_FALSE;
            quad = GL_FALSE;
            lineloop = GL_FALSE;
            linestrip = GL_FALSE;
            quadstrip = GL_FALSE;
            glutPostRedisplay();
            break;
            
            //Draw a Triangle. The triangle must be filled in with some color.
        case 't':
        case 'T':
            clear = GL_FALSE;
            triangle = GL_TRUE;
            line = GL_FALSE;
            polygon = GL_FALSE;
            point = GL_FALSE;
            quad = GL_FALSE;
            lineloop = GL_FALSE;
            linestrip = GL_FALSE;
            quadstrip = GL_FALSE;
            glutPostRedisplay();
            break;
            
            //Draw a line loop.
        case 'g':
        case 'G':
            lineloop = GL_TRUE;
            linestrip = GL_FALSE;
            clear = GL_FALSE;
            triangle = GL_FALSE;
            line = GL_FALSE;
            polygon = GL_FALSE;
            point = GL_FALSE;
            quad = GL_FALSE;
            quadstrip = GL_FALSE;
            glutPostRedisplay();
            break;
            
            //Draw a line strip.
        case 's':
        case 'S':
            linestrip = GL_TRUE;
            clear = GL_FALSE;
            triangle = GL_FALSE;
            line = GL_FALSE;
            polygon = GL_FALSE;
            point = GL_FALSE;
            quad = GL_FALSE;
            quadstrip = GL_FALSE;
            glutPostRedisplay();
            break;
            
            //Draw a Triangle fan.
        case 'r':
        case 'R':
            quadstrip = GL_TRUE;
            linestrip = GL_FALSE;
            clear = GL_FALSE;
            triangle = GL_FALSE;
            line = GL_FALSE;
            polygon = GL_FALSE;
            point = GL_FALSE;
            quad = GL_FALSE;
            glutPostRedisplay();
            break;
            
            //Clear
        case 'c':
        case 'C':
            clear = GL_TRUE;
            triangle = GL_FALSE;
            line = GL_FALSE;
            polygon = GL_FALSE;
            point = GL_FALSE;
            quad = GL_FALSE;
            lineloop = GL_FALSE;
            linestrip = GL_FALSE;
            quadstrip = GL_FALSE;
            break;
            
            //Esc
        case 27:
            exit(0);
            break;
        default:
            break;
    }
}

/**
 Function to enable and record mouse clicks
 */
void mouse(int button, int state, int x, int y)
{
    GLint viewport[4];
    GLdouble mvmatrix[16], projmatrix[16];
    
    GLint realy;  /*  OpenGL y coordinate position  */
    
    switch (button) {
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN) {
                
                glGetIntegerv (GL_VIEWPORT, viewport);
                glGetDoublev (GL_MODELVIEW_MATRIX, mvmatrix);
                glGetDoublev (GL_PROJECTION_MATRIX, projmatrix);
                realy = viewport[3] - (GLint) y - 1;
                gluUnProject ((GLdouble) x, (GLdouble) realy, 0.0,
                              mvmatrix, projmatrix, viewport, &wx, &wy, &wz);
                ctr ++;
                xp[ctr] = wx;
                yp[ctr] = wy;
                glutPostRedisplay();
            }
            break;
            
        default:
            break;
    }
}

//  Main Loop
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (800, 800);
    glutCreateWindow (argv[0]);
    glutReshapeFunc (reshape);
    glutKeyboardFunc (keyboard);
    glutMouseFunc(mouse);
    glutDisplayFunc (display);
    glutMainLoop();
    return 0;
}