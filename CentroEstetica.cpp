#include <stdio.h>
#include <stdlib.h>
#include "libreriajuantfi.h"
#include<windows.h>
#include <iostream>
using namespace std;
void gotoxy(int x,int y);
void dibujarCuadro(int x1,int y1,int x2,int y2);
void menu();
main(){
	    system("mode con: cols=80 lines=25"); 
	    system("COLOR B0"); 
	    dibujarCuadro(0,0,78,24); 
	    dibujarCuadro(1,1,77,3); 
	    gotoxy(30,2); cout << "PROGRAMA CENTRO DE SALUD\n\n";
		//HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
        //SetConsoleTextAttribute(hConsole, 10);  
        menu();
        gotoxy (2,12); system("pause");
        
        return 0;
}
void gotoxy(int x,int y){  
      HANDLE hcon;  
      hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
      COORD dwPos;  
      dwPos.X = x;  
      dwPos.Y= y;  
      SetConsoleCursorPosition(hcon,dwPos);  
 }
void dibujarCuadro(int x1,int y1,int x2,int y2){
	int i;
	
    for (i=x1;i<x2;i++){
		gotoxy(i,y1); cout << "\304"; 
		gotoxy(i,y2); cout << "\304"; 
    }

    for (i=y1;i<y2;i++){
		gotoxy(x1,i); cout <<"\263"; 
		gotoxy(x2,i); cout <<"\263"; 
	}
	
    gotoxy(x1,y1); cout<< "\332"; 
    gotoxy(x1,y2); cout<< "\300";
    gotoxy(x2,y1); cout<< "\277";
    gotoxy(x2,y2); cout<< "\331";
}
void menu(){
	int op;
	    do{
	    printf("\t\t\t------------------------\n");
		printf("\t\t\t1-MODULO ESPACIOS     \n");
		printf("\t\t\t------------------------\n");
		printf("\t\t\t2-MODULO RECEPCION    \n");
		printf("\t\t\t------------------------\n");
		printf("\t\t\t3-MODULO ADMINISTRACION\n");
		printf("\t\t\t------------------------\n");
		printf("\t\t\t4-SALIR DEL PROGRAMA\n");	
		printf("\t\t\t------------------------\n");	
		printf("\t\t\tIngrese una opcion por favor: ");
		scanf("%d", &op);		
		switch(op){
			case 1:
				system("ModuloEspacios.exe");
                getch();
				break;
			case 2:
				system("ModuloRecepcion.exe");
				getch();
				break;
			case 3:
				system("ModuloAdministracion.exe");
				getch();
				break;
		}
	}while(op != 4);
}

