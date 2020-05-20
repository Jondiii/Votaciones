/*
 * vAlternativo.cpp
 *
 *  Created on: 14 may. 2020
 *      Author: Jon
 */

#include "vAlternativo.h"

#include <string.h>
#include <iostream>

using namespace std;

vAlternativo::vAlternativo(int* idOpciones,int paso, int nParticipantes)
{
    this->idOpciones = new int[nParticipantes];
    for (int i = 0; i <nParticipantes; i++)
    {
        this->idOpciones[i] = idOpciones[i];
    }
    this->paso = paso;
}

vAlternativo::vAlternativo(const vAlternativo &vAlternativo)
{
	this->idOpciones = vAlternativo.idOpciones;
	this->paso = vAlternativo.paso;
}
vAlternativo::vAlternativo()
{
	this->paso = 0;
	this->idOpciones = NULL;
}
vAlternativo::~vAlternativo()
{
	delete [] idOpciones;
}
int* vAlternativo::getIdOpciones()
{
	return this->idOpciones;
}
int vAlternativo::getPaso()
{
	return this->paso;
}

void vAlternativo::imprimirValternativo(int numCandidatos)
{
    cout << " [ " ;
    for (int i = 0; i<numCandidatos; i++)
    {
        cout << " [ "<< this->idOpciones[i] << " ] " ;
        if (i != numCandidatos -1)
        {
            cout << " , " ;
        }
    }
    cout << " ] " <<endl;
}

