
//  Created by Trung Huynh on 1/27/17.
//  Copyright © 2017 Trung Huynh. All rights reserved.
//
//#include <iostream>
#include <math.h>
#include <iostream>
#include <GLUT/GLUT.h>
void keyboard (unsigned char key, int x, int y);
void mouse (int button, int state, int x, int y);
void init (void);
void display(void);
void drawCircle(int x,int y);
double distance(int x,int y, int a ,int b);

int pts[100][2];
int num_pts = 0;
int ptsIndex = 0;

int  numberLine = 100;
int radius=50;
using namespace std;

int main(int argc, char** argv)
{
    
    
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (640, 480);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Interactive drawing");

    init ();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    
    glutMainLoop();
    
    
}


void keyboard (unsigned char key, int x, int y)
{ int i;
    
       switch (key)
    {
        case 'q':
            glutDestroyWindow(glutGetWindow());
            _Exit(0);

            break;
        case 'Q':
            glutDestroyWindow(glutGetWindow());
            _Exit(0);

            break;
        default:
            break;
    }
}


void mouse (int button, int state, int x, int y)
{
    int i;
    
    y = glutGet(GLUT_WINDOW_HEIGHT) - y;
    switch (button)
    {
        case GLUT_LEFT_BUTTON:
        {
            if (state == GLUT_DOWN) {
                pts[ptsIndex][0]=x;
                pts[ptsIndex][1] = y;
                ptsIndex = (ptsIndex +1)% 100;
                
                glutPostRedisplay();
            }
            break;
        }
        case GLUT_RIGHT_BUTTON:
        {
            if (state == GLUT_DOWN) {
                
                for(int i = ptsIndex-1 ; i>=0 ; i--)
                    if (distance(x, y, pts[i][0],pts[i][1]) <= radius) {

                        if (i<ptsIndex-1) {
                            pts[i][0] =  pts[ptsIndex-1][0];
                            pts[i][1] = pts[ptsIndex-1][1];
                        }
                        --ptsIndex;
                    }
                
                }
                
                
                
                glutPostRedisplay();
            }
            break;
    }
    
    
}
double distance(int x,int y, int a ,int b){
    
    return sqrt ( pow((x-a), 2) + pow((y-b), 2) );

}

void init (void)
{
    /*  select clearing (background) color       */
    glClearColor (0.0, 0.0, 0.0, 0.0);
//    glClearColor (1, 1, 1, 1);

    
    /*  initialize viewing values  */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

void display(void)
{
    int i;
    
    /*  clear all pixels  */
    glClear (GL_COLOR_BUFFER_BIT);
    
    /* Write code to display all lines */
    glColor3f (1.0, 1.0, 1.0);

    int currentPt = 0;

    for (int i = 0 ; i <ptsIndex ; i++)
    {
          drawCircle(pts[i][0], pts[i][1]);
    }
    
    
    glFlush ();
}

void drawCircle(int x,int y){

    glColor3d((x%100)/100.0, (y%100)/100.0, (x+y)%100/100);

      glBegin(GL_LINE_LOOP);
    
    
    for(int i = 0; i < numberLine; i++)
    {

        float theta = 2.0f * 3.1415926f * float(i) / float(numberLine);
        
        float newX = radius * cosf(theta);
        float newY = radius * sinf(theta);
        glVertex2i( (GLint)x + (GLint)newX,  (GLint)y + (GLint)newY);
       
    }
    glEnd();

}
