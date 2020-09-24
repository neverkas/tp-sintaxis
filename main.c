// gcc -g main.c automata.c -o main && ./main
#include <stdio.h>
#include <string.h> // strcpy, strcmp
#include <stdlib.h> // malloc
#include <ctype.h> // isdigit

#include "estructuras.h"
#include "globales.h"
#include "funciones.h"
#include "automata.h"

int main(){
  Automata automata;
  /* char* palabra = (char*) malloc(10*sizeof(char)); */

  int TABLA_DE_TRANSICION[6][4] = {
    {1,5,5,5}, // ESTADO_0
    {3,2,5,4}, // ESTADO_1
    {4,5,4,5}, // ESTADO_2
    {3,5,5,4}, // ESTADO_3
    {5,5,5,5}, // ESTADO_4
    {5,5,5,5}, // ESTADO_5
  };

  int estado_actual = ESTADO_INICIAL; // 0
  printf("estado_actual: %d\n", estado_actual);

  /* estado_actual = 1; */
  char* palabra = "0.";
  for(int i=0; palabra[i] != '\0'; i++){
    // for(int i=0; estado_actual != 6 || estado_actual != 4 || estado_actual != 2; i++){
    estado_actual = transicion(palabra[i], estado_actual);
    printf("estado_actual: %d, caracter:%c, \n",
           estado_actual, palabra[i]);
  }

  /* if(estado_actual != ESTADO_RECHAZO && estado_actual == 4 && estado_actual == 2){ */
  if(estado_actual == 4 || estado_actual == 2){
    printf("La palabra forma parte del lenguaje\n");
  }else{
    printf("La palabra NO pertenece al lenguaje\n");
  }

  /* estado_actual = transicion(palabra[0], estado_actual); */

  /* for(int posicion=0; palabra[posicion] != '\0'; posicion++){ */
  /*   transicion(ESTADO_0) */
  /* } */

  /* automata.estado = INICIAL; */
  /* automata.cantidad_estados = 6; */
  /* automata.alfabeto = (char*) malloc(12*sizeof(char)); */

  /* strcpy(automata.alfabeto, "0123456789.B"); */
  /* /\* inicializarAutomata(automata); *\/ */

  /* if(estaEntreLosNumeros(0,10, palabra[1])){ */
  /*   printf("numero:%d\n", char_to_int(palabra[1])); */
  /* } */
  /* if(esElCaracter('h', palabra[2])){ */
  /*   printf("caracter:%c\n", palabra[2]); */
  /* } */

  /* inicializarTablaTransicion(automata); */
  /* printf("%s\n", automata.palabra); */

  /* printf("cardinalidad:%d\n", strlen(automata.alfabeto)); */
  /* printf("estado: %d\n", automata.estado); */

  return 0;
}
