#include "pedidos.h"
  //-------------------------------------------------------------------------------------------------------------
  void funcionpedidos::nuevopedido(vectordepacientes pacientes, vectordepedidos &pedidos, int &numeropedido, int numeropaciente){
    char opcionotrofarmaco, opcionotropedido;
    tipopedido nuevopedido;
    tipofarmaco nuevofarmaco;
    if (numeropedido!=numeromaximodepedidos&&numeropaciente!=0){
      printf("Nuevo pedido:");
      do{
        nuevopedido.pesopedido=0;
        nuevopedido.numerofarmaco=0;
        nuevopedido.secuenciadeenvios=new tiponodoenvios;
        nuevopedido.secuenciadeenvios->siguiente=NULL;
        tomarint(nuevopedido.id,1,numeropaciente,"\nRef.paciente? (entre 1 y 20)");
        tomarint(nuevopedido.numerodeenvios,1,INT_MAX,"Numero de envios?");
        if (nuevopedido.numerodeenvios==1){
          tomarfecha(nuevopedido.secuenciadeenvios->fecha.dia, nuevopedido.secuenciadeenvios->fecha.mes, nuevopedido.secuenciadeenvios->fecha.anyo, "Dia del envio?", "Mes del envio?", "A�o del envio?");
          }else {
            tomarint(nuevopedido.diasentrecadaenvio,1,numeromaximodediasentrecadaenvio,"Numero de d�as entre cada envio? (Entre 1 y 15 d�as)");
            tomarfecha(nuevopedido.secuenciadeenvios->fecha.dia, nuevopedido.secuenciadeenvios->fecha.mes, nuevopedido.secuenciadeenvios->fecha.anyo,"Dia del primer envio?", "Mes del primer envio?", "A�o del primer envio?");
            for(int i=0;i<nuevopedido.numerodeenvios-1;i++){
              guardarenvio(nuevopedido);
              }
          }
        do{
          nuevofarmaco.pesoporunidades=0;
          do{
            tomarstring (nuevofarmaco.nombre,1,numeromaximodecaracteresmedio,"Nombre farmaco? (Entre 1 y 20 caracteres)");
            tomarint (nuevofarmaco.peso,1,pesomaximodelpedido-nuevopedido.pesopedido,"Peso farmaco? (Menor de 3000 gramos)");
            tomarint (nuevofarmaco.unidades,1,INT_MAX,"Unidades de farmaco?");
            if (nuevopedido.pesopedido+(nuevofarmaco.unidades*nuevofarmaco.peso)>pesomaximodelpedido){
              incorrecto();
              }
            }while (nuevopedido.pesopedido+(nuevofarmaco.unidades*nuevofarmaco.peso)>pesomaximodelpedido);
          guardarfarmaco(nuevopedido, nuevofarmaco);
          printf("Farmaco guardado\n");
          tomarchar (opcionotrofarmaco,"Otro farmaco?(s/n)");
        }while(opcionotrofarmaco=='s'&&nuevopedido.pesopedido<pesomaximodelpedido&&nuevopedido.numerofarmaco<numeromaximodefarmacos);
        if ((nuevopedido.pesopedido==pesomaximodelpedido||nuevopedido.numerofarmaco==numeromaximodefarmacos)&&opcionotrofarmaco=='s'){
          printf("Tu pedido esta completo\n");
          }
        guardarpedido(nuevopedido, pedidos, numeropedido);
        printf("Pedido guardado\n");
        tomarchar (opcionotropedido,"Otro pedido mismo almacen?(s/n)");
        }while(opcionotropedido=='s'&&numeropedido<numeromaximodepedidos);
      }
      if(numeropedido==numeromaximodepedidos){
        printf ("No tenemos capacidad para mas pedidos\n");
        }
      if(numeropaciente==0){
        printf("No hay pacientes registrados\n");
        }
    }
    //-------------------------------------------------------------------------------------------------------------
  void funcionpedidos::listadiariadepedidos(vectordepacientes pacientes, vectordepedidos pedidos, int numeropedido, string nombre){
    tipofecha fechadada;
    int x=1;
    tipopunteroenvios punterocursor;
    tomarfecha (fechadada.dia, fechadada.mes, fechadada.anyo, "Dia?", "Mes?", "A�o?");
    printf("ALMACEN - %s\n\n",nombre);
    for(int i=0;i<numeropedido;i++){
      punterocursor=pedidos[i].secuenciadeenvios;
      while (punterocursor!=NULL){
        if((fechadada.dia==punterocursor->fecha.dia)&&
          (fechadada.mes==punterocursor->fecha.mes)&&
          (fechadada.anyo==punterocursor->fecha.anyo)){
            printf("    \n\nPedido %d",x);
            printf("\nUbicacion destino: Distancia: %d y Angulo: %d",pacientes[pedidos[i].id-1].adressdistance,pacientes[pedidos[i].id-1].adressangle);
            for(int k=0;k<pedidos[i].numerofarmaco;k++){
              printf("\n%4d Unidades  %20s  Peso: %4d gramos",pedidos[i].farmacos[k].unidades,pedidos[i].farmacos[k].nombre,pedidos[i].farmacos[k].pesoporunidades);
              }
            printf("\nPeso total del envio: %4d gramos",pedidos[i].pesopedido);
            x++;
            }
        punterocursor=punterocursor->siguiente;
        }
      }
    }
    //-------------------------------------------------------------------------------------------------------------
  void funcionpedidos::inicializarpedidos(vectordepedidos &pedidos){
    for (int i=0;i<numeromaximodepedidos;i++){
      pedidos[i].id=0;
      pedidos[i].numerodeenvios=0;
      pedidos[i].diasentrecadaenvio=0;
      pedidos[i].pesopedido=0;
      pedidos[i].numerofarmaco=0;
      pedidos[i].secuenciadeenvios=NULL;
      for(int j=0;j<numeromaximodefarmacos;j++){
        pedidos[i].farmacos[j].peso=0;
        pedidos[i].farmacos[j].unidades=0;
        pedidos[i].farmacos[j].pesoporunidades=0;
        }
      }
    }
    //-----------------------------------------------------------------------------------------------------------------
    //--------------------------------------------LOCAL----------------------------------------------------------
    //-------------------------------------------------------------------------------------------------------------
  void funcionpedidos::guardarenvio (tipopedido &nuevopedido){
    tipovector diasdelosmeses={0,31,0,31,30,31,30,31,31,30,31,30,31};
    tipopunteroenvios  envioanterior, enviocursor, envionuevo;
    enviocursor=nuevopedido.secuenciadeenvios;
    envioanterior=NULL;
    while(enviocursor!=NULL){
      envioanterior=enviocursor;
      enviocursor=enviocursor->siguiente;
      }
      envionuevo=new tiponodoenvios;
      envionuevo->fecha.dia=envioanterior->fecha.dia+nuevopedido.diasentrecadaenvio;
      envionuevo->fecha.mes=envioanterior->fecha.mes;
      envionuevo->fecha.anyo=envioanterior->fecha.anyo;
      if((envionuevo->fecha.anyo%4==0&&envionuevo->fecha.anyo%100!=0)||envionuevo->fecha.anyo%400==0){
      diasdelosmeses[2]=29;
      } else{
        diasdelosmeses[2]=28;
        }
      if (envionuevo->fecha.dia>diasdelosmeses[envionuevo->fecha.mes]){
        envionuevo->fecha.dia=envionuevo->fecha.dia-diasdelosmeses[envionuevo->fecha.mes];
        envionuevo->fecha.mes++;
        }
      if(envionuevo->fecha.mes>12){
        envionuevo->fecha.mes=1;
        envionuevo->fecha.anyo++;
        }
    envionuevo->siguiente=envioanterior->siguiente;
    envioanterior->siguiente=envionuevo;
    }
    //-------------------------------------------------------------------------------------------------------------
  void funcionpedidos::guardarfarmaco(tipopedido &nuevopedido, tipofarmaco &nuevofarmaco){
    nuevofarmaco.pesoporunidades=nuevofarmaco.peso*nuevofarmaco.unidades;
    nuevopedido.pesopedido=nuevopedido.pesopedido+nuevofarmaco.pesoporunidades;
    nuevopedido.farmacos[nuevopedido.numerofarmaco]=nuevofarmaco;
    nuevopedido.numerofarmaco++;
    }
    //-------------------------------------------------------------------------------------------------------------
  void funcionpedidos::guardarpedido(tipopedido &nuevopedido, vectordepedidos &pedidos, int &numeropedido){
    pedidos[numeropedido]=nuevopedido;
    numeropedido++;
    }