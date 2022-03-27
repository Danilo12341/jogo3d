#ifndef TIRO_H
#define TIRO_H
#include <GL/gl.h>
#include <GL/glu.h>

#define radiusTiro 1.0



class Tiro {
    GLfloat gXInit;
    GLfloat gYInit;
    GLfloat gZInit;
    GLfloat gX;
    GLfloat gY;
    GLfloat gZ;
    GLfloat gDirectionAng;
    GLfloat gDirectionAng2;
    GLfloat gVel;

  private:
    void DesenhaCirc(GLint radius, GLfloat R, GLfloat G, GLfloat B);
    void DesenhaTiro(GLfloat x, GLfloat y, GLfloat z);

  public:
    Tiro(GLfloat x, GLfloat y,  GLfloat z,GLfloat directionAng,GLfloat directionAng2) {
        gXInit = x;
        gYInit = y;
        gYInit = z;
        gX = x;
        gY = y;
        gZ = z;
        gDirectionAng = directionAng;
        gDirectionAng2 = directionAng2;
        gVel = 0.1;
    };
    ~Tiro();
    void Desenha() { DesenhaTiro(gX, gY,gZ); };
    void Move(GLdouble deltaTime);
    bool Valido();
    void GetPos(GLfloat& xOut, GLfloat& yOut,GLfloat& zOut) {
        xOut = gX;
        yOut = gY;
        zOut = gZ;
    };
    void getVel(GLfloat& velOut) { velOut = gVel; };
    void getDirectionAng(GLfloat& directionAngOut) {
        directionAngOut = gDirectionAng;
    };
};

#endif /* TIRO_H */
