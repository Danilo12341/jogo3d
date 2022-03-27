#ifndef RETANGULO_H_
#define RETANGULO_H_
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include "tiro.h"

using namespace std;

class Retangulo{
    double width;
    double height;
    double tamz;
    double rx;
    double ry;
    double rz;
    string cor;
  
public:
    void setWidth(const double width1);
    double getWidth();
    void setHeight(const double height1);
    double getHeight();
    void setRx(const double rx1);
    double getRx();
    void setRy(const double ry1);
    double getRy();
    void setRz(const double rz1);
    double getRz();
    void setCor(const string circRaio);
    string getCor();
    bool Atingido(Tiro* tiro);
    void DesenhaRect(double R, double G, double B);
    
};



#endif // RETANGULO_H_
