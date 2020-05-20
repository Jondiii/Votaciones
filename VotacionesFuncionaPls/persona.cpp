#include "Persona.h"
#include "sqlite3.h"
#include "vAlternativo.h"
#include "Votacion.h"
#include "VotacionAlter.h"

#include <string.h>
#include <iostream>
using namespace std;

Persona::Persona(int dni)
{
	this->dni = dni;
	this->cod_postal = 0;
	this->edad = 18;
}

Persona::Persona(const Persona &p)
{
	this->dni = p.dni;
	this->edad = p.edad;
	this->cod_postal = p.cod_postal;
}

Persona::~Persona()
{
}
int Persona::getDni()
{
	return this->dni;
}
int Persona::getEdad()
{
	return this->edad;
}
void Persona::setEdad(int edad)
{
	this->edad = edad;
}

bool Persona::comprobarDni(int dni, int id)
{
    bool no_coincidencia = true;
    sqlite3 *db;
    sqlite3_stmt * stmt;
    if (sqlite3_open("votaciones.sql", &db) == SQLITE_OK)
    {
    sqlite3_prepare( db, "SELECT ID_V, ID_P from votos;", -1, &stmt, NULL );
    int rc = sqlite3_step( stmt );
    int ncols = sqlite3_column_count(stmt);
         while(rc == SQLITE_ROW)
         {
             for(int i=0; i < ncols;)
             {
                 if (( sqlite3_column_int(stmt, i) == id) & (sqlite3_column_int(stmt, i+1) == dni))
                 {

                     no_coincidencia = false;
                 }
                 else
                 {
                     no_coincidencia = true;
                 }
                 i = i+2;
              }
              fprintf(stderr, "\n");
              rc = sqlite3_step(stmt);
          }
    }
    else
    {
        cout << "No se pudo abrir la base de datos \n";
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return no_coincidencia;
}

int Persona::getCodigo()
{
    return this->cod_postal;
}

void Persona::setCodigo(int cod_postal)
{
    this->cod_postal = cod_postal;
}

void Persona::insertarPersonaDB(int id)
{
    bool no_coincidencia = true;
    sqlite3 *db;
    sqlite3_stmt * stmt;
    sqlite3_stmt * stmt_1;
    sqlite3_stmt * stmt_2;
    string sqlstatement = "INSERT INTO persona VALUES(" + to_string(this->getDni()) + "," + to_string(this->getEdad()) + "," + to_string(this->getCodigo()) + ");";
    string sqlstatement_2 = "INSERT INTO votos VALUES(" + to_string(id) + "," +to_string(this->getDni()) + ");";

    if (sqlite3_open("votaciones.sql", &db) == SQLITE_OK)
    {
        sqlite3_prepare( db, "SELECT ID_P from perosna;", -1, &stmt_2, NULL );
        int rc = sqlite3_step( stmt );
        int ncols = sqlite3_column_count(stmt);
        while(rc == SQLITE_ROW)
        {
            for(int i=0; i < ncols; i++)
            {
                if (( sqlite3_column_int(stmt_2, i) == dni))
                {
                    no_coincidencia = false;
                }
            }
        }
        sqlite3_prepare( db, sqlstatement_2.c_str(), -1, &stmt, NULL );
        sqlite3_step( stmt );
        if (no_coincidencia){
            sqlite3_prepare( db, sqlstatement.c_str(), -1, &stmt_1, NULL );
            sqlite3_step( stmt_1 );
        }
    }
    else
    {
    cout << "No se ha podido abrir db\n";
    }
    sqlite3_finalize(stmt);
    sqlite3_finalize(stmt_1);
    sqlite3_finalize(stmt_2);
    sqlite3_close(db);
    return;
}
