#ifndef AUTOMATA
#define AUTOMATA

#include "globales.h"
#include "tipos.h"
#include "funciones.h"
#include "automata.h"

#include <stdio.h>

extern int TABLA_DE_TRANSICION[6][4] = {
  {1,5,5,5}, // ESTADO_0
  {3,2,5,4}, // ESTADO_1
  {4,5,4,5}, // ESTADO_2
  {3,5,5,4}, // ESTADO_3
  {5,5,5,5}, // ESTADO_4
  {5,5,5,5}, // ESTADO_5
};

void imprimir_resultados(){
  printf("estado_actual: %d\n", estado_actual);

  if(estado_actual == 4 || estado_actual == 2){
    printf("La palabra forma parte del lenguaje\n");
  }else{
    printf("La palabra NO pertenece al lenguaje\n");
  }
}

void reconocer_palabra(){
  // agregar scanf
  // y que si tiene una por defecto que no haga scanf (?)
  char* palabra = "0.";

  for(int i=0; palabra[i] != '\0'; i++){
    estado_actual = transicion(palabra[i], estado_actual);
    printf("estado_actual: %d, caracter:%c, \n", estado_actual, palabra[i]);
  }
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