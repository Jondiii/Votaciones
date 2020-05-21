/*
 * VotacionAlter.h
 *
 *  Created on: 18 may. 2020
 *      Author: Jon
 */

#ifndef VOTACIONALTER_H_
#define VOTACIONALTER_H_

#include "Opcion.h"
#include "VAlternativo.h"
#include "Votacion.h"

class VotacionAlter: public Votacion
{
	int numVotantes;
	vAlternativo **alternativos;
	void vaciador(int cantidadOpciones, int *resultados);
public:
	VotacionAlter(int id, int fecha_inicio, int fecha_fin, const char* tipoVotacion, const char* ganador, const char* nombreVotacion, int nParticipantes, Opcion * paticipantes[], int num_VA, vAlternativo *alternativos[]);
	VotacionAlter(const VotacionAlter &);
	VotacionAlter();
	virtual ~VotacionAlter();

	int getNumVotantes();
	vAlternativo* getAlternativo(int i);
	void anadirvAlternativo(vAlternativo *alternativo);

	void setId(int id);
	void setNombreVotacion(const char* nombreVotacion);
	void setFecha_inicio(int fecha_inicio);
	void setFecha_fin(int fecha_fin);
	void setNParticipantes(int numero);
	void setParticipantes(Opcion* opciones[]);
	void setTipoVotacion(const char* tipoVotacion);
	void setOpcion(Opcion op, int num);
	void setNumVotantes(int votantes);
	void setAlternativos(vAlternativo* alternativo[]);

	virtual int terminarVot();
	virtual void votar();
};
#endif /* VOTACIONALTER_H_ */
