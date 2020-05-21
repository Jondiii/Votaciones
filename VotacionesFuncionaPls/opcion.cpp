/*
 * opcion.cpp
 *
 *  Created on: 14 may. 2020
 *      Author: Jon
 */

#include "Opcion.h"
#include "sqlite3.h"

#include <sstream>
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
    cout << " ID: [ "<< this->id << " ]  Nombre: " << this->nombre << " " << endl;
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
void Opcion::updateBD(int id)
{
	sqlite3 *db;
	sqlite3_stmt * stmt;
	ostringstream updateCan;
	updateCan << "UPDATE candidato SET VOTOS = " << this->votos;
	updateCan << " WHERE ID_VOT = " << id << " AND NOMBRE ='" << this->nombre << "';";
	if (sqlite3_open("votaciones.sql", &db) == SQLITE_OK)
	{
		sqlite3_prepare( db,updateCan.str().c_str(), -1, &stmt, NULL );
		sqlite3_step( stmt );
	}
	sqlite3_finalize(stmt);
	sqlite3_close(db);
}


