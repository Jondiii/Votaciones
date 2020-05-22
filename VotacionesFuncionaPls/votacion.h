#ifndef VOTACION___H_
#define VOTACION___H_

#include "Opcion.h"

class Votacion{
	/*
	 * int id : identificador de la votación
	 * char* ganador : nombre de la opción ganadora
	 * char* nombreVotacion : nombre de la votacion
	 * int nParticipantes : numero de
	 * int fecha_inicio : fecha de inicio de la votacion
	 * int fecha_fin : fecha de fin de la votacion
	 * char* tipoVotacion : tipo de votación
	 * Opcion ** participantes : Array de opciones
	 * bool votAbiero : indica si la votación esta abierta
	 */
protected:
	int id;
	char* ganador;
	char* nombreVotacion;
	int nParticipantes;
	int fecha_inicio;
	int fecha_fin;
	char* tipoVotacion;
	Opcion ** participantes;
	bool votAbiero;

public:
	Votacion(int id, int fecha_inicio, int fecha_fin, const char* tipoVotacion, const char* ganador, const char* nombreVotacion, int nParticipantes, Opcion * paticipantes[]);
	Votacion(const Votacion &);
	Votacion();
	virtual ~Votacion();

	void setId(int id);
	void setGanador(const char* ganador);
	void setNombreVotacion(const char* nombreVotacion);
	void setFecha_inicio(int fecha_inicio);
	void setFecha_fin(int fecha_fin);
	void setNParticipantes(int numero);
	void setParticipantes(Opcion* opciones[]);
	void setTipoVotacion(const char* tipoVotacion);
	void setOpcion(Opcion op, int num);
	void setVotAbierto(bool si);

	char* getTipoVotacion();
	Opcion* getOpcion(int i);
	int  getId();
	char* getGanador();
	char* getNombreVotacion();
	int getnParticipantes();
	int getFecha_inicio();
	int getFecha_fin();
	Opcion** getOpciones();
	bool getVotAbierta();

	virtual void votar();
	virtual int terminarVot();
	void imprimirVotacion();
};

#endif /* VOTACION___H_ */
