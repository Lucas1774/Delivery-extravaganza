#include "comprobacionlib.h"
//----------------------------------------------------------------------------------------------------
  void incorrecto(){
    printf ("datos incorrectos\n");
    }
  //----------------------------------------------------------------------------------------------------
  void tomarchar(char &dato, stringpregunta pregunta){
    char datotemp;
    do {
      fflush(stdin);
      printf(" %s",pregunta);
      scanf(" %c",&datotemp);
      if (datotemp!='s'&&datotemp!='n'){
        incorrecto();
        }
      } while (datotemp!='s'&&datotemp!='n');
        dato=datotemp;
    }
  //----------------------------------------------------------------------------------------------------
  void tomarint(int &dato, int min, int max, stringpregunta pregunta){
    int datotemp;
    do {
      datotemp=0;
      fflush(stdin);
      printf(" %s",pregunta);
      scanf(" %d",&datotemp);
      if (datotemp<min||datotemp>max){
        incorrecto();
        }
      } while (datotemp<min||datotemp>max);
    dato=datotemp;
    }
  //----------------------------------------------------------------------------------------------------
  void tomarstring(string &dato, int min, int max, stringpregunta pregunta){
    string datotemp;
    int longitud;
    do {
      longitud=0;
      fflush(stdin);
      printf(" %s",pregunta);
      scanf(" %s",datotemp);
      longitud=strlen(datotemp);
      if (longitud<min||longitud>max){
        incorrecto();
        }
      } while (longitud<min||longitud>max);
    strcpy(dato,datotemp);
    }
  //----------------------------------------------------------------------------------------------------
  void tomarfecha(int &dia, int& mes, int &anyo, stringpregunta pregunta1, stringpregunta pregunta2, stringpregunta pregunta3){
    tipovector diasdelosmeses={0,31,0,31,30,31,30,31,31,30,31,30,31};
    int diatemp, mestemp, anyotemp;
    do{
      diatemp=0;
      mestemp=0;
      anyotemp=0;
      tomarint (diatemp,1,31, pregunta1);
      tomarint (mestemp,1,12, pregunta2);
      tomarint (anyotemp,1601,3000, pregunta3);
      if((anyotemp%4==0&&anyotemp%100!=0)||anyotemp%400==0){
      diasdelosmeses[2]=29;
      } else {
        diasdelosmeses[2]=28;
        }
      if (diatemp>diasdelosmeses[mestemp]){
        printf("La fecha indicada no existe\n");
        }
      }while(diatemp>diasdelosmeses[mestemp]);
    dia=diatemp;
    mes=mestemp;
    anyo=anyotemp;
    }
