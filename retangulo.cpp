#include "retangulo.h"
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glu.h>


void Retangulo::setWidth(const double width){
    this->width = width;
}
double Retangulo:: getWidth(){
   return this->width;
}
void Retangulo::setHeight(const double height){
    this->height= height;
}
double Retangulo:: getHeight(){
   return this->height;
}
void Retangulo::setRy(const double ry){
    this->ry = ry;
}
double Retangulo:: getRy(){
   return this->ry;
}
void Retangulo::setRx(const double rx){
    this->rx = rx;
}
double Retangulo:: getRx(){
   return this->rx;
}
void Retangulo::setRz(const double rz){
    this->rz = rz;
}
double Retangulo:: getRz(){
   return this->rz;
}

void Retangulo::setCor(const string cor){
    this->cor = cor;
}
string Retangulo:: getCor(){
   return this->cor;
}



void Retangulo::DesenhaRect(double R, double G, double B){
    if(this->cor=="blue"){
        GLfloat materialEmission[] = { 0.00, 0.00, 0.00, 1.00};
        GLfloat materialColor[] = { 0.0, 0.0, 1.0, 1.0};
        GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0};
        GLfloat mat_shininess[] = { 128 };
        glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);
        glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, materialColor);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
        glPushMatrix();
        glColor3f(R,G,B);
        glTranslatef(this->rx+(this->width/2),this->ry+this->height+2,0); // put in one end
        glScalef(this->width,2,this->height/2);
        glutSolidCube(1);
        glPopMatrix();
    }
    else{
        GLfloat materialEmission[] = { 0.00, 0.00, 0.00, 1.00};
        GLfloat materialColor[] = { 1.0, 1.0, 1.0, 1.0};
        GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0};
        GLfloat mat_shininess[] = { 128 };
        glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);
        glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, materialColor);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
        glPushMatrix();
        glColor3f(R,G,B);
        glTranslatef(this->rx+(this->width/2),this->ry+(this->height/2),0); // put in one end
        glScalef(this->width,this->height,this->height/2);
        glutSolidCube(1);
        glPopMatrix();
    } 
    
}
bool Retangulo::Atingido(Tiro* tiro){

    GLfloat posx, posy,posz;
    tiro->GetPos(posx, posy,posz);

    if(posx > this->getRx() && posx < this->getRx() + this->getWidth()
    && posy > this->getRy() && posy < this->getRy() + this->getHeight()
    && posz > - this->height/4 && posz < this->height/4
    ){
         return 1;
     }else{
         return 0;
     }


}



