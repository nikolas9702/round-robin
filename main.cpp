// RoundRobin.cpp: define el punto de entrada de la aplicación de consola.

#include "stdafx.h"
#include <iostream>

struct Nodo
{
	int cantidad;
	Nodo * siguiente = NULL;
};

typedef struct Nodo Nodo;

Nodo * cabeza = NULL; Nodo * cola;
void insertar();
void mostrar();
void mostrarRound();
int menu();
void ejecutarRound();
void avanzarActividad(Nodo *& , bool & );
int longitudLista = 0;
const int limiteMinimo = 5;
const int limiteMaximo = 10;
const int steapIntervalos = 3;

int main()
{
	insertar();
	insertar();
	insertar();
	insertar();
	insertar();
	int auxMenu;
	do {
		auxMenu = menu();
	} while (auxMenu < 5);
	
    return 0;
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
	while (aux != NULL ) {
		std::cout << aux->cantidad << "\t";
		aux = aux->siguiente;
		if (cabeza == aux)
			break;
	}
	std::cout << std::endl;
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
			mostrarRound();
			auxAnterior = auxCiclo;
			if (eliminar == true) {
				longitudLista--;
				auxAnterior->siguiente = auxCiclo->siguiente;
				if (cabeza == auxCiclo) {
					cabeza = auxCiclo->siguiente;
					cola->siguiente = cabeza;
				}
				else if (cola == auxCiclo) {
					cola = auxAnterior;
					cola->siguiente = cabeza;
				}
				if (cabeza == cola) {
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
