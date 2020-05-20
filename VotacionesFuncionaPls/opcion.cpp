/*
 * opcion.cpp
 *
 *  Created on: 14 may. 2020
 *      Author: Jon
 */

#include "Opcion.h"

#include <string.h>
#include <iostream>
using namespace std;

Opcion::Opcion(int id, int votos, const char* nombre)
{
	this->id = id;
	this->votos = votos;
	this->nombre = new char[strlen(nombre) + 1];
	strcpy(this->nombre, nombre);
}

Opcion::Opcion(const Opcion& opc)
{
	this->id = opc.id;
	this->nombre = new char[strlen(opc.nombre) + 1];
	strcpy(this->nombre, opc.nombre);
	this->votos = opc.votos;
}
Opcion::Opcion()
{
	this->id = 0;
	this->nombre = "";
	this->votos = 0;
}
Opcion::~Opcion()
{
	delete [] nombre;
}
int Opcion::getId()
{

	return this->id;
}

char* Opcion::getNombre()
{
	return this->nombre;
}

int Opcion::getVotos()
{
	return this->votos;
}

void Opcion::incrementarVotos()
{
	this->votos += 1;
}
void Opcion::imprimirOpcion()
{
    cout << " ID: [ "<< this->id << " ]  Nombre: " << this->nombre << " ( " <<  this->votos  << " votos )" << " " << endl;
}

void Opcion::setId(int id)
{
	this->id = id;
}
void Opcion::setNombre(const char* nombre)
{
	this->nombre = new char[strlen(nombre) + 1];
	strcpy(this->nombre, nombre);
}
void Opcion::setVotos(int votos)
{
	this->votos = votos;
}


