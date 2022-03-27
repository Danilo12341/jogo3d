#include "tiro.h"
#include <cstdio>
#include <math.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glu.h>
#define DISTANCIA_MAX 500

void Tiro::DesenhaCirc(GLint radius, GLfloat R, GLfloat G, GLfloat B) {
    glColor3f(R, G, B);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 20) {
        glVertex2f(radius * cos(i * M_PI / 180), radius * sin(i * M_PI / 180));
    }
    glEnd();
}

void Tiro::DesenhaTiro(GLfloat x, GLfloat y,GLfloat z) {
        GLfloat materialEmission[] = { 0.00, 0.00, 0.00, 1.00};
        GLfloat materialColor[] = { 1.0, 0.0, 0.0, 1.0};
        GLfloat mat_specular[] = { 0.0, 0.0, 0.0, 1.0};
        GLfloat mat_shininess[] = { 128 };
        glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);
        glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, materialColor);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
        glPushMatrix();
        glTranslatef(x,y,z);
        glScalef(1,1,1);
        glutSolidCube(0.25);
        //glutSolidSphere(1, 100, 200);
        glPopMatrix();   

}

void Tiro::Move(GLdouble deltaTime) {
    gX += gVel * sin(-gDirectionAng * M_PI / 180)*cos(-gDirectionAng2 * M_PI / 180) * deltaTime;
    gY += gVel * cos(-gDirectionAng * M_PI / 180) * deltaTime;
    gZ += gVel * sin(-gDirectionAng * M_PI / 180)*sin(-gDirectionAng2 * M_PI / 180) * deltaTime;
}

Tiro::~Tiro() {}

bool Tiro::Valido() { return DISTANCIA_MAX > sqrt(pow(gX, 2) + pow(gY, 2)); }
