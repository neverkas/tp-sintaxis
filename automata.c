#ifndef AUTOMATA
#define AUTOMATA
#include "globales.h"
#include "tipos.h"
#include "funciones.h"
#include "automata.h"

#include <stdio.h>
#include <string.h> // strcpy, strcmp
#include <stdlib.h> // malloc
#include <ctype.h> // malloc

int estado_actual = ESTADO_INICIAL;
char palabra[MAX_LONGITUD_PALABRA] = "";
int longitud_palabra = 0;

Transicion *transiciones;

const int estados_finales[2] = {2,4};
const int TABLA_DE_TRANSICION[6][4] = {
  {1,5,5,5}, // ESTADO_0 (ESTADO INICIAL)
  {3,2,5,4}, // ESTADO_1
  {4,5,4,5}, // ESTADO_2 (ESTADO DE ACEPTACIÓN/FINAL)
  {3,5,5,4}, // ESTADO_3
  {5,5,5,5}, // ESTADO_4 (ESTADO DE ACEPTACIÓN/FINAL)
  {5,5,5,5}, // ESTADO_5 (ESTADO DE RECHAZO)
};

static void imprimir_traza_transiciones(char palabra[]){
  char caracter = palabra[0];
  int posicionUltimoCaracter = strlen(palabra)-1;

  printf("Traza de Transiciones: ");

  for(int i=0; i < longitud_palabra; i++){
    imprimirTransicion(transiciones[i]);

    if(i < posicionUltimoCaracter)
      printf(", ");
  }

  printf("\n");
}

static void mensaje(){
  printf("Observaciones generales:\n");
  printf("1. La (ER) Expresión Regular precargada es: %s\n", EXPRESION_REGULAR);
  printf("2. El alfabeto es: {%s}\n", ALFABETO);
  printf("3. La Tabla de transición a utilizar será la siguiente\n");

  imprimir_tabla_transicion();
}

static void imprimir_tabla_transicion(){
  char tipo_de_estado;

  for(int i=0; i < CANTIDAD_ESTADOS; i++){
    for(int j=0; j < TABLA_TRANSICION_COLUMNAS; j++){
      if(j==0){
        if(i == 0) tipo_de_estado = '-';
        else if(es_estado_final(i)) tipo_de_estado = '+';
        else tipo_de_estado =' ';

        printf("%cq%d | ", tipo_de_estado,i);
      }
      printf("%d ", TABLA_DE_TRANSICION[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

void iniciar_automata(){
  mensaje();
  confirmar_evaluar_cadena();
}

static boolean es_estado_final(int estado){
  boolean es_final = false;

  for(int i=0; i < CANTIDAD_ESTADOS_FINALES;i++){
    if (estados_finales[i] != estado) continue;
    es_final = true;
  }

  return es_final;
}

static void reconocer_palabra(char* palabra){
  estado_actual = ESTADO_INICIAL;
  int numero_de_paso = 1;
  int estado_anterior = 0;
  char caracter_leido;

  longitud_palabra = strlen(palabra);
  transiciones = (Transicion*) malloc(longitud_palabra * sizeof(Transicion));

  for(int i=0, numero_de_paso=2; palabra[i] != '\0'; i++, numero_de_paso++){
    caracter_leido = palabra[i];
    estado_anterior = estado_actual;
    estado_actual = transicion(palabra[i], estado_actual);

    Transicion t = crearTransicion(estado_anterior, estado_actual, caracter_leido);
    agregarTransicion(i, t, transiciones);
  }

  printf("Palabra Evaluada: %s\n", palabra);
  printf("La palabra forma parte del lenguaje: %s\n",
         es_estado_final(estado_actual) ? "SI" : "NO");

  imprimir_traza_transiciones(palabra);

  printf("\n");
}

static void agregarTransicion(int Numero, Transicion t, Transicion* transiciones){
  transiciones[Numero] = t;
}

static void imprimirTransicion(Transicion t){
  // determinamos que tipo de estado son
  // son unicamente para la parte visual
  char tipo_de_estado_origen = (t.estado_origen == 0) ? '-' : ' ';
  char tipo_de_estado_destino = (es_estado_final(t.estado_destino)) ? '+' : ' ';

  printf("%cq%d", tipo_de_estado_origen,t.estado_origen);
  printf("=>%c=>", t.caracter);
  printf("%cq%d", tipo_de_estado_destino, t.estado_destino);

  /* printf("q%d=>%c=>q%d", t.estado_origen, t.caracter, t.estado_destino); */
}

static Transicion crearTransicion(int origen, int destino, char caracter){
  Transicion t;
  t.estado_origen = origen;
  t.estado_destino = destino;
  t.caracter = caracter;

  return t;
}

// retorna el siguiente estado
static int transicion(char caracterLeido, int estadoOrigen){
  int estadoDestino;
  int estadoOk = false;

  for(int columna=0; columna <= TABLA_TRANSICION_COLUMNAS; columna++){
    // si la transición tiene un estado de rechazo,
    // entonces saltamos a la siguiente iteración del for (lo que le siga no será evaluado)
    if(TABLA_DE_TRANSICION[estadoOrigen][columna] == ESTADO_RECHAZO){
      continue;
    }

    if(columnaCaracter(columna, caracterLeido)){
      estadoOk = true;
      estadoDestino = TABLA_DE_TRANSICION[estadoOrigen][columna];
      break;
    }
  }

  // utilizamos el operador ternario
  return (estadoOk) ? estadoDestino : ESTADO_RECHAZO;
}

// utilizamos una estructura switch para representar aquellas columnas
// de la tabla de transición que repitan algún patrón
//
// Observación: Esto no es un impedimento para la matriz, trabajan en conjunto.
static boolean columnaCaracter(int columna_tabla_transicion, char caracterLeido){
  switch(columna_tabla_transicion){
  case 0: // Columna 1
    return estaEntreLosNumeros(0, 1, caracterLeido);
    break;
  case 1: // columna 2
      return esElCaracter('.', caracterLeido);
      break;
  case 2: // columna 3
      return estaEntreLosNumeros(2, 9, caracterLeido);
      break;
  case 3: // columna 4
      return esElCaracter('B', caracterLeido);
      break;
  default: // estado de rechazo
    return false;
    break;
  }
}

void confirmar_evaluar_cadena(){
  char cadena[255];
  char confirmacion;

  solicitar_evaluar_cadena(cadena);

  // se podria haber utilizado un centinela
  // pero se optó utilizar la palabra reservada break
  // para detener la iteración
  while(1){
    printf("Desea ingresar otra cadena? (s/n)\n");
    scanf("%s", &confirmacion);
    // limpiamos el buffer de entrada
    fflush(stdin);

    if(confirmacion == 'n' || confirmacion == 'N') break;
    else if(confirmacion == 's' || confirmacion == 'S'){
      solicitar_evaluar_cadena(cadena);
    }
  }
}

void solicitar_evaluar_cadena(char *cadena){
  printf("Ingrese la cadena a evaluar: ");
  scanf("%s", cadena);
  // limpiamos el buffer de entrada
  fflush(stdin);

  printf("palabra ingresada: %s\n", cadena);
  // analizamos si no es una palabra vacia
  if(cadena[0] != '\0'){
    evaluar_cadena(cadena);
  }
}

void evaluar_cadena(char *cadena){
  char *p = cadena; // por comodidad en el código que sigue, hacemos que apunte a p
  char palabra[MAX_LONGITUD_PALABRA];
  int cantidad_palabras = 0;
  char *palabras[MAX_CANTIDAD_PALABRAS];

  // cambiamos el centinela por un espacio para representar que no se ingresó nada
  if(cadena[0] == '#') cadena[0] = ' ';

  int i, j=0, longitud_palabra;
  // aumentamos la cantidad de elementos que soporta nuestro
  // puntero a cadena caracteres
  while(*p == '#' ) cantidad_palabras++;

  while(*p!='\0'){
    // vaciamos la palabra
    strcpy(palabra, "");
    // si es un centinela, avanzo
    // j: numero de palabra (se usará como indice para el arreglo de cadena de caracteres)
    while(*p == '#' ) j++, cantidad_palabras++, p++;

    // inicializo
    i = 0;
    // guardamos los caracteres de cada palabra delimitada por el centinela
    // - mientras el caracter al que apunta el puntero no es final de linea
    // - ni tampoco sea el centinela
    while(*p!='\0' && *p!='#'){
      // concatenamos en una cadena de caracteres,
      // cada caracter al que apunta el puntero
      palabra[i] = *p;
      // i: lo usamos como indice del arreglo de caracteres, donde se guardará
      // p: avanzamos al siguiente caracter al que apunta
      i++, p++;
    }

    // - le agregamos el fin de cadena como cualquier cadena de caracter
    palabra[i]='\0';
    // calculamos la longitud para determinar el espacio en memoria que ocupará
    longitud_palabra = strlen(palabra);
    /* printf("palabra:%s, longitud:%d\n", palabra, longitud_palabra); */
    // reservamos memoria por cada cadena que vayamos a agregar
    palabras[j] = (char*) malloc(longitud_palabra*sizeof(char));
    // copiamos la cadena de caracteres
    strcpy(palabras[j], palabra);
  }

  for(int i=0; i < cantidad_palabras;i++){
    // empieza el proceso de evaluación
    // palabra por palabra utilizando la tabla de transición
    reconocer_palabra(palabras[i]);
  }
}

#endif
