#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int binToDec(int *bin, int len);

void binToHex(int *prot, char *protocol);

void concatenar(int *b1, int *b2, int *concat);

int soma(int *b1, int *b2, int *resp, int vaiUm);

int checksum_verify(int bytes_normalizados[30000][8], int *check_concat,
                    int *prot, int campos, int data[30000][8], int index_data);

int equal(int *b1, int *b2);

void normalizar_input(int bytes_normalizados[30][6251][8], int *palavras,
                      int input[30000][8], int qtd_bytes, int *campos);

void print(int bytes_normalizados[30000][8], int campos, int index,
           int palavras);

int main() {
  int len, bytes_normalizados[30][6251][8];
  int bytes[30000][8];
  int qtd_bytes, i, j, palavras = -1, campos[100];
  char input[50000];

  scanf("%s", input);
  len = strlen(input);

  qtd_bytes = len / 8;

  for (i = 0; i < qtd_bytes; i++) {
    for (j = 0; j < 8; j++) {
      if (input[(i * 8) + j] == '0')
        bytes[i][j] = 0;
      else
        bytes[i][j] = 1;
    }
  }

  normalizar_input(bytes_normalizados, &palavras, bytes, qtd_bytes, campos);

  for (i = 0; i < palavras; i++) {
    print(bytes_normalizados[i], campos[i], i, palavras);
  }

  return 0;
}

int binToDec(int *bin, int len) {
  int d2 = 1;
  int dec = 0;

  int i;
  for (i = len - 1; i >= 0; i--) {
    dec += bin[i] * d2;
    d2 *= 2;
  }

  return dec;
}

void binToHex(int *prot, char *protocol) {
  int hex = 0;
  int dec = binToDec(prot, 16);

  int i;
  for (i = 3; i >= 0; i--) {
    hex = dec % 16;
    dec /= 16;

    if (hex >= 10) {
      protocol[i] = hex + 55;
    } else {
      protocol[i] = hex + 48;
    }
  }
}

void concatenar(int *b1, int *b2, int *concat) {
  int i;
  for (i = 0; i < 8; i++) {
    concat[i] = b1[i];
    concat[i + 8] = b2[i];
  }
}

int soma(int *b1, int *b2, int *resp, int vaiUm) {
  int i;

  for (i = 15; i >= 0; i--) {

    int soma = vaiUm + b1[i] + b2[i];

    if (soma == 0) {
      resp[i] = 0;
      vaiUm = 0;
    } else if (soma == 1) {
      resp[i] = 1;
      vaiUm = 0;
    } else if (soma == 2) {
      resp[i] = 0;
      vaiUm = 1;
    } else if (soma == 3) {
      resp[i] = 1;
      vaiUm = 1;
    }
  }

  return vaiUm;
}

int checksum_verify(int bytes_normalizados[30000][8], int *check_concat,
                    int *prot, int campos, int data[30000][8], int index_data) {
  int i;
  int adControl[16];
  int check_aux[16];
  int resp[16];
  int vaiUm = 0;
  int aux_sum[16];
  int concat[16];
  int sum_check_concat[16], aux = 1;

  concatenar(bytes_normalizados[0], bytes_normalizados[1], adControl);

  vaiUm = soma(adControl, prot, resp, vaiUm);

  for (i = 1; i < index_data; i = i + 2) {
    concatenar(data[i - 1], data[i], concat);
    vaiUm = soma(resp, concat, resp, vaiUm);
  }

  soma(resp, check_concat, sum_check_concat, vaiUm);

  for (i = 0; i < 16; i++) {
    if (sum_check_concat[i] != 1)
      aux = 0;
  }

  return aux;
}

int equal(int *b1, int *b2) {
  int isEqual = 1;

  int i = 0;
  while (i < 8) {
    if (b1[i] != b2[i])
      isEqual = 0;
    i++;
  }

  return isEqual;
}

void normalizar_input(int bytes_normalizados[30][6251][8], int *palavras,
                      int input[30000][8], int qtd_bytes, int *campos) {
  int flag[8] = {0, 1, 1, 1, 1, 1, 1, 0};
  int escape[8] = {0, 1, 1, 1, 1, 1, 0, 1};
  int in, j, i;

  (*palavras)++;
  campos[*palavras] = 0;
  in = 1;

  for (i = 1; i < qtd_bytes; i++) {
    if (equal(input[i - 1], escape) == 1 || equal(input[i], flag) == 0) {
      in = 0;
      for (j = 0; j < 8; j++) {
        bytes_normalizados[*palavras][campos[*palavras]][j] = input[i][j];
      }
      campos[*palavras]++;
    } else {
      if (in == 0) {
        (*palavras)++;
        campos[*palavras] = 0;
        in = 1;
      }
    }
  }
}

void print(int bytes_normalizados[30000][8], int campos, int index,
           int palavras) {

  char *protocol, *checksum;
  int i, j, verify_checksum, index_data = 0, address, control;
  int check_concat[16], prot[16], data[30000][8];
  int escape[8] = {0, 1, 1, 1, 1, 1, 0, 1};

  printf("| PPP Frame %d control fields |\n\n", index);

  address = binToDec(bytes_normalizados[0], 8);
  control = binToDec(bytes_normalizados[1], 8);

  concatenar(bytes_normalizados[2], bytes_normalizados[3], prot);
  protocol = (char *)malloc(sizeof(char *) * 4);
  binToHex(prot, protocol);

  printf("Address: %d\n\nControl: %d\n\n", address, control);
  printf("Protocol: ");
  for (i = 0; i < 4; i++)
    printf("%c", protocol[i]);

  concatenar(bytes_normalizados[campos - 2], bytes_normalizados[campos - 1],
             check_concat);
  checksum = (char *)malloc(sizeof(char *) * 16);
  binToHex(check_concat, checksum);

  printf("\n\nChecksum: ");
  for (i = 0; i < 4; i++)
    printf("%c", checksum[i]);
  printf(" (Binary ");
  for (i = 0; i < 16; i++)
    printf("%d", check_concat[i]);
  printf(")");

  /* Filtrando data */
  for (i = 4; i < campos - 2; i++) {
    if (equal(bytes_normalizados[i], escape) == 0) {
      j = 0;
      while (j < 8) {
        data[index_data][j] = bytes_normalizados[i][j];
        j++;
      }
      index_data++;
    } else if (equal(bytes_normalizados[i - 1], escape) == 1) {
      j = 0;
      while (j < 8) {
        data[index_data][j] = bytes_normalizados[i][j];
        j++;
      }
      index_data++;
    }
  }

  if (index_data % 2 != 0) {
    for (i = 0; i < 8; i++)
      data[index_data][i] = 0;
    index_data++;
  }

  printf("\n\nData: ");
  for (i = 0; i < index_data; i++) {
    printf("%c", binToDec(data[i], 8));
  }

  verify_checksum = checksum_verify(bytes_normalizados, check_concat, prot,
                                    campos, data, index_data);

  if (verify_checksum == 1)
    printf("\n\nData integrity: ok.\n");
  else
    printf("\n\nData integrity: not ok.\n");
}