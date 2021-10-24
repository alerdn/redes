#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char *decToBin(int *oct) {
  int d, i, j;
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
    for (j = 0; j < aux; j++) {
      strcat(auxChar, "0");
    }
    strcat(auxChar, respChar);

    strcat(retorno, auxChar);

    if (i < 3) {
      strcat(retorno, " ");
    }

    strcpy(respChar, "");
    strcpy(auxChar, "");
  }

  return retorno;
}

int convertBit(bit, x) {
  int result = 0;
  int i;
  for (i = 0; i < x; i++) {
    result += pow(2, i);
  }

  return result;
}

int main() {
  char *ip = (char *)malloc(sizeof(char *) * 80);
  int hosts;
  int octetos[4];
  int oct[4];
  int octHosts;
  char *ptr;
  int i, j;

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

  for (j = 8*(octHosts-1); j < octHosts * 8; j++) {
    if (pow(2, j) > hosts) break;
  }
  j -= 8*(octHosts-1);
  printf("j: %d\n", j);

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
    oct[4 - octHosts] = 255 - convertBit(2, j);
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
    oct[4 - octHosts] = convertBit(2, j);
    printf("%d", oct[i]);
    if (i < 4 - 1)
      printf(".");
  }
  printf(" (%s)\n", decToBin(oct));

  free(ip);
  return 0;
}