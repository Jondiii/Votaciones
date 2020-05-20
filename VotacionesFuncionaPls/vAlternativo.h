/*
 * vAlternativo.h
 *
 *  Created on: 14 may. 2020
 *      Author: Jon
 */

#ifndef VALTERNATIVO_H_
#define VALTERNATIVO_H_

class vAlternativo{
	int* idOpciones;	// [5,4,3,1,2] (id de las opciones en el orden que las ha puesto el votante)
	int paso;
public:
	vAlternativo(int* idOpciones,int paso, int nParticipantes);
	vAlternativo(const vAlternativo &vAlternativo);
	vAlternativo();
	virtual ~vAlternativo();

	int* getIdOpciones();
	int getPaso();

	void imprimirValternativo(int numCandidatos);
};

#endif /* VALTERNATIVO_H_ */
