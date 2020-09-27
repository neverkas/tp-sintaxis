#include <stdio.h>
#include <string.h>

void separar_palabras_por_centinela(char *cadena, int cantidad){
  char palabra[255];

  char *p=cadena;
  int i;
  while(*p!='\0'){
    // vaciamos la palabra
    strcpy(palabra, "");
    while(*p == '#' ){p++;}

    i = 0;
    // guardamos los caracteres de cada palabra delimitada por el centinela
    while(*p!='\0' && *p!='#'){
      palabra[i] = *p;
      i++, p++;
    }
    // le agregamos el fin de cadena
    palabra[i]='\0';

    printf("La palabra es: %s\n", palabra);
  }
}


int main(){
  //char* palabras[] = {"hola","como"};
  //char* otras[4];

  //cantidad_palabras = contarCentinelas(palabra);
  int cantidad;
  char *palabras[cantidad];

  char cadena;
  scanf("%s", &cadena);
  separar_palabras_por_centinela(&cadena, cantidad);

  //printf("y...: %s\n", palabras[0]);

  return 0;
}



  // intento fallido (?)
  /* char palabra_ingresada[] = "hola#como#estas#che#bien"; */
  /* for(int i=0,j=0; palabra_ingresada[i] != '\0'; i++){ */
  /*   if(palabra_ingresada[i] == '#'){ */
  /*     j = 0; */
  /*     printf("%s\n", cadena); */
  /*   } */
  /*   else if(palabra_ingresada[i] != '#'){ */
  /*     cadena[j] = palabra_ingresada[i]; */
  /*     j++; */
  /*   } */
  /* } */
