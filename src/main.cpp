// MIT License
// 
// Copyright (c) 2021 jcastro0x
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <iostream>
#include <cmath>

#ifdef BUILD_LIB_FREEGLUT
#include <GL/freeglut.h>
#endif

#ifdef BUILD_LIB_GLUI
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#include <GL/glui.h>
#pragma GCC diagnostic pop
#endif

#ifdef BUILD_LIB_GLM
#include <glm/glm.hpp>
#endif

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600
#define WINDOW_ARATIO WINDOW_WIDTH/(float)WINDOW_HEIGHT



using namespace std;
using namespace glm;

int glutWindow = 0;

struct GUI {

    int numberOfPoints = 60;
    float radius = std::min(WINDOW_HEIGHT, WINDOW_WIDTH)/10.f;

};

GUI* gui = nullptr;

void initGlut()
{
    glClearColor(0,0,0,1);

    glPointSize(5);
    glLineWidth(5);

    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


void initGlui()
{
    static GLUI *glui = GLUI_Master.create_glui( "GLUI" );
    auto points = new GLUI_Spinner( glui, "Number of Points:", &gui->numberOfPoints );
    auto radius = new GLUI_Spinner( glui, "Radius:", &gui->radius );

    points->set_int_limits( 5, 60 );
    radius->set_float_limits( std::min(WINDOW_HEIGHT, WINDOW_WIDTH)/100.f, std::min(WINDOW_HEIGHT, WINDOW_WIDTH)/2.f );

    glui->set_main_gfx_window( glutWindow );
}

void resize(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    /**
     *  0,0.................W,0
     *  .                    .
     *  .                    .
     *  .                    .
     *  .                    .
     *  0,H.................W,H
     */
    glOrtho(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glBegin(GL_LINE_LOOP);
        const float increment = M_PI*2/(float)gui->numberOfPoints;
        const float color = 1/(float)gui->numberOfPoints;
        for(int i = 0; i < gui->numberOfPoints; ++i)
        {
            vec2 pos {cos(static_cast<float>(i)*increment) * gui->radius, sin(static_cast<float>(i)*increment) * gui->radius};
            vec2 center {WINDOW_WIDTH/2.f, WINDOW_HEIGHT/2.f};
            pos += center;

            glColor3f(color*static_cast<float>(i), 1 - color*static_cast<float>(i), 0);
            glVertex2f(pos.x, pos.y);
        }
    glEnd();

    glColor3f(1,1,1);
    glRasterPos2d(0, 15);
    glutBitmapString(GLUT_BITMAP_9_BY_15, reinterpret_cast<const unsigned char *>("GLUTBase (Educational project)"));

    glutSwapBuffers();
}


int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(WINDOW_WIDTH,WINDOW_HEIGHT);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutWindow = glutCreateWindow("GLUTBase");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);

    gui = new GUI();

    initGlut();
    initGlui();
    glutMainLoop();

    delete gui;
    return EXIT_SUCCESS;
}
