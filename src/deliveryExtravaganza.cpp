#include "pedidos.h"
#include <math.h>
const int numeromaximodealmacenes=10;
const int numeromaximodecaracterescorto=16;
const float pi=3.141592653589793238462643383279502884;
const float variaciondeconsumo=0.00008333333333333333333334;
  //-------------------------------------------------------------------------------------------------------------
  typedef struct tipoalmacen{
    int id;
    string calle;
    string municipio;
    string provincia;
    string descripcion;
    int numeropaciente;
    int numeropedido;
    vectordepacientes pacientes;
    vectordepedidos pedidos;
    };
  typedef tipoalmacen vectordealmacenes[numeromaximodealmacenes];
    typedef struct tiponodo{
    int id;
    int adressdistance;
    int adressangle;
    int pesopedido;
    bool yahepasado;
    };
  typedef tiponodo vectordenodos[numeromaximodepedidos+1];
  typedef struct tipodestino{
    int id;
    int adressdistance;
    int adressangle;
    int pesopedido;
    tipodestino* siguiente;
  };
  typedef tipodestino* tiposecuenciadestinos;
  typedef struct tiporuta{
    int id;
    int distanciarecorrida;
    int cargainicial;
    int distanciadevuelta;
    int angulodevuelta;
    tiposecuenciadestinos secuenciadestinos;
    tiporuta* siguiente;
  };
  typedef tiporuta* tiposecuenciarutas;
  //-------------------------------------------------------------------------------------------------------------
  //-------------------------------------------------------------------------------------------------------------
  //-------------------------------------------------------------------------------------------------------------
  void programarrutas(vectordepacientes &pacientes, vectordepedidos &pedidos, int &numeropedido){
    tipofecha fechadada;
    tipopunteroenvios punterocursor;
    vectordenodos nodos, nodosoriginal;
    tiposecuenciarutas secuenciarutas, nuevorutas, cursorrutas, anteriorrutas;
    tiposecuenciadestinos nuevodestinos, cursordestinos, anteriordestinos;
    int numerodenodos=0;
    int nodosentregados=0;
    int distanciaminima;
    float alfa;
    int nodoalqueir;
    float autonomia=25000;
    int carga=pesomaximodelpedido;
    float coeficientedeconsumo=1+(carga*variaciondeconsumo);
    for(int i=0; i<numeromaximodepedidos; i++){
      nodos[i].id=0;
      nodos[i].adressdistance=0;
      nodos[i].adressangle=0;
      nodos[i].pesopedido=0;
      nodos[i].yahepasado=true;
    }
    tomarfecha (fechadada.dia, fechadada.mes, fechadada.anyo, "Dia?", "Mes?", "A�o?");
    for(int i=0;i<numeropedido;i++){
      punterocursor=pedidos[i].secuenciadeenvios;
      while (punterocursor!=NULL){
        if(fechadada.dia==punterocursor->fecha.dia&&fechadada.mes==punterocursor->fecha.mes&&fechadada.anyo==punterocursor->fecha.anyo){
          numerodenodos++;
          nodos[numerodenodos].id=pacientes[pedidos[i].id-1].id;
          nodos[numerodenodos].adressdistance=pacientes[pedidos[i].id-1].adressdistance;
          nodos[numerodenodos].adressangle=pacientes[pedidos[i].id-1].adressangle;
          nodos[numerodenodos].pesopedido=pedidos[i].pesopedido;
          nodos[numerodenodos].yahepasado=false;
        }
        punterocursor=punterocursor->siguiente;
      }
    }
    if (numerodenodos>0){
      secuenciarutas=new tiporuta;
      secuenciarutas->siguiente=NULL;
      secuenciarutas->id=1;
      secuenciarutas->distanciarecorrida=0;
      secuenciarutas->cargainicial=0;
      secuenciarutas->secuenciadestinos=NULL;
      cursorrutas=secuenciarutas;
      anteriorrutas=NULL;
      for(int i=0;i<numeromaximodepedidos;i++){
        nodosoriginal[i]=nodos[i];
      }
      while((nodosentregados<numerodenodos)){
        distanciaminima=20001;
        for (int i=0; i<numerodenodos+1;i++){
          if (nodos[i].yahepasado==false&&nodos[i].adressdistance<distanciaminima&&nodos[i].pesopedido<=carga){
            distanciaminima=nodos[i].adressdistance;
            nodoalqueir=i;
          }
        }
        if(autonomia<distanciaminima+distanciaminima*coeficientedeconsumo){
          cursorrutas->distanciarecorrida=cursorrutas->distanciarecorrida+nodos[0].adressdistance;
          cursorrutas->distanciadevuelta=nodos[0].adressdistance;
          cursorrutas->angulodevuelta=nodos[0].adressangle;
          anteriorrutas=cursorrutas;
          nuevorutas=new tiporuta;
          nuevorutas->siguiente=NULL;
          nuevorutas->id=anteriorrutas->id+1;
          nuevorutas->distanciarecorrida=0;
          nuevorutas->cargainicial=0;
          nuevorutas->secuenciadestinos=NULL;
          anteriorrutas->siguiente=nuevorutas;
          cursorrutas=cursorrutas->siguiente;
          for (int i=0; i<numerodenodos+1;i++){
            nodos[i].adressdistance=nodosoriginal[i].adressdistance;
            nodos[i].adressangle=nodosoriginal[i].adressangle;
          }
          autonomia=25000;
          carga=pesomaximodelpedido;
          coeficientedeconsumo=1+(carga*variaciondeconsumo);
          distanciaminima=20001;
          for (int i=0; i<numerodenodos+1;i++){
            if (nodos[i].yahepasado==false&&nodos[i].adressdistance<distanciaminima&&nodos[i].pesopedido<=carga){
              distanciaminima=nodos[i].adressdistance;
              nodoalqueir=i;
            }
          }
        }
        nuevodestinos=new tipodestino;
        nuevodestinos->id=nodos[nodoalqueir].id;
        nuevodestinos->adressdistance=nodos[nodoalqueir].adressdistance;
        nuevodestinos->adressangle=nodos[nodoalqueir].adressangle;
        nuevodestinos->pesopedido=nodos[nodoalqueir].pesopedido;
        nuevodestinos->siguiente=NULL;
        cursordestinos=cursorrutas->secuenciadestinos;
        anteriordestinos=NULL;
        while (cursordestinos!=NULL){
          anteriordestinos=cursordestinos;
          cursordestinos=cursordestinos->siguiente;
        }
        if (anteriordestinos==NULL){
          cursorrutas->secuenciadestinos=nuevodestinos;
        }else{
          anteriordestinos->siguiente=nuevodestinos;
        }
        for (int i=0; i<numerodenodos+1;i++){
          if (i==nodoalqueir){
            nodos[i].yahepasado=true;
            cursorrutas->distanciarecorrida=cursorrutas->distanciarecorrida+distanciaminima;
            cursorrutas->cargainicial=cursorrutas->cargainicial+nodos[i].pesopedido;
            carga=carga-nodos[i].pesopedido;
            autonomia=autonomia-distanciaminima*coeficientedeconsumo;
            coeficientedeconsumo=1+(carga*variaciondeconsumo);
            nodosentregados++;
          } else {
            nodos[i].adressdistance= int(ceil(+sqrtf(nodosoriginal[i].adressdistance*nodosoriginal[i].adressdistance+nodosoriginal[nodoalqueir].adressdistance*nodosoriginal[nodoalqueir].adressdistance-(2*nodosoriginal[i].adressdistance*nodosoriginal[nodoalqueir].adressdistance*cosf((nodosoriginal[i].adressangle*pi/1000)-(nodosoriginal[nodoalqueir].adressangle*pi/1000))))));
            if(nodos[i].adressdistance==0){
              nodos[i].adressangle=0;
            } else{
              alfa=acos((powf(nodosoriginal[i].adressdistance,2)-powf(nodos[i].adressdistance,2)-powf(nodosoriginal[nodoalqueir].adressdistance,2))/(-2*nodos[i].adressdistance*nodosoriginal[nodoalqueir].adressdistance))*1000/pi;
              nodos[i].adressangle=int(roundf(1000-alfa+nodosoriginal[nodoalqueir].adressangle));
            }
            if (nodos[i].adressangle>2000){
                nodos[i].adressangle=nodos[i].adressangle%2000;
            }
          }
        }
        if (nodosentregados==numerodenodos){
          cursorrutas->distanciarecorrida=cursorrutas->distanciarecorrida+nodos[0].adressdistance;
          cursorrutas->distanciadevuelta=nodos[0].adressdistance;
          cursorrutas->angulodevuelta=nodos[0].adressangle;
        }
      }
      cursorrutas=secuenciarutas;
      while (cursorrutas!=NULL){
        printf (    "ruta %d\n",cursorrutas->id);
        cursordestinos=cursorrutas->secuenciadestinos;
        anteriordestinos=NULL;
        while (cursordestinos!=NULL){
          if (anteriordestinos==NULL){
            printf ("Origen a Cliente %2d -- Distancia recorrida: %5d Angulo: %4d Peso: %4d gramos\n", cursordestinos->id, cursordestinos->adressdistance, cursordestinos->adressangle, cursorrutas->cargainicial);
          }else{
            printf ("Cliente %2d a Cliente %2d -- Distancia recorrida: %5d Angulo: %4d Peso: %4d gramos\n", anteriordestinos->id, cursordestinos->id, cursordestinos->adressdistance, cursordestinos->adressangle, cursorrutas->cargainicial);
          }
          cursorrutas->cargainicial=cursorrutas->cargainicial-cursordestinos->pesopedido;
          anteriordestinos=cursordestinos;
          cursordestinos=cursordestinos->siguiente;
        }
        printf("Cliente %2d a Origen -- Distancia recorrida: %5d Angulo: %4d\n", anteriordestinos->id, cursorrutas->distanciadevuelta, cursorrutas->angulodevuelta);
        printf("Distancia total de la ruta: %5d\n", cursorrutas->distanciarecorrida);
        cursorrutas=cursorrutas->siguiente;
      }
    }
  }
  void tomarcodigoalmacenlibre(vectordealmacenes almacenes, int &id){
    bool almacenocupado;
    do{
      almacenocupado=false;
      tomarint (id,1,numeromaximodealmacenes,"Tdentificador almacen? (entre 1 y 10)");
      for(int i=0;i<numeromaximodealmacenes;i++){
        if (almacenes[i].id==id){
          almacenocupado=true;
          }
        }
      if (almacenocupado==true){incorrecto();}
      }while (almacenocupado==true);
  }
  void tomarcodigoalmacenocupado(vectordealmacenes almacenes, int &id){
    bool almacenocupado;
    do{
      almacenocupado=false;
      tomarint (id,1,numeromaximodealmacenes,"Tdentificador almacen? (entre 1 y 10)");
      for(int i=0;i<numeromaximodealmacenes;i++){
        if (almacenes[i].id==id){
          almacenocupado=true;
          }
        }
      if (almacenocupado==false){incorrecto();}
      }while (almacenocupado==false);
  }
  void inicializargestion(vectordealmacenes &almacenes, int &numeroalmacen){
    typedef tipofarmaco vectordefarmacosparaintroducir[8];
    typedef tipofecha vectordefechasparaintroducir[8];
    funcionpacientes funcionesdepacientes;
    funcionpedidos funcionesdepedidos;

    const tipovector idalmacen={2,4,6,7,8};
    const string calledealmacen[5]={"Hortaleza, 70","Camino de Madrid, 6", "Catlina Zambrano, S/N","Manuel Zorrilla, 6","de Los Bordadores, 56"};
    const string municipiodealmacen[5]={"Villalba","Zaragoza","Pinto","Reus","Torrelodones"};
    const string proviniciadealmacen[5]={"Madrid","Huesca","Madrid","Barcelona","Madrid"};
    const string descripciondealmacen[5]={"Almacen urbano","El mejor que hay","Entre Pinto y Valdemoro","El agua no es potable","Frente al casino"};

    vectordepacientes pacientesalmacen1={{"Mario Vaquerizo",432,321,1},{"Philip Fry",432,1432,2},{"Jimenez Losantos",123,42,3}};
    vectordepacientes pacientesalmacen2={{"Jaimitio Gonzalez",8113,245,1},{"Luis Valladares",4321,234,2},{"Carlota Ponce",8742,1234,3},{"Miguel Vialcho",412,2,4},{"Nuria Roca",1123,23,5},{"Daniel Moricllo",2423,32,6},{"Javier Torrilla",1423,432,7}};

    vectordepedidos pedidosparaalmacen1={{1,3,12,0,0},{3,5,10,0,0},{3,40,5,0,0},{2,6,5,0,0},{1,7,6,0,0},{3,32,3,0,0},{2,100,2,0,0}};
    vectordefechasparaintroducir fechadelprimerenvioparapedidosparaalmacen1={{3,2,2001},{5,2,2001},{7,4,2001},{1,5,2001},{12,9,2001},{24,9,2001},{15,11,2001}};
    vectordefarmacosparaintroducir farmacosparapedidosparaalmacen1={{"aspirina",20,4,0},{"paracetamol",3,20,0},{"nolotil",32,4,0},{"paracetamol",32,1,0},{"ibuprofeno",321,2,0},{"paracetamol",31,2,0},{"omeprazol",34,6,0}};
    vectordepedidos pedidosparaalmacen2={{5,7,4,0,0},{2,15,7,0,0},{3,28,3,0,0},{2,31,4,0,0},{2,12,10,0,0},{1,16,13,0,0},{2,54,2,0,0},{7,13,13,0,0}};
    vectordefechasparaintroducir fechadelprimerenvioparapedidosparaalmacen2={{2,3,2001},{24,3,2001},{12,5,2001},{16,7,2001},{18,7,2001},{22,8,2001},{12,9,2001},{21,11,2001}};
    vectordefarmacosparaintroducir farmacosparapedidosparaalmacen2={{"en",31,4,0},{"que",314,3,0},{"estaban",413,4,0},{"pensando",45,3,0},{"al",413,5,0},{"disenyar",30,3,0},{"esta",52,3,0},{"practica",32,4,0}};

  for (int i=0;i<5;i++){
    almacenes[idalmacen[i]-1].id=idalmacen[i];
    strcpy(almacenes[idalmacen[i]-1].calle,calledealmacen[i]);
    strcpy(almacenes[idalmacen[i]-1].municipio,municipiodealmacen[i]);
    strcpy(almacenes[idalmacen[i]-1].provincia,proviniciadealmacen[i]);
    strcpy(almacenes[idalmacen[i]-1].descripcion,descripciondealmacen[i]);
    if (numeroalmacen<5){
      numeroalmacen++;
      }
    }
  for(int i=0; i<3; i++){
    funcionesdepacientes.guardardatos (pacientesalmacen1[i],almacenes[3].pacientes,almacenes[3].numeropaciente);
    }
  for(int i=0; i<7; i++){
    funcionesdepacientes.guardardatos (pacientesalmacen2[i], almacenes[7].pacientes, almacenes[7].numeropaciente);
    }
  for (int i=0; i<7;i++){
    funcionesdepedidos.guardarfarmaco (pedidosparaalmacen1[i], farmacosparapedidosparaalmacen1[i]);
    pedidosparaalmacen1[i].secuenciadeenvios=new tiponodoenvios;
    pedidosparaalmacen1[i].secuenciadeenvios->siguiente=NULL;
    pedidosparaalmacen1[i].secuenciadeenvios->fecha=fechadelprimerenvioparapedidosparaalmacen1[i];
    if(pedidosparaalmacen1[i].numerodeenvios>1){
      for (int j=0; j<pedidosparaalmacen1[i].numerodeenvios-1; j++){
        funcionesdepedidos.guardarenvio (pedidosparaalmacen1[i]);
        }
      }
    }
  for (int i=0; i<8;i++){
    funcionesdepedidos.guardarfarmaco (pedidosparaalmacen2[i], farmacosparapedidosparaalmacen2[i]);
    pedidosparaalmacen2[i].secuenciadeenvios=new tiponodoenvios;
    pedidosparaalmacen2[i].secuenciadeenvios->siguiente=NULL;
    pedidosparaalmacen2[i].secuenciadeenvios->fecha=fechadelprimerenvioparapedidosparaalmacen2[i];
    if(pedidosparaalmacen2[i].numerodeenvios>1){
      for (int j=0; j<pedidosparaalmacen2[i].numerodeenvios-1; j++){
        funcionesdepedidos.guardarenvio (pedidosparaalmacen2[i]);
        }
      }
    }
  for (int i=0; i<7; i++){
    funcionesdepedidos.guardarpedido(pedidosparaalmacen1[i], almacenes[3].pedidos, almacenes[3].numeropedido);
    }
  for (int i=0; i<8; i++){
    funcionesdepedidos.guardarpedido(pedidosparaalmacen2[i], almacenes[7].pedidos, almacenes[7].numeropedido);
    }
  }
  void inicializargestionimprimir (vectordealmacenes almacenes){
    funcionpacientes funcionesdepacientes;
   printf ("Listadogestion FarmadDron\n");
    for (int i=0; i<numeromaximodealmacenes;i++){
      if (almacenes[i].id!=0){
        printf ("\n   Almacen %d - %s - %s - %s\n   Descripcion: %s\n",almacenes[i].id, almacenes[i].calle, almacenes[i].municipio, almacenes[i].provincia, almacenes[i].descripcion);
        if (almacenes[i].numeropaciente!=0){
          funcionesdepacientes.imprimirpacientes(almacenes[i].pacientes, almacenes[i].numeropaciente);
          }
        if(almacenes[i].numeropedido!=0){
          printf("  Pedidos\n\n");
          printf("Cliente        Fecha                  Farmaco   Peso  Unidades\n\n");
          for (int j=0; j<almacenes[i].numeropedido;j++){
            printf("%7d%5d/%2d/%4d%25s%7d%10d\n",almacenes[i].pedidos[j].id,almacenes[i].pedidos[j].secuenciadeenvios->fecha.dia,almacenes[i].pedidos[j].secuenciadeenvios->fecha.mes,almacenes[i].pedidos[j].secuenciadeenvios->fecha.anyo,almacenes[i].pedidos[j].farmacos[0].nombre,almacenes[i].pedidos[j].farmacos[0].peso,almacenes[i].pedidos[j].farmacos[0].unidades);
            }
          }
        }
      }
    }
  void registraralmacen(vectordealmacenes &almacenes, int &numeroalmacen){
  funcionpacientes funcionesdepacientes;
  funcionpedidos funcionesdepedidos;
  char confirmacion;
  tipoalmacen nuevoalmacen;
  funcionesdepacientes.inicializarpacientes(nuevoalmacen.pacientes);
  funcionesdepedidos.inicializarpedidos(nuevoalmacen.pedidos);
  do {
    if (numeroalmacen==numeromaximodealmacenes){
      tomarint (nuevoalmacen.id,1,numeromaximodealmacenes,"Todos los almacenes estan ocupados, seleccione almacen sobre el que sobreescribir");
      } else{
      tomarcodigoalmacenlibre(almacenes, nuevoalmacen.id);
      }
      tomarstring (nuevoalmacen.calle,1,numeromaximodecaractereslargo,"Direccion almacen?( entre 1 y 48 caracteres)");
      tomarstring (nuevoalmacen.municipio,1,numeromaximodecaractereslargo,"Municipio almacen? (entre 1 y 48 caracteres)");
      tomarstring (nuevoalmacen.provincia,1,numeromaximodecaracterescorto,"Provincia almacen? (entre 1 y 16 caracteres)");
      tomarstring (nuevoalmacen.descripcion,1,numeromaximodecaracterescorto,"Descripcion almacen? (entre 1 y 48 caracteres)");
      tomarchar (confirmacion, "\nDatos correctos? (s/n)");
    }while (confirmacion=='n');
    almacenes[nuevoalmacen.id-1]=nuevoalmacen;
    if (numeroalmacen!=10){
      numeroalmacen++;
    }
  }
  bool controlopcionmenuprincipal(char &opciondelmenuprincipal){
    if (opciondelmenuprincipal!='i'&&opciondelmenuprincipal!='m'&&opciondelmenuprincipal!='a'&&opciondelmenuprincipal!='u'&&opciondelmenuprincipal!='n'&&opciondelmenuprincipal!='l'&&opciondelmenuprincipal!='p'&&opciondelmenuprincipal!='s'){
          return false;} else {
            return true;
            };
    }
  void menuprincipal (char &opciondelmenuprincipal){
    do {
      system ("cls");
      fflush (stdin);
      printf ("FarmaDron: Distribucion de Farmacos con Dron\n");
      printf ("  Iniciar gestion                  (Pulsar i)\n");
      printf ("  Alta almacen                     (Pulsar m)\n");
      printf ("  Alta paciente almacen            (Pulsar a)\n");
      printf ("  Ubicar pacientes                 (Pulsar u)\n");
      printf ("  Nuevo pedido                     (Pulsar n)\n");
      printf ("  Lista diaria de pedidos          (Pulsar l)\n");
      printf ("  Programar rutas diarias del dron (Pulsar p)\n");
      printf ("  Salir                            (Pulsar s)\n");
      printf ("Teclear una opci�n valida (i|m|a|u|n|l|p|s)");
      scanf (" %c",&opciondelmenuprincipal);
      system ("cls");
      } while (!controlopcionmenuprincipal (opciondelmenuprincipal));
    }
  //-------------------------------------------------------------------------------------------------------------
  //main
  //-------------------------------------------------------------------------------------------------------------
  int main(){
    char opciondelmenuprincipal;
    int numeroalmacen=0;
    int referenciaalmacenparaguardar;
    funcionpacientes funcionesdepacientes;
    funcionpedidos funcionesdepedidos;
    vectordealmacenes almacenes;
    //-------------------------------------------------------------------------------------------------------------
    for (int i=0; i<numeromaximodealmacenes;i++){
      almacenes[i].id=0;
      funcionesdepacientes.inicializarpacientes(almacenes[i].pacientes);
      funcionesdepedidos.inicializarpedidos(almacenes[i].pedidos);
      }
    do {
      menuprincipal(opciondelmenuprincipal);
      switch (opciondelmenuprincipal){
        case 'i':
          inicializargestion (almacenes, numeroalmacen);
          inicializargestionimprimir (almacenes);
          system("pause");
          break;
        case 'm':
          registraralmacen (almacenes, numeroalmacen);
          break;
        case 'a':
          if (numeroalmacen!=0){
            printf("\nAlta nuevo paciente:\n");
            tomarcodigoalmacenocupado(almacenes, referenciaalmacenparaguardar);
            funcionesdepacientes.nuevopaciente(almacenes[referenciaalmacenparaguardar-1].pacientes, almacenes[referenciaalmacenparaguardar-1].numeropaciente);
            }
            else {printf("No hay almacenes registrados\n");
            }
          system("pause");
          break;
        case 'u':
          if (numeroalmacen!=0){
            printf("\nLista de pacientes y su ubicacion:\n");
            tomarcodigoalmacenocupado(almacenes, referenciaalmacenparaguardar);
            funcionesdepacientes.imprimirpacientes(almacenes[referenciaalmacenparaguardar-1].pacientes, almacenes[referenciaalmacenparaguardar-1].numeropaciente);
            }
            else {printf("No hay almacenes registrados\n");
            }
          system("pause");
          break;
        case 'n':
          if (numeroalmacen!=0){
            printf("\nNuevo pedido:\n");
            tomarcodigoalmacenocupado(almacenes, referenciaalmacenparaguardar);
            funcionesdepedidos.nuevopedido(almacenes[referenciaalmacenparaguardar-1].pacientes, almacenes[referenciaalmacenparaguardar-1].pedidos,  almacenes[referenciaalmacenparaguardar-1].numeropedido, almacenes[referenciaalmacenparaguardar-1].numeropaciente);
            }
            else {printf("No hay almacenes registrados\n");
            }
          system("pause");
          break;
        case 'l':
          if (numeroalmacen!=0){
            printf("\nLista diaria de pedidos:\n");
            tomarcodigoalmacenocupado(almacenes, referenciaalmacenparaguardar);
            funcionesdepedidos.listadiariadepedidos(almacenes[referenciaalmacenparaguardar-1].pacientes, almacenes[referenciaalmacenparaguardar-1].pedidos, almacenes[referenciaalmacenparaguardar-1].numeropedido,almacenes[referenciaalmacenparaguardar-1].descripcion);
            }
            else {printf("No hay almacenes registrados\n");
            }
          system("pause");
          break;
        case 'p':
          if (numeroalmacen!=0){
            printf("\nRutas:\n");
            tomarcodigoalmacenocupado(almacenes, referenciaalmacenparaguardar);
            programarrutas(almacenes[referenciaalmacenparaguardar-1].pacientes, almacenes[referenciaalmacenparaguardar-1].pedidos, almacenes[referenciaalmacenparaguardar-1].numeropedido );
            }
            else {printf("No hay almacenes registrados\n");
            }
          system("pause");
          break;
        default:
          return 0;
        }
      } while(opciondelmenuprincipal!='s');
    }