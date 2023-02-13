#pragma once
#include "pacientes.h"
const int numeromaximodepedidos=100;
const int numeromaximodefarmacos=5;
const int pesomaximodelpedido=3000;
const int numeromaximodediasentrecadaenvio=15;
  //-------------------------------------------------------------------------------------------------------------
  typedef struct tipofecha{
    int dia;
    int mes;
    int anyo;
    };
  typedef struct tiponodoenvios{
    tipofecha fecha;
    tiponodoenvios* siguiente;
    };
  typedef tiponodoenvios* tipopunteroenvios;
  typedef struct tipofarmaco{
      string nombre;
      int peso;
      int unidades;
      int pesoporunidades;
    };
  typedef tipofarmaco vectordefarmacos[numeromaximodefarmacos];
  typedef struct tipopedido{
    int id;
    int numerodeenvios;
    int diasentrecadaenvio;
    int pesopedido;
    int numerofarmaco;
    tipopunteroenvios secuenciadeenvios;
    vectordefarmacos farmacos;
    };
  typedef tipopedido vectordepedidos[numeromaximodepedidos];
    //-------------------------------------------------------------------------------------------------------------
  typedef struct funcionpedidos{
      void nuevopedido(vectordepacientes pacientes, vectordepedidos &pedidos, int &numeropedido, int numeropaciente);
      void listadiariadepedidos(vectordepacientes pacientes, vectordepedidos pedidos, int numeropedido, string nombre);
      void inicializarpedidos(vectordepedidos &pedidos);
      void guardarenvio(tipopedido &nuevopedido);
      void guardarfarmaco (tipopedido &nuevopedido, tipofarmaco &nuevofarmaco);
      void guardarpedido(tipopedido &nuevopedido, vectordepedidos &pedidos, int &numeropedido);
       };



