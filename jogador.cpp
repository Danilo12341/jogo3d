#include "jogador.h"
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glu.h>
float PI2=3.1416;


void Jogador::setCx(const double cx){
    this->cx = cx;
}
double Jogador:: getCx(){
   return this->cx;
}

double Jogador::geteixoy(){
    return this->eixoy;
}
double Jogador::getzf(){
   return  this->setz;
}

void Jogador::setCz(const double cz){
    this->cz = cz;
}
void Jogador::setzf(const double cz){
    this->setz = cz;
}

  
double Jogador:: getCz(){
   return this->cz;
}
void Jogador::setCy(const double cy){
    this->cy = cy;
}
double Jogador::getThetabraco(){
    return this->Thetabraco;
}
double Jogador:: getCy(){
   return this->cy;
}
void Jogador::setRaio(const double raio){
    this->raio = raio;
}
double Jogador::getRaio(){
   return this->raio;
}
void Jogador::setCor(const string cor){
    this->cor = cor;
}
string Jogador:: getCor(){
   return this->cor;
}

int  Jogador::getparadodireita(){
    return this->paradodireita;
}
        
void  Jogador::setparadodireita(int valor){
      this->paradodireita=valor;
}

void Jogador::MoveEmX(double dx,GLdouble deltaTime, double eixoy2)
{
   double angulo = (eixoy2*(3.14)/180);
   this->cx += dx*deltaTime*cos(angulo);

}
void Jogador::MoveEmZ(double dz,GLdouble deltaTime, double eixoy2)
{
   double angulo = (eixoy2*(3.14)/180);
   this->cz += dz*deltaTime*sin(angulo);
  
}
void Jogador::MoveEmY(double dy,GLdouble deltaTime)
{
   this->cy += (dy*deltaTime);
    
}
void Jogador::RodaBracoup(double inc){
 
         
    if (Thetabraco > -45){
        Thetabraco += inc;
        
    }
     
}
void Jogador::RodaBracoesq(double inc){
 
    //cout <<  Thetabracoz << endl;
    if (Thetabracoz > -45){
        Thetabracoz += inc;
        
    }
     
}
void Jogador::RodaBracodir(double inc){
 
         
    if (Thetabracoz < 45){
        Thetabracoz += inc;
        
    }
     
}
void Jogador::RodaBracodown(double inc){
 
    if (Thetabraco < 45){
        Thetabraco += inc;
        
    }    
}
void Jogador::Rodaquadrail1op (double inc)
{
    
    if(Thetaquadril1 < 46 && voltandoperna1op == 0 && andarop == 0){
        Thetaquadril1+= inc;
    }else{
        if(andarop==0){
        voltandoperna1op =1;
        if (voltandoperna1op==1)
             Thetaquadril1-= inc;
        if(Thetaquadril1 == 0){
            voltandoperna1op=0;
            andarop =1;
        }
      }

    }
}
void Jogador::Rodaquadrail2op (double inc)

{
    if(Thetaquadril2 < 46 && voltandoperna2op == 0 && andarop == 1 ){      
     Thetaquadril2+= inc;
    }else{
      if(andarop==1){
        voltandoperna2op =1;
        if (voltandoperna2op==1)
        Thetaquadril2-= inc;
        if(Thetaquadril2== 0){
            voltandoperna2op=0;
            andarop=0;
        }
      }

    } 
}
void Jogador::Rodaquadrail1 (double inc)
{
    if(Thetaquadril1 > -46 && voltandoperna1 == 0 && andar == 0){
        
        Thetaquadril1+= inc;
    }else{
      if(andar==0){
        voltandoperna1 =1;
        if (voltandoperna1==1)
        Thetaquadril1-= inc;
        if(Thetaquadril1 == 0){
            voltandoperna1=0;
            andar =1;
        }
      }

    }    
    
}

void Jogador::Rodaquadrail2 (double inc)
{
    if(Thetaquadril2 > -46 && voltandoperna2 == 0 && andar == 1 ){
        
        Thetaquadril2+= inc;
    }else{
      if(andar==1){
        voltandoperna2 =1;
        if (voltandoperna2==1)
        Thetaquadril2-= inc;
        if(Thetaquadril2 == 0){
            voltandoperna2=0;
            andar =0;
        }
      }

    }    
    
}
void Jogador::Rodajoelho1op (double inc)

{   

    if(Thetajoelho1 > -60 && voltandojoelho1op == 0){
      Thetajoelho1 += inc;
      
    }else{
        voltandojoelho1op=1;
        if(voltandojoelho1op==1){
           Thetajoelho1 -= inc;
        }
        if(Thetajoelho1 ==0){
            voltandojoelho1op=0;
        }
    }
    
    
}
void Jogador::Rodajoelho2op (double inc)

{   
    if(Thetajoelho2 > -60 && voltandojoelho2op == 0){
      Thetajoelho2 += inc;
      
    }else{
        voltandojoelho2op=1;
        if(voltandojoelho2op==1){
           Thetajoelho2 -= inc;
        }
        if(Thetajoelho2 ==0){
            voltandojoelho2op=0;
        }
    }
    
    
}

void Jogador::Rodajoelho1 (double inc)
{   
    
    if(Thetajoelho1 < 60 && voltandojoelho1 == 0){
      Thetajoelho1 += inc;
      
    }else{
        voltandojoelho1=1;
        if(voltandojoelho1==1){
           Thetajoelho1 -= inc;
        }
        if(Thetajoelho1 ==0){
            voltandojoelho1=0;
        }
    }
    
    
}
void Jogador::Rodajoelho2 (double inc)
{   
    if(Thetajoelho2 < 60 && voltandojoelho2 == 0){
      Thetajoelho2 += inc;
      
      
    }else{
        voltandojoelho2=1;
        if(voltandojoelho2==1){
           Thetajoelho2 -= inc;
        }
        if(Thetajoelho2 ==0){
            voltandojoelho2=0;
        }
    }
    
    
}
void Jogador::Rodaeixoy(double inc){
      this->eixoy += inc;
      
}
void mudarcor(GLfloat R,GLfloat G,GLfloat B){

    GLfloat materialEmission[] = { 0.00, 0.00, 0.00, 1.00};
    GLfloat materialColor[] = { R, G, B, 1.0};
    GLfloat mat_specular[] = { 0, 0,0, 1.0};
    GLfloat mat_shininess[] = { 128 };
    glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);
    glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, materialColor);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

}

void Jogador::Desenhacirculo(double x, double y,double z,double R, double G, double B){

   
  
    if(this->cor=="green"){ 
        glPushMatrix();
        glColor3f(1,1,1);
        glTranslatef(x,y-0.15*this->raio,z);
        glRotatef(eixoy, 0, 1, 0);
        Desenhacorpo(0,0.15*this->raio,0,0,255,0);
        mudarcor(0,1,0);
        glScalef(this->raio*0.2,this->raio*0.3,this->raio*0.15);
        glutSolidCube(1);
        glPopMatrix();
      
    }else{   
        glPushMatrix();
        glColor3f(1,0,0);
        glTranslatef(x,y-0.15*this->raio,z);
        glRotatef(eixoy, 0, 1, 0);
        Desenhacorpo(0,0.15*this->raio,0,0,255,0);
        mudarcor(1,0,0);
        glScalef(this->raio*0.2,this->raio*0.3,this->raio*0.15);
        glutSolidCube(1);
        glPopMatrix();

    }
}

void Jogador::DesenhaRect(double altura,double largura,double R, double G, double B){
    glColor3f(R, G, B);
    glBegin(GL_POLYGON);
        glVertex2f(0,0);
        glVertex2f(largura,0);
        glVertex2f(largura,altura);
        glVertex2f(0,altura);
    glEnd();
}

void Jogador::DesenhaRect2(double x,double y,double z, double R,double G, double B){

        glPushMatrix();
        glColor3f(R,G,B);
        glScalef(x,y,z);
        glutSolidCube(1);
        glPopMatrix();
   
}

void Jogador::Desenhacorpo(double x,double y,double z,double R, double G, double B){

 
    glPushMatrix(); 
    mudarcor(1,1,0);
    Desenhabraco(x,y,z,255,255,0);
    Desenhabraco2(x,y,z,255,255,0);
    Desenhaarma(x,y,z,255,255,0);
    Desenhaperna1(x,y,z,0,255,0);
    Desenhaperna2(x,y,z,0,255,0);
    mudarcor(0,1,0);
    glTranslatef(x,y+(0.7/2)*this->raio,z); // put in one end
    glScalef(0.2*this->raio,0.7*this->raio,0.3*this->raio);
    glutSolidCube(1);
    glPopMatrix();

}
void Jogador::Desenhaarma(double x,double y,double z,double R, double G, double B){
    if(this->cor == "green"){
        glPushMatrix();
        mudarcor(0,1,0);
        glColor3f(0,1,0);
        glTranslatef(x+0.1*this->raio,y+0.1*this->raio,z);
        glRotatef(Thetabraco, 0, 0, 1); 
       // glRotatef(Thetabracoz, 0, 1, 0);
        glTranslatef(0.25*this->raio,0,0);
        DesenhaRect2(0.5*this->raio,0.1*this->raio,0.05*this->raio,0,0,0);
        glTranslatef(0.25*this->raio,0,0);
        DesenhaRect2(0.1*this->raio,0.15*this->raio,0.3*this->raio,0,0,0);
        glTranslatef(0,0.15*this->raio,0);
        DesenhaRect2(0.1*this->raio,0.3*this->raio,0.05*this->raio,0,0,0);
        glTranslatef(0.1*this->raio,-0.15*this->raio,0);
        DesenhaRect2(0.25*this->raio,0.1*this->raio,0.05*this->raio,0,0,0);
        glPopMatrix();   
    }

}
void Jogador::Desenhabraco(double x,double y,double z,double R, double G, double B){
    if(this->cor == "green"){
        glPushMatrix();
        glColor3f(0,1,0);
        glTranslatef(x+0.1*this->raio,y+0.1*this->raio,z-0.15*this->raio);
        glRotatef(Thetabraco, 0, 0, 1); 
       // glRotatef(Thetabracoz, 0, 1, 0);
        glTranslatef(0.25*this->raio,0,0);
        DesenhaRect2(0.5*this->raio,0.1*this->raio,0.05*this->raio,0,0,0);
        //glTranslatef(0.35*this->raio,0,0);
        //DesenhaRect2(0.1*this->raio,0.3*this->raio,0.05*this->raio,0,0,0);
        //glTranslatef(0.1*this->raio,-0.2*this->raio,0);
        //DesenhaRect2(0.5*this->raio,0.1*this->raio,0.05*this->raio,0,0,0);
        glPopMatrix();   
    }
    if(this->cor == "red"){
        glPushMatrix();
        glColor3f(0,1,0);
        glTranslatef(x,y+0.1*this->raio,z-0.125*this->raio);
        glRotatef(Thetabraco, 0, 0, 1);
        glTranslatef(-0.35*this->raio,0,0);
        DesenhaRect2(0.5*this->raio,0.1*this->raio,0.05*this->raio,0,0,0);
        glTranslatef(-0.35*this->raio,0,0);
        DesenhaRect2(0.1*this->raio,0.3*this->raio,0.05*this->raio,0,0,0);
        glTranslatef(-0.1*this->raio,-0.2*this->raio,0);
        DesenhaRect2(0.5*this->raio,0.1*this->raio,0.05*this->raio,0,0,0);
        glPopMatrix();   
    }
}

void Jogador::Desenhabraco2(double x,double y,double z,double R, double G, double B){
    if(this->cor == "green"){
        glPushMatrix();
        glColor3f(0,1,0);
        glTranslatef(x+0.1*this->raio,y+0.1*this->raio,z+0.15*this->raio);
        glRotatef(Thetabraco, 0, 0, 1); 
       // glRotatef(Thetabracoz, 0, 1, 0);
        glTranslatef(0.25*this->raio,0,0);
        DesenhaRect2(0.5*this->raio,0.1*this->raio,0.05*this->raio,0,0,0);
        //glTranslatef(0.35*this->raio,0,0);
        //DesenhaRect2(0.1*this->raio,0.3*this->raio,0.05*this->raio,0,0,0);
        //glTranslatef(0.1*this->raio,-0.2*this->raio,0);
        //DesenhaRect2(0.5*this->raio,0.1*this->raio,0.05*this->raio,0,0,0);
        glPopMatrix();   
    }
    if(this->cor == "red"){
        glPushMatrix();
        glColor3f(0,1,0);
        glTranslatef(x,y+0.1*this->raio,z+0.125*this->raio);
        glRotatef(Thetabraco, 0, 0, 1);
        glTranslatef(-0.35*this->raio,0,0);
        DesenhaRect2(0.5*this->raio,0.1*this->raio,0.05*this->raio,0,0,0);
        glTranslatef(-0.35*this->raio,0,0);
        DesenhaRect2(0.1*this->raio,0.3*this->raio,0.05*this->raio,0,0,0);
        glTranslatef(-0.1*this->raio,-0.2*this->raio,0);
        DesenhaRect2(0.5*this->raio,0.1*this->raio,0.05*this->raio,0,0,0);
        glPopMatrix();   
    }
}
void Jogador::Desenhaperna1 (double x,double y,double z,double R, double G, double B){
    
    if(this->cor=="green"){
        glPushMatrix();
        mudarcor(1,1,0);
        glTranslatef(x,y+0.7*this->raio,z-(0.15/2)*this->raio);
        glRotatef(Thetaquadril1, 0, 0, 1);
        glTranslatef(0,0.2*this->raio,0);
        DesenhaRect2(0.1*this->raio,0.4*this->raio,(0.1)*this->raio,0,0,0);
        glTranslatef(0,0.25*this->raio,0);
        Desenhaosso1((0.1/2)*this->raio,0.1*this->raio,(0.1/2)*this->raio,0,0,0);
        glTranslatef(0,0.05*this->raio,0);
        glRotatef(Thetajoelho1, 0, 0, 1);
        mudarcor(1,1,0);
        glTranslatef(0,0.2*this->raio,0);
        DesenhaRect2((0.1/2)*this->raio,0.4*this->raio,(0.1/2)*this->raio,0,0,0);
        glTranslatef((0.1/2)*this->raio,0.25*this->raio,0);
        DesenhaRect2(0.1*this->raio,0.1*this->raio,(0.1/2)*this->raio,0,0,0);
        glPopMatrix(); 
    } else{
        glPushMatrix();
        mudarcor(1,1,0);
        glTranslatef(x,y+0.7*this->raio,z-(0.15/2)*this->raio);
        glRotatef(Thetaquadril1, 0, 0, 1);
        glTranslatef(0,0.2*this->raio,0);
        DesenhaRect2(0.1*this->raio,0.4*this->raio,(0.1)*this->raio,0,0,0);
        glTranslatef(0,0.25*this->raio,0);
        Desenhaosso1((0.1/2)*this->raio,0.1*this->raio,(0.1/2)*this->raio,0,0,0);
        glTranslatef(0,0.05*this->raio,0);
        glRotatef(Thetajoelho1, 0, 0, 1);
        mudarcor(1,1,0);
        glTranslatef(0,0.2*this->raio,0);
        DesenhaRect2((0.1/2)*this->raio,0.4*this->raio,(0.1/2)*this->raio,0,0,0);
        glTranslatef(-(0.1/2)*this->raio,0.25*this->raio,0);
        DesenhaRect2(0.1*this->raio,0.1*this->raio,(0.1/2)*this->raio,0,0,0);
        glPopMatrix();   

    }


}
void Jogador::Desenhaosso1 (double x,double y,double z, double R,double G, double B){   
       
        glPushMatrix();
        mudarcor(1,0,0);
        glScalef(x,y,x);
        glutSolidCube(1);
        glutSolidSphere(1, 100, 200);
        glPopMatrix();

}
void Jogador::Desenhaperna2(double x,double y,double z,double R, double G, double B){
       if(this->cor=="green"){
        glPushMatrix();
        mudarcor(1,1,0);
        glTranslatef(x,y+0.7*this->raio,z+(0.15/2)*this->raio);
        glColor3f(1,1,0);
        glRotatef(Thetaquadril2, 0, 0, 1);
        glTranslatef(0,0.2*this->raio,0);
        DesenhaRect2(0.1*this->raio,0.4*this->raio,(0.1)*this->raio,0,0,0);
        glTranslatef(0,0.25*this->raio,0);
        Desenhaosso1((0.1/2)*this->raio,0.1*this->raio,(0.1/2)*this->raio,0,0,0);
        glTranslatef(0,0.05*this->raio,0);
        glRotatef(Thetajoelho2, 0, 0, 1);
        glTranslatef(0,0.2*this->raio,0);
        mudarcor(1,1,0);
        DesenhaRect2((0.1/2)*this->raio,0.4*this->raio,(0.1/2)*this->raio,0,0,0);
        glTranslatef((0.1/2)*this->raio,0.25*this->raio,0);
        DesenhaRect2(0.1*this->raio,0.1*this->raio,(0.1/2)*this->raio,0,0,0);
        glPopMatrix(); 
    } else{
        glPushMatrix();
        mudarcor(1,1,0);
        glColor3f(1,1,0);
        glTranslatef(x,y+0.7*this->raio,z+(0.15/2)*this->raio);
        glRotatef(Thetaquadril2, 0, 0, 1);
        glTranslatef(0,0.2*this->raio,0);
        DesenhaRect2(0.1*this->raio,0.4*this->raio,(0.1)*this->raio,0,0,0);
        glTranslatef(0,0.25*this->raio,0);
        Desenhaosso1((0.1/2)*this->raio,0.1*this->raio,(0.1/2)*this->raio,0,0,0);
        glTranslatef(0,0.05*this->raio,0);
        glRotatef(Thetajoelho2, 0, 0, 1);
        glTranslatef(0,0.2*this->raio,0);
        mudarcor(1,1,0);
        DesenhaRect2((0.1/2)*this->raio,0.4*this->raio,(0.1/2)*this->raio,0,0,0);
        glTranslatef(-(0.1/2)*this->raio,0.25*this->raio,0);
        DesenhaRect2(0.1*this->raio,0.1*this->raio,(0.1/2)*this->raio,0,0,0);
        glPopMatrix();   

    }
}
void Jogador::DesenhaJogador(double x,double y,double z){
    glPushMatrix();
    glTranslatef(x,y-1.7*this->raio,z);
    Desenhacirculo(this->cx,this->cy,this->cz,0,255,0);
    glPopMatrix();
}

Tiro* Jogador::Atira() {
    
    if(this->cor == "green"){
        int radius = this->raio*0.1;
        int Angule = Thetabraco;
        int Angule2 = this->eixoy;
        int firstX = (this->cx+2) + radius * sin(-Angule * M_PI / 180)*radius*cos(-(Angule2) * M_PI / 180);
        int firstY = (this->cy - 1.5*this->raio) +  radius * cos(-Angule * M_PI / 180);
        int firstZ = (this->cz) +  radius * sin(-Angule * M_PI / 180)*radius*sin(-(Angule2)* M_PI / 180);
        cout << Angule2 << endl;
        return new Tiro(firstX ,firstY, firstZ, Angule-90,Angule2);
    }else{
        int radius = this->raio*0.1;
        int Angule = Thetabraco;
        int Angule2 = this->eixoy;
        int firstX = this->cx +  radius * sin(-Angule * M_PI / 180);
        int firstY = (this->cy-1.7*this->raio) +  radius * cos(-Angule * M_PI / 180);
        int firstZ = this->cz;
        return new Tiro(firstX ,firstY,firstZ, Angule - 270,0);

    }
}

 void Jogador::resetarthetas(){

    this->Thetabraco=0;
    this->Thetaquadril1=0;
    this->Thetajoelho1=0;
    this->Thetaquadril2=0;
    this->Thetajoelho2=0;

    voltandoperna1 = 0;
    voltandojoelho1 = 0;
    voltandoperna2 = 0;
    voltandojoelho2 = 0;
    andar =0;
    voltandoperna1op=0;
    voltandoperna2op=0;
    andarop = 0;
    voltandojoelho1op=0;
    voltandojoelho2op=0;
            
}

bool Jogador::Atingido(Tiro* tiro) {
    GLfloat posx, posy,posz;
    tiro->GetPos(posx, posy,posz);
    //cout << "posx = " << posx << " posy = " << posy << endl;

    if(posx > (this->getCx()- this->getRaio()*0.3) && posx < (this->getCx()+ this->getRaio()*0.3)
    && posy > this->getCy()-2*this->getRaio() && posy < (this->getCy()) 
    && posz > this->getCz()-0.15*this->getRaio() && posz < this->getCz()+0.15*this->getRaio()
    ){
         return 1;
     }else{
         return 0;
     }
              
    
}