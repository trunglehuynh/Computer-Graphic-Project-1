//  part2.cpp
//  ComputerGraohic-Proj1-TrungHuynh-801060243
//
//  Created by Trung Huynh on 2/9/17.
//  Copyright © 2017 Trung Huynh. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include <GLUT/GLUT.h>
#include <unistd.h>



void keyboard (unsigned char key, int x, int y);
void mouse (int button, int state, int x, int y);
void init (void);
void display(void);
void menu(int id);
GLfloat *drawCircle(int x,int y,GLfloat cycle[]);
void animation(GLfloat x, GLfloat y);



//inline void mySleep(clock_t sec);

// Fill your code to declare a number of global variables to
// store the geometry information, including position, orientation, and scaling
// ...
#define pointNum 5
#define PI 3.14159265

GLfloat house[pointNum][2] = {{40,40},{40,90},{70,120},{100,90},{100,40}};

GLfloat test[10] = {40,40,70,100,100,40,90,120,90,40};

//GLdouble idenMatrix[3][3] = {{1,0,0},{0,1,0},{0,0,1}};
GLdouble idenMatrix[9] = {1,0,0,0,1,0,0,0,1};


//
GLfloat d[16] = {1,0,0,0,0,1,0,0,0,0,1,0,5,0,0,1};
GLfloat w[16] = {1,0,0,0,0,1,0,0,0,0,1,0,0,5,0,1};
GLfloat a[16] = {1,0,0,0,0,1,0,0,0,0,1,0,-5,0,0,1};
GLfloat s[16] = {1,0,0,0,0,1,0,0,0,0,1,0,0,-5,0,1};
GLfloat zMove[16] =  {1,0,0,0,0,1,0,0,0,0,1,0, 0,0,0,1};
GLfloat zMove2[16] = {1,0,0,0,0,1,0,0,0,0,1,0, 0,0,0,1};
GLfloat newX =0 , newY = 0;

int main(int argc, char** argv)
{
    for (int i=0; i<pointNum; i++) {
        house[i][0] = house[i][0] +200;
        house[i][1] = house[i][1] +200;

    }
    
    for (int i = 0 ; i< 10; i++)
    {
        test[i] = test[i] + 300;
    }
    
    
       for (int i = 0; i < pointNum; ++i) {
        newX =newX+house[i][0];
        newY =newY+house[i][1];
    }
    
    newX =newX /pointNum;
    newY =newY /pointNum;
    zMove[12] = -newX;
    zMove[13] = -newY;
    
    zMove2[12] = newX;
    zMove2[13] = newY;
    
    
    int subMenu_Translation, subMenu_Scaling, subMenu_Rotation;
    
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
//    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize (640, 480);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Interactive 2D Transformation");
    
    glutDisplayFunc(display);
//    glutMouseFunc(mouse);
//    glutKeyboardFunc(keyboard);
    
    // create sub menu for translation
    subMenu_Translation = glutCreateMenu(menu);
    // The second parameter of glutAddMenuEntry() is the ID that will be used in menu()
        glutAddMenuEntry("Horizontal increment", 1);
        glutAddMenuEntry("Horizontal decrement", -1);

        glutAddMenuEntry("Vertical increment", 2);
        glutAddMenuEntry("Vertical decrement", -2);
    
    
    subMenu_Scaling = glutCreateMenu(menu);
        glutAddMenuEntry("Horizontal enlarging", 3);
        glutAddMenuEntry("Horizontal shrinking", -3);
    
        glutAddMenuEntry("Vertical enlarging", 4);
        glutAddMenuEntry("Vertical shrinking", -4);

    subMenu_Rotation = glutCreateMenu(menu);
        glutAddMenuEntry("Clockwise", 5);
        glutAddMenuEntry("Counter-clockwise", -5);
    
    // create main "right click" menu
    glutCreateMenu(menu);
    glutAddSubMenu("Translation", subMenu_Translation);
    glutAddSubMenu("Scaling", subMenu_Scaling);
    glutAddSubMenu("Rotation", subMenu_Rotation);
    
 
     glutAddMenuEntry("Moved Around", 11);
    glutAddMenuEntry("Quit", 10);
   
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    
    init ();
    
  
    
    glutMainLoop();
    return 0;   /* ISO C requires main to return int. */
}


//void keyboard (unsigned char key, int x, int y)
//{
//    int i;
//    
//    switch (key)
//    {
//        case 'q':
//            printf("QQQQQQ\n");
//            break;
//        case 'c':
//            glClear (GL_COLOR_BUFFER_BIT);
//            break;
//        case 'd':
//            glMultMatrixf(d);
//            break;
//        case 'a':
//            glMultMatrixf(a);
//            break;
//        case 'w':
//        {
//            glMultMatrixf(w);
//            break;
//        }
//        case 's':
//          glMultMatrixf(s);
//            break;
//
//        case 'z':
//        {
//            // rotation
//            
//            GLfloat angle = 10.0;
//            angle = angle* PI /180.0;
//            GLfloat costAngle = cosf(angle);
//            GLfloat sinAngle = sinf(angle);
//            GLfloat z[16] = {costAngle,sinAngle,0,0,-sinAngle,costAngle,0,0,0,0,1,0,0,0,0,1};
//        
//            glMultMatrixf(zMove2);
//            glMultMatrixf(z);
//            glMultMatrixf(zMove);
//            break;
//        }
//            
//        case 'x':
//        {
//            
//            // rotation
//            
//            GLfloat angle = -10.0;
//            angle = angle* PI /180.0;
//            GLfloat costAngle = cosf(angle);
//            GLfloat sinAngle = sinf(angle);
//            GLfloat z[16] = {costAngle,sinAngle,0,0,-sinAngle,costAngle,0,0,0,0,1,0,0,0,0,1};
//     
//            glMultMatrixf(zMove2);
//            glMultMatrixf(z);
//            glMultMatrixf(zMove);
//            break;
//
//        }
//            
//        case 'e':
//        {
//            
//            float shrinking = 0.5;
//
//            GLfloat r[16] = {1,0,0,0,shrinking,1,0,0,0,0,1,0,0,0,0,1};
//
//             glMultMatrixf(zMove2);
//            glMultMatrixf(r);
//            glMultMatrixf(zMove);
//            break;
//            
//        }
//        case 'r':
//        {
//            
//            float shrinking = -0.5;
//            GLfloat r[16] = {1,0,0,0,shrinking,1,0,0,0,0,1,0,0,0,0,1};
//            glMultMatrixf(zMove2);
//            glMultMatrixf(r);
//            glMultMatrixf(zMove);
//            break;
//            
//        }
//            
//        case 't':
//        {
//            
//            
//            float enlarging = 2;
//            
//            GLfloat t[16] = {enlarging,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
//            
//            glMultMatrixf(zMove2);
//            glMultMatrixf(t);
//            glMultMatrixf(zMove);
//            break;
//            
//        }
//            
//        case 'y':
//        {
//            
//            
//            float enlarging = 0.5;
//            
//            GLfloat y[16] = {enlarging,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
//            
//            glMultMatrixf(zMove2);
//            glMultMatrixf(y);
//            glMultMatrixf(zMove);
//            
//            break;
//            
//        }
//            
//        case 'u':
//        {
////            glMatrixMode(GL_MODELVIEW);
//
//            GLfloat cycle[200] ;
//            drawCircle(newX,newY,cycle);
//            GLfloat cy[16] = {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
//           
//            for (int i = 99 ; i > 0; i--) {
//            cy[12] =  cycle[i] - cycle[i-1];
//            cy[13] =  cycle[i+100] - cycle[i+99];
//                
//            printf("%f      %f  \n", cycle[i], cycle[i+100]);
//            glMultMatrixf(cy);
//            display();
//            usleep(10000); // 1 second
//
//            }
//            break;
//            
//        }
//  
//    }
//    
//    glutPostRedisplay();
//
//}



GLfloat *drawCircle(int x,int y,GLfloat cycle[]){
    
    int numberLine = 100;
    int radius=100;

    x= x - radius;
    
    for(int i = 0; i < numberLine; i++)
    {
        
        float theta = 2.0f * 3.1415926f * float(i) / float(numberLine-1);
        
        cycle[i] = x + (radius * cosf(theta));
        cycle[i+numberLine] = y + (radius * sinf(theta));
    }
    return cycle;
}


//void mouse (int button, int state, int x, int y)
//{
//    int i;
//    
//    switch (button)
//    {
//        case GLUT_LEFT_BUTTON:
//            if (state == GLUT_DOWN) {
//                // Fill your code to initialize the position of an object, i.e., the save the (x,y)
//                // of a left click
//                // ...
//                
//                glutPostRedisplay();
//            }
//            break;
//        default:
//            break;
//    }
//}

void init (void)
{
    /*  select clearing (background) color       */
    glClearColor (0.0, 0.0, 0.0, 0.0);
    
    /*  initialize viewing values  */
//    glMatrixMode(GL_PROJECTION);
    glMatrixMode(GL_MODELVIEW);
    
 


    glLoadIdentity();
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
//    gluOrtho2D(0.0, 2000, 0.0, 480.0);

}

void display(void)
{
    
    /*  clear all pixels  */
    glClear (GL_COLOR_BUFFER_BIT);
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    
    glColor3f (1.0, 1.0, 1.0);
    // Fill your code to draw an object (you can choose your favorate object)
    // under an interactive 2D transformation
    // ...
    
    // Fill your code to reset some variables if necessary
    // ...
    
    
    /*  don't wait!
     *  start processing buffered OpenGL routines
     */
    
    glBegin(GL_LINE_LOOP);
    
    for(int  i = 0 ; i < 5 ; i++)
    {
        glVertex2f(house[i][0], house[i][1]);
    }
    glEnd();
    
    glFlush ();
    
//    glutSwapBuffers();
}

void menu(int id)
{
    
    switch(id) {
        case 1:
            glMultMatrixf(d);
            break;
        case -1:
            glMultMatrixf(a);
            break;
        case 2:
        {
            glMultMatrixf(w);
            break;
        }
        case -2:
            glMultMatrixf(s);
            break;
            
            // Fill your code to handle the other transformation
            // ...
        case -5:
        {
            // rotation
            
            GLfloat angle = 10.0;
            angle = angle* PI /180.0;
            GLfloat costAngle = cosf(angle);
            GLfloat sinAngle = sinf(angle);
            GLfloat z[16] = {costAngle,sinAngle,0,0,-sinAngle,costAngle,0,0,0,0,1,0,0,0,0,1};
            
            glMultMatrixf(zMove2);
            glMultMatrixf(z);
            glMultMatrixf(zMove);
            break;
        }
            
        case 5:
        {
            
            // rotation
            
            GLfloat angle = -10.0;
            angle = angle* PI /180.0;
            GLfloat costAngle = cosf(angle);
            GLfloat sinAngle = sinf(angle);
            GLfloat z[16] = {costAngle,sinAngle,0,0,-sinAngle,costAngle,0,0,0,0,1,0,0,0,0,1};
            
            glMultMatrixf(zMove2);
            glMultMatrixf(z);
            glMultMatrixf(zMove);
            break;
            
        }
            
        case -3:
        {
            
            float shrinking = 0.5;
            
            GLfloat r[16] = {shrinking,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
            
            glMultMatrixf(zMove2);
            glMultMatrixf(r);
            glMultMatrixf(zMove);
            break;
            
        }
       
        case 3:
        {
            
            
            float enlarging = 2;
            
            GLfloat t[16] = {enlarging,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
            
            glMultMatrixf(zMove2);
            glMultMatrixf(t);
            glMultMatrixf(zMove);
            break;
            
        }
            
        case -4:
        {
            
            float shrinking = 0.5;
            
            GLfloat r[16] = {1,0,0,0,0,shrinking,0,0,0,0,1,0,0,0,0,1};
            
            glMultMatrixf(zMove2);
            glMultMatrixf(r);
            glMultMatrixf(zMove);
            break;
            
        }
            
        case 4:
        {
            
            
            float enlarging = 2;
            
            GLfloat t[16] = {1,0,0,0,0,enlarging,0,0,0,0,1,0,0,0,0,1};
            
            glMultMatrixf(zMove2);
            glMultMatrixf(t);
            glMultMatrixf(zMove);
            break;
            
        }
            
            
        case 11:
        {
            
            GLfloat cycle[200] ;
            drawCircle(newX,newY,cycle);
            GLfloat cy[16] = {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
            
            for (int i = 99 ; i > 0; i--) {
                cy[12] =  cycle[i] - cycle[i-1];
                cy[13] =  cycle[i+100] - cycle[i+99];
                
//                printf("%f      %f  \n", cycle[i], cycle[i+100]);
                glMultMatrixf(cy);
                display();
                usleep(10000);
                
            }
            break;
            
        }
        case 10:
            glutDestroyWindow(glutGetWindow());
            _Exit(0);
            break;
    }
    glutPostRedisplay();

}
