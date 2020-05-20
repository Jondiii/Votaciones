/*
 * persona.h
 *
 *  Created on: 14 may. 2020
 *      Author: Jon
 */
#ifndef PERSONA_H_
#define PERSONA_H_
#include "votacion.h"

class Persona
{
private:
	int dni;
	int edad;
	int cod_postal;
public:
	Persona(int dni);
	Persona(const Persona &);
	~Persona();

	static bool comprobarDni(int dni, int id);
	void insertarPersonaDB(int id);

	void setEdad(int edad);
	void setCodigo(int cod_postal);

	int getCodigo();
	int getDni();
	int getEdad();
};

#endif /* PERSONA_H_ */
