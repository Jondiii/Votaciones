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

//void vaciador(int cantidadOpciones, int *resultados){
//    for (int x = 0; x < cantidadOpciones; ++x) {
//        resultados[x] = 0;
//    }
//}
//
//int SegundaInstantanea(vAlternativo *va[], int cantidadDeVotos, int cantidadOpciones){
//	int resultados[cantidadOpciones];
//
//	int eliminados[cantidadOpciones];
//	vaciador(cantidadOpciones, eliminados);
//	cout <<"votos"<<cantidadDeVotos << endl;
//	cout <<"opciones"<<cantidadOpciones << endl;
//	cout <<"--"<<eliminados[2] << endl;
//
//
//	//array temporal
//	int resultadosTemp[cantidadOpciones];
//
//	//array con todos los votos
//	vAlternativo *votos[cantidadDeVotos];
//	for (int i = 0; i < cantidadDeVotos; ++i) {
//		votos[i] = va[i];
//
//		cout <<"holaaa?????" << va[i]->getIdOpciones()[0] <<endl;
//	}
//
//
//	int votosNecesarios;
//
//	votosNecesarios = ((cantidadDeVotos/2) + 1)	; //<---------------------------------------[][][]][]
//		fflush(stdout);
//		printf("Votosnecesarios = %i\n", votosNecesarios);
//
//	int numVotTemp;
//	int numResTemp;
//	int Elimin;
//	int SWeliminado;
//	int ganador;
//	int paso = 0;
//	int hayGanador = 0;
//	int noResultado = 0;
//	int contador = 0;
//
//	while(hayGanador == 0 && noResultado == 0 && contador < cantidadOpciones ){
//		contador = contador + 1;
////		cout << contador<< "VS"<<cantidadOpciones<<endl;
////		cout << "000000000000000000000000000000000000000000000000000000000000000000000000000" <<endl;
//
//		//meto cuanto votos tiene cada partido
//		vaciador(cantidadOpciones, resultados);
//		//		printf("cantidad de votos ANTES = %i\n ", cantidadDeVotos);
//		//		fflush(stdout);
//		//		printf("1-%i\n",votos[0].idOpciones[0]);
//		//		fflush(stdout);
//		//		printf("2-%i\n",votos[1].idOpciones[0]);
//		//		fflush(stdout);
//		//		printf("3-%i\n",votos[2].idOpciones[0]);
//		//		fflush(stdout);
//		//		printf("4-%i\n",votos[3].idOpciones[0]);
//		//		fflush(stdout);
//		//		printf("5-%i\n",votos[4].idOpciones[0]);
//		//		fflush(stdout);
//
////		cout << votos[0]->getIdOpciones()[0] <<endl;
////		cout << votos[1]->getIdOpciones()[0] <<endl;
////		cout << votos[2]->getIdOpciones()[0] <<endl;
////		cout << votos[3]->getIdOpciones()[0] <<endl;
////		cout<<"1 For"<< endl;
//		for (int i = 0;   i < cantidadDeVotos; ++i) {
////			fflush(stdout);
////			printf("\n entro 333333333333333333333333333333333    POR %i\n", i);
//
//																											//printf("el votante numero %i vota a opcion numero %i\n",i , votos[i].idOpciones[0]);
////			cout << "\n el votante numero "<< i<<" vota a opcion numero " << votos[i]->getIdOpciones()[0] << ":" << endl;
////			fflush(stdout);
//			//guardo los votos del votante i en los resultados temporales
//																											//resultadosTemp = votos[i].idOpciones;
//			//Guardo en numVotTemp que partido ha puesto en el la opcíon en la que esté mirando
//			numVotTemp = votos[i]->getIdOpciones()[0];
//			//Saco la cantidad de votos que tiene la opcion selecionada por el votante
//			numResTemp = resultados[numVotTemp - 1];
//			//Le sumo 1 a la opción del votante
//																											//printf("antes de sumar %i\n", numResTemp);
//																											//fflush(stdout);
//			numResTemp = numResTemp + 1;
//			//printf("para opcion %i + 1 = %i\n", numVotTemp, numResTemp);
//			//fflush(stdout);
//			//Guardo el nuevo numero en la lista de resultado
//			resultados[numVotTemp - 1] = numResTemp;
////			cout <<numResTemp<<endl;
////			cout <<"terminooooooooooooooooo"<<endl;
//		}
//
//		for (int x = 0; x < cantidadOpciones; ++x) {
////			cout <<"Partido "<< x <<":"<<resultados[x] << endl ;
//		}
//
//		cout<<"2 For"<< endl;
//		for (int j = 0; j < cantidadOpciones; ++j) {
//
////			cout <<"4444444444444444444444444444444"<<endl;
////			cout <<"P"<< j <<":"<<resultados[j] << endl ;
////			fflush(stdout);
//			numVotTemp = resultados[j];
////			cout <<numVotTemp<<">="<< votosNecesarios <<endl<< endl;
//			if (numVotTemp >= votosNecesarios){
//				ganador = j;
//				hayGanador = 1;
////				printf("HAY GANADOR Y ES %i \n ",ganador);
//
//				return ganador + 1;
//
//			}
//		}
//		if (hayGanador == 0) {
////			printf("\n\n entro 5555555555555555555555555555555555555 \n");
//			//			fflush(stdout);
//			numVotTemp = resultados[0];
//			Elimin = 0;
//
////			cout<< "eliminadosv" << contador<<": " <<eliminados[0] <<eliminados[1] <<eliminados[2] <<eliminados[3] <<endl;
////			cout<< "vualta" << contador<<": " <<resultados[0] <<resultados[1] <<resultados[2] <<resultados[3] <<endl;
//			for (int k = 1; k < cantidadOpciones; ++k) {
//
////
////				cout<< k <<endl;
////				cout<< (votos[k]->getIdOpciones()[0])<<"***************************************************"<<endl;
////				cout<< (eliminados[votos[k]->getIdOpciones()[0]- 1])<<"***************************************************"<<endl;
////				cout<<numVotTemp<< ">" << k << ":" << resultados[k] <<endl<< " && "<< eliminados[(votos[k]->getIdOpciones()[0]) - 1] <<endl<<endl;
////				while(eliminados[Elimin] == 1){
////					Elimin = Elimin + 1;
////					numVotTemp = resultados[Elimin];
////					cout <<"EL NUCE=" << Elimin <<endl;
////				}
//				 if(eliminados[k] == 1 ){
//
////					 cout <<k<<"YA ESTA ELIMINADO"<<endl;
//				 }else{
////					 cout <<k<<"*NO* ESTA ELIMINADO"<<endl;
//					 if (numVotTemp > resultados[k] || eliminados[Elimin] ==1){
//
//						 //cout << "numVotTemp" << Elimin << "(" << numVotTemp << ") >" << "resultados" << k << "(" << resultados[k] << ")" <<endl <<endl;
//						 //					printf("numVotTemp%i(%i) > resultados%i(%i)\n",Elimin, numVotTemp,k,resultados[k]);
//						 fflush(stdout);
////						 cout << "numVotTemp ANTES:"<<numVotTemp<<endl;
//						 numVotTemp = resultados[k];
////						 cout << "numVotTemp DESP:"<<numVotTemp<<endl<<endl;
////						 cout << "Elimin ANTES:"<<Elimin<<endl;
//						 Elimin = k;
////						 cout << " DESP:"<<Elimin<<endl<<endl;
////						 cout<<"*////////////////////////////////////////////////////////////////////////////////////////////////////////"<<endl;
//
//						 //					printf("elim = %i",Elimin);
//						 //					fflush(stdout);
//					 }
//
//				 }
//
//
//
//			}
//
//			//1 significa eliminado
////			cout<<"Se elimina opción:"<< Elimin << endl;
//			eliminados[Elimin] = 1;
//
////			cout<<"3 For"<< endl;
//
//			for (int q = 0;  q < cantidadDeVotos; ++ q) {
////				cout<<"primera opcion votante"<< q <<":"<< (votos[q]->getIdOpciones()[0]) << endl<< endl;
//			}
////			cout<<"POSICIOOOOON"<< endl;
//			for (int q = 0;  q < cantidadDeVotos; ++ q) {
//
////				cout<<"posicion"<< q <<":"<< eliminados[q] << endl;
//			}
//
//
//
//			for (int l = 0; l < cantidadDeVotos; ++l) {
//				//while(Eliminado == 0){
////				cout<<"IIIIIIIIIIIIIIIIINNN3 For"<< endl;
//				SWeliminado = 1;
//				while  (SWeliminado == 1){
////					cout<< endl <<"MIRANDO DENTROOOOOOOOOO:" << endl;
////					cout<<"MIRANDO POSICION:"<< (votos[l]->getIdOpciones()[0] - 1) << endl;
////					cout<<"DENTRO:"<< (eliminados[(votos[l]->getIdOpciones()[0]) - 1])<< endl;
//
//					if (eliminados[(votos[l]->getIdOpciones()[0]) - 1] == 1) {
//						SWeliminado = 1;
//						// mover 1
//						for (int n = 1; n < cantidadOpciones; ++n) {
////							printf("\n entro666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666\n");
//							//							fflush(stdout);
//							//							printf("%i <-- %i\n",votos[l].idOpciones[n - 1], votos[l].idOpciones[n]);
//							//							fflush(stdout);
//							votos[l]->getIdOpciones()[n - 1] = votos[l]->getIdOpciones()[n];
//						}
//					}else{
//						SWeliminado = 0;
//					}
//					//					getchar();
//				}
//			}
//		}
//	}
////	cout <<"EMPAAAAAAAAATE"<<endl;
//	return -1;
//}
//
int firstPassThePost2(Opcion Opciones[], int cantidadOpciones){
    Opcion opcionGuar = Opciones[0];
    int cantGuar; //= punteroOpciones->getVotos();
    int empate = 0;

    for (int i = 1;  i < cantidadOpciones ; ++ i) {
        Opcion opcionCar = Opciones[i];
        if (opcionGuar.getVotos() < opcionCar.getVotos()) {
            cantGuar = opcionCar.getVotos();
            opcionGuar = opcionCar;
            empate = 0;
        }else if(cantGuar == opcionCar.getVotos()){
            empate = 1;
        }
    }
    if (empate == 1) {
        return 0;
    }

    return opcionGuar.getId();
}

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
			cout << "Ha habido un problema al crear la BD" << endl; return;
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

static int cuentaVotacionesBD(void *unused, int nCols, char **data, char **colName)
{
	nVotaciones++;
	return 0;
}

static int cuentaCandidatosBD(void *unused, int nCols, char **data, char **colName)
{
	nCandidatos++;
	return 0;
}

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
	if (strcmp("N", data[5]) == 0)
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

void recuento() {
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
     cout << nombres[i] << endl;

     int o = 0;
     Opcion *listaOpcion = new Opcion[numCand];
     while (o < numCand){
         cout << "¿Cuántos votos ha obtenido " << nombres[o] << "?" << endl;
         int voto = 0;
         cin >> voto;
         int n = nombres[o].length();
         char charNombres[n + 1];
         strcpy(charNombres, nombres[o].c_str());
         Opcion option(o + 1, voto, charNombres);
         listaOpcion[o] = option;
         //option.imprimirOpcion();
          o++;
     }

     o = 0;
     int votos_totales = 0;

     while (o < numCand){
         votos_totales += listaOpcion[o].getVotos();
         o++;
     }
    int ganador = firstPassThePost2(listaOpcion, numCand);
    if (ganador == 0){
            cout << "Ha habido un empate" << endl;
        }
        else{
            cout << listaOpcion[ganador - 1].getNombre() << " es el ganador con el id: " << listaOpcion[ganador - 1].getId() << endl;
        }

    delete[] nombres;
    delete[] listaOpcion;
}

bool comprobarFecha(/*char*/ string stringf)
{
	// int f_size = sizeof(f) / sizeof(char);
	// string stringf = convertToString(f, f_size);

	if(stringf.length() != 10)
	{
		// cout<<"mec"<<endl;
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
    cout << "¿Que quieres hacer? \n" << endl;

    cout << "1. Cerrar Votacion"  << endl;
    cout << "2. Consultar Votacion" << endl;
    int numero;
    cin>> numero;

    switch (numero) {
    case 1:
        for (int i = 0; i < nVotaciones; i++){
            cout << i + 1 <<". ";
            listadoVotaciones[i]->imprimirVotacion();
        }
        cout << "¿Que votacion desea cerrar? \n" << endl;
        cin >> numero;
        numero -=1;
        cout << listadoVotaciones[numero]->terminarVot() << endl;
        break;


    case 2:
        for (int i = 0; i<nVotaciones; i++){
            cout << i + 1 <<". ";
            listadoVotaciones[i]->imprimirVotacion();
        }
        cout << "¿Que votacion desea ver? \n" << endl;
        cin >> numero;
        numero -=1;
        cout << "CANDIDATOS:" << endl;
        for (int i = 0; i<listadoVotaciones[numero]->getnParticipantes(); i++)
        {
            cout << i + 1 <<". ";
            listadoVotaciones[numero]->getOpcion(i)->imprimirOpcion();
        }
        break;

    default:
        cout <<"Introduzca una opción dentro del rango"<< endl;

    }
}

void creaVotacion(Votacion *v)
{
	bool finNuevaVotacion = false;
	char name[50];
	int nCandidatos;
	Opcion **opciones;

	bool bNombre = false;
	bool bCandidatos = false;
	bool bPeriodo = false;

	string fIni;
	string fFin;

			while(!finNuevaVotacion)
			{
				cout << "1. Nombre\n2. Candidatos\n3. Periodo\n4. Aceptar\n" << endl;
				int key2;
				cin >> key2;
				if(!comprobarNumero(key2, 5)) break;
				switch(key2)
				{
				case 1:
					cout << "Introduce el nombre: ";
					cin >> name;
					cout << "\nNombre: " << name << endl;
					strtok(name, "\n");
					v->setNombreVotacion(name);
					bNombre = true;
					break;

				case 2:
					cout << "Introduce el número de candidatos: " <<endl;
					cin >> nCandidatos;
					v->setNParticipantes(nCandidatos);
					//IMPORTANTE: AL DECLARAR ESTO SE ESTÁN HACIENDO TANTAS OPCIONES CON EL CONSTRUCTOR
					//VACÍO COMO nCandidatos. No hay que volver a crearlas luego.
					opciones = new Opcion*[nCandidatos];

					int i;

					for (i = 0; i < nCandidatos; i++) {
						char nomCandidato[20];
						cout << "\nIntroduce el Nombre del candidato " << i+1 << ":" << endl;
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
//						int nIni = fIni.length();
//						char charFIni[nIni + 1];
//						strcpy(charFIni, fIni.c_str());
//						int nFin = fFin.length();
//						char charFFin[nFin + 1];
//						strcpy(charFFin, fFin.c_str());

						cout << "Las fechas se han introducido correctamente." << endl;
						v->setFecha_inicio(convierteFecha(fIni));
						v->setFecha_fin(convierteFecha(fFin));
						cout << "fIni: " << fIni << endl;
						cout << "fFin: " << fFin << endl;
						bPeriodo = true;
					} else
					{
						cout << "Alguna fecha no ha sido introducida correctamente." << endl;
						bPeriodo = false;
					}

					break;

				case 4:
					if(bNombre && bCandidatos && bPeriodo)
					{
						finNuevaVotacion = true;
						//v->imprimirVotacion();

						ostringstream insertVotaciones;//(ID_V, NOMBRE, GANADOR, F_INI, F_FIN, TIPO_VOTACION, VOT_ABIERTA)
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
//						(*VotacionAlter)
						//v->imprimirVotacion();
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

				default:
					fflush(stdout);
					printf("Error, introduce una opción válida.\n");
					finNuevaVotacion = true;

					break;
				}
			}
}

void guardarEnBD()
{
	for (int i = 0; i < nVotaciones; ++i)
	{
		ostringstream updateGanador;
		updateGanador << "UPDATE votacion SET GANADOR = " << listadoVotaciones[i]->getGanador();
		updateGanador << " WHERE ID = " << listadoVotaciones[i]->getId() << ";";
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

    //listadoVotaciones[nVotaciones - 1].imprimirVotacion();
    cout << "Elegir votación: (Introduce el numero de la votacion en la que desee participar)" << endl;

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
        cout << "Ya has votado en esta VOTACION."<<endl;
        return;
    }

    listadoVotaciones[votacion_elegida]->votar();
    p1.insertarPersonaDB(listadoVotaciones[votacion_elegida]->getId());
}

void menu()
{
//	Votacion *v = new Votacion[2];
//	int id = 1;
//
//	char *ganador = "Juan";
//	char *nombre_vot = "HOLA_SOY UNA VOTACIONALTER";
//	char *ganador_2 = "MARTA";
//	char *nombre_vot_2 = "HOLA_SOY UNA VOTACION";
//	char *tipo ="A";
//	char *tipo_2 = "N";
//	int fecha_ini = 0; sadvdsfsdvsdasdvsvsdvcsdv
//	int fecha_fin = 0;
//	int nParticipantes = 3;
//	char * nombre1 = "Pepe";
//	char *nombre2 = "Juan";
//	char *nombre3 = "Teresa";
//
//	Opcion o(1, 0, nombre1);
//	Opcion o1(2, 0, nombre2);
//	Opcion o2(3, 9, nombre3);
//
//	Opcion *lista_o[] = {&o, &o1, &o2};
//
//	int num_VA = 2;
//	int *idOpciones = new int[3];
//	idOpciones[0] = 1;
//	idOpciones[1] = 3;
//	idOpciones[2] = 2;
//	vAlternativo v1(idOpciones, 0, 3);
//
//	int *idOpciones1 = new int[3];
//	idOpciones1[0] = 1;
//	idOpciones1[1] = 2;
//	idOpciones1[2] = 3;
//	vAlternativo v2(idOpciones1, 0, 3);
//
//	vAlternativo *va[] = {&v1, &v2};
//
//
//	VotacionAlter vo1(id, fecha_ini, fecha_fin, tipo, ganador, nombre_vot, nParticipantes, lista_o, num_VA, va );
//	Votacion vot1(2, fecha_ini, fecha_fin, tipo_2, ganador_2, nombre_vot_2, nParticipantes, lista_o);
//	v[0] = vo1;
//	v[1] = vot1;



//	VotacionAlter* vAlt = new VotacionAlter();
//	vAlt->setNombreVotacion(name);
//	vAlt->setFecha_fin(con)
	int tipoVot = 0;
	bool finPrograma = false;
	while(!finPrograma)
		{
			cout << "1. Crear Votación\n2. Votar\n3. Recuento\n4. Historial\n5. Acabar y guardar" << endl;
			int key = 0;
			cin >> key;
			if(!comprobarNumero(key, 5)) return;
			//cout << "Has metido: " << key << endl;
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
//				VotacionAlter* l = dynamic_cast<VotacionAlter*> (&listadoVotaciones[nVotaciones]);
				//(*VotacionAlter)(listadoVotaciones[nVotaciones].imprimirVotacion();
				break;

			case 2:
				votar();
				break;

			case 3:
				recuento();
				break;

			case 4: //Aquí mostrar la actual (WIP) (Esto será el historial)
				historial();
				break;

			case 5:
				//guardarEnBD();
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
	cout << "Error al abrir la Base de Datos\n" << endl;
	return(0);
	} else {
	cout << "Base de datos abierta correctamente\n" << endl;
	}

	//Cuenta cuántas votaciones hay en la BD.
	sqlite3_exec(db, "SELECT * FROM VOTACION;", cuentaVotacionesBD, 0, NULL);
	listadoVotaciones = new Votacion*[nVotaciones];

	cout << "nVotaciones: " << nVotaciones << endl;
	sqlite3_exec(db, "SELECT * FROM VOTACION;", creaVotacionesBD, 0, NULL);

	contador = 0;
	//sqlite3_exec(db, "SELECT * FROM CANDIDATO WHERE ID_VOT = 0", cuentaCandidatosBD, 0, NULL);
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
	cout << "candidatosTotales: " << candidatosTotales << endl;

	creaBD();
	menu();

	sqlite3_close(db);
}

