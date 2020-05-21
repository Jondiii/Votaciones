/*
 * main.cpp
 *
 *  Created on: 11 may. 2020
 *      Author: Jon
 */


extern "C" {
	#include "sqlite3.h"
}

#include "opcion.h"
#include "persona.h"
#include "vAlternativo.h"
#include "votacion.h"
#include "VotacionAlter.h"

#include <typeinfo>
#include <unistd.h>
#include <sstream>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

static sqlite3 *db;

int nVotaciones = 0;
int nCandidatos = 0;
int candidatosTotales = 0;
int contador = 0;

Votacion** listadoVotaciones;

void anyadirVotacion(Votacion *vot)
{
    nVotaciones ++;
    Votacion **vota = new Votacion*[nVotaciones];
    for(int i = 0; i <nVotaciones-1; i++)
    {
        vota[i] = listadoVotaciones[i];
      //vota[i].imprimirVotacion();
    }
    vota[nVotaciones - 1] = vot;
//  vota[nVotaciones].imprimirVotacion();
    listadoVotaciones = vota;

//    for(int i = 0; i <nVotaciones; i++)
//    {
////    	fflush(stdout);
//        listadoVotaciones[i] = vota[i];
////      listadoVotaciones[i].imprimirVotacion();
//    }
}

void creaBD()
{
	char *error;
	if (sqlite3_open("votaciones.sql", &db))
		{
			cout << "Ha habido un problema al crear la BD." << endl; return;
		}
	else
	{//callback: https://stackoverflow.com/questions/31146713/sqlite3-exec-callback-function-clarification/31168999
		char* sentencia;

		sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS VOTACION("
			      "ID_V INT PRIMARY KEY NOT NULL,"
			      "NOMBRE TEXT,"
			      "GANADOR CHAR(30),"
			      "F_INI INT,"
			      "F_FIN INT,"
			      "TIPO_VOTACION CHAR(20),"
				  "VOT_ABIERTA INT DEFAULT 1,"
			      "CHECK (F_INI<F_FIN)"
			      ");", NULL, 0, &error);

		sentencia = "CREATE TABLE IF NOT EXISTS CANDIDATO("
				      "ID_C INT PRIMARY KEY NOT NULL,"
				      "NOMBRE CHAR(30),"
					  "VOTOS INT DEFAULT 0,"
					  "ID_VOT INT,"
				  	  "FOREIGN KEY (ID_VOT) REFERENCES VOTACION(ID_V)"
				      ");";

		sqlite3_exec(db, sentencia, NULL, 0, &error);

		sentencia = "CREATE TABLE IF NOT EXISTS PERSONA("
				      "ID_P INT PRIMARY KEY NOT NULL,"//Este sería el DNI de la persona.
				      "EDAD INT,"
				      "CP CHAR(6),"
				      "CHECK (EDAD>0),"
				      "CHECK (EDAD<120)"
				      ");";

		sqlite3_exec(db, sentencia, NULL, 0, &error);

		sentencia = "CREATE TABLE IF NOT EXISTS VOTOS("//Interesa saber si una persona ha votado en una votación concreta.
				      "ID_V INT NOT NULL,"
				      "ID_P INT NOT NULL,"
				      "FOREIGN KEY (ID_V) REFERENCES VOTACION(ID_V),"
					  "FOREIGN KEY (ID_P) REFERENCES PERSONA(ID_P)"
				      ");";

		sqlite3_exec(db, sentencia, NULL, 0, &error);
	}
}

/*
 * Cuenta el número de votaciones que hay en la BD.
 */
static int cuentaVotacionesBD(void *unused, int nCols, char **data, char **colName)
{
	nVotaciones++;
	return 0;
}

/*
 * Cuenta los candidatos de una única votación.
 */
static int cuentaCandidatosBD(void *unused, int nCols, char **data, char **colName)
{
	nCandidatos++;
	return 0;
}

/*
 * Se añaden a la votación correspondiente los candidatos.
 */
static int anyadeCandidatosBD(void *unused, int nCols, char **data, char **colName)
{
	Opcion* op = new Opcion();
	op->setId(nCandidatos);
	op->setNombre(data[1]);
	op->setVotos(std::stoi(data[2]));
	listadoVotaciones[contador]->getOpciones()[nCandidatos] = op;

	nCandidatos++;

	return 0;
}

/*
 * Arguments:
 *
 *   	unused - unused, see the documentation for sqlite3_exec
 *   	nCols - The number of columns in the result set
 *    	data - The row's data
 *  	colName - The column names
 */
static int creaVotacionesBD(void *unused, int nCols, char **data, char **colName)
{
	if (strcmp("N", data[5]) == 0)//Comprueba si es una votación Normal o una Alternativa
	{
		Votacion *vot = new Votacion();
		vot->setId(std::stoi(data[0]));
		vot->setNombreVotacion(data[1]);
		vot->setGanador(data[2]);
		vot->setFecha_inicio(std::stoi(data[3]));
		vot->setFecha_fin(std::stoi(data[4]));
		vot->setTipoVotacion(data[5]);
		listadoVotaciones[contador] = vot;
	} else
	{
		VotacionAlter *vot = new VotacionAlter();
		vot->setId(std::stoi(data[0]));
		vot->setNombreVotacion(data[1]);
		vot->setGanador(data[2]);
		vot->setFecha_inicio(std::stoi(data[3]));
		vot->setFecha_fin(std::stoi(data[4]));
		vot->setTipoVotacion(data[5]);
		listadoVotaciones[contador] = vot;
	}

	contador++;
	return 0;
}

bool comprobarNumero(int num, int max)
{
	if (num <= max)
	{
		return true;
	}
	cout << "\nEl número introducido tiene que ser menor o igual que " << max <<".\n" << endl;
	return false;
}

void recuento()
{
    string candidatos;
    cout << "Deberás poner a continuación todos los participantes de esta votación, separados por comas y un espacio: ";
    fflush(stdin);
    getline (cin, candidatos);
    string candidatosCopia = candidatos;
    string delimiter = ", ";
    size_t pos = 0;
    int numCand = 0;
    while ((pos = candidatosCopia.find(delimiter)) != string::npos) {
        candidatosCopia.erase(0, pos + delimiter.length());
        numCand++;
    }

    numCand++;
    string token;
    string* nombres = new string[numCand];
    int i = 0;
    while ((pos = candidatos.find(delimiter)) != string::npos) {
        token = candidatos.substr(0, pos);
        nombres[i] = token;
        candidatos.erase(0, pos + delimiter.length());
        i++;
    }
     token = candidatos.substr(0, pos);
     nombres[i] = token;

     int metodo;
     cout<< "Elije qué método de votación quieres usar:\n1.FPP\n2.Segunda Instantanea" << endl;
     cin >> metodo;
     if(metodo == 1){
		 int o = 0;
		 Opcion **listaOpcion = new Opcion*[numCand];
		 while (o < numCand){
			 cout << "¿Cuántos votos ha obtenido " << nombres[o] << "?" << endl;
			 int voto = 0;
			 cin >> voto;

			 Opcion* option = new Opcion(o + 1, voto, nombres[o].c_str());
			 listaOpcion[o] = option;
			 option->imprimirOpcion();
			 o++;
		 }

		Votacion* vot = new Votacion();
		vot->setId(nVotaciones);
		vot->setFecha_inicio(0);
		vot->setFecha_fin(0);
		vot->setTipoVotacion("N");
		vot->setNombreVotacion("Recuento Manual");
		vot->setNParticipantes(numCand);
		vot->setParticipantes(listaOpcion);

		int idGanador = vot->terminarVot();

		for (int i = 0; i < vot->getnParticipantes(); ++i)
		{
			vot->getOpcion(i)->imprimirOpcion();
		}

		if(idGanador == 0)
		{
			cout << "Ha habido un empate." << endl;
		} else
		{
			cout << "El ganador es: " << vot->getGanador() << ".\n" << endl;
		}

    }
     if (metodo == 2)
     {
		 string orden;
		 vAlternativo** listaVotos = new vAlternativo*[numCand];
		 int x = 0;
		 int* listaOrden = new int[numCand];
		 int numPers;
		 int ord;
		 cout << "¿Cuántas personas votarán?" << endl;
		 cin >> numPers;
		 for(int i = 0; i < numPers; i++)
		 {
			 ord = 0;
			 cout << "Persona nº "<< i + 1 << ", di los "<< numCand << " candidatos en el orden que quieras, separado por comas y un espacio, usando sus IDs." << endl;
			 for (int o = 0; o < numCand; o++){
				 cout << nombres[o] << " tiene el ID " << o + 1 << "." << endl;
			 }
			 fflush(stdin);
			 getline (cin, orden);

			 pos = 0;
			 while ((pos = orden.find(delimiter)) != string::npos)
			 {
				 token = orden.substr(0, pos);
				 stringstream geek(token);
				 x = 0;
				 geek >> x;
				 listaOrden[ord] = x;
				 orden.erase(0, pos + delimiter.length());
				 ord++;
				 }
			 stringstream geek(orden);
			 geek >> x;
			 listaOrden[ord] = x;

			 vAlternativo *voto = new vAlternativo(listaOrden, 0, numCand);
			 listaVotos[i] = voto;

		 }
		 for (i = 0; i < numPers ; i++ ){
			 listaVotos[i]->imprimirValternativo(numCand);
		 }
		 Opcion** listaOp = new Opcion*[numCand];
		 VotacionAlter* votAlt = new VotacionAlter();
		 votAlt->setNParticipantes(numCand);
		 votAlt->setParticipantes(listaOp);
		 votAlt->setNumVotantes(numPers);
		 votAlt->setAlternativos(listaVotos);

		int idGanador = votAlt->terminarVot();


		if(idGanador == -1)
		{
			cout << "Ha habido un empate." << endl;
		} else
		{
			cout << "Ha ganado: " << nombres[idGanador - 1 ] << ", con ID: " << idGanador << "." << endl;
			votAlt->setGanador(nombres[idGanador - 1].c_str());
		}


     } if (metodo != 1 && metodo != 2) {
    	 cout <<"No se ha dado un método valido." << endl;
     }
}

bool comprobarFecha(/*char*/ string stringf)
{
	if(stringf.length() != 10)
	{
		return false;
	}

	string copiaF = stringf;

	string delimiter = "/";
	string token;
	size_t pos = 0;
	int *fechas = new int[3];
	int i = 0;
	int x = 0;
	while ((pos = copiaF.find(delimiter)) != string::npos)
	{
		token = copiaF.substr(0, pos);
		copiaF.erase(0, pos + delimiter.length());
		stringstream geek(token);
		x = 0;
		geek >> x;
		fechas[i] = x;
		i++;
	}
	stringstream geek(copiaF);
	x = 0;
	geek >> x;
	fechas[i] = x;

	if(fechas[0] <= 1800 || fechas[0] > 2100 || fechas[1] > 12 || fechas[1] < 1 || fechas[2] > 31 || fechas[2] < 1)
		{
			delete[] fechas;
			return false;
		}

	delete[] fechas;
	return true;
}

int convierteFecha(string fecha){
    string nuevaFech;
    string delimiter = "/";
    string token;
    size_t pos = 0;
    while ((pos = fecha.find(delimiter)) != string::npos) {
        token = fecha.substr(0, pos);
        fecha.erase(0, pos + delimiter.length());
        nuevaFech.append(token);
    }
    nuevaFech.append(fecha);
    stringstream geek(nuevaFech);
    int x = 0;
    geek >> x;
    return x;
}

void historial()
{
    cout << "¿Qué quieres hacer? \n" << endl;

    cout << "1. Cerrar Votación"  << endl;
    cout << "2. Consultar Votación" << endl;
    int numero;
    cin>> numero;
	if(!comprobarNumero(numero, 2)) return;
	int idGanador;
	 ostringstream cerrarVot;
    switch (numero) {
    case 1:
        for (int i = 0; i < nVotaciones; i++)
        {
            cout << i + 1 <<". ";
            listadoVotaciones[i]->imprimirVotacion();
        }
        cout << "¿Qué votacion deseas cerrar? \n" << endl;
        cin >> numero;
        numero -=1;
        idGanador = listadoVotaciones[numero]->terminarVot();
        listadoVotaciones[numero]->setGanador(listadoVotaciones[numero]->getOpcion(idGanador)->getNombre());
        cout << "Ha ganado: " << listadoVotaciones[numero]->getGanador() << "." << endl;

        cerrarVot << "UPDATE votacion SET VOT_ABIERTA = 0 WHERE ID_V = " << numero << ";";
        sqlite3_exec(db, cerrarVot.str().c_str(), NULL, 0, NULL);

        break;


    case 2:
        for (int i = 0; i<nVotaciones; i++){
            cout << i + 1 <<". ";
            listadoVotaciones[i]->imprimirVotacion();
        }
        cout << "¿Qué votación deseas ver? \n" << endl;
        cin >> numero;
        numero -=1;
        cout << "CANDIDATOS:" << endl;
        for (int i = 0; i<listadoVotaciones[numero]->getnParticipantes(); i++)
        {
            cout << i + 1 <<". ";
            listadoVotaciones[numero]->getOpcion(i)->imprimirOpcion();
        }

  	  int fin;
  	  cout << "Escribe algo y pulsa intro cuando hayas acabado de consultar las votaciones." << endl;
  	  cin >> fin;
  	  cout << "\n";

        break;
    default:
        cout <<"Introduce una opción dentro del rango."<< endl;
    }

}

void creaVotacion(Votacion *v)
{
	bool finNuevaVotacion = false;
	char name[50];
	int nCandidatos;
	Opcion **opciones;

	bool bNombre = false;//Estos se usarán para saber que se han introducido los datos necesarios.
	bool bCandidatos = false;
	bool bPeriodo = false;

	string fIni;
	string fFin;

			while(!finNuevaVotacion)
			{
				cout << "1. Nombre\n2. Candidatos\n3. Periodo\n4. Aceptar\n" << endl;
				int key2;
				cin >> key2;
				if(!comprobarNumero(key2, 4))
					{
						cout << "\n";
						break;
					}
				switch(key2)
				{
				case 1:
					cout << "Introduce el nombre: ";
					cin >> name;
					cout << "\nNombre: " << name << "." << endl;
					strtok(name, "\n");
					v->setNombreVotacion(name);
					bNombre = true;
					break;

				case 2:
					cout << "Introduce el número de candidatos: " <<endl;
					cin >> nCandidatos;
					v->setNParticipantes(nCandidatos);
					opciones = new Opcion*[nCandidatos];

					for (int i = 0; i < nCandidatos; i++)
					{
						char nomCandidato[20];
						cout << "\nIntroduce el nombre del candidato " << i+1 << ":" << endl;
						cin >> nomCandidato;
						Opcion* op = new Opcion(i+1, 0, nomCandidato);
						opciones[i] = op;

						opciones[i]->imprimirOpcion();
					}

					v->setParticipantes(opciones);

					bCandidatos = true;
					break;

				case 3:
					cout << "Introduce la fecha de inicio en el formato AAAA/MM/DD: ";
					fflush(stdin);
					getline(cin, fIni);

					cout << "Introduce la fecha de fin en el formato AAAA/MM/DD: ";
					fflush(stdin);
					getline(cin, fFin);

					if (comprobarFecha(fIni) && comprobarFecha(fFin))
					{
						cout << "Las fechas se han introducido correctamente." << endl;
						v->setFecha_inicio(convierteFecha(fIni));
						v->setFecha_fin(convierteFecha(fFin));
						cout << "fIni: " << fIni << endl;
						cout << "fFin: " << fFin << endl;
						bPeriodo = true;
					} else
					{
						cout << "Alguna fecha no ha sido introducida correctamente." << endl;
					}

					break;

				case 4:
					if(bNombre && bCandidatos && bPeriodo)
					{
						finNuevaVotacion = true;

						ostringstream insertVotaciones;
						insertVotaciones << "INSERT INTO votacion VALUES (";
						insertVotaciones << v->getId() << ", '" << v->getNombreVotacion() << "', '";
						insertVotaciones << v->getGanador() << "', '" << v->getFecha_inicio() << "', '";
						insertVotaciones << v->getFecha_fin() << "', '" << v->getTipoVotacion() << "', ";
						insertVotaciones << 1 << ");";
						sqlite3_exec(db, insertVotaciones.str().c_str(), NULL, 0, NULL);

						for (int i = 0; i < v->getnParticipantes(); ++i)
						{
							ostringstream insertCandidatos;
							insertCandidatos << "INSERT INTO candidato VALUES (";
							insertCandidatos << candidatosTotales << ", '";
							insertCandidatos << v->getOpcion(i)->getNombre() << "', ";
							insertCandidatos << v->getOpcion(i)->getVotos() << ", " << v->getId() << ");";
							sqlite3_exec(db, insertCandidatos.str().c_str(), NULL, 0, NULL);
							candidatosTotales++;
						}

						anyadirVotacion(v);

						cout << "Votación creada correctamente.\n" << endl;
						fflush(stdout);

					} else {
						cout << "Aún falta: ";
						if(bNombre == false)
						{
							cout << "nombre, ";
						}
						if(bCandidatos == false)
						{
							cout << "los candidatos,  ";
						}
						if(bPeriodo == false)
						{
							cout << "el periodo.";
						}
						cout << endl;
					}
					break;
				}
			}
}

/*
 * Actualiza los ganadores de las votaciones que hay en la BD.
 */
void guardarEnBD()
{
	for (int i = 0; i < nVotaciones; ++i)
	{
		ostringstream updateGanador;
		updateGanador << "UPDATE votacion SET GANADOR = '" << listadoVotaciones[i]->getGanador();
		updateGanador << "' WHERE ID_V = " << listadoVotaciones[i]->getId() << ";";
		sqlite3_exec(db, updateGanador.str().c_str(), NULL, 0, NULL);
	}
}

void votar()
{
    int dni;
    cout << "Introduce tu identificativo:(dni)" << endl;
    cin >> dni;
    Persona p1(dni);

    int edad;
    cout << "Introduce tu edad:" << endl;
    cin >> edad;
    p1.setEdad(edad);

    int cod;
    cout << "Introduce tu Codigo postal:" << endl;
    cin >> cod;
    p1.setCodigo(cod);

    cout << "Elegir votación: (Introduce el numero de la votación en la que desee participar)" << endl;

    for (int i = 0; i< nVotaciones;i++)
    {
        cout << i + 1 <<". ";
        listadoVotaciones[i]->imprimirVotacion();
    }

    int votacion_elegida;
    cin >> votacion_elegida;
    votacion_elegida -= 1;
    if (!Persona::comprobarDni(p1.getDni(), listadoVotaciones[votacion_elegida]->getId()))
    {
        cout << "Ya has votado en esta votación."<<endl;
        return;
    }

    listadoVotaciones[votacion_elegida]->votar();
    p1.insertarPersonaDB(listadoVotaciones[votacion_elegida]->getId());
}

void menu()
{
	int tipoVot = 0;
	bool finPrograma = false;
	while(!finPrograma)
		{
			cout << "1. Crear Votación\n2. Votar\n3. Recuento\n4. Historial/Cerrar Votación\n5. Acabar y guardar" << endl;
			int key = 0;
			cin >> key;

			if(!comprobarNumero(key, 5)) return;

			cout << endl;
			switch (key)
			{
			case 1:
				cout << "Elige el método de votación:\n1.First Pass The Post\n2. Segunda Instantánea" << endl;
				cin >> tipoVot;

				if(tipoVot == 1)
				{
					Votacion* vot = new Votacion();
					vot->setId(nVotaciones);
					vot->setTipoVotacion("N");
					creaVotacion(vot);

				} else if(tipoVot == 2)
				{
					VotacionAlter* vot = new VotacionAlter();
					vot->setId(nVotaciones);
					vot->setTipoVotacion("A");
					creaVotacion(vot);

				} else {
					cout << "Introduce una opción correcta." << endl;
				}
				break;

			case 2:
				votar();
				break;

			case 3:
				recuento();
				break;

			case 4:
				historial();
				break;

			case 5:
				guardarEnBD();
				finPrograma = true;
				cout << "Fin del programa." << endl;
				break;
			}
		}
	return;
}

int main()
{
	int rc;

	rc = sqlite3_open("votaciones.sql", &db); //Esto antes me chillaba, se ha arreglado tras project->C/C++ index->rebuild.

	if( rc )
	{
	cout << "Error al abrir la Base de Datos.\n" << endl;
	return(0);
	} else {
	cout << "Base de datos abierta correctamente.\n" << endl;
	}

	//Cuenta cuántas votaciones hay en la BD.
	sqlite3_exec(db, "SELECT * FROM VOTACION;", cuentaVotacionesBD, 0, NULL);
	listadoVotaciones = new Votacion*[nVotaciones];

	sqlite3_exec(db, "SELECT * FROM VOTACION;", creaVotacionesBD, 0, NULL);

	contador = 0; 	//Lo ponemos a 0 porque anteriormente se ha estado usando para meter las votaciones en la
					//posición correspondiente. Ahora se usará para meter los candidatos en la votación apropiada.

	for (int i = 0; i < nVotaciones; ++i)
	{
		ostringstream sentencia1;
		sentencia1 << "SELECT * FROM CANDIDATO WHERE ID_VOT = "  << i << ";";
		sqlite3_exec(db, sentencia1.str().c_str(), cuentaCandidatosBD, 0, NULL);

		listadoVotaciones[i]->setNParticipantes(nCandidatos);
		candidatosTotales += nCandidatos;
		nCandidatos = 0;
		sqlite3_exec(db, sentencia1.str().c_str(), anyadeCandidatosBD, 0, NULL);
		contador++;
		nCandidatos = 0;
	}

	creaBD();
	menu();

	sqlite3_close(db);
}

