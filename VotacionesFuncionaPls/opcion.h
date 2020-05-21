/*
 * opcion.h
 *
 *  Created on: 14 may. 2020
 *      Author: Jon
 */

#ifndef OPCION_H_
#define OPCION_H_

class Opcion{
	int id;
	int votos;
	char* nombre;
public:

	Opcion(int id, int votos, const char* nombre);
	Opcion(const Opcion& opcion);
	Opcion();
	virtual ~Opcion();


	int getId();
	char* getNombre();
	int getVotos();

	void setId(int id);
	void setNombre(const char* nombre);
	void setVotos(int votos);

	void incrementarVotos();
	void imprimirOpcion();

};

#endif

