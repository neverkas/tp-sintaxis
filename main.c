// gcc -g main.c funciones.c automata.c -o ./bin/automata && ./bin/automata
#include "automata.h"

#include <stdio.h>
#include <string.h> // strcpy, strcmp
#include <stdlib.h> // malloc
#include <ctype.h> // isdigit

int main(){
  /* char* palabra = (char*) malloc(10*sizeof(char)); */

  reconocer_palabra();
  imprimir_resultados();

  return 0;
}
