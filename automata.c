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

int estados_finales[2] = {2,4};

int TABLA_DE_TRANSICION[6][4] = {
  {1,5,5,5}, // ESTADO_0
  {3,2,5,4}, // ESTADO_1
  {4,5,4,5}, // ESTADO_2
  {3,5,5,4}, // ESTADO_3
  {5,5,5,5}, // ESTADO_4
  {5,5,5,5}, // ESTADO_5
};

static void imprimir_resultados(){
  printf("Palabra Analizada: %s \n", palabra);
  imprimir_derivacion(palabra);
  printf("Longitud de la Palabra: %d\n", strlen(palabra));
  printf("La palabra forma parte del lenguaje: %s\n",
         es_estado_final(estado_actual) ? "SI" : "NO");
}

static void imprimir_derivacion(char palabra[]){
  char caracter = palabra[0];
  int posicionUltimoCaracter = strlen(palabra)-1;

  printf("Derivación:\n");
  for(int posicion=0; caracter != '\0'; posicion++){
    // alternativa usando strlen()
    /* for(int posicion=0; posicion < strlen(palabra) ; posicion++){ */
    caracter=palabra[posicion];

    if(isprint(caracter)){
      printf("%c", caracter);

      if(posicion < posicionUltimoCaracter)
        printf(" => ");
    }
  }
  printf("\n");
}

static void mensaje(){
  printf("Observaciones generales:\n");
  printf("1. La (ER) Expresión Regular precargada es: [01]\\.[0-9]? | [01]+B\n");
  printf("2. El alfabeto es: {%s}\n", ALFABETO);
  printf("3. La Tabla de transición a utilizar será la siguiente\n");
  imprimir_tabla_transicion();
}

/* int estados_finales[2] = {2,4}; */
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
  char palabra_ingresada;

  mensaje();
  reconocer_palabra();
  imprimir_resultados();

  // alternativa: en vez del while(1) podria utilizar un centinela
  while(1){
    printf("Desea ingresar otra palabra? (s/n)\n");

    scanf("%c", &palabra_ingresada);
    fflush(stdin);

    if(palabra_ingresada == 's' || palabra_ingresada == 'S'){
      printf("\n----------------------------------------------------\n\n");

      estado_actual = ESTADO_INICIAL;

      reconocer_palabra();
      imprimir_resultados();
    }
    else if(palabra_ingresada =='n' || palabra_ingresada == 'N'){
      break;
    }
  }
}

static boolean es_estado_final(int estado){
  boolean es_final = false;

  for(int i=0; i < CANTIDAD_ESTADOS_FINALES;i++){
    if (estados_finales[i] != estado) continue;
    es_final = true;
  }

  return es_final;
}

static void reconocer_palabra(){
  int numero_de_paso = 1;

  printf("Ingrese una palabra a analizar: ");
  scanf("%s", &palabra);
  fflush(stdin);

  printf("\n");
  printf("Analisis:\n");
  printf("%d. Estado actual: %d, \n", numero_de_paso, estado_actual);
  for(int i=0, numero_de_paso=2; palabra[i] != '\0'; i++, numero_de_paso++){
    estado_actual = transicion(palabra[i], estado_actual);
    printf("%d. Estado actual: %d, Caracter analizado:%c, \n", numero_de_paso, estado_actual, palabra[i]);
  }
  printf("\n");
}

// retorna el siguiente estado
static int transicion(char caracterLeido, int estadoOrigen){
  int estadoDestino;
  int estadoOk = false;

  for(int columna=0; columna <= TABLA_TRANSICION_COLUMNAS; columna++){
    // si la transición tiene un estado de rechazo,
    // entonces saltamos a la siguiente iteración del for (lo que le siga no será evaluado)
    // creo que habría que mejorar el concepto de RECHAZO (?)
    if(TABLA_DE_TRANSICION[estadoOrigen][columna] == ESTADO_RECHAZO){
      continue;
    }

    if(columnaCaracter(columna, caracterLeido)){
      estadoOk = true;
      estadoDestino = TABLA_DE_TRANSICION[estadoOrigen][columna];
      break;
    }
  }

  if(estadoOk)
    return estadoDestino;
  else
    return ESTADO_RECHAZO;
}

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

#endif
