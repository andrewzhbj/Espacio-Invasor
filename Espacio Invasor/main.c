#include <stdio.h>
#include <stdlib.h>
#include <conio.c>
#include <windows.h>

/* Entorno */
int Menu			(void);
int Dificultad      (void);
void Cuadro			(void);
void generarCuadro  (int);
void OcultarCursor	(void);
/* Nave */
void crearNave		(int, int);
void borrarNave		(int, int);
void crearBala		(int, int);
void borrarBala		(int, int);
/* Enemigo */
void crearEne		(int, int);
void borrarEne      (int, int);
void crearBalaE		(int, int);
void borrarBalaE 	(int, int);


int main(){
	/* Nave jugador*/
	int jugando 		= -1;
	int teclapulsada 	= -1;
	int retornoTecla	= -1;
	int disparo 		= -1;
	int x				= 0;
	int y				= 0;
	int xb 				= 0;
	int yb 				= 0;
	int naveC           = 0; 	/* respawn de nave */
	int ganar           = -1;
	int d_jugador       = -1;
	/* Jugador */
	int contD       = 0;    	/* contador de disparos */
	int contE 		= 0;    	/* contador de error */
	int nivel 		= 0;
	int volver  	= 0;
	int terminar 	= -1;
    int vida[2]     = {0,0};
    int puntaje[2] 	= {0,0};
	/* Variables */
	int k 	= 0;
	int j 	= 0;
	int i 	= 0;
	int xc 	= 0;
	int yf 	= 0;
	/* Nave Enemigo */
	int MAX 				= 0;            /* máximo de naves e.*/
	int maxd 				= 0;            /* máximo de naves e. disp. */
	int cont 				= 0;            /* contador de disparos */
	int contEne             = 0;            /* contador e. muertos*/
	int eneCreado 			= 0;
	int xbe[5] 				= {0,0,0,0,0};  /* x bala e. */
	int ybe[5] 				= {0,0,0,0,0};  /* y bala e. */
	int eid[5] 				= {0,0,0,0,0};  /* instancia e.*/
	int direccion_ene[5] 	= {0,0,0,0,0};
	int d_enemigo[5] 		= {0,0,0,0,0};
	/* Coordenadas nave e. */
	int ce[5][2] =
	{	40,4,
		20,6,
		40,8,
		60,10,
		35,12
	};
    //MessageBox(0, "Esta opción no existe, intentalo devuelta." , "Error", 0);
	/* Juego */
	SetConsoleTitle("Invasion Cosmica (Manu)");
	OcultarCursor();
	generarCuadro(1);
    //MessageBeep(MB_ICONHAND); /* play asterisk sound */
	do{
	switch(Menu()){
		case 1:
            clrscr();
		    MessageBeep(MB_OK); /* play asterisk sound */
			nivel = Dificultad();
            if(nivel == 4){
                contE = 0;
                clrscr();
                generarCuadro(1);
                break;
			}
            clrscr();
			generarCuadro(0);
			switch(nivel){
				case 1:
					maxd 	= 1;
					MAX     = 2;
					eid[0] 	= 1;
					eid[1] 	= 1;
					vida[0] = 6;
					d_enemigo[0] = 0;
					direccion_ene[0] = 1;
					direccion_ene[1] = 0;

				break;
				case 2:
					maxd 	= 2;
                    MAX     = 3;
					eid[0] 	= 1;
					eid[1] 	= 1;
					eid[2] 	= 1;
                    vida[0] = 4;
					d_enemigo[2] = 1;
					d_enemigo[5] = 1;
					direccion_ene[0] = 0;
					direccion_ene[1] = 1;
					direccion_ene[2] = 0;
				break;
				case 3:
					maxd 	= 3;
					MAX     = 5;
					eid[0]	= 1;
					eid[1] 	= 1;
					eid[2] 	= 1;
					eid[3] 	= 1;
					eid[4] 	= 1;
					vida[0] = 2;
					d_enemigo[0] = 1;
					d_enemigo[2] = 1;
					d_enemigo[5] = 1;
					direccion_ene[0] = 1;
					direccion_ene[1] = 1;
					direccion_ene[2] = 0;
					direccion_ene[3] = 1;
					direccion_ene[4] = 0;
				break;
				case 4:

                break;
			}
			x 	= 30;
			y 	= 17;
            contEne     = MAX;
            puntaje[0]  = 0;
			eneCreado 	= 1;
			jugando 	= 1;
			crearNave(x,y);
			/* Crea naves enemigas */
			for(k=0;k<6;k++){
				if(eid[k] == 1) crearEne(ce[k][0],ce[k][1]);
			}
			do{
				/* Velocidad de fps */
				switch(nivel){
					case 3: Sleep(40);
					break;
					case 2: Sleep(60);
					break;
					case 1: Sleep(100);
					break;
				}
				/* Disparo del enemigo y colisión con el jugador*/
				for(k=0;k<5;k++){
					if(d_enemigo[k] == 1){
						if(eid[k] == 1){
							if(ybe[k] < 19){
								borrarBalaE(xbe[k],ybe[k]);
								ybe[k]++;
								crearBalaE(xbe[k],ybe[k]);
								if(ybe[k] == y && (xbe[k] == x || xbe[k] == x-1 || xbe[k] == x+1)){
                                    d_enemigo[k] = 0;
									borrarBalaE(xbe[k],ybe[k]);
									naveC = 1;
                                    vida[0]--;
									crearNave(x,y);
									clrscr();
									generarCuadro(0);
                                    gotoxy(37,24); printf("Vidas: %d (x:%d,y:%d,n:%d)", vida[0], x, y, naveC);
								}
							}else{
								borrarBalaE(xbe[k],ybe[k]);
								d_enemigo[k] = 0;
							}
						}
					}
				}
				/* Disparo del jugador y colisión con nave enemiga */
				if(disparo == 1){
					if(yb > 4){
						borrarBala(xb,yb); //0 derecha
						yb--;
						crearBala(xb,yb);
						for(k=0;k<MAX;k++){
							if(eid[k] == 1){
                                //if(((xb == ce[k][0]+1 || xb == ce[k][0]+2) && yb == ce[k][1]) || ((xb == ce[k][0]-1 || xb == ce[k][0]-2) && yb == ce[k][1]) || (xb == ce[k][0] && yb == ce[k][1])){
                                if((xb == ce[k][0]-1 || xb == ce[k][0]+1 || xb == ce[k][0]) && yb == ce[k][1]){
                                //if(direccion_ene[k] == 1){
                                	//if(xb < ce[k][0] && xb > ce[k][0]-3){
                					borrarEne(ce[k][0],ce[k][1]);
                                    //clrscr();
                                    //generarCuadro(0);
                                    gotoxy(37,22); printf("        ", k);
                                    gotoxy(37,22); printf("Choco:%d", k);
                                    eid[k] = -1;
                                    contE++;
                                    puntaje[0]+= 10;
									}
								}
                            }
					}else{
						borrarBala(xb,yb);
						disparo = 0;
					}
					gotoxy(37,21); printf("            ", xb,yb);
					gotoxy(37,21); printf("xb:%d yb:%d", xb,yb);
				}
				/* Movimiento del enemigo (0 derecha - 1 izquierda) */
				for(k=0;k<5;k++){
					if(ce[k][0] == 74){
							direccion_ene[k] = 1;
							if(ce[k+1][0] == 6){
								direccion_ene[k+1] = 0;
							}
						}else if(ce[k][0] == 6){
							direccion_ene[k] = 0;
							if(ce[k+1][0] == 74){
								direccion_ene[k+1] = 1;
							}
						}
					if(eid[k] == 1){
						if(direccion_ene[k] == 0){
							borrarEne(ce[k][0],ce[k][1]);
							ce[k][0]++;
							crearEne(ce[k][0],ce[k][1]);
						}else if(direccion_ene[k] == 1){
							borrarEne(ce[k][0],ce[k][1]);
							ce[k][0]--;
							crearEne(ce[k][0],ce[k][1]);
						}
						gotoxy(10,21); printf("                           ");
						gotoxy(10,21); printf("0ex:%d ey:%d  d:%d i:%d", ce[0][0],ce[0][1], direccion_ene[0], eid[0]);
						gotoxy(10,22); printf("                           ");
						gotoxy(10,22); printf("1ex:%d ey:%d  d:%d i:%d", ce[1][0],ce[1][1], direccion_ene[1], eid[1]);
						gotoxy(10,23); printf("                           ");
						gotoxy(10,23); printf("2ex:%d ey:%d  d:%d i:%d", ce[2][0],ce[2][1], direccion_ene[2], eid[2]);
						gotoxy(10,24); printf("                           ");
						gotoxy(10,24); printf("3ex:%d ey:%d d:%d i:%d", ce[3][0],ce[3][1], direccion_ene[3], eid[3]);
						gotoxy(10,25); printf("                           ");
						gotoxy(10,25); printf("4ex:%d ey:%d d:%d i:%d", ce[4][0],ce[4][1], direccion_ene[4], eid[4]);
						gotoxy(3,22); printf("     ");
						gotoxy(3,22); printf("di:%d", d_jugador);
					}
				}
				/* Teclas */
				if(kbhit()){
					teclapulsada = getch();
					/* Movimiento izq-der del jugador */
            		if(teclapulsada == 65 || teclapulsada == 97){ 			/* a */
						d_jugador = 1;
						if(x <= 6) crearNave(x,y);
            	    	else{
            	    		borrarNave(x,y);
            	    		x--;
            	    		crearNave(x,y);
						}
            		}else if(teclapulsada == 68 || teclapulsada == 100){ 	/* d */
						d_jugador = 0;
						if(x >= 74) crearNave(x,y);
            	    	else{
            	    		borrarNave(x,y);
            	    		x++;
            	    		crearNave(x,y);
						}
					/* Disparo del jugador y el enemigo */
           			}else if(teclapulsada == 32){
           				if(disparo == 1){
						   
						}else{
							cont++;
							if(cont == 10) cont = 0;
						    contD++;
						    disparo = 1;
           					xb = x;
           					yb = y;
           					crearBala(xb,yb);
           					for(k=0;k<maxd;k++){
           						if(d_enemigo[k] == 1){
								   }
           						else if(cont == 3 || cont == 5 || cont == 7){
							   		d_enemigo[k] = 1;
           					    	xbe[k] = ce[k][0];
           							ybe[k] = ce[k][1];
           							crearBalaE(xbe[k] ,ybe[k]);
								}
							}
						}
					}
           		gotoxy(3,21); printf("     ", x);
           		gotoxy(3,21); printf("x:%d", x);
           		}
        		gotoxy(60,23); printf("C: %d, contE: %d", cont, contE);
        		/* respawn nave */
       			if(naveC == 1){ crearNave(x,y); naveC = 0; }
       				if(vida[0] == 0){
                   		ganar = 0;
                   		break;
               		}else if(contE == MAX){
                   		ganar = 1;
                   		break;
               		}
				}while(jugando != 0);
				clrscr();
				generarCuadro(0);
				gotoxy(32,6);
               	if(ganar == 1) printf("Has ganado!"); 
                else printf("Has perdido!");
            	gotoxy(25,8);	textcolor(LIGHTCYAN);   printf("Estadisticas:");            	textcolor(WHITE);
            	gotoxy(25,11);	textcolor(DARKGRAY);    printf("> Disparos totales: ");     	textcolor(WHITE); printf("%d", contD);
            	gotoxy(25,10);	textcolor(DARKGRAY);    printf("> Puntaje total:    ");     	textcolor(WHITE); printf("%d", puntaje[0]);
				gotoxy(5,19); 	textcolor(DARKGRAY);  	printf("["); textcolor(LIGHTMAGENTA); 	printf("ENTER"); textcolor(DARKGRAY);  printf("]"); textcolor(WHITE); printf(" Menu");
				do{
					if(kbhit()) retornoTecla = getch();
				}while(retornoTecla != 13 );
				for(k=0;k<6;k++){
					d_enemigo[k] = 0;
					eid[k] = 0;
				}
				retornoTecla = -1;
				contD  = 0;
				contE  = 0;
				cont   = 0;
				clrscr();
				generarCuadro(1);
			break;
			case 2:

			break;
			case 3:
				clrscr();
				generarCuadro(3);
				gotoxy(29,7);	textcolor(LIGHTMAGENTA); printf("> C R E D I T O S <"); 	textcolor(WHITE);
				gotoxy(24,10);	textcolor(DARKGRAY);  printf("Alumno: "); 		 			textcolor(WHITE); printf("   Manuel Cabral");
				gotoxy(24,13);	textcolor(DARKGRAY);  printf("Profesor: "); 	 			textcolor(WHITE); printf(" Walter Vaneskeheian");
				gotoxy(24,12); 	textcolor(DARKGRAY);  printf("Escuela: "); 	     			textcolor(WHITE); printf("  Fragata Libertad");
				gotoxy(24,11); 	textcolor(DARKGRAY);  printf("Materia: "); 	     			textcolor(WHITE); printf("  A. y E. de Datos");
				gotoxy(24,19); 	textcolor(DARKGRAY);  printf("["); textcolor(LIGHTMAGENTA); printf("ENTER"); textcolor(DARKGRAY);  printf("]"); textcolor(WHITE); printf(" Menu");
				do{
					if(kbhit()) retornoTecla = getch();
				}while(retornoTecla != 13 );
				retornoTecla = -1;
				contE = 0;
				clrscr();
				generarCuadro(1);
			break;
			case 4:
				clrscr();
				generarCuadro(4);
				gotoxy(29,7);	textcolor(LIGHTMAGENTA); printf("> C O N T R O L E S <"); 	textcolor(WHITE);
				gotoxy(24,9);	textcolor(LIGHTMAGENTA); printf("> PRIMER JUGADOR:"); 		textcolor(WHITE);
				gotoxy(24,10);	textcolor(DARKGRAY);  printf("Derecha:   "); 		 		textcolor(WHITE); printf(" D");
				gotoxy(24,11);	textcolor(DARKGRAY);  printf("Izquierda: "); 	    		textcolor(WHITE); printf(" A");
				gotoxy(24,12); 	textcolor(DARKGRAY);  printf("Disparar:  "); 	   			textcolor(WHITE); printf(" ESPACIO");
				gotoxy(24,14); 	textcolor(LIGHTMAGENTA);  printf("> SEGUNDO JUGADOR:");
        	    gotoxy(24,15);	textcolor(DARKGRAY);  printf("Derecha:   "); 		 		textcolor(WHITE); printf(" N");
				gotoxy(24,16);	textcolor(DARKGRAY);  printf("Izquierda: "); 	     		textcolor(WHITE); printf(" M");
				gotoxy(24,17); 	textcolor(DARKGRAY);  printf("Disparar:  "); 	   			textcolor(WHITE); printf(" CTRL DER");
				gotoxy(24,19); 	textcolor(DARKGRAY);  printf("["); textcolor(LIGHTMAGENTA); printf("ENTER"); textcolor(DARKGRAY);  printf("]"); textcolor(WHITE); printf(" Menu");
				do{
					if(kbhit()) retornoTecla = getch();
				}while(retornoTecla != 13 );
				retornoTecla = -1;
				contE = 0;
				clrscr();
				generarCuadro(1);
			break;
			case 5:
            	if(MessageBox(0, "¿Estas seguro de que quieres salir?" , "Aviso", 1) == 1){
                	clrscr();
                	return 0;
            	}else{ }
        	break;
		}
	}while(terminar != 1);
	system("pause>silvio");
}

int Dificultad(void){
    int nivel = 0, pos = 0, teclapulsada = -1, coor[4] = {10,11,12,14};
    generarCuadro(5);
    gotoxy(33,7);   textcolor(LIGHTMAGENTA); 	printf("> M O D O <");
    gotoxy(32,10);  textcolor(DARKGRAY);  		printf("[ ]"); 				textcolor(LIGHTGREEN); 	printf(" FACIL");
    gotoxy(32,11);  textcolor(DARKGRAY);  		printf("[ ]"); 				textcolor(YELLOW); 		printf(" MEDIO");
    gotoxy(32,12);  textcolor(DARKGRAY); 		printf("[ ]"); 				textcolor(LIGHTRED); 	printf(" DIFICIL");
    gotoxy(32,14);  textcolor(DARKGRAY);  		printf("[ ] "); 		 	textcolor(DARKGRAY);    printf("Volver");
    textcolor(LIGHTMAGENTA);
   	gotoxy(33,coor[pos]); printf("%c", 175);
	do{
		do{
			if(kbhit()){
            	teclapulsada = getch();
            		if(teclapulsada == 87 || teclapulsada == 119){ 			/* w */
                		if(pos <= 0){
                		gotoxy(33,coor[pos]); printf("%c", 175);	
						}else{
							gotoxy(33,coor[pos]); printf(" ");
							pos--;
							gotoxy(33,coor[pos]); printf("%c", 175);
						}
           	 		}else if(teclapulsada == 83 || teclapulsada == 115){ 	/* s */
               			if(pos >= 3){
              		  		gotoxy(33,coor[pos]); printf("%c", 175);	
						}else{
							gotoxy(33,coor[pos]); printf(" ");
							pos++;
							gotoxy(33,coor[pos]); printf("%c", 175);	
						}
					}else if(teclapulsada == 13){
						pos++;
						nivel = pos;
					}
        		}
			}while(teclapulsada != 13);
    	}while(nivel != 1 && nivel != 2 && nivel != 3 && nivel != 4);
    return nivel;
}

int Menu(void){
	int opc = 0, pos = 0, teclapulsada = -1, coor[5] = {10,11,12,13,14};
	gotoxy(33,7);  textcolor(LIGHTMAGENTA); printf("> M E N U <"); textcolor(WHITE);
	gotoxy(32,10);  textcolor(DARKGRAY);    printf("[ ]"); textcolor(GREEN); printf(" JUGAR");
	gotoxy(32,11);  textcolor(DARKGRAY);    printf("[ ]"); textcolor(LIGHTGREEN); printf(" VERSUS");
	gotoxy(32,12);  textcolor(DARKGRAY);    printf("[ ]"); textcolor(CYAN); printf(" CREDITOS");
	gotoxy(32,13);  textcolor(DARKGRAY);    printf("[ ]"); textcolor(YELLOW); printf(" CONTROLES");
	gotoxy(32,14);  textcolor(DARKGRAY);    printf("[ ]"); textcolor(LIGHTRED); printf(" SALIR");
	textcolor(LIGHTMAGENTA);
	gotoxy(33,coor[pos]); printf("%c", 175);
	do{
		do{
			if(kbhit()){
                teclapulsada = getch();
                if(teclapulsada == 87 || teclapulsada == 119){ 			/* w */
                	if(pos <= 0){
                		gotoxy(33,coor[pos]); printf("%c", 175);	
					}else{
						gotoxy(33,coor[pos]); printf(" ");
						pos--;
						gotoxy(33,coor[pos]); printf("%c", 175);
					}
                }else if(teclapulsada == 83 || teclapulsada == 115){ 	/* s */
                	if(pos >= 4){
                		gotoxy(33,coor[pos]); printf("%c", 175);
					}else{
						gotoxy(33,coor[pos]); printf(" ");
						pos++;
						gotoxy(33,coor[pos]); printf("%c", 175);
					}
				}else if(teclapulsada == 13){
					pos++;
					opc = pos;
				}
            }
		}while(teclapulsada != 13);
	}while(opc != 1 && opc != 2 && opc != 3 && opc != 4 && opc != 5);
	return opc;
}

void crearNave(int x, int y){
	gotoxy(x,y);     printf("%c", 95);
	gotoxy(x-1,y+1); printf("%c", 47); printf("%c", 176); printf("%c", 92);
	gotoxy(x-1,y+2); printf("%c", 42); printf("%c", 42); printf("%c", 42);
}

void borrarNave(int x, int y){
	gotoxy(x,y);     printf("  ");
	gotoxy(x-1,y+1); printf("   ");
	gotoxy(x-1,y+2); printf("   ");
}

void crearBala(int x, int y){ gotoxy(x,y); printf("%c", 248); }
void borrarBala(int x,int y){ gotoxy(x,y); printf(" "); }
void crearBalaE(int x, int y){ gotoxy(x,y); printf("%c", 248); }
void borrarBalaE(int x,int y){ gotoxy(x,y); printf(" "); }

void crearEne(int x, int y){
	gotoxy(x,y);   printf("%c", 178);
	gotoxy(x+1,y); printf("%c", 204);
	gotoxy(x-1,y); printf("%c", 185);
}
void borrarEne(int x, int y){
	gotoxy(x,y); printf(" ");
	gotoxy(x+1,y); printf(" ");
	
gotoxy(x-1,y); printf(" ");
}

void OcultarCursor(void){
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO estatsCursor;
   estatsCursor.dwSize = 20;
   estatsCursor.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &estatsCursor);
}
/* Lo estoy arreglando para bajar redundancia al código */
void generarCuadro(int tipo){
	int xc = 0, yf = 0;
	switch(tipo){
		case 0:
			/* Fondo batalla */
			textcolor(LIGHTMAGENTA); gotoxy(24,2); printf("I n v a s i o n  C o s m i c a");
			textcolor(DARKGRAY);
			for(xc=5;xc<=75;xc++){
				gotoxy(xc,3); printf("%c", 205);
				gotoxy(xc,20); printf("%c", 205);
				for(yf=4;yf<=19;yf++){
					gotoxy(4,yf); printf("%c", 186);
					gotoxy(76,yf); printf("%c", 186);
				}
			}
			gotoxy(4,20); 	printf("%c", 200);	//esquina inferior izq
			gotoxy(4,3); 	printf("%c", 201);		//esquina superior izq
			gotoxy(76,20); 	printf("%c", 188);	//esquina inferior der
			gotoxy(76,3); 	printf("%c", 187);	//esquina superior der
			textcolor(WHITE);	
		break;
		case 1:
			/* Menu	*/
    		textcolor(DARKGRAY);
    		for(xc=20;xc<=60;xc++){
        		if(xc >= 30 && xc <= 46){
            		gotoxy(xc,6); printf("%c", 205);
            		gotoxy(xc,8); printf("%c", 205);
            		gotoxy(xc,16); printf("%c", 205);
       			}if(xc >= 24 && xc <= 53){
            		gotoxy(xc,4); printf("%c", 205);
            		gotoxy(xc,2); printf("%c", 205);
        		}
				for(yf=1;yf<=15;yf++){
           			if(yf >= 7){
                		gotoxy(30,yf); printf("%c", 186);
                		gotoxy(46,yf); printf("%c", 186);
            		}if(yf == 3){
                		gotoxy(23,yf); printf("%c", 186);
                		gotoxy(54,yf); printf("%c", 186);
           			}
				}
    		}
    		gotoxy(23,4);   printf("%c", 200);	//esquina inferior izq
			gotoxy(23,2);   printf("%c", 201);	//esquina superior izq
			gotoxy(54,4);   printf("%c", 188);	//esquina inferior der
			gotoxy(54,2);   printf("%c", 187);	//esquina superior der
    		textcolor(LIGHTMAGENTA); gotoxy(24,3); printf("I n v a s i o n  C o s m i c a");
    		textcolor(DARKGRAY);
    		gotoxy(30,16);  printf("%c", 200);	//esquina inferior izq
			gotoxy(30,6);   printf("%c", 201);	//esquina superior izq
			gotoxy(46,16);  printf("%c", 188);	//esquina inferior der
			gotoxy(46,6);   printf("%c", 187);	//esquina superior der
		break;
		case 2:
			/* Versus */
		break;
		case 3:
			/* Créditos	*/
			textcolor(DARKGRAY);
            for(xc=20;xc<=60;xc++){
                if(xc >= 23 && xc <= 54){
                    gotoxy(xc,6); printf("%c", 205);
                    gotoxy(xc,8); printf("%c", 205);
                    gotoxy(xc,16); printf("%c", 205);
                }if(xc >= 24 && xc <= 53){
                    gotoxy(xc,4); printf("%c", 205);
                    gotoxy(xc,2); printf("%c", 205);
                }
                for(yf=1;yf<=15;yf++){
                    if(yf >= 7){
                        gotoxy(22,yf); printf("%c", 186);
                        gotoxy(55,yf); printf("%c", 186);
                    	}if(yf == 3){
                            gotoxy(23,yf); printf("%c", 186);
                            gotoxy(54,yf); printf("%c", 186);
                        }
                    }
                }
                gotoxy(23,4);   printf("%c", 200);	//esquina inferior izq
                gotoxy(23,2);   printf("%c", 201);	//esquina superior izq
                gotoxy(54,4);   printf("%c", 188);	//esquina inferior der
                gotoxy(54,2);   printf("%c", 187);	//esquina superior der
                textcolor(LIGHTMAGENTA); gotoxy(24,3); printf("I n v a s i o n  C o s m i c a");
                textcolor(DARKGRAY);
                gotoxy(22,16);  printf("%c", 200);	//esquina inferior izq
                gotoxy(22,6);   printf("%c", 201);	//esquina superior izq
                gotoxy(55,16);  printf("%c", 188);	//esquina inferior der
                gotoxy(55,6);   printf("%c", 187);	//esquina superior der
		break;
		case 4:
			/* Controles */
			textcolor(DARKGRAY);
            for(xc=20;xc<=60;xc++){
                if(xc >= 23 && xc <= 54){
                    gotoxy(xc,6); 	printf("%c", 205);
                    gotoxy(xc,8); 	printf("%c", 205);
                    gotoxy(xc,20); 	printf("%c", 205);
                }if(xc >= 24 && xc <= 53){
                    gotoxy(xc,4); 	printf("%c", 205);
                    gotoxy(xc,2); 	printf("%c", 205);
                }
                for(yf=1;yf<=20;yf++){
                    if(yf >= 7){
                        gotoxy(22,yf); printf("%c", 186);
                        gotoxy(55,yf); printf("%c", 186);
                    	}if(yf == 3){
                            gotoxy(23,yf); printf("%c", 186);
                            gotoxy(54,yf); printf("%c", 186);
                        }
                    }
                }
                gotoxy(23,4);   printf("%c", 200);	//esquina inferior izq
                gotoxy(23,2);   printf("%c", 201);	//esquina superior izq
                gotoxy(54,4);   printf("%c", 188);	//esquina inferior der
                gotoxy(54,2);   printf("%c", 187);	//esquina superior der
                textcolor(LIGHTMAGENTA); gotoxy(24,3); printf("I n v a s i o n  C o s m i c a");
                textcolor(DARKGRAY);
                gotoxy(22,20);  printf("%c", 200);	//esquina inferior izq
                gotoxy(22,6);   printf("%c", 201);	//esquina superior izq
                gotoxy(55,20);  printf("%c", 188);	//esquina inferior der
                gotoxy(55,6);   printf("%c", 187);	//esquina superior der
        break;
        case 5:
        	textcolor(DARKGRAY);
    		for(xc=20;xc<=60;xc++){
        		if(xc >= 30 && xc <= 46){
            		gotoxy(xc,6); printf("%c", 205);
            		gotoxy(xc,8); printf("%c", 205);
            		gotoxy(xc,16); printf("%c", 205);
        		}if(xc >= 24 && xc <= 53){
            		gotoxy(xc,4); printf("%c", 205);
            		gotoxy(xc,2); printf("%c", 205);
        		}
				for(yf=1;yf<=15;yf++){
            		if(yf >= 7){
                		gotoxy(30,yf); printf("%c", 186);
                		gotoxy(46,yf); printf("%c", 186);
            		}if(yf == 3){
                		gotoxy(23,yf); printf("%c", 186);
                		gotoxy(54,yf); printf("%c", 186);
            		}
				}
    		}
    		gotoxy(23,4);   printf("%c", 200);	//esquina inferior izq
			gotoxy(23,2);   printf("%c", 201);	//esquina superior izq
			gotoxy(54,4);   printf("%c", 188);	//esquina inferior der
			gotoxy(54,2);   printf("%c", 187);	//esquina superior der
    		textcolor(LIGHTMAGENTA); gotoxy(24,3); printf("I n v a s i o n  C o s m i c a");
    		textcolor(DARKGRAY);
    		gotoxy(30,16);   printf("%c", 200);	//esquina inferior izq
			gotoxy(30,6);    printf("%c", 201);	//esquina superior izq
			gotoxy(46,16);   printf("%c", 188);	//esquina inferior der
			gotoxy(46,6);    printf("%c", 187);	//esquina superior der
        break;
	}
}
