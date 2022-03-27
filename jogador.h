#ifndef JOGADOR_H_
#define JOGADOR_H_

#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include <math.h>
#include "tiro.h"

using namespace std;

class Jogador{

    double cx;
    double cy;
    double cz;
    double raio;
    double x;
    double y;
    double z;
    double setz;
    string cor;
    double Thetabraco;
    double Thetabracoz;
    double Thetaquadril1;
    double Thetajoelho1;
    double Thetaquadril2;
    double Thetajoelho2;
    double eixoy;
    double gravidade;
    int paradodireita;
    int voltandoperna1 = 0;
    int voltandojoelho1 = 0;
    int voltandoperna2 = 0;
    int voltandojoelho2 = 0;
    int andar =0;
    int voltandoperna1op=0;
    int voltandoperna2op=0;
    int andarop = 0;
    int voltandojoelho1op=0;
    int voltandojoelho2op=0;    
    public:
        void jogador(){
        x= 0.0; 
        y= 0.0;
        z=0.0;
        setz=0;
        Thetabraco = 0; 
        Thetabracoz=0;
        Thetaquadril1 = 0;
        Thetajoelho1 = 0;
        Thetaquadril2 = 0;
        Thetajoelho2 = 0;
        paradodireita=0;
        eixoy=0;
        };
        void resetarthetas();           
        void setCx(const double cx);
        double getCx();
        void setCy(const double cy);
        double getCy();
        double getThetabraco();
        void setzf(const double valor);
        double getzf();
        void setCz(const double cz);
        double getCz();
        int getparadodireita();
        double geteixoy();
        void setparadodireita(int valor);
        void setRaio(const double raio);
        double getRaio();
        void setCor(const string cor);
        string getCor();
        void Desenhacirculo(double x, double y,double z, double R, double G, double B);
        void DesenhaRect(double altura,double largura,double R, double G, double B);
        void DesenhaRect2(double x,double y,double z, double R,double G, double B);
        void Desenhacabeca(double R, double G, double B);
        void Desenhacorpo(double x, double y,double z,double R, double G, double B);
        void Desenhabraco(double x,double y,double z,double R, double G, double B);
        void Desenhabraco2(double x,double y,double z,double R, double G, double B);
        void Desenhaarma(double x,double y,double z,double R, double G, double B);
        void Desenhaperna1(double x,double y,double z,double R, double G, double B);
        void Desenhaosso1 (double x,double y,double z, double R,double G, double B);
        void Desenhaperna2(double x,double y,double z,double R, double G, double B);
        void DesenhaJogador(double x,double y,double z);
        void MoveEmX(double dx,GLdouble deltaTime,double eixoy2);
        void MoveEmY(double dx,GLdouble deltaTime);
        void MoveEmZ(double dz,GLdouble deltaTime, double eixoy2);
        void RodaBracoup(double inc);
        void RodaBracodown(double inc);
        void RodaBracoesq(double inc);
        void RodaBracodir(double inc);
        void Rodaquadrail1(double inc);
        void Rodajoelho1(double inc);
        void Rodaquadrail2(double inc);
        void Rodaquadrail1op (double inc);
        void Rodaquadrail2op (double inc);
        void Rodajoelho1op (double inc);
        void Rodajoelho2op (double inc);
        void Rodajoelho2(double inc);
        void Rodaeixoy(double inc);
        bool Atingido(Tiro* tiro);
        Tiro* Atira();
        void Desenha(){ 
            DesenhaJogador(x,y,z);
        };

};
#endif // JOGADOR_H_s