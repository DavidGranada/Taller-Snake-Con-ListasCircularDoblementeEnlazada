/*
============================================================
UNIVERSIDAD DE LAS FUERZAS ARMADAS - "ESPE"
============================================================
Tema:		LISTAS CIRCULARES DOBLEMENTE ENLAZADAS
Carrera:	Ingeniería en Sistemas
Profesor:	Ing. Fernando Solis
Integrantes:		Granada David
					Ivan Conejo
					Francisco Sanpedro
============================================================
Fecha Creación:		20/11/17
Fecha Modificación:	20/11/17
============================================================
PRUEBA PARCIAL I .- Generar una lista circular doblemente enlazada.
============================================================
*/
#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <conio.h>

#define ARRIBA 72
#define IZQUIERDA 75
#define DERECHA 77
#define ABAJO 80
#define ESC 27
using namespace std;
int cuerpo[200][2];
int n = 1, tam = 2, dir = 3;
int x = 10, y = 12;
int xc = 30, yc = 15;
int velocidad = 100;

/////////////////////////////
///LISTA DOBLE CIRCULAR
struct nodo {
	int dato;

	struct nodo *siguiente;
	struct nodo *anterior;
};


struct nodo *cabeza = NULL;
struct nodo *cola = NULL;
struct nodo *actual = NULL;

bool esVacio() {
	return cabeza == NULL;
}
void insertarPrimero(int dato) {

	//crear un nuevo nodo
	struct nodo *nuevo = (struct nodo*) malloc(sizeof(struct nodo));
	nuevo->dato = dato;

	if (esVacio()) {
		//hacer una nueva cola
		cola = nuevo;
	}
	else {
		//actualiza la cabeza anterior a nuevo
		cabeza->anterior = nuevo;
	}

	//puntero hacia el antiguo primero
	nuevo->siguiente = cabeza;

	//apunta a la cabeza nuevo
	cabeza = nuevo;
}

void mostrar() {

	//comenzar desde el principio
	struct nodo *ptr = cabeza;

	//navegar desde el principio hasta el fin de la lista
	printf("\n[ ");

	while (ptr != NULL) {
		printf("(%d) ", ptr->dato);
		ptr = ptr->siguiente;
	}

	printf(" ]");
}

char tecla;

void gotoxy(int x, int y)
{
	HANDLE hCon;
	COORD dwPos;

	dwPos.X = x;
	dwPos.Y = y;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hCon, dwPos);
}			
void OcultaCursor() {
	CONSOLE_CURSOR_INFO cci = { 100, FALSE };

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
}
void pintar() {
	for (int i = 2; i < 78; i++) {
		gotoxy(i, 3); printf("%c", 205);
		gotoxy(i, 23); printf("%c", 205);
	}
	for (int v = 4; v < 23; v++) {
		gotoxy(2, v);  printf("%c", 186);
		gotoxy(77, v);  printf("%c", 186);
	}
	gotoxy(2, 3);    printf("%c", 201);
	gotoxy(2, 23);    printf("%c", 200);
	gotoxy(77, 3);    printf("%c", 187);
	gotoxy(77, 23);    printf("%c", 188);
}
void guardar_posicion() {
	cuerpo[n][0] = x;
	cuerpo[n][1] = y;
	n++;
	if (n == tam) n = 1;
}
void dibujar_cuerpo() {
	for (int i = 1; i < tam; i++) {
		gotoxy(cuerpo[i][0], cuerpo[i][1]); printf("%c", 4);
	}
}
void borrar_cuerpo() {
	gotoxy(cuerpo[n][0], cuerpo[n][1]); printf(" ");
}
void teclear() {
	if (_kbhit()) {
		tecla = _getch();
		switch (tecla) {
		case ARRIBA: if (dir != 2) dir = 1; break;
		case ABAJO: if (dir != 1) dir = 2; break;
		case DERECHA: if (dir != 4) dir = 3; break;
		case IZQUIERDA: if (dir != 3) dir = 4; break;
		}
	}
}

int  comida(int temporal)
{

	if (x == xc && y == yc)
	{
		xc = (rand() % 73) + 4;
		yc = (rand() % 19) + 4;


		insertarPrimero(temporal);


		gotoxy(20, 25); mostrar();
		temporal = 1 + rand() % (11 - 1);
		gotoxy(xc, yc); printf("%i", temporal);
	}
	return temporal;
}
bool game_over()
{
	if (y == 3 || y == 23 || x == 2 || x == 77) return false;
	for (int j = tam - 1; j > 0; j--) {
		if (cuerpo[j][0] == x &&  cuerpo[j][1] == y)
			return false;
	}
	return true;
}
int main()
{
	int  ncomida = 1 + rand() % (11 - 1);
	OcultaCursor();
	gotoxy(0, 25); cout << "la lista circular es:";
	pintar();

	gotoxy(xc, yc); printf("%d", ncomida);

	while (tecla != ESC && game_over())
	{

		borrar_cuerpo();
		guardar_posicion();
		dibujar_cuerpo();
		ncomida = comida(ncomida);

		teclear();
		teclear();

		if (dir == 1) y--;
		if (dir == 2) y++;
		if (dir == 3) x++;
		if (dir == 4) x--;

		Sleep(velocidad);
	}
	pintar();

	return 0;
}
