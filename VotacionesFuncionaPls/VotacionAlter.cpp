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
	this->alternativos = new vAlternativo*[this->nParticipantes];
	for (int i = 0; i <this->numVotantes;i++)
	{
		this->alternativos[i] = alternativos[i];
	}
}
VotacionAlter::VotacionAlter(const VotacionAlter &va):Votacion(va)
{
	this->numVotantes = va.numVotantes;
	this->alternativos = new vAlternativo*[this->nParticipantes];
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
	cout << "PARTICIPANTES:" << endl;
	for (int i = 0; i< this->getnParticipantes(); i++)
	{
		cout << i + 1 <<". ";
		this->getOpcion(i)->imprimirOpcion();
	}
	cout << "Ordena las Opciones en orden de preferencia:" << endl;
	int numero;
	int *votos = new int[this->getnParticipantes()]; //Aquí se guarda el id de las opciones metidas.
	for (int i = 0; i< this->getnParticipantes() ;i++)
	{
		cout << "Opcion "<< i + 1 << " : ";
		cin >> numero;
		numero -= 1;
		votos[i] = this->getOpcion(numero)->getId();
	}
	vAlternativo *v1 = new vAlternativo(votos, 0, this->getnParticipantes());
	this->anadirvAlternativo(v1); //Añade el voto de esta persona. Funciona como añadir votación.
}

void VotacionAlter::vaciador(int cantidadOpciones, int *resultados)
{
	for (int x = 0; x < cantidadOpciones; ++x) {
		resultados[x] = 0;
	}
}

//devuelve la id del ganador.
int VotacionAlter::terminarVot()
{

	int resultados[this->nParticipantes];
	//es un array que marca cual de las opciones ha sido eliminada [0,0,1,0] en este caso la opción 3 está eliminada
	int eliminados[this->nParticipantes]; //Se usan 0s y 1s, se podrían haber usado booleanos.

	vaciador(this->nParticipantes, eliminados);//El array que se le pasa se pone a 0.


	//array con todos los votos
	vAlternativo * votos[this->numVotantes];
	for (int i = 0; i < this->numVotantes; ++i)
	{
		votos[i] = this->alternativos[i];//Se meten todos los votos de una votación.
	}


	int votosNecesarios;
	//calculo cuantos votos son el 50% + 1 (los necesarios para ganar).
	votosNecesarios = ((this->numVotantes/2) + 1);
	fflush(stdout);
	printf("Votosnecesarios = %i\n", votosNecesarios);

	int numVotTemp;
	int numResTemp;
	int Elimin;
	int SWeliminado;
	int ganador;
	int hayGanador = 0;
	int noResultado = 0;
	int contador = 0;

	while(hayGanador == 0 && noResultado == 0 && contador < this->nParticipantes ){ //El while no se tiene que hacer más veces que el número de participanes
																					//(porque se quita un participante por vuelta)
		contador = contador + 1;

		vaciador(this->nParticipantes, resultados);

		//intento sacar cual de las opciones tiene más votos
		for (int i = 0;   i < this->numVotantes; ++i) {
			numVotTemp = votos[i]->getIdOpciones()[0]; //Coger la primera opción del votante i
			numResTemp = resultados[numVotTemp - 1]; //+1 al array de resultados en la posición de la id del votante (si votas en la opción 1
													//se suma uno a la posición 0, etc. Se hace por cada votante.
			numResTemp = numResTemp + 1;
			resultados[numVotTemp - 1] = numResTemp;
		}

		//Miro si la opcion con mas votos pasa los votos necesa
		for (int j = 0; j < this->nParticipantes; ++j) {
			numVotTemp = resultados[j];
			if (numVotTemp >= votosNecesarios){ //Miramos si alguna opción tiene suficientes votos como para ganar.
				ganador = j;
				hayGanador = 1;
				this->votAbiero = false;
				return ganador + 1;
			}
		}

		//si no hay ganador
		if (hayGanador == 0) {
			numVotTemp = resultados[0]; //Se meten la cantidad de votos de la primera opción.
			Elimin = 0; //"eliminar la primera opción".

			//se mira si alguna de las opciones esta eliminada
			for (int k = 1; k < this->nParticipantes; ++k) {
				if(eliminados[k] == 1 ){//Se mira cada opción si está eliminada, y si no lo está...
				}else{
					//si la cantidad de votos de la opción k es mayor que la que ya esta guardada se intercamban siempre y cuando no haya estado eliminada antes
					if (numVotTemp > resultados[k] || eliminados[Elimin] ==1) //Similar a lo de antes, para saber cuál tiene menos votos.
					{
						numVotTemp = resultados[k];
						Elimin = k; //Se guarda la opción que se va a eliminar.
					} //Al final nos quedamos con la que menos votos tenga.
				}
			}
			//la opción guardada en Elim se marca como eliminada
			eliminados[Elimin] = 1; //1 para marcar "true" de eliminado.

			// se comprueba si alguno de los arrais de votaciones tiene una opcion que este eliminada y en caso de que lo este se mueven todos los votos
			// una posicion a la izquierda  hasta que la primera opcion no esté eliminada
			//EJ: la opcion 3 y 2 esta eliminada [3,2,1,4] --> [2,1,4,4] --> [1,4,4,4] //Los últimos son 4s porque no se pueden meter null, pero son votos que ya no "están".
			for (int l = 0; l < this->numVotantes; ++l) {
				SWeliminado = 1;
				while  (SWeliminado == 1){
					if (eliminados[(votos[l]->getIdOpciones()[0]) - 1] == 1) {
						SWeliminado = 1;
						for (int n = 1; n < this->nParticipantes; ++n) {
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
