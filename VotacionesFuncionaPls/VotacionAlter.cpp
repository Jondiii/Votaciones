/*
 * VotacionAlter.cpp
 *
 *  Created on: 18 may. 2020
 *      Author: Jon
 */

#include "VotacionAlter.h"
#include "Votacion.h"
#include "VAlternativo.h"
#include <string.h>
#include <iostream>

using namespace std;

VotacionAlter::VotacionAlter(int id, int fecha_inicio, int fecha_fin, const char* tipoVotacion, const char* ganador, const char* nombreVotacion, int nParticipantes, Opcion * paticipantes[], int num_VA, vAlternativo* alternativos[]):Votacion(id, fecha_inicio, fecha_fin,tipoVotacion, ganador, nombreVotacion, nParticipantes,paticipantes)
{
	this->numVotantes = num_VA;
	this->alternativos = new vAlternativo*[this->numVotantes];
	for (int i = 0; i <this->numVotantes;i++)
	{
		this->alternativos[i] = alternativos[i];
	}
}
VotacionAlter::VotacionAlter(const VotacionAlter &va):Votacion(va)
{
	this->numVotantes = va.numVotantes;
	this->alternativos = new vAlternativo*[this->numVotantes];
	for (int i = 0; i <this->numVotantes;i++)
	{
		this->alternativos[i] = va.alternativos[i];
	}
}
VotacionAlter::VotacionAlter():Votacion()
{
	this->alternativos = new vAlternativo*[0];
	this->numVotantes = 0;
}
VotacionAlter::~VotacionAlter()
{
	delete [] alternativos;
}
int VotacionAlter::getNumVotantes()
{
	return this->numVotantes;
}
vAlternativo* VotacionAlter::getAlternativo(int i)
{
	return this->alternativos[i];
}

void VotacionAlter::setAlternativos(vAlternativo* alternativo[])
{
	this->alternativos = new vAlternativo*[this->nParticipantes];
	for (int i = 0;  i < this->numVotantes; i ++)
	{
		this->alternativos[i] = alternativo[i];
	}
}
void VotacionAlter::setNumVotantes(int numero){
	this-> numVotantes = numero;
}

void VotacionAlter::anadirvAlternativo(vAlternativo *alternativo)
{
	int nuevo_Va = this->numVotantes + 1;
	vAlternativo **vA = new vAlternativo*[nuevo_Va];
	for (int i = 0 ; i <this->numVotantes; i++)
	{
		vA[i] = this->alternativos[i];
	}
	vA[this->numVotantes] = alternativo;
	this->numVotantes = nuevo_Va;
	this->alternativos = new vAlternativo*[nuevo_Va];
	for (int i = 0 ; i <this->numVotantes; i++)
	{
		this->alternativos[i] = vA[i];
	}
}
void VotacionAlter::votar()
{
	if (!this->votAbiero)
	    {
	        cout << "La Votacion ya esta cerrada"<<endl;
	        return;
	    }
	cout << "PARTICIPANTES:" << endl;
	for (int i = 0; i< this->getnParticipantes() ;i++)
	{
		cout << i + 1 <<". ";
		this->getOpcion(i)->imprimirOpcion();
	}
	cout << "Ordena las Opciones en orden de preferencia:" << endl;
	int numero;
	int *votos = new int[this->getnParticipantes()];
	for (int i = 0; i< this->getnParticipantes() ;i++)
	{
		cout << "Opcion "<< i + 1 << " : ";
		cin >> numero;
		numero -= 1;
		votos[i] = numero;
	}
	vAlternativo *v1 = new vAlternativo(votos, 0, this->getnParticipantes());
	this->anadirvAlternativo(v1);
}

void VotacionAlter::vaciador(int cantidadOpciones, int *resultados)
{

	for (int x = 0; x < cantidadOpciones; ++x) {
		resultados[x] = 0;
	}

}

int VotacionAlter::terminarVot()
{

	int resultados[this->nParticipantes];

	int eliminados[this->nParticipantes];
	vaciador(this->nParticipantes, eliminados);




	int resultadosTemp[this->nParticipantes];


	vAlternativo * votos[this->numVotantes];
	for (int i = 0; i < this->numVotantes; ++i) {
		votos[i] = this->alternativos[i];
	}


	int votosNecesarios;

	votosNecesarios = ((this->numVotantes/2) + 1)	;

	int numVotTemp;
	int numResTemp;
	int Elimin;
	int SWeliminado;
	int ganador;
	int paso = 0;
	int hayGanador = 0;
	int noResultado = 0;
	int contador = 0;

	while(hayGanador == 0 && noResultado == 0 && contador < this->nParticipantes ){
		contador = contador + 1;
		vaciador(this->nParticipantes, resultados);
		for (int i = 0;   i < this->numVotantes; ++i) {
			numVotTemp = votos[i]->getIdOpciones()[0];
			numResTemp = resultados[numVotTemp - 1];
			numResTemp = numResTemp + 1;
			resultados[numVotTemp - 1] = numResTemp;
		}

		for (int j = 0; j < this->nParticipantes; ++j) {
			numVotTemp = resultados[j];
			if (numVotTemp >= votosNecesarios){
				ganador = j;
				hayGanador = 1;
				this->votAbiero = false;
				return ganador + 1;
			}
		}

		if (hayGanador == 0) {
			numVotTemp = resultados[0];
			Elimin = 0;

			for (int k = 1; k < this->nParticipantes; ++k) {

				if(eliminados[k] == 1 ){

				}else{
					if (numVotTemp > resultados[k] || eliminados[Elimin] ==1){

						numVotTemp = resultados[k];
						Elimin = k;
					}
				}
			}

			eliminados[Elimin] = 1;

			for (int l = 0; l < this->numVotantes; ++l) {
				SWeliminado = 1;
				while  (SWeliminado == 1){

					if (eliminados[(votos[l]->getIdOpciones()[0]) - 1] == 1) {
						SWeliminado = 1;
						// mover 1
						for (int n = 1; n < this->nParticipantes; ++n) {
							fflush(stdout);
							votos[l]->getIdOpciones()[n - 1] = votos[l]->getIdOpciones()[n];
						}
					}else{
						SWeliminado = 0;
					}

				}
			}
		}
	}

	this->votAbiero = false;
	return -1;

}
