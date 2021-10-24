#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *decToBin(int *oct) {
  int d, i;
  int resp;
  int m10;
  int aux;
  char *retorno = (char *)malloc(sizeof(char *) * 15);
  char *respChar = (char *)malloc(sizeof(char *) * 3);
  char *auxChar = (char *)malloc(sizeof(char *) * 8);

  for (i = 0; i < 4; i++) {

    d = oct[i];
    resp = 0;
    m10 = 1;

    do {
      resp += (d % 2) * m10;
      m10 *= 10;
      d /= 2;
    } while (d != 0);

    sprintf(respChar, "%d", resp);

    aux = 8 - strlen(respChar);
    for (i = 0; i < aux; i++) {
      strcat(auxChar, "0");
    }
    strcat(auxChar, respChar);

    strcat(retorno, auxChar);

    if (i < 7)
      strcat(retorno, " ");

    strcpy(respChar, "");
    strcpy(auxChar, "");
  }

  return retorno;
}

int main() {
  char *ip = (char *)malloc(sizeof(char *) * 80);
  int hosts;
  int octetos[4];
  int oct[4];
  int octHosts;
  char *ptr;
  int i;

  scanf("%s %d", ip, &hosts);

  ptr = strtok(ip, ".");
  for (i = 0; i < 4; i++) {
    octetos[i] = atoi(ptr);
    ptr = strtok(NULL, ".");
  }

  if (hosts <= 255) {
    octHosts = 1;
  } else if (hosts > 255 && hosts <= 65025) {
    octHosts = 2;
  } else if (hosts > 65025 && hosts < 16581375) {
    octHosts = 3;
  }

  /* Endereço informado */
  printf("Endereço informado: ");
  for (i = 0; i < 4; i++) {
    oct[i] = octetos[i];
    printf("%d", oct[i]);
    if (i < 4 - 1)
      printf(".");
  }
  printf(" (%s)\n", decToBin(oct));

  /* Máscara da sub-rede */
  printf("Máscara da sub-rede: ");
  for (i = 0; i < 4; i++) {
    oct[i] = (4 - i) <= octHosts ? 0 : 255;
    printf("%d", oct[i]);
    if (i < 4 - 1)
      printf(".");
  }
  printf(" (%s)\n", decToBin(oct));

  /* Endereço da sub-rede */
  printf("Endereço da sub-rede: ");
  for (i = 0; i < 4; i++) {
    oct[i] = (4 - i) <= octHosts ? 0 : octetos[i];
    printf("%d", oct[i]);
    if (i < 4 - 1)
      printf(".");
  }
  printf(" (%s)\n", decToBin(oct));

  /* End. broadcast da sub-rede */
  printf("End. broadcast da sub-rede: ");
  for (i = 0; i < 4; i++) {
    oct[i] = (4 - i) <= octHosts ? 255 : octetos[i];
    printf("%d", oct[i]);
    if (i < 4 - 1)
      printf(".");
  }
  printf(" (%s)\n", decToBin(oct));

  free(ip);
  return 0;
}