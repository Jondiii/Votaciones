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
	this->num_VA = num_VA;
	this->alternativos = new vAlternativo*[this->num_VA];
	for (int i = 0; i <this->num_VA;i++)
	{
		this->alternativos[i] = alternativos[i];
	}
}
VotacionAlter::VotacionAlter(const VotacionAlter &va):Votacion(va)
{
	this->num_VA = va.num_VA;
	this->alternativos = new vAlternativo*[this->num_VA];
	for (int i = 0; i <this->num_VA;i++)
	{
		this->alternativos[i] = va.alternativos[i];
	}
}
VotacionAlter::VotacionAlter():Votacion()
{
	this->alternativos = new vAlternativo*[0];
	this->num_VA = 0;
}
VotacionAlter::~VotacionAlter()
{
	delete [] alternativos;
}
int VotacionAlter::getNum_VA()
{
	return this->num_VA;
}
vAlternativo* VotacionAlter::getAlternativo(int i)
{
	return this->alternativos[i];
}
void VotacionAlter::anadirvAlternativo(vAlternativo *alternativo)
{
	int nuevo_Va = this->num_VA + 1;
	vAlternativo **vA = new vAlternativo*[nuevo_Va];
	for (int i = 0 ; i <this->num_VA; i++)
	{
		vA[i] = this->alternativos[i];
	}
	vA[this->num_VA] = alternativo;
	this->num_VA = nuevo_Va;
	this->alternativos = new vAlternativo*[nuevo_Va];
	for (int i = 0 ; i <this->num_VA; i++)
	{
		this->alternativos[i] = vA[i];
	}
}
void VotacionAlter::votar()
{
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
	}
	vAlternativo *v1 = new vAlternativo(votos, 0, this->getnParticipantes());
	this->anadirvAlternativo(v1);
}

void VotacionAlter::vaciador(int cantidadOpciones, int *resultados){

	for (int x = 0; x < cantidadOpciones; ++x) {
		resultados[x] = 0;
	}

}

int VotacionAlter::terminarVot(){
//	int SegundaInstantanea(vAlternativo *va[], int cantidadDeVotos, int cantidadOpciones){
		int resultados[this->nParticipantes];

		int eliminados[this->nParticipantes];
		vaciador(this->nParticipantes, eliminados);
		cout <<"votos"<<this->num_VA << endl;
		cout <<"opciones"<<this->nParticipantes << endl;
		cout <<"--"<<eliminados[2] << endl;


		//array temporal
		int resultadosTemp[this->nParticipantes];

		//array con todos los votos
		vAlternativo * votos[this->num_VA];
		for (int i = 0; i < this->num_VA; ++i) {
			votos[i] = this->alternativos[i];

			cout <<"holaaa?????" << this->alternativos[i]->getIdOpciones()[0] <<endl;
		}


		int votosNecesarios;

		votosNecesarios = ((this->num_VA/2) + 1)	; //<---------------------------------------[][][][]
			fflush(stdout);
			printf("Votosnecesarios = %i\n", votosNecesarios);

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
	//		cout << contador<< "VS"<<this->nParticipantes<<endl;
	//		cout << "000000000000000000000000000000000000000000000000000000000000000000000000000" <<endl;

			//meto cuanto votos tiene cada partido
			vaciador(this->nParticipantes, resultados);
			//		printf("cantidad de votos ANTES = %i\n ", this->num_VA);
			//		fflush(stdout);
			//		printf("1-%i\n",votos[0].idOpciones[0]);
			//		fflush(stdout);
			//		printf("2-%i\n",votos[1].idOpciones[0]);
			//		fflush(stdout);
			//		printf("3-%i\n",votos[2].idOpciones[0]);
			//		fflush(stdout);
			//		printf("4-%i\n",votos[3].idOpciones[0]);
			//		fflush(stdout);
			//		printf("5-%i\n",votos[4].idOpciones[0]);
			//		fflush(stdout);

	//		cout << votos[0]->getIdOpciones()[0] <<endl;
	//		cout << votos[1]->getIdOpciones()[0] <<endl;
	//		cout << votos[2]->getIdOpciones()[0] <<endl;
	//		cout << votos[3]->getIdOpciones()[0] <<endl;
	//		cout<<"1 For"<< endl;
			for (int i = 0;   i < this->num_VA; ++i) {
	//			fflush(stdout);
	//			printf("\n entro 333333333333333333333333333333333    POR %i\n", i);

																												//printf("el votante numero %i vota a opcion numero %i\n",i , votos[i].idOpciones[0]);
	//			cout << "\n el votante numero "<< i<<" vota a opcion numero " << votos[i]->getIdOpciones()[0] << ":" << endl;
	//			fflush(stdout);
				//guardo los votos del votante i en los resultados temporales
																												//resultadosTemp = votos[i].idOpciones;
				//Guardo en numVotTemp que partido ha puesto en el la opcíon en la que esté mirando
				numVotTemp = votos[i]->getIdOpciones()[0];
				//Saco la cantidad de votos que tiene la opcion selecionada por el votante
				numResTemp = resultados[numVotTemp - 1];
				//Le sumo 1 a la opción del votante
																												//printf("antes de sumar %i\n", numResTemp);
																												//fflush(stdout);
				numResTemp = numResTemp + 1;
				//printf("para opcion %i + 1 = %i\n", numVotTemp, numResTemp);
				//fflush(stdout);
				//Guardo el nuevo numero en la lista de resultado
				resultados[numVotTemp - 1] = numResTemp;
	//			cout <<numResTemp<<endl;
	//			cout <<"terminooooooooooooooooo"<<endl;
			}

			for (int x = 0; x < this->nParticipantes; ++x) {
	//			cout <<"Partido "<< x <<":"<<resultados[x] << endl ;
			}

			cout<<"2 For"<< endl;
			for (int j = 0; j < this->nParticipantes; ++j) {

	//			cout <<"4444444444444444444444444444444"<<endl;
	//			cout <<"P"<< j <<":"<<resultados[j] << endl ;
	//			fflush(stdout);
				numVotTemp = resultados[j];
	//			cout <<numVotTemp<<">="<< votosNecesarios <<endl<< endl;
				if (numVotTemp >= votosNecesarios){
					ganador = j;
					hayGanador = 1;
	//				printf("HAY GANADOR Y ES %i \n ",ganador);
					this->votAbiero = false;
					return ganador + 1;


				}
			}
			if (hayGanador == 0) {
	//			printf("\n\n entro 5555555555555555555555555555555555555 \n");
				//			fflush(stdout);
				numVotTemp = resultados[0];
				Elimin = 0;

	//			cout<< "eliminadosv" << contador<<": " <<eliminados[0] <<eliminados[1] <<eliminados[2] <<eliminados[3] <<endl;
	//			cout<< "vualta" << contador<<": " <<resultados[0] <<resultados[1] <<resultados[2] <<resultados[3] <<endl;
				for (int k = 1; k < this->nParticipantes; ++k) {

	//
	//				cout<< k <<endl;
	//				cout<< (votos[k]->getIdOpciones()[0])<<"***************************************************"<<endl;
	//				cout<< (eliminados[votos[k]->getIdOpciones()[0]- 1])<<"***************************************************"<<endl;
	//				cout<<numVotTemp<< ">" << k << ":" << resultados[k] <<endl<< " && "<< eliminados[(votos[k]->getIdOpciones()[0]) - 1] <<endl<<endl;
	//				while(eliminados[Elimin] == 1){
	//					Elimin = Elimin + 1;
	//					numVotTemp = resultados[Elimin];
	//					cout <<"EL NUCE=" << Elimin <<endl;
	//				}
					 if(eliminados[k] == 1 ){

	//					 cout <<k<<"YA ESTA ELIMINADO"<<endl;
					 }else{
	//					 cout <<k<<"*NO* ESTA ELIMINADO"<<endl;
						 if (numVotTemp > resultados[k] || eliminados[Elimin] ==1){

							 //cout << "numVotTemp" << Elimin << "(" << numVotTemp << ") >" << "resultados" << k << "(" << resultados[k] << ")" <<endl <<endl;
							 //					printf("numVotTemp%i(%i) > resultados%i(%i)\n",Elimin, numVotTemp,k,resultados[k]);
							 fflush(stdout);
	//						 cout << "numVotTemp ANTES:"<<numVotTemp<<endl;
							 numVotTemp = resultados[k];
	//						 cout << "numVotTemp DESP:"<<numVotTemp<<endl<<endl;
	//						 cout << "Elimin ANTES:"<<Elimin<<endl;
							 Elimin = k;
	//						 cout << " DESP:"<<Elimin<<endl<<endl;
	//						 cout<<"*////////////////////////////////////////////////////////////////////////////////////////////////////////"<<endl;

							 //					printf("elim = %i",Elimin);
							 //					fflush(stdout);
						 }

					 }



				}

				//1 significa eliminado
	//			cout<<"Se elimina opción:"<< Elimin << endl;
				eliminados[Elimin] = 1;

	//			cout<<"3 For"<< endl;

				for (int q = 0;  q < this->num_VA; ++ q) {
	//				cout<<"primera opcion votante"<< q <<":"<< (votos[q]->getIdOpciones()[0]) << endl<< endl;
				}
	//			cout<<"POSICIOOOOON"<< endl;
				for (int q = 0;  q < this->num_VA; ++ q) {

	//				cout<<"posicion"<< q <<":"<< eliminados[q] << endl;
				}



				for (int l = 0; l < this->num_VA; ++l) {
					//while(Eliminado == 0){
	//				cout<<"IIIIIIIIIIIIIIIIINNN3 For"<< endl;
					SWeliminado = 1;
					while  (SWeliminado == 1){
	//					cout<< endl <<"MIRANDO DENTROOOOOOOOOO:" << endl;
	//					cout<<"MIRANDO POSICION:"<< (votos[l]->getIdOpciones()[0] - 1) << endl;
	//					cout<<"DENTRO:"<< (eliminados[(votos[l]->getIdOpciones()[0]) - 1])<< endl;

						if (eliminados[(votos[l]->getIdOpciones()[0]) - 1] == 1) {
							SWeliminado = 1;
							// mover 1
							for (int n = 1; n < this->nParticipantes; ++n) {
	//							printf("\n entro666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666\n");
								//							fflush(stdout);
								//							printf("%i <-- %i\n",votos[l].idOpciones[n - 1], votos[l].idOpciones[n]);
								//							fflush(stdout);
								votos[l]->getIdOpciones()[n - 1] = votos[l]->getIdOpciones()[n];
							}
						}else{
							SWeliminado = 0;
						}
						//					getchar();
					}
				}
			}
		}
	//	cout <<"EMPAAAAAAAAATE"<<endl;
		this->votAbiero = false;
		return -1;

}
