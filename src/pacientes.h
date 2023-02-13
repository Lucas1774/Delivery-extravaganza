#pragma once
#include "comprobacionlib.h"
const int numeromaximodepacientes=20;
const int distanciamaxima=10000;
const int angulomaximo=2000;
const char numeromaximodecaracteresmedio=20;
const char espacio[]=" ";

  //-------------------------------------------------------------------------------------------------------------
  typedef struct tipopaciente{
    string nombre;
    int adressdistance;
    int adressangle;
    int id;
    };
  typedef tipopaciente vectordepacientes[numeromaximodepacientes];
  //-------------------------------------------------------------------------------------------------------------
  typedef struct funcionpacientes{
    void nuevopaciente (vectordepacientes &pacientes, int &numeropaciente);
    void imprimirpacientes (vectordepacientes pacientes, int numeropaciente);
    void inicializarpacientes(vectordepacientes &pacientes);
    void guardardatos(tipopaciente &nuevo, vectordepacientes &pacientes, int &numeropaciente);
      };
