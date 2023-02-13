#include "pacientes.h"
  //-----------------------------------------------------------------------------------------------------------------
  void funcionpacientes::nuevopaciente(vectordepacientes &pacientes, int &numeropaciente){
    tipopaciente nuevo;
    string apellido;
    int longitud;
    char opcion, confirmacion;
    if (numeropaciente!=numeromaximodepacientes){
      printf("Alta nuevo paciente:");
      do{
        do{
          do {
            longitud=0;
            fflush(stdin);
            printf("\n\nIdentificador (entre 1 y 20 caracteres)");
            scanf(" %s %s",nuevo.nombre, apellido);
            strcat(nuevo.nombre,espacio);
            strcat(nuevo.nombre,apellido);
            longitud=strlen(nuevo.nombre);
            if (longitud<1||longitud>numeromaximodecaracteresmedio){
              incorrecto();
              }
            } while (longitud<1||longitud>numeromaximodecaracteresmedio);
          tomarint(nuevo.adressdistance,1,distanciamaxima,"Distancia (hasta 10000 metros a plena carga)");
          tomarint(nuevo.adressangle,1,angulomaximo,"Angulo (entre 1 y 2000  pi/1000 radianes)");
          tomarchar (confirmacion, "\nDatos correctos? (s/n)");
          }while (confirmacion=='n');
        guardardatos(nuevo, pacientes, numeropaciente);
        printf("paciente guardado\n");
        tomarchar(opcion,"Otro paciente mismo almacen?(s/n)");
        } while ((opcion=='s'&&numeropaciente<numeromaximodepacientes));
      }
    if(numeropaciente==numeromaximodepacientes){
      printf ("No tenemos capacidad para mas pacientes\n");
      }
    }
    //-----------------------------------------------------------------------------------------------------------------
  void funcionpacientes::imprimirpacientes(vectordepacientes pacientes, int numeropaciente){
    printf("  Ref.        Identificador   Distancia     Angulo\n\n");
    for(int i=0;i<numeropaciente;i++){
      printf("  %2d   %20s        %4d      %5d\n",pacientes[i].id, pacientes[i].nombre, pacientes[i].adressdistance, pacientes[i].adressangle);
      }
    if (numeropaciente==0){
      printf ("No hay pacientes registrados en este almacen\n");
      }
    }
    //-----------------------------------------------------------------------------------------------------------------
  void funcionpacientes::inicializarpacientes(vectordepacientes &pacientes){
    for (int i=0;i<numeromaximodepacientes;i++){
      pacientes[i].id=0;
      pacientes[i].adressdistance=0;
      pacientes[i].adressangle=0;
      }
    }
    //-----------------------------------------------------------------------------------------------------------------
    //--------------------------------------------LOCAL----------------------------------------------------------
    //-------------------------------------------------------------------------------------------------------------
  void funcionpacientes::guardardatos (tipopaciente &nuevo, vectordepacientes &pacientes, int &numeropaciente){
    if (numeropaciente==0){
      nuevo.id=1;
      }else{
        nuevo.id=pacientes[numeropaciente-1].id+1;
        }
    pacientes[numeropaciente]=nuevo;
    numeropaciente++;
    }
