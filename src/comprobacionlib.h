#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
const int numeromaximodecaractereslargo=48;
  typedef char string[numeromaximodecaractereslargo+1];
  typedef char stringpregunta[];
  typedef int tipovector[];
  void incorrecto();
  void tomarint(int &dato, int min, int max, stringpregunta pregunta);
  void tomarchar(char &dato, stringpregunta pregunta);
  void tomarstring(string &dato, int min, int max, stringpregunta pregunta);
  void tomarfecha(int &dia, int &mes, int &anyo, stringpregunta pregunta1, stringpregunta pregunta2, stringpregunta pregunta3);
