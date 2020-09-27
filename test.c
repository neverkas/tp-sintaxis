#include <stdio.h>
#include <string.h>

int main(){
  char cadena[];
  char caracter;

  char palabra_ingresada[] = "hola#como#estas#che#bien";

  /* for(int i=0, j=0; palabra_ingresada[i] != '\0'; i++,j++){ */
  for(int i=0, j=0; i< strlen(palabra_ingresada); i++,j++){
    if(palabra_ingresada[i] == '#'){
      j=0;
    }
    else{
      //cadena[j] = palabra_ingresada[i];
    }

  }

  return 0;
}
