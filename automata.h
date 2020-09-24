#ifndef AUTOMATA_H
#define AUTOMATA_H

#include "tipos.h"

typedef enum{
  INICIAL=0,FINAL=5,RECHAZO=6, ACEPTACION
} Estado;

typedef struct{
  int estado_origen;
  int estado_destino;
  char caracter_leido;
} Transicion;

typedef struct{
  Estado estado;
  char caracter_leido;
  int cantidad_estados;
  char *alfabeto;
  /* int tabla_transicion[6][4]; // matriz[][] */
} Automata;

static boolean columnaCaracter(int columna_tabla_transicion, char caracterLeido);

void imprimir_resultados();
void reconocer_palabra();
static int transicion(char caracterLeido, int estadoOrigen);

#endif
