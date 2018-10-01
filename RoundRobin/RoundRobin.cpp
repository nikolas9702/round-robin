// RoundRobin.cpp: define el punto de entrada de la aplicación de consola.

#include "stdafx.h"
#include <iostream>
#include <string>   // C++ string class
#include <cstring>  // C-string
#include <time.h>

struct Nodo
{
	int cantidad;
	Nodo * siguiente = NULL;
};

typedef struct Nodo Nodo;

Nodo * cabeza = NULL; Nodo * cola; Nodo * auxIntervalo;
void insertar();
void mostrar();
void mostrarRound();
int menu();
void ejecutarRound();
void avanzarActividad(Nodo *& , bool & );
void mostrarLista(Nodo * , int , Nodo *, bool  );
void linea(int , int , bool , bool);
void sleep(int);
int longitudLista = 0;
const int limiteMinimo = 2;
const int limiteMaximo = 6;
const int steapIntervalos = 3;
int tabs = 8;
unsigned int microseconds;

int main()
{
	int auxMenu;
	do {
		auxMenu = menu();
	} while (auxMenu < 5);
	system("pause");
    return 0;
}

void mostrarLista (Nodo * NodoInicial , int longitud , Nodo * inicio , bool limpiar = false ) {
	bool elmentoAdicional = false;
	bool salir = false;
	int ubicacion = (longitudLista - 1);
	if (limpiar == true)
		system("cls");
	else
		std::cout << std::endl;
	if (longitud == 1) {
		longitud = 1;
		tabs = 13;
	}
	else if (longitud == 2) {
		tabs = 10;
		elmentoAdicional = true;
	}
	else if (longitud == 3) {
		tabs = 7;
		longitud = 4;
		elmentoAdicional = true;
	}
	else if (longitud == 4) {
		tabs = 9;
		elmentoAdicional = true;
	}
	else if (longitud == 6) {
		tabs = 4;
		longitud = 13;
		elmentoAdicional = true;
	}
	
	
	do
	{
		
		Nodo * aux = NodoInicial;
		if (inicio == NULL) {
			linea(longitud, tabs, elmentoAdicional, true);
			std::cout << std::endl << char(186);
			while (aux != NULL)
			{
				std::cout << "\t" << aux->cantidad;
				aux = aux->siguiente;
				if (aux == NodoInicial)
					break;
			}
			std::cout << "\t" << char(186);
			linea(longitud, tabs, elmentoAdicional, false);
		}
		if (inicio != NULL) {
			system("cls");
			int * datos = new int[longitudLista];
			for (int i = 0; i < longitudLista; i++)
			{
				datos[i] = char();
			}
			datos[ubicacion] = inicio->cantidad;
			aux = inicio;
			linea(longitud, tabs, elmentoAdicional, true);
			std::cout << std::endl << char(186);
			while (aux != NULL)
			{
				std::cout << "\t" << aux->cantidad;
				aux = aux->siguiente;
				if (aux == inicio)
					break;
			}
			std::cout << "\t" << char(186);
			linea(longitud, tabs, elmentoAdicional, false);

			std::cout << "\n";

			linea(longitud, tabs, elmentoAdicional, true);
			std::cout << std::endl << char(186);
			for (int i = 0; i < longitudLista; i++)
			{
				std::cout << "\t" << datos[i];
			}
			ubicacion--;
			if (ubicacion == 0) {
				salir = true;
			}
			else {
				datos[ubicacion] = datos[(ubicacion + 1)];
				datos[(ubicacion + 1)] = NULL;
			}
			std::cout << "\t" << char(186);
			linea(longitud, tabs, elmentoAdicional, false);
			sleep(1);
		}
	} while (inicio != NULL && !salir);
}

void linea(int longitud, int tabs, bool elmentoAdicional, bool arriba = true) {
	int arreglo[] = { 200,188 };
	if (arriba) {
		arreglo[0] = 201;
		arreglo[1] = 187;
	}
	std::cout << std::endl << char(arreglo[0]);
	for (int i = 0; i <= (longitud*tabs) + 1; i++) {
		std::cout << "=";
		if (elmentoAdicional && i == (longitud*tabs) + 1)
			std::cout << "=";
	}
	std::cout << char(arreglo[1]);
}

void insertar() {
	Nodo * nuevoNodo = new Nodo();
	std::cout << "\n longitudLista : " << longitudLista << " limiteMaximo : " << limiteMaximo << "\n";
	if (longitudLista < limiteMaximo ) {
		std::cout << "\n Digite la duracion del evento : ";
		std::cin >> nuevoNodo->cantidad;
		if (cabeza == NULL) {
			cabeza = nuevoNodo;
		}
		else {
			cola->siguiente = nuevoNodo;
			nuevoNodo->siguiente = cabeza;
		}
		longitudLista++;
		cola = nuevoNodo;
	}
	else {
		std::cout << "\n No puede tener mas procesos la lista" ;
	}
}

bool numero( std::string valor , std::string mensaje ) {
	return false;
}

void mostrar() {
	Nodo * aux = cabeza;
	while (aux != NULL ) {
		std::cout << aux->cantidad<<std::endl;
		aux = aux->siguiente;
		if (cabeza == aux)
			break;
	}
}

void mostrarRound() {
	int elementos = 0;
	Nodo * aux = cabeza;
	mostrarLista(cabeza, longitudLista , auxIntervalo , false );
	std::cout << std::endl;
}

void sleep(int segundos) {
	time_t timer, actual;
	actual = time(NULL) + segundos;
	timer = actual;
	while (actual >= timer)
	{
		timer = time(NULL);
	}
}

void ejecutarRound() {
	int contadorCeros = 0;
	bool eliminar = false;

	if (longitudLista >= limiteMinimo && longitudLista <= limiteMaximo ) {
		Nodo * auxCiclo = cabeza;
		Nodo * auxAnterior = NULL;
		while (auxCiclo != NULL && longitudLista > 0)
		{
			avanzarActividad(auxCiclo , eliminar);
			auxIntervalo = auxCiclo;
			mostrarRound();
			auxAnterior = auxCiclo;
			if (eliminar == true) {
				longitudLista--;
				auxAnterior->siguiente = auxCiclo->siguiente;
				if (cabeza == auxCiclo) { // Si es la cabeza
					cabeza = auxCiclo->siguiente;
					cola->siguiente = cabeza;
				}
				else if (cola == auxCiclo) { // si es la cola
					cola = auxAnterior;
					cola->siguiente = cabeza;
				}

				if (cabeza == cola) { // si se acabo el proceso
					cabeza = NULL;
					break;
				}
				delete auxCiclo;
				auxCiclo = cabeza;
				eliminar = false;
			}
			auxCiclo = auxCiclo->siguiente;
		}
	}
	else {
		std::cout << "No hay suficientes procesos en la actividad ." << std::endl;
	}
}

void avanzarActividad( Nodo *& trabajando , bool &eliminar) {
	int contadorAvances = 1;
	while ( steapIntervalos >= contadorAvances && trabajando->cantidad > 0)
	{
		contadorAvances++;
		trabajando->cantidad--;
		if (trabajando->cantidad == 0)
			eliminar = true;
	}
}

int menu() {
	int menu;
	std::cout << "\t Round Robin \n1) Insertar \n2) Mostrar\n3) Round Robin\n " ;
	std::cin >> menu;
	switch (menu)
	{
		case 1 :
			insertar();
			mostrarLista(cabeza, longitudLista , NULL, true);
		break;
		case 2:
			mostrar();
		break;
		case 3:
			ejecutarRound();
		break;
	}
	return menu;
}
