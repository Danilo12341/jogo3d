#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include "tinyxml.h"
#include <math.h>
#include "circulo.h"
#include "retangulo.h"
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include "jogador.h"
#define windowSize 500
#define TAMANHO_JANELA 500
#define INC_KEY 0.02
#define INC_ANG 1
#define INC_KEYIDLE 0.01

using namespace std;
vector<Circulo> circulos;
vector<Retangulo> retangulos;
Retangulo arena;
Circulo jogador1;
Jogador jogadorplay1;
Jogador jogadorplay1inicial;
vector<Jogador> jogadores;
vector<Jogador> jogadoresInicial;
double camXYAngle=0;
double camXZAngle=0;
int zoom=1;
int lastX = 0;
int lastY = 0;
int buttonDown=0;
int valorx,valorz=0;
int z=0;
int morte=0;
int contadorClicks = 0;
int night=false;
double gravidade;
bool fim = false;
bool morreu = false;
bool pular = false;
bool first_person = false;
bool cam_gun = false;
bool third_person = false;
bool person = true;
//Key status
int keyStatus[256];
Tiro* tiro = NULL;
Tiro* tiro2 = NULL;
Tiro* tiros[30];

int camerateste =1;


static GLdouble framerate = 0;
int teste=0;
void * timesRoman = GLUT_BITMAP_TIMES_ROMAN_24;
static char str[2000];


bool loadXml(char** argv){
    TiXmlDocument doc;
	string diretorio = argv[1];
	/*strcat(argv[1], "arena_teste.svg");*/
	if(!doc.LoadFile(argv[1])){
		cout << "Falha ao abrir o svg Certifique-se que contém o arquivo arena_teste.svg no diretorio " << diretorio << endl;
		return false;
	}
	TiXmlElement* root = doc.FirstChildElement();
    if ( NULL != root){
       for(TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()){
            std::string elemName = elem->Value();
            const char* attr;
            Circulo c;
            Retangulo r;
            if(elemName == "rect"){	
                
                attr = elem->Attribute("width");
                if(attr != NULL)
                   r.setWidth(atof(attr));

                attr = elem->Attribute("height");
                if(attr != NULL)
                   r.setHeight(atof(attr));

                attr = elem->Attribute("x");
                if(attr != NULL)
                    r.setRx(atof(attr));

                attr = elem->Attribute("y");
                if(attr != NULL)
                   r.setRy(atof(attr));

                attr = elem->Attribute("fill");
                if(attr != NULL)
                    r.setCor(attr);

              retangulos.push_back(r);
            }
            else if(elemName == "circle"){

              
                attr = elem->Attribute("cx");
                if(attr != NULL)
                  c.setCx(atof(attr));

                attr = elem->Attribute("cy");
                if(attr != NULL)
                   c.setCy(atof(attr));

                attr = elem->Attribute("r");
                if(attr != NULL)
                   c.setRaio(atof(attr));

                attr = elem->Attribute("fill");
                if(attr != NULL)
                   c.setCor(attr);

                circulos.push_back(c);
               		    
            }
       }
    }
    doc.Clear();
	return true;
}
void resetar(){
    
   jogadores =jogadoresInicial;
   jogadorplay1 =jogadorplay1inicial;
   jogadorplay1.resetarthetas();
   first_person = false;
   cam_gun = false;
   third_person = false;
   person = true;
   morreu = false;
   valorx=0;
   valorz=0;
   z=0;
   morte=0;

   for(int i=0;i<jogadores.size();i++){
       jogadores[i].resetarthetas();
   }

   
  
}
void changeCamera(int angle, int w, int h)
{
    glMatrixMode (GL_PROJECTION);

    glLoadIdentity ();

    gluPerspective (angle, 
            (GLfloat)w / (GLfloat)h, 1, 150.0);

    glMatrixMode (GL_MODELVIEW);
}




void keyup(unsigned char key, int x, int y)
{
    keyStatus[(int)(key)] = 0;
    glutPostRedisplay();
}



void ResetKeyStatus()
{
    int i;
    //Initialize keyStatus
    for(i = 0; i < 256; i++)
       keyStatus[i] = 0; 
}
int valor =1;


void salvainicial(){


    jogadoresInicial = jogadores;
    jogadorplay1inicial = jogadorplay1;

   
}
void desenhajogadormap(Jogador jogador, double posx, double posy){

        double varix=(jogador.getRaio()/arena.getWidth())/3.7;
        double variy=(jogador.getRaio()/arena.getHeight())/4;
        if(jogador.getCor()=="green"){
          glColor3f(0, 255, 0);
        }else{
          glColor3f(255,0, 0);
        }
        
        glBegin(GL_POLYGON);
            glVertex2f(posx,posy);
            glVertex2f(posx+varix,posy);
            glVertex2f(posx+varix,posy-variy);
            glVertex2f(posx,posy-variy);
        glEnd();

}
void RasterChars(GLfloat x, GLfloat y, GLfloat z, const char * text, double r, double g, double b)
{
       //Push to recover original attributes
        glPushAttrib(GL_ENABLE_BIT);
        glDisable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);
        //Draw text in the x, y, z position

        
        double mx = (1-0.75)/((arena.getRx()+arena.getWidth())-arena.getRx());
        double posjogadorx = mx*(jogadorplay1.getCx()-arena.getRx())+0.75;
        
        double my = (1-0.875)/((arena.getRy()+arena.getHeight())-arena.getRy());
        double posjogadory = my*(jogadorplay1.getCy()-arena.getRy())+0.875;
         //cout << mx<< endl;
         //cout << jogadorplay1.getCx()<< endl;
         //cout << posjogadorx<< endl;
         //cout << posjogadory<< endl;
    

        double tamanhoy = (0.25* arena.getWidth())/arena.getWidth();
        glColor3f(255,255,255);
        glBegin(GL_LINES);
            glVertex2f(0.75,0.875); // linha 1
            glVertex2f(1,0.875);
            glVertex2f(0.75,1); // linha 2
            glVertex2f(1,1); 
            glVertex2f(0.75,1); // linha 3
            glVertex2f(0.75,0.875);
            glVertex2f(1,1); // linha 4
            glVertex2f(1,0.875);
        glEnd();
        
        desenhajogadormap(jogadorplay1,posjogadorx,posjogadory);

        for(int i=0;i<jogadores.size();i++){
            if(jogadores[i].getCor()=="red"){
                double posjogadorxi = mx*(jogadores[i].getCx()-arena.getRx())+0.75;
                double posjogadoryi = my*(jogadores[i].getCy()-arena.getRy())+0.875;
                desenhajogadormap(jogadores[i],posjogadorxi,posjogadoryi);

            }
        }
        for(int i=0;i<retangulos.size();i++){
            if(retangulos[i].getCor() == "black"){
                
              double posrecx = mx*(retangulos[i].getRx()-arena.getRx())+0.75;
              double posrecxlar = mx*((retangulos[i].getRx()+ retangulos[i].getWidth())-arena.getRx())+0.75;
              double posrecy = my*(retangulos[i].getRy()-arena.getRy())+0.875;
              double posrecyalt = my*(((retangulos[i].getRy()+retangulos[i].getHeight()))-arena.getRy())+0.875;
               glColor3f(1,1,1);
               glBegin(GL_POLYGON);
               glVertex2f(posrecx,posrecyalt);
               glVertex2f(posrecxlar,posrecyalt);
               glVertex2f(posrecxlar,posrecy);
               glVertex2f(posrecx,posrecy);
               glEnd();
            }
        }

        glRasterPos3f(x, y, z);
        const char* tmpStr;
        tmpStr = text;
        while( *tmpStr ){
            glutBitmapCharacter(timesRoman, *tmpStr);
            tmpStr++;
        }
    glPopAttrib();
}

void PrintText(GLfloat x, GLfloat y, const char * text, double r, double g, double b)
{
    //Draw text considering a 2D space (disable all 3d features)
    glMatrixMode (GL_PROJECTION);
    //Push to recover original PROJECTION MATRIX
    glPushMatrix();
        glClear (GL_COLOR_BUFFER_BIT );
        glLoadIdentity ();
        glOrtho (0, 1, 1, 0, -1, 1);
       
      
        RasterChars(x, y, 0, text, r, g, b);
    glPopMatrix();
    glMatrixMode (GL_MODELVIEW);
}



void ganhou()
{   

    jogadorplay1.setCx(arena.getRx() + arena.getWidth()+1000);
    jogadorplay1.setCy(arena.getRy()+arena.getHeight());
    jogadorplay1.setCz(0);
    glColor3ub(0,255,255);
    char *tmpStr;
    sprintf(str, "You Win, Press r to Reset");
    glRasterPos2f(jogadorplay1.getCx()-30, jogadorplay1.getCy()-20);
    tmpStr = str;
    while( *tmpStr ){
        glutBitmapCharacter(timesRoman, *tmpStr);
        tmpStr++;
    }
}
void perdeu()
{   
    
    jogadorplay1.setCx(arena.getRx() + arena.getWidth()+1000);
    jogadorplay1.setCy(arena.getRy()+arena.getHeight());
    jogadorplay1.setCz(0);
    glColor3ub(0,255,255);
    char *tmpStr;
    sprintf(str, "Game Over, Press r to Reset");
    glRasterPos2f(jogadorplay1.getCx()-30, jogadorplay1.getCy()-20);
    tmpStr = str;
    while( *tmpStr ){
        glutBitmapCharacter(timesRoman, *tmpStr);
        tmpStr++;
    }
}


void init(void)
{
  glClearColor(0.0, 0.0,0.0, 0.0);
  glShadeModel (GL_SMOOTH);
  glEnable(GL_CULL_FACE);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);
  glViewport (0, 0, (GLsizei) windowSize, (GLsizei) windowSize);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective (60, 1, 1, 500);

}

int colisao(Jogador jog1, vector<Retangulo> regantulo){
   
    for (int p = 0; p < regantulo.size(); p++){
        if (regantulo[p].getCor() == "black"){
            if(jog1.getCx() > regantulo[p].getRx() && jog1.getCx() < (regantulo[p].getRx()+regantulo[p].getWidth())
               && jog1.getCy() > regantulo[p].getRy() && jog1.getCy() < (regantulo[p].getRy()+regantulo[p].getHeight())
               && jog1.getCz() > -(regantulo[p].getHeight()/4) &&  jog1.getCz() < (regantulo[p].getHeight()/4)
               && (jog1.getCz()-0.15*jog1.getRaio() > -(regantulo[p].getHeight()/4) &&  jog1.getCz()+0.15*jog1.getRaio() < (regantulo[p].getHeight()/4)
                ||  jog1.getCz()+0.15*jog1.getRaio() > -(regantulo[p].getHeight()/4) &&  jog1.getCz()-0.15*jog1.getRaio() < -(regantulo[p].getHeight()/4) 
                ||  jog1.getCz()+0.15*jog1.getRaio() > (regantulo[p].getHeight()/4) &&  jog1.getCz()-0.15*jog1.getRaio() < (regantulo[p].getHeight()/4))
               ){
                return 1;
              
            }
           
        }
        
    }
    return 0;       
}

int colisao3(Jogador jog1, vector<Retangulo> regantulo){
   
    for (int p = 0; p < regantulo.size(); p++){
        if (regantulo[p].getCor() == "black"){
            if(jog1.getCx() > regantulo[p].getRx()+jog1.getRaio()*0.5 && jog1.getCx() < (regantulo[p].getRx()+regantulo[p].getWidth()-jog1.getRaio()*0.5)
               && jog1.getCy() > regantulo[p].getRy() && jog1.getCy() < (regantulo[p].getRy()+regantulo[p].getHeight()))
             
             {
                return 1;
              
            }
           
        }
        
    }
    return 0;       
}


int colisadodireita(Jogador jog1, vector<Retangulo> regantulo){

    for (int p = 0; p < regantulo.size(); p++){
        if (regantulo[p].getCor() == "black"){
            if(jog1.getCx()+jog1.getRaio()*0.3 > regantulo[p].getRx() && jog1.getCx()+jog1.getRaio()*0.3 < regantulo[p].getRx()+regantulo[p].getWidth()
               && (jog1.getCy()-2*jog1.getRaio() > regantulo[p].getRy() && jog1.getCy()-2*jog1.getRaio() < regantulo[p].getRy()+regantulo[p].getHeight()
              || jog1.getCy()-0.2*jog1.getRaio() > regantulo[p].getRy() && jog1.getCy()-0.2*jog1.getRaio() < regantulo[p].getRy()+regantulo[p].getHeight()
              || jog1.getCy()-2*jog1.getRaio() < regantulo[p].getRy() && jog1.getCy() > regantulo[p].getRy()+regantulo[p].getHeight())
                && (jog1.getCz()-0.15*jog1.getRaio() > -(regantulo[p].getHeight()/4) &&  jog1.getCz()+0.15*jog1.getRaio() < (regantulo[p].getHeight()/4)
                ||  jog1.getCz()+0.15*jog1.getRaio() > -(regantulo[p].getHeight()/4) &&  jog1.getCz()-0.15*jog1.getRaio() < -(regantulo[p].getHeight()/4) 
                ||  jog1.getCz()+0.15*jog1.getRaio() > (regantulo[p].getHeight()/4) &&  jog1.getCz()-0.15*jog1.getRaio() < (regantulo[p].getHeight()/4))
              ){
                jogadorplay1.setCx(jogadorplay1.getCx()-0.01);
                return 1;
              
            }
           
        }
        
    }
    return 0;

}

int colisadodireitainimigo(Jogador jog1, vector<Jogador> jogadores){

    for (int p = 0; p < jogadores.size(); p++){
        if (jogadores[p].getCor() == "red"){
            if(jog1.getCx()+jog1.getRaio()*0.3 > jogadores[p].getCx()-jogadores[p].getRaio()*0.3 && jog1.getCx()+jog1.getRaio()*0.3 < jogadores[p].getCx()+jogadores[p].getRaio()*0.3 
               && (jog1.getCy()-2*jog1.getRaio() > jogadores[p].getCy()-jogadores[p].getRaio()*2 && jog1.getCy()-2*jog1.getRaio() < jogadores[p].getCy() 
              || jog1.getCy()-0.2*jog1.getRaio() > jogadores[p].getCy()-jogadores[p].getRaio()*2 && jog1.getCy()-0.2*jog1.getRaio() < jogadores[p].getCy())
              && ((jog1.getCz()-jog1.getRaio()*0.15 > jogadores[p].getCz()-jogadores[p].getRaio()*0.15 && 
                  jog1.getCz()-jog1.getRaio()*0.15 < jogadores[p].getCz()+jogadores[p].getRaio()*0.15) ||
               (jog1.getCz()+jog1.getRaio()*0.15 > jogadores[p].getCz()-jogadores[p].getRaio()*0.15 && 
                 jog1.getCz()+jog1.getRaio()*0.15 < jogadores[p].getCz()+jogadores[p].getRaio()*0.15))
              
              )
            
    
             {
                
                return 1;
              
            }
           
        }
        
    }
    return 0;

}

int colisadoesquerdainimigo(Jogador jog1, vector<Jogador> jogadores){

    for (int p = 0; p < jogadores.size(); p++){
        if (jogadores[p].getCor() == "red"){
            if(jog1.getCx()-jog1.getRaio()*0.3 > jogadores[p].getCx()-jogadores[p].getRaio()*0.3 && jog1.getCx()-jog1.getRaio()*0.3 < jogadores[p].getCx()+jogadores[p].getRaio()*0.3 
               && (jog1.getCy()-2*jog1.getRaio() > jogadores[p].getCy()-jogadores[p].getRaio()*2 && jog1.getCy()-2*jog1.getRaio() < jogadores[p].getCy() 
              || jog1.getCy()-0.2*jog1.getRaio() > jogadores[p].getCy()-jogadores[p].getRaio()*2 && jog1.getCy()-0.2*jog1.getRaio() < jogadores[p].getCy())
                 && ((jog1.getCz()-jog1.getRaio()*0.15 > jogadores[p].getCz()-jogadores[p].getRaio()*0.15 && 
                  jog1.getCz()-jog1.getRaio()*0.15 < jogadores[p].getCz()+jogadores[p].getRaio()*0.15) ||
               (jog1.getCz()+jog1.getRaio()*0.15 > jogadores[p].getCz()-jogadores[p].getRaio()*0.15 && 
                 jog1.getCz()+jog1.getRaio()*0.15 < jogadores[p].getCz()+jogadores[p].getRaio()*0.15))
              )
            
    
             {
                
                return 1;
              
            }
           
        }
        
    }
    return 0;

}
int colisadoesquerdainimigo2(Jogador jog1, Jogador jog2){


    if(jog1.getCx()+jog1.getRaio()*0.3 > jog2.getCx()-jog2.getRaio()*0.3 && jog1.getCx()-jog1.getRaio()*0.3 < jog2.getCx()+jog2.getRaio()*0.3 
    && (jog1.getCy()-2*jog1.getRaio() > jog2.getCy()-jog2.getRaio()*2 && jog1.getCy()-2*jog1.getRaio() < jog2.getCy() 
    || jog1.getCy() > jog2.getCy()-jog2.getRaio()*2 && jog1.getCy() < jog2.getCy())
     && ((jog1.getCz()-jog1.getRaio()*0.15 > jog2.getCz()-jog2.getRaio()*0.15 && 
     jog1.getCz()-jog1.getRaio()*0.15 < jog2.getCz()+jog2.getRaio()*0.15) ||
      (jog1.getCz()+jog1.getRaio()*0.15 > jog2.getCz()-jog2.getRaio()*0.15 && 
     jog1.getCz()+jog1.getRaio()*0.15 < jog2.getCz()+jog2.getRaio()*0.15))
    )
            
     {
                
        return 1;
              
    }              
    return 0;

}
int colisadodireitainimigo2(Jogador jog1, Jogador jog2){


    if(jog1.getCx()-jog1.getRaio()*0.3 > jog2.getCx()-jog2.getRaio()*0.3 && jog1.getCx()-jog1.getRaio()*0.3 < jog2.getCx()+jog2.getRaio()*0.3 
    && (jog1.getCy()-2*jog1.getRaio() > jog2.getCy()-jog2.getRaio()*2 && jog1.getCy()-2*jog1.getRaio() < jog2.getCy() 
    || jog1.getCy() > jog2.getCy()-jog2.getRaio()*2 && jog1.getCy()< jog2.getCy())
     && ((jog1.getCz()-jog1.getRaio()*0.15 > jog2.getCz()-jog2.getRaio()*0.15 && 
     jog1.getCz()-jog1.getRaio()*0.15 < jog2.getCz()+jog2.getRaio()*0.15) ||
      (jog1.getCz()+jog1.getRaio()*0.15 > jog2.getCz()-jog2.getRaio()*0.15 && 
     jog1.getCz()+jog1.getRaio()*0.15 < jog2.getCz()+jog2.getRaio()*0.15)
      )
    )
            
     {
                
        return 1;
              
    }
                 
    return 0;

}


int colisadoesquerda(Jogador jog1, vector<Retangulo> regantulo){

    for (int p = 0; p < regantulo.size(); p++){
        if (regantulo[p].getCor() == "black"){
            if(jog1.getCx()-jog1.getRaio()*0.3 > regantulo[p].getRx() && jog1.getCx()-jog1.getRaio()*0.3 < regantulo[p].getRx()+regantulo[p].getWidth()
               && (jog1.getCy()-2*jog1.getRaio() > regantulo[p].getRy() && jog1.getCy()-2*jog1.getRaio() < regantulo[p].getRy()+regantulo[p].getHeight()
              || jog1.getCy()-0.2*jog1.getRaio() > regantulo[p].getRy() && jog1.getCy()-0.2*jog1.getRaio() < regantulo[p].getRy()+regantulo[p].getHeight()
              || jog1.getCy()-2*jog1.getRaio() < regantulo[p].getRy() && jog1.getCy() > regantulo[p].getRy()+regantulo[p].getHeight())
                 && (jog1.getCz()-0.15*jog1.getRaio() > -(regantulo[p].getHeight()/4) &&  jog1.getCz()+0.15*jog1.getRaio() < (regantulo[p].getHeight()/4)
                ||  jog1.getCz()+0.15*jog1.getRaio() > -(regantulo[p].getHeight()/4) &&  jog1.getCz()-0.15*jog1.getRaio() < -(regantulo[p].getHeight()/4) 
                ||  jog1.getCz()+0.15*jog1.getRaio() > (regantulo[p].getHeight()/4) &&  jog1.getCz()-0.15*jog1.getRaio() < (regantulo[p].getHeight()/4))
              )
             {
                jogadorplay1.setCx(jogadorplay1.getCx()+0.05);
                return 1;
              
            }
           
        }
        
    }
    return 0;

}
int colisadotopo(Jogador jog1, vector<Retangulo> regantulo){

    for (int p = 0; p < regantulo.size(); p++){
        if (regantulo[p].getCor() == "black"){
            if(jog1.getCy()-jog1.getRaio()*2 > regantulo[p].getRy() && jog1.getCy()-jog1.getRaio()*2 < regantulo[p].getRy()+regantulo[p].getHeight()
               && (jog1.getCx()-0.15*jog1.getRaio() > regantulo[p].getRx() && jog1.getCx()-0.15*jog1.getRaio() < regantulo[p].getRx()+regantulo[p].getWidth()
              || jog1.getCx()+0.15*jog1.getRaio() > regantulo[p].getRx() && jog1.getCx()+0.15*jog1.getRaio() < regantulo[p].getRx()+regantulo[p].getWidth()))
            
    
             {
            
                return 1;
              
            }
           
        }
        
    }
    return 0;

}
int colisadotopinimigo(Jogador jog1, vector<Jogador> jogadores){

    for (int p = 0; p < jogadores.size(); p++){
        if (jogadores[p].getCor() == "red"){
            if(jog1.getCy() > jogadores[p].getCy()-jogadores[p].getRaio()*2 && jog1.getCy() < jogadores[p].getCy()
               && (jog1.getCx()-0.3*jog1.getRaio() > jogadores[p].getCx()-jogadores[p].getRaio()*0.3 && jog1.getCx()-0.3*jog1.getRaio() < jogadores[p].getCx()+jogadores[p].getRaio()*0.3
              || jog1.getCx()+ 0.3*jog1.getRaio() > jogadores[p].getCx()-jogadores[p].getRaio()*0.3 && jog1.getCx()+0.3*jog1.getRaio() < jogadores[p].getCx()+jogadores[p].getRaio()*0.3)
              && ((jog1.getCz()-jog1.getRaio()*0.15 > jogadores[p].getCz()-jogadores[p].getRaio()*0.15 && 
                  jog1.getCz()-jog1.getRaio()*0.15 < jogadores[p].getCz()+jogadores[p].getRaio()*0.15) ||
               (jog1.getCz()+jog1.getRaio()*0.15 > jogadores[p].getCz()-jogadores[p].getRaio()*0.15 && 
                 jog1.getCz()+jog1.getRaio()*0.15 < jogadores[p].getCz()+jogadores[p].getRaio()*0.15)))
            
    
             {
                
                return 1;
              
            }
           
        }
        
    }
    return 0;

}

void keyPress(unsigned char key, int x, int y)
{
    switch (key)
    {     
        case '1':
              first_person = true;
              cam_gun = false;
              third_person = false;
              person = false; 
             break;
        case '2':
              first_person = false;
              cam_gun = true;
              third_person= false;
              person = false; 
             break;
        case '3':
              first_person = true;
              cam_gun = false;
              third_person= true;
              person = false; 
             break;
        case '4':
              first_person = false;
              cam_gun = false;
              third_person = false;
              person = true; 
             break;    
        case 's':
        case 'S':
             keyStatus[(int)('s')] = 1;
             break;
        case 'w':
        case 'W':
             keyStatus[(int)('w')] = 1;
             break;
        case ' ':
             if(jogadorplay1.getCy() > (arena.getRy()+arena.getHeight()) || colisao(jogadorplay1,retangulos) || colisadotopinimigo(jogadorplay1,jogadores)){
                  pular=true;         
              }
             break;
        case 'n':
        case 'N':
            if(night==0)
                night= 1;
            else if(night==1)
                night= 0;
            break;  
        case 'p':
        case 'P':
             valorx++;
             break;
        case 'O':
        case 'o':
             valorx--;
             break;
        case 'z':
        case 'Z':
             z++;
             break;
        case 'x':
        case 'X':
             morte++;
             break;
        case 'k':
        case 'K':
             valorz++;
             break;
        case 'L':
        case 'l':
             valorz--;
             break;
        case 'd':
        case 'D':
             jogadorplay1.Rodaeixoy(INC_ANG);
             break;
        case 'a':
        case 'A':
             jogadorplay1.Rodaeixoy(-INC_ANG);
             break;
        case '+':
            zoom++;
            break;
        case '-':
            zoom--;
             break;
        case 'r':
        case 'R':
             keyStatus[(int)('r')] = 1;
             break;
             
      
    }
    glutPostRedisplay();
}

void desenhaArena(){

    arena.DesenhaRect(0,0,1);
    for (int i = 0; i < retangulos.size(); i++){
        if(retangulos[i].getCor()=="black"){
          retangulos[i].DesenhaRect(1,1,0);
        }
    } 
}

void display(void)
{
   /* Limpar todos os pixels  */
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (fim == false){
        if(first_person){
            double ang2= jogadorplay1.geteixoy();
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluPerspective (60+zoom, 1, 1, 500);
            glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            PrintText(0.1, 0.1, "first_person", 0,1,-2);
            glRotatef(180, 0, 0, 1);
            gluLookAt(jogadorplay1.getCx(),jogadorplay1.getCy()-2*jogadorplay1.getRaio(),jogadorplay1.getCz(),
            jogadorplay1.getCx()+ 2*jogadorplay1.getRaio()*cos(-jogadorplay1.geteixoy()* M_PI / 180),
            jogadorplay1.getCy()-1.5*jogadorplay1.getRaio(),
            jogadorplay1.getCz()+ jogadorplay1.getRaio()*sin(-jogadorplay1.geteixoy()* M_PI / 180),
            0,1,0);
            

        }
        if(cam_gun){
            double camXYAngle1 = jogadorplay1.getThetabraco();
            glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            PrintText(0.1, 0.1, "cam_gun", 0,1,-2);
            glRotatef(180, 0, 0, 1);
            gluLookAt(jogadorplay1.getCx()+2,jogadorplay1.getCy()-1.4*jogadorplay1.getRaio(),jogadorplay1.getCz(),
            jogadorplay1.getCx()+5+sin(-jogadorplay1.geteixoy()* M_PI / 180),
            jogadorplay1.getCy()-1.4*jogadorplay1.getRaio()+cos(-jogadorplay1.geteixoy()* M_PI / 180),
            jogadorplay1.getCz(),
            0,1,0);
            glutPostRedisplay();


        }
        if(third_person){
            double ang2= jogadorplay1.geteixoy();
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluPerspective (60+zoom, 1, 1, 500);
            glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            PrintText(0.1, 0.1, "third_person", 0,1,-2);
            glRotatef(180, 0, 0, 1);
            gluLookAt(jogadorplay1.getCx()-15,jogadorplay1.getCy()-4*jogadorplay1.getRaio(),jogadorplay1.getCz()-2,
            jogadorplay1.getCx()+ 2*jogadorplay1.getRaio()*cos(-jogadorplay1.geteixoy()* M_PI / 180),
            jogadorplay1.getCy()-1.5*jogadorplay1.getRaio(),
            jogadorplay1.getCz()+ jogadorplay1.getRaio()*sin(-jogadorplay1.geteixoy()* M_PI / 180),
            0,1,0);
          
        }
        if(person){
            double ang2= jogadorplay1.geteixoy();
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluPerspective (60+zoom, 1, 1, 500);
            glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            PrintText(0.1, 0.1, "Personalizada", 0,1,-2);
            glRotatef(180, 0, 0, 1);
            gluLookAt(jogadorplay1.getCx()-20+valorx,jogadorplay1.getCy()-6*jogadorplay1.getRaio(),jogadorplay1.getCz()+valorz,
            jogadorplay1.getCx()+20,
            jogadorplay1.getCy()-2*jogadorplay1.getRaio(),
            jogadorplay1.getCz(),
            0,1,0);
            glutPostRedisplay();

        }
    }else{
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glRotatef(180, 0, 0, 1);
        gluLookAt(jogadorplay1.getCx()-45,jogadorplay1.getCy()-3*jogadorplay1.getRaio(),-8,jogadorplay1.getCx()+50,170,1,0,1,0);
        glutPostRedisplay();
       
    } 
    if (night==false){
       GLfloat light_position[] = {(GLfloat)arena.getRx(),(GLfloat)(arena.getRy() +arena.getHeight()-10), 0, 1.0 };
        glLightfv( GL_LIGHT0, GL_POSITION, light_position);
        glShadeModel (GL_FLAT);

    }
    if(night==true){
        GLfloat light_position[] = {(GLfloat)
        (GLfloat)jogadorplay1.getCx()+5,
        (GLfloat)(jogadorplay1.getCy() -2*jogadorplay1.getRaio()), 
        (GLfloat)jogadorplay1.getCz(), 
        1.0 };
        glLightfv( GL_LIGHT0, GL_POSITION, light_position);
        glShadeModel (GL_FLAT);
        
        
    }
    
   
    /*jogador1.Desenhacirculo(0,255,0); 
     jogadorplay1.getCy() > (91.6-4.2*jogadorplay1.getRaio()
    */
    desenhaArena();
   
    if(jogadorplay1.getCx() > arena.getRx()+ arena.getWidth() || morreu== true){
         fim = true;
         if(morreu==true){
            
           perdeu();
         }else{
            ganhou(); 
         }
         
    

    }
   
   for (int i = 0; i < jogadores.size(); i++){

       if(jogadores[i].getCy() < (arena.getRy()+arena.getHeight()) && !colisao(jogadores[i],retangulos) && jogadores[i].getCor()=="red"){
       
           jogadores[i].MoveEmY(0.1,1);
           jogadores[i].setCy(jogadores[i].getCy()+0.1);

       }
                     
    }
    
    if(jogadorplay1.getCy() < (arena.getRy()+arena.getHeight()) && !colisao(jogadorplay1,retangulos) && !colisadotopinimigo(jogadorplay1,jogadores)){
        
        static GLdouble prevTime = glutGet(GLUT_ELAPSED_TIME);
        GLdouble curTime, deltaTime;
        curTime = glutGet(GLUT_ELAPSED_TIME);
        deltaTime = curTime - prevTime;
        prevTime = curTime;
        framerate = 1.0 / deltaTime * 1000;
        double inc = INC_KEYIDLE;
          
        jogadorplay1.MoveEmY(0.1,1);
        jogadorplay1.setCy(jogadorplay1.getCy()+0.1);

        
    }
   

    jogadorplay1.Desenha();
    for (int i = 0; i < jogadores.size(); i++){
        if(jogadores[i].getCor()=="red"){
           jogadores[i].Desenha();
        }
    }
  
    if (tiro)
        tiro->Desenha();


    for(int k=0;k<jogadores.size();k++){
       if(jogadores[k].getCor()=="red"){
           if(tiros[k])
              tiros[k]->Desenha();

       }
    }  
  
     
           
   glutSwapBuffers(); //Funcao apropriada para janela double buffer
 
}
int teste2;
void  moveoponente(GLdouble time){

    for(int i=0;i<jogadores.size();i++){
        if(jogadores[i].getparadodireita() == 0 && !colisadoesquerdainimigo2(jogadores[i],jogadorplay1) && colisao3(jogadores[i],retangulos)){   
            jogadores[i].MoveEmX(0.002,time,jogadores[i].geteixoy());
            jogadores[i].setCx(jogadores[i].getCx()+ 0.002*time);    
        }
        else{
          if(jogadores[i].getCy()<(arena.getRy()+arena.getHeight())){
              if(jogadores[i].getparadodireita()==0){
                jogadores[i].MoveEmX(-0.002,time,jogadores[i].geteixoy());
                jogadores[i].setCx(jogadores[i].getCx()-0.002*time);
                jogadores[i].setparadodireita(1);
              }  
                if(colisao3(jogadores[i],retangulos) && jogadores[i].getparadodireita() == 1){    
                jogadores[i].MoveEmX(-0.002,time,jogadores[i].geteixoy());
                jogadores[i].setCx(jogadores[i].getCx()-0.002*time);
                }else{
                    jogadores[i].MoveEmX(0.002,time,jogadores[i].geteixoy());
                    jogadores[i].setCx(jogadores[i].getCx()+0.002*time);
                    jogadores[i].setparadodireita(0);
                }
            }
        }
    }

}

void  moveoponente2(GLdouble time){
   
   for(int i=0;i<jogadores.size();i++){
     if(jogadores[i].getCy() > (arena.getRy()+arena.getHeight())){
          
        
       
         if(!colisadodireita(jogadores[i],retangulos) && jogadores[i].getCor()=="red" && !colisadoesquerdainimigo2(jogadores[i],jogadorplay1)  && jogadores[i].getCx() < (arena.getRx()+arena.getWidth()) && jogadores[i].getparadodireita() == 0 ){
            //jogadores[i].MoveEmX(0.002,time,jogadores[i].geteixoy());
             jogadores[i].setCx(jogadores[i].getCx()+ 0.004*time);
             
         }else{                    
            jogadores[i].setparadodireita(1);
            if(!colisadoesquerda(jogadores[i],retangulos) && !colisadodireitainimigo2(jogadores[i],jogadorplay1) &&jogadores[i].getCx() > arena.getRx() && jogadores[i].getparadodireita() == 1){
               // jogadores[i].MoveEmX(-0.002,time,jogadores[i].geteixoy());
                jogadores[i].setCx(jogadores[i].getCx()-0.004*time);
                        
            }else{
                jogadores[i].setparadodireita(0);
                
            }


         }

     }


   }

}
bool arenaemz(Jogador jogador1){

   if(jogador1.getCz() > - (arena.getHeight()/4 -2) && jogador1.getCz() < (arena.getHeight()/4-2) ){
       return true;
      

   }else{
       if(jogador1.getCz() < 0){
       jogadorplay1.setCz(jogadorplay1.getCz()+0.1);
       }
       if(jogador1.getCz() > 0){
       jogadorplay1.setCz(jogadorplay1.getCz()-0.2);
       }
       return false;


   }


}
bool inicioarena(Jogador jogador1){

    if(jogador1.getCx() -0.3*jogador1.getRaio() < arena.getRx()){
        jogadorplay1.setCx(jogadorplay1.getCx()+0.1);
        return true;
    }else{
        return false;
    }

}

double anterior;
double anterior2;
double anterior3;
int valor3;
bool liberado=true;
double test11=0;
void idle(void)
{
    static GLdouble prevTime = glutGet(GLUT_ELAPSED_TIME);
    GLdouble curTime, deltaTime;
    curTime = glutGet(GLUT_ELAPSED_TIME);
    deltaTime = curTime - prevTime;
    prevTime = curTime;
    framerate = 1.0 / deltaTime * 1000;
    double inc = INC_KEYIDLE;
   
    
    
    if(keyStatus[(int)('s')] && !colisadoesquerda(jogadorplay1,retangulos) && !colisadodireita(jogadorplay1,retangulos) && arenaemz(jogadorplay1) && !colisadoesquerdainimigo(jogadorplay1,jogadores) && !inicioarena(jogadorplay1))
    {
        //jogadorplay1.setCx(jogadorplay1.getCx()-INC_KEY*deltaTime);
        jogadorplay1.MoveEmX(-INC_KEY,deltaTime,jogadorplay1.geteixoy());
        jogadorplay1.MoveEmZ(INC_KEY,deltaTime,jogadorplay1.geteixoy());
        jogadorplay1.Rodaquadrail1(-INC_ANG);
        jogadorplay1.Rodaquadrail2(-INC_ANG);
        jogadorplay1.Rodajoelho1(INC_ANG);
        jogadorplay1.Rodajoelho2(INC_ANG);
        
    }
    
    if(keyStatus[(int)('w')] && !colisadodireita(jogadorplay1,retangulos) && !colisadoesquerda(jogadorplay1,retangulos) && !colisadodireitainimigo(jogadorplay1,jogadores) && arenaemz(jogadorplay1) && !inicioarena(jogadorplay1))
    {   
        double angulo = (jogadorplay1.geteixoy()*(3.14)/180);
        //jogadorplay1.setCx(jogadorplay1.getCx()+(INC_KEY*deltaTime*cos(angulo)));
        jogadorplay1.MoveEmX(INC_KEY,deltaTime,jogadorplay1.geteixoy());
        jogadorplay1.MoveEmZ(-INC_KEY,deltaTime,jogadorplay1.geteixoy());
        //jogadorplay1.setCx(jogadorplay1.getCx()+(INC_KEY*deltaTime));
        jogadorplay1.Rodaquadrail1(-INC_ANG);
        jogadorplay1.Rodaquadrail2(-INC_ANG);
        jogadorplay1.Rodajoelho1(INC_ANG);
        jogadorplay1.Rodajoelho2(INC_ANG);

       // cout << jogadorplay1.getCx() << ":" << jogadorplay1.getCy() << ":" << jogadorplay1.getCz()  << endl;
    
    }
    if(true){
      moveoponente(deltaTime);
      moveoponente2(deltaTime);
      for(int u=0;u<jogadores.size();u++){
          if(jogadores[u].getCor()!="green"){
            jogadores[u].Rodaquadrail1op(INC_ANG);
            jogadores[u].Rodaquadrail2op(INC_ANG);
            jogadores[u].Rodajoelho1op(-INC_ANG);
            jogadores[u].Rodajoelho2op(-INC_ANG);
          }
       }     

    }
    //double teste10=0;
    if(pular){
     
        jogadorplay1.setCy(jogadorplay1.getCy()-jogadorplay1.getRaio()*3);
        jogadorplay1.MoveEmY(-jogadorplay1.getRaio()*3,1);
        pular=false;
        

 
    }
    
    if(keyStatus[(int)('r')]){
       if(fim){
           resetar();
           fim = false;
           morreu=false;
       }
    }
    if(prevTime-anterior>4000){
        for(int k=0;k<jogadores.size();k++){
            if(jogadores[k].getCor()=="red" && jogadores[k].getCy()>(arena.getRy()+arena.getHeight())){
                anterior = prevTime;
                tiros[k] = jogadores[k].Atira();
                
            }
        }
    }
    for(int k=0;k<jogadores.size();k++){

        if(jogadores[k].getCor()=="red" && jogadores[k].getCy()>(arena.getRy()+arena.getHeight())){
             if (tiros[k]) {
                tiros[k]->Move(deltaTime);

                for (int j=0;j<retangulos.size();j++){
                    if (retangulos[j].Atingido(tiros[k]) && retangulos[j].getCor()=="black") {
                        delete tiros[k];
                        tiros[k] = NULL;
                        return;    
                    } 
                }

                if (jogadorplay1.Atingido(tiros[k])) {
                    delete tiros[k];
                    tiros[k] = NULL;
                    if(morte%2==0){
                      morreu=true;
                    }
                    return;    
                }
                if(true){
                    GLfloat posx, posy,posz;
                    tiros[k]->GetPos(posx, posy,posz);
                    if( posx < arena.getRx() || posx > arena.getRx()+arena.getWidth()){
                        delete tiros[k];
                        tiros[k] = NULL;
                        return;
                    }
                }
     

                if (!tiros[k]->Valido()) {
                    delete tiros[k];
                    tiros[k]= NULL;
                }
            }
        }

    }
    if(prevTime-anterior2>5000){
        for(int k=0;k<jogadores.size();k++){
            if(jogadores[k].getCor()=="red" && jogadores[k].getCy() < (arena.getRy()+arena.getHeight())){
                anterior2 = prevTime;
                tiros[k] = jogadores[k].Atira();
                
            }
        }
    }
    for(int k=0;k<jogadores.size();k++){
        if(jogadores[k].getCor()=="red" && jogadores[k].getCy()<(arena.getRy()+arena.getHeight())){
             if (tiros[k]) {
                tiros[k]->Move(deltaTime);
                
                for (int j=0;j<retangulos.size();j++){
                    if (retangulos[j].Atingido(tiros[k]) && retangulos[j].getCor()=="black") {
                        delete tiros[k];
                        tiros[k] = NULL;
                        return;    
                    } 
                }

                
                 if(true){
                    GLfloat posx, posy,posz;
                    tiros[k]->GetPos(posx, posy,posz);
                    if( posx < arena.getRx() || posx > arena.getRx()+arena.getWidth()){
                        delete tiros[k];
                        tiros[k] = NULL;
                        return;
                    }
                }

                if (jogadorplay1.Atingido(tiros[k])) {
                    delete tiros[k];
                    tiros[k] = NULL;
                    if(morte%2==0){
                      morreu=true;
                    }
                    return;    
                } 
                            
                if (!tiros[k]->Valido()) {
                    delete tiros[k];
                    tiros[k]= NULL;
                }
            }
        }

    }
    if (tiro) {
        tiro->Move(deltaTime);

        for (int j=0;j<jogadores.size();j++){
            if (jogadores[j].Atingido(tiro) && jogadores[j].getCor()=="red") {
                delete tiro;
                tiro = NULL;
                jogadores[j].setCy(arena.getRy()+arena.getHeight() +1000);
                jogadores[j].setCx(arena.getRx()+arena.getWidth()+2000);
                return;    
            } 
        }

        for (int j=0;j<retangulos.size();j++){
            if (retangulos[j].Atingido(tiro) && retangulos[j].getCor()=="black") {
                delete tiro;
                tiro = NULL;
                return;    
            } 
        }
         if(true){
                    GLfloat posx, posy,posz;
                    tiro->GetPos(posx, posy,posz);
                    //cout << "x:" << posx << "y:" << posy  << "z:"<< posz << endl;
                    if( posx < arena.getRx() || posx > arena.getRx()+arena.getWidth() ||
                    posy < arena.getRy() || posy > arena.getRy()+arena.getHeight() 
                    ||  posz > arena.getHeight()/4 || posz < - arena.getHeight()/4){
                        delete tiro;
                        tiro = NULL;
                        return;
                    }
                }
        
        if (!tiro->Valido()) {
            delete tiro;
            tiro = NULL;
        }
       

    }
   glutPostRedisplay();
}

void mouse(int button, int state, int x, int y){

     if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
        lastX = x;
        lastY = y;
        buttonDown = 1;
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
        buttonDown = 0;
    }
    
    if (button == GLUT_LEFT_BUTTON){
        if (true)
            tiro = jogadorplay1.Atira();
                 
    }
 

  
}
void move(int x, int y)
{
    if (!buttonDown)
        return;
    
    if(y<250){
      jogadorplay1.RodaBracoup(-(250-y)*0.005);
    }
    if (y>250){   
     jogadorplay1.RodaBracodown(-(250-y)*0.005);
    }
}

void motionMouse(int x, int y)

{
    if(y<250){
      jogadorplay1.RodaBracoup(-(250-y)*0.005);
    }
    if (y>250){   
     jogadorplay1.RodaBracodown(-(250-y)*0.005);
    }
    
    if(x<250 && z%2==0){
      jogadorplay1.RodaBracoesq(-(250-x)*0.005);
    }
    if (x>250 && z%2==0){   
      jogadorplay1.RodaBracodir(-(250-x)*0.005);
    }
   
}
int main(int argc, char** argv){
    if(argc == 1){
		cout << "Informe o diretório do xml com as configurações!" << endl;
		return 0;
	}
	if(!loadXml(argv)){
		return 0;
	}
    for (int j = 0; j < retangulos.size(); j++){
        if(retangulos[j].getCor ()== "blue"){
            arena = retangulos[j];
        }
    }

    for (int i = 0; i < circulos.size(); i++){
        if(circulos[i].getCor()=="green"){
            jogador1 = circulos[i];
        }
    }
    for (int i = 0; i < circulos.size(); i++){
       Jogador j;
       jogadores.push_back(j);
       jogadores[i].setCx(circulos[i].getCx());
       jogadores[i].setCy(circulos[i].getCy());
       jogadores[i].setCor(circulos[i].getCor());
       jogadores[i].setRaio(circulos[i].getRaio());

       if(jogadores[i].getCor() == "green")  {
           jogadorplay1 = jogadores[i];
       } 
    }
    salvainicial();
    
    glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (500,500); 
    glutInitWindowPosition (150, 150);
    glutCreateWindow ("Trabalho cg-3d");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyPress);
    glutIdleFunc(idle);
    glutKeyboardUpFunc(keyup);
    glutPassiveMotionFunc(motionMouse);
    glutMouseFunc(mouse);
    glutMotionFunc(move);
    init ();
    glutMainLoop();

    return 0;

}