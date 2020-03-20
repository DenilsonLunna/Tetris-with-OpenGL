#include <stdio.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>

//====================================================================== CLASSE QUADRADO ===========================================================



class Quadrado{
public:
    int x=250;
    int y=100;
    int tam = 10;
    bool colidiu = false;
    bool isFig = true;
    Quadrado(){}
  	Quadrado(int posX, int posY){
	  x = posX;
	  y = posY;
	}
    void desenha(float r, float g, float b){
    	glColor3f(r,g,b);
        glBegin(GL_QUADS);
               glVertex2i(x-tam,y+tam);
               glVertex2i(x-tam,y-tam);
               glVertex2i(x+tam,y-tam);
               glVertex2i(x+tam,y+tam);

        glEnd();
        glColor3f(0.0f,0.0f,0.0f);
        glLineWidth(1);
        glBegin(GL_LINE_LOOP);
               glVertex2i(x-tam,y+tam);
               glVertex2i(x-tam,y-tam);
               glVertex2i(x+tam,y-tam);
               glVertex2i(x+tam,y+tam);

        glEnd();
    }
    void cair(){
    	if(!colidiu){
			y -= tam*2;
		}
    }
    void moverQuad(int direcao){
			switch(direcao){
				case 1:
					x -= tam*2;
					break;
				case 2:
					x += tam*2;
					break;
				case 3:
					y -= tam*2;
					break;
			}
		}
    bool colidir(std::vector<Quadrado*> objsCena){
		if(objsCena.size() >=1){
			std::vector<Quadrado*>::iterator it;
			for(it = objsCena.begin(); it != objsCena.end(); it++){
				Quadrado *q = (*it);
				if(q != NULL){
					if((y-tam) <= (q->y+tam) && x == q->x){
						return true;
					}
				}
			}
		}
    }
    void inGame( std::vector<Quadrado*> objsCena){
    	desenha(0,0,1);
		colidir(objsCena);
		cair();
    }
};
//====================================================================== FIM CLASSE QUADRADO ===========================================================
//====================================================================== INICIO CLASSE FIGURA ===========================================================
class Figura{
	private:
		 
	public:
		Quadrado *figura[4];
		Quadrado *pivot;
		bool colidiu = false;
		int myTipe;

		Figura(Quadrado *p, int tipo){
			pivot =  p;
			figura[0] = pivot;
			criarFigura(tipo);
		}
		void criarFigura(int tipo){
			switch(tipo){
				case 1: // Linha reta    |
				{	
					figura[1] = new Quadrado(pivot->x,(pivot->y+(pivot->tam*2)));
					figura[2] = new Quadrado(pivot->x,(pivot->y+(pivot->tam*4)));
					figura[3] = new Quadrado(pivot->x,(pivot->y+(pivot->tam*6)));
				}
					break; 
				case 2:// podio         _|_
				{
					figura[1] = new Quadrado(pivot->x,(pivot->y+(pivot->tam*2)));
					figura[2] = new Quadrado(pivot->x-(pivot->tam*2),(pivot->y+(pivot->tam*2)));
					figura[3] = new Quadrado(pivot->x,(pivot->y+(pivot->tam*4)));
				}
					break;
				case 3:// escada        .-'
					figura[1] = new Quadrado(pivot->x,(pivot->y+(pivot->tam*2)));
					figura[2] = new Quadrado(pivot->x+(pivot->tam*2),(pivot->y+(pivot->tam*2)));
					figura[3] = new Quadrado(pivot->x+(pivot->tam*2),(pivot->y+(pivot->tam*4)));
					break;
				case 4:// L              L
					figura[1] = new Quadrado(pivot->x,(pivot->y+(pivot->tam*2)));
					figura[2] = new Quadrado(pivot->x,(pivot->y+(pivot->tam*4)));
					figura[3] = new Quadrado(pivot->x+(pivot->tam*2),pivot->y);
					break;
				case 5:// quadrado       []
					figura[1] = new Quadrado(pivot->x,(pivot->y+(pivot->tam*2)));
					figura[2] = new Quadrado(pivot->x+(pivot->tam*2),(pivot->y+(pivot->tam*2)));
					figura[3] = new Quadrado(pivot->x+(pivot->tam*2),pivot->y);
					break;
			}
		}
		void rotacionarFig01(int estado){
			switch(estado){
				case 1: 
					figura[1] = new Quadrado(pivot->x,(pivot->y+(pivot->tam*2)));
					figura[2] = new Quadrado(pivot->x,(pivot->y+(pivot->tam*4)));
					figura[3] = new Quadrado(pivot->x,(pivot->y+(pivot->tam*6)));
					break;
				case 2: 
					figura[1] = new Quadrado(pivot->x+(pivot->tam*2),pivot->y);
					figura[2] = new Quadrado(pivot->x+(pivot->tam*4),pivot->y);
					figura[3] = new Quadrado(pivot->x+(pivot->tam*6),pivot->y);
					break;
				case 3: 
					figura[1] = new Quadrado(pivot->x,(pivot->y-(pivot->tam*2)));
					figura[2] = new Quadrado(pivot->x,(pivot->y-(pivot->tam*4)));
					figura[3] = new Quadrado(pivot->x,(pivot->y-(pivot->tam*6)));
					break;
				case 4: 
					figura[1] = new Quadrado(pivot->x-(pivot->tam*2),pivot->y);
					figura[2] = new Quadrado(pivot->x-(pivot->tam*4),pivot->y);
					figura[3] = new Quadrado(pivot->x-(pivot->tam*6),pivot->y);
					break;	
			}
		}
		void rotacionarFig02(int estado){
			switch(estado){
				case 1: 
					figura[1] = new Quadrado(pivot->x,(pivot->y+(pivot->tam*2)));
					figura[2] = new Quadrado(pivot->x-(pivot->tam*2),(pivot->y+(pivot->tam*2)));
					figura[3] = new Quadrado(pivot->x,(pivot->y+(pivot->tam*4)));
					break;
				case 2: 
					figura[1] = new Quadrado(pivot->x+(pivot->tam*2),pivot->y);
					figura[2] = new Quadrado(pivot->x+(pivot->tam*2),(pivot->y+(pivot->tam*2)));
					figura[3] = new Quadrado(pivot->x+(pivot->tam*4),pivot->y);
					break;
				case 3: 
					figura[1] = new Quadrado(pivot->x,(pivot->y-(pivot->tam*2)));
					figura[2] = new Quadrado(pivot->x+(pivot->tam*2),(pivot->y-(pivot->tam*2)));
					figura[3] = new Quadrado(pivot->x,(pivot->y-(pivot->tam*4)));
					break;
				case 4: 
					figura[1] = new Quadrado(pivot->x-(pivot->tam*2),pivot->y);
					figura[2] = new Quadrado(pivot->x-(pivot->tam*2),(pivot->y-(pivot->tam*2)));
					figura[3] = new Quadrado(pivot->x-(pivot->tam*4),pivot->y);
					break;	
			}
		}
		void rotacionarFig03(int estado){
			switch(estado){
				case 1: 
					figura[1] = new Quadrado(pivot->x,(pivot->y+(pivot->tam*2)));
					figura[2] = new Quadrado(pivot->x+(pivot->tam*2),(pivot->y+(pivot->tam*2)));
					figura[3] = new Quadrado(pivot->x+(pivot->tam*2),(pivot->y+(pivot->tam*4)));
					break;
				case 2: 
					figura[1] = new Quadrado(pivot->x+(pivot->tam*2),pivot->y);
					figura[2] = new Quadrado(pivot->x+(pivot->tam*2),(pivot->y-(pivot->tam*2)));
					figura[3] = new Quadrado(pivot->x+(pivot->tam*4),(pivot->y-(pivot->tam*2)));
					break;
				case 3: 
					figura[1] = new Quadrado(pivot->x,(pivot->y-(pivot->tam*2)));
					figura[2] = new Quadrado(pivot->x-(pivot->tam*2),(pivot->y-(pivot->tam*2)));
					figura[3] = new Quadrado(pivot->x-(pivot->tam*2),(pivot->y-(pivot->tam*4)));
					break;
				case 4: 
					figura[1] = new Quadrado(pivot->x-(pivot->tam*2),pivot->y);
					figura[2] = new Quadrado(pivot->x-(pivot->tam*2),(pivot->y+(pivot->tam*2)));
					figura[3] = new Quadrado(pivot->x-(pivot->tam*4),(pivot->y+(pivot->tam*2)));
					break;	
			}
		}
		void rotacionarFig04(int estado){
			switch(estado){
				case 1: 
					figura[1] = new Quadrado(pivot->x,(pivot->y+(pivot->tam*2)));
					figura[2] = new Quadrado(pivot->x,(pivot->y+(pivot->tam*4)));
					figura[3] = new Quadrado(pivot->x+(pivot->tam*2),pivot->y);
					break;
				case 2: 
					figura[1] = new Quadrado(pivot->x+(pivot->tam*2),pivot->y);
					figura[2] = new Quadrado(pivot->x+(pivot->tam*4),pivot->y);
					figura[3] = new Quadrado(pivot->x,pivot->y-(pivot->tam*2));
					break;
				case 3: 
					figura[1] = new Quadrado(pivot->x,(pivot->y-(pivot->tam*2)));
					figura[2] = new Quadrado(pivot->x,(pivot->y-(pivot->tam*4)));
					figura[3] = new Quadrado(pivot->x-(pivot->tam*2),pivot->y);
					break;
				case 4: 
					figura[1] = new Quadrado(pivot->x-(pivot->tam*2),pivot->y);
					figura[2] = new Quadrado(pivot->x-(pivot->tam*4),pivot->y);
					figura[3] = new Quadrado(pivot->x,pivot->y+(pivot->tam*2));
					break;	
			}
		}
		void desenharFigura(){
			for(int i = 0; i < 4; i ++){
				figura[i]->desenha(0,0,1);
			}
		}
		void colidir(std::vector<Quadrado*> objsCena){
			if(!colidiu){
				for(int i = 0; i < 4; i++){
					if(figura[i]->colidir(objsCena)){
						colidiu = true;
						figura[0]->colidiu = true;
						figura[1]->colidiu = true;
						figura[2]->colidiu = true;
						figura[3]->colidiu = true;
						return;
						
					}
				}
			}	
		}
		void cair(){
			if(!colidiu){
				for(int i = 0; i < 4; i++){
					figura[i]->cair();	
				}
			}		
		}
		void moverFig(int direcao, std::vector<Quadrado*> objsCena){
			switch(direcao){
				case 1:
					if(podeMover(1,objsCena)){
						for(int i = 0; i < 4; i++){
							figura[i]->moverQuad(1);
						}
					}
						
					
					
					break;
				case 2:
					if(podeMover(2,objsCena)){
						for(int i = 0; i < 4; i++){
							figura[i]->moverQuad(2);
						}
					}
					
					break;
				case 3:
						if(podeMover(3,objsCena)){
							for(int i = 0; i < 4; i++){
								figura[i]->moverQuad(3);
							}
						}
					break;
			}
		}
		bool podeMover(int direcao, std::vector<Quadrado*> objsCena){
			std::vector<Quadrado*>::iterator it;
			int tamObjs = figura[0]->tam;
			switch(direcao){
				case 1:
					for(int i =0;i < 4; i ++){
						int x = figura[i]->x - (tamObjs*2);
						int y = figura[i]->y; 
						for(it = objsCena.begin(); it != objsCena.end(); it++){
							Quadrado *q = (*it);
							if(q != NULL){
								if(q->x == x && y == q->y){
									printf("Não pode");
									return false;
								}
							}
						}
							
					}
					return true;
					break;
				case 2:
					for(int i =0;i < 4; i ++){
						int x = figura[i]->x + (tamObjs*2);
						int y = figura[i]->y; 
						for(it = objsCena.begin(); it != objsCena.end(); it++){
							Quadrado *q = (*it);
							if(q != NULL){
								if(q->x == x && y == q->y){
									return false;
								}
							}
						}
							
					}
					return true;
					break;
				case 3:
					for(int i =0;i < 4; i ++){
						int x = figura[i]->x;
						int y = figura[i]->y + (tamObjs*2); 
						for(it = objsCena.begin(); it != objsCena.end(); it++){
							Quadrado *q = (*it);
							if(q != NULL){
								if(q->x == x && y == q->y){
									return false;
								}
							}
						}
							
					}
					
					break;
			}
		}
		
		void inGame(std::vector<Quadrado*> objsCena){
			desenharFigura();
			cair();
			colidir(objsCena);	
		}
		
	
};
		



	

//====================================================================== FIM CLASSE FIGURA ===========================================================
Quadrado *quad = new Quadrado();
std::vector<Quadrado*> objsCena;
std::vector<Quadrado*>::iterator it;
int tipoFigura = 4;
Figura *fig = new Figura(quad,tipoFigura);

int estadoRotacao = 1;
void inicio(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	gluOrtho2D(0,500,0,500);
}
void GerenciaTeclado(unsigned char key, int x, int y)
{
    switch (key) {
            case 'd':
                if(quad->x < 390){
                    fig->moverFig(2, objsCena);
                }
                break;
            case 'a':
                if(quad->x > 110){
                    fig->moverFig(1, objsCena);
                }
                break;
            case 'w':
            	switch(estadoRotacao){
            		case 1:
            			estadoRotacao = 2;
            			break;
            		case 2:
            			estadoRotacao = 3;
            			break;
            		case 3:
            			estadoRotacao = 4;
            			break;
            		case 4:
            			estadoRotacao = 1;
            			break;
            	}
                if(fig->myTipe == 1){
                	fig->rotacionarFig01(estadoRotacao);
                } 
				if(fig->myTipe == 2){
                	fig->rotacionarFig02(estadoRotacao);
                }   
                if(fig->myTipe == 3){
                	fig->rotacionarFig03(estadoRotacao);
                }  
                if(fig->myTipe == 4){
                	fig->rotacionarFig04(estadoRotacao);
                }  
                break;
    }
    glutPostRedisplay();
}
void timer(int value){
	glutPostRedisplay();
	glutTimerFunc(1000,timer,1);
}
void desenhaEixo(){
        glColor3f(1.0f,0.0f,0.0f);
        glBegin(GL_LINES);
               glVertex2i(0,250);
               glVertex2i(500,250);
        glEnd();
        glColor3f(0.0f,1.0f,0.0f);
        glBegin(GL_LINES);
               glVertex2i(250,0);
               glVertex2i(250,500);
        glEnd();
}
void verificaColisao(){
	if(fig->colidiu){
		for(int i = 0; i < 4; i ++){
			objsCena.push_back(fig->figura[i]);
		}
		estadoRotacao = 1;
		fig = new Figura(new Quadrado(250,480),tipoFigura);
		fig->myTipe = tipoFigura;
	}
}
void desenhaObjetos(){
	for(it = objsCena.begin(); it != objsCena.end(); it++){
		Quadrado *q = (*it);
		if(q != NULL){
			if(q->isFig){ // é uma objeto do ttipo figura
				q->desenha(0,0,1);
				q->colidiu=true;
			}else{ // é um objeto do tipo cenario
				q->desenha(1,1,1);	
			}
		}
	}
}
void desenha(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
    fig->inGame(objsCena);
    desenhaObjetos();
    verificaColisao();
    glFlush();
}

void criaCenario(){
	int x = 90;
	int y = 20;
	
	for(int i =0; i < 15; i++){
    		Quadrado *quad = new Quadrado(x,y);
    		quad->isFig = false;
    		objsCena.push_back(quad);
    		x+= 20;
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600,600);
    glutCreateWindow("Tetris");
    glutDisplayFunc(desenha);
    glutTimerFunc(33,timer,1);
    glutKeyboardFunc(GerenciaTeclado);
    inicio();
    criaCenario();
    glutMainLoop();
}
