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
    Quadrado(){}
  	Quadrado(int posX, int posY){
	  x = posX;
	  y = posY;
	}
    void desenha(){
    	glColor3f(0.0f,0.0f,1.0f);
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
    		printf("TesteQ");
			y -= tam*2;
		}
    }
    void colidir(std::vector<Quadrado*> objsCena){
    	if((y-tam) <= tam){
    		printf("Colidiu");
			colidiu = true;
		}
		if(objsCena.size() >=1){
			std::vector<Quadrado*>::iterator it;
			for(it = objsCena.begin(); it != objsCena.end(); it++){
				Quadrado *q = (*it);
				if(q != NULL){
					if((y-tam) <= (q->y+tam) && x == q->x){
						printf("Teste");
						colidiu = true;
					}
				}
			}
		}
    }
    void inGame( std::vector<Quadrado*> objsCena){
    	desenha();
		colidir(objsCena);
		cair();
    }
};
//====================================================================== FIM CLASSE QUADRADO ===========================================================
//====================================================================== INICIO CLASSE FIGURA ===========================================================
class Figura{
	private:
		 bool colidiu;
	public:
		Quadrado *figura[4];
		Quadrado *pivot;
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
		
		void desenharFigura(std::vector<Quadrado*> objsCena){
			for(int i = 0; i < 4; i ++){
				figura[i]->desenha();
				figura[i]->cair();
				figura[i]->colidir(objsCena);
			}
		}
		void colidir(){
			for(int i = 0; i < 4; i++){
				if(figura[i]->colidiu){
					colidiu = true;
				}
			}
			if(colidiu){
				for(int i = 0; i < 4; i++){
					figura[i]->colidiu = true;
				}
			}
			
		}
		void cair(){
			if(!colidiu){
				for(int i = 0; i < 4; i++){
					if(figura[i]->colidiu){
						figura[i]->cair();
					}
				}	
				
			}
			
		}
		void inGame(std::vector<Quadrado*> objsCena){
			desenharFigura(objsCena);
			colidir();
			cair();
			
		}
		
	
};
		
		


	

//====================================================================== FIM CLASSE FIGURA ===========================================================
Quadrado *quad = new Quadrado();
std::vector<Quadrado*> objsCena;
std::vector<Quadrado*>::iterator it;
Figura *fig = new Figura(quad,4);
void inicio(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	gluOrtho2D(0,500,0,500);
}
void GerenciaTeclado(unsigned char key, int x, int y)
{
    switch (key) {
            case 'd':
                if(quad->x < 390){
                    quad->x += 20;
                }
                break;
            case 'a':
                if(quad->x > 110){
                    quad->x -= 20;
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
void desenhaLimites(){
    glColor3f(0.0f,0.0f,0.0f);
    glLineWidth(5);
    glBegin(GL_LINES);
        glVertex2i(100,500);
        glVertex2i(100,-500);
    glEnd();

    glBegin(GL_LINES);
        glVertex2i(400,500);
        glVertex2i(400,-500);
    glEnd();
    
    glBegin(GL_LINES);
        glVertex2i(100,10);
        glVertex2i(400,10);
    glEnd();

}
void desenhaObjetos(){
	for(it = objsCena.begin(); it != objsCena.end(); it++){
		Quadrado *q = (*it);
		if(q != NULL){
			q->desenha();
			q->colidiu=true;
		}
	}
}
void desenha(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
    //quad->inGame(objsCena);
    fig->inGame(objsCena);
    //desenhaEixo();
    desenhaLimites();
    //desenhaObjetos();
    glFlush();
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
    glutMainLoop();
}
