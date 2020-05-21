#include "Opcion.h"
#include "Votacion.h"
#include <string.h>
#include <iostream>
#include "Persona.h"

#include "VAlternativo.h"
using namespace std;

Votacion::Votacion()
{
	this->id = 0;
	this->nParticipantes = 0;
	this->participantes = 0;
	this->fecha_inicio = 0;
	this->fecha_fin = 0;
	this->ganador = "NADIE";
	this->nombreVotacion = 0;
	this->tipoVotacion = 0;

}
Votacion::Votacion(int id, int fecha_inicio, int fecha_fin, const char* tipoVotacion, const char* ganador, const char* nombreVotacion, int nParticipantes, Opcion * participantes[])
{
	this->id = id;
	this->nParticipantes = nParticipantes;
	this->participantes = new Opcion*[this->nParticipantes];
	for (int i = 0;  i < this->nParticipantes; i++ )
	{
		this->participantes[i] = participantes[i];
	}
	this->fecha_inicio = fecha_inicio;
	this->fecha_fin = fecha_fin;
	this->ganador = new char [strlen(ganador)+1];
		strcpy(this->ganador, ganador);
	this->nombreVotacion = new char [strlen(nombreVotacion)+1];
		strcpy(this->nombreVotacion, nombreVotacion);
	this->tipoVotacion = new char [strlen(tipoVotacion)+1];
		strcpy(this->tipoVotacion, tipoVotacion);
		this->votAbiero = true;

}
Votacion::Votacion(const Votacion &v)
{
	this->id = v.id;
	this->nParticipantes = v.nParticipantes;
	this->participantes = new Opcion*[v.nParticipantes];
	for (int i = 0;  i <v.nParticipantes; i ++)
	{
		this->participantes[i] = v.participantes[i];
	}
	this->fecha_inicio = v.fecha_inicio;
	this->fecha_fin = v.fecha_fin;
	this->ganador = new char [strlen(v.ganador)+1];
		strcpy(this->ganador, v.ganador);
	this->nombreVotacion = new char [strlen(v.nombreVotacion)+1];
		strcpy(this->nombreVotacion, v.nombreVotacion);
	this->tipoVotacion = new char [strlen(v.tipoVotacion)+1];
			strcpy(this->tipoVotacion, v.tipoVotacion);
	this->votAbiero = true;
}

Votacion::~Votacion()
{
	delete [] ganador;
	delete [] participantes;
	delete [] nombreVotacion;
}
int Votacion::getId()
{
	return this->id;
}
char* Votacion::getGanador()
{
	return this->ganador;
}
char* Votacion::getTipoVotacion()
{
	return this->tipoVotacion;
}
char* Votacion::getNombreVotacion()
{
	return this->nombreVotacion;
}
int Votacion::getFecha_fin()
{
	return this->fecha_fin;
}
int Votacion::getFecha_inicio()
{
	return this->fecha_inicio;
}
int Votacion::getnParticipantes()
{
	return this->nParticipantes;
}
Opcion** Votacion::getOpciones()
{
	return this->participantes;
}
Opcion* Votacion::getOpcion(int i)
{
	return this->participantes[i];
}
void Votacion::setNParticipantes(int numero)
{
	this->nParticipantes = numero;
	this->participantes = new Opcion*[numero];
}
void Votacion::setParticipantes(Opcion* opciones[])
{
	this->participantes = new Opcion*[this->nParticipantes];
	for (int i = 0;  i <this->nParticipantes; i ++)
	{
		this->participantes[i] = opciones[i];
	}
}
void Votacion::setId(int id)
{
	this->id = id;
}
void Votacion::setFecha_fin(int fecha_fin)
{
	this->fecha_fin = fecha_fin;
}
void Votacion::setFecha_inicio(int fecha_inicio)
{
	this->fecha_inicio = fecha_inicio;
}
void Votacion::setTipoVotacion(const char* tipoVotacion)
{
	this->tipoVotacion = new char [strlen(tipoVotacion)+1];
	strcpy(this->tipoVotacion, tipoVotacion);
}
void Votacion::setGanador(const char* ganador)
{
	this->ganador = new char [strlen(ganador)+1];
	strcpy(this->ganador, ganador);
}
void Votacion::setNombreVotacion(const char* nombreVotacion)
{
	this->nombreVotacion = new char [strlen(nombreVotacion)+1];
	strcpy(this->nombreVotacion, nombreVotacion);
}
void Votacion::imprimirVotacion()
{
	cout <<"ID [ "<< this->getId() << " ] "<< "NOMBRE : ( "<< this->nombreVotacion <<  " ) " << "INICIO: "<< this->fecha_inicio << " FIN: "<< this->fecha_fin << endl;
}
void Votacion::votar()
{
	cout << "PARTICIPANTES: " << endl;
	for (int i = 0; i< this->getnParticipantes() ;i++)
	{
		cout << i + 1 <<". ";
		this->getOpciones()[i]->imprimirOpcion();
	}

	cout << "Introduce el numero de la Opcion a la que desea votar:" << endl;
	int numero;
	cin >> numero;
	numero -= 1;
	this->getOpcion(numero)->incrementarVotos();
	this->getOpcion(numero)->updateBD(this->getId());
}
void Votacion::setOpcion(Opcion op, int num)
{
    this->participantes[num]->setId(op.getId());
    this->participantes[num]->setNombre(op.getNombre());
    this->participantes[num]->setVotos(op.getVotos());
}
int Votacion::terminarVot(){
//    int firstPassThePost2(Opcion Opciones[], int cantidadOpciones){
    Opcion * opcionGuar = this->participantes[0];
    int cantGuar; //= punteroOpciones->getVotos();
    int empate = 0;

    for (int i = 1;  i < this->nParticipantes ; ++ i) {
        Opcion * opcionCar = this->participantes[0];
        if (opcionGuar->getVotos() < opcionCar->getVotos()) {
            cantGuar = opcionCar->getVotos();
            opcionGuar = opcionCar;
            empate = 0;
        }else if(cantGuar == opcionCar->getVotos()){
            empate = 1;
        }
    }
    if (empate == 1) {
        setGanador("Empate");
        this->votAbiero = false;
        return 0;
    }
    setGanador(opcionGuar->getNombre());
    this->votAbiero = false;
    return opcionGuar->getId();
}

