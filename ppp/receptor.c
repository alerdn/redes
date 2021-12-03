#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char sum(char **b1, char *b2, int vaiUm) {
  int i;
  char *resp = (char *)malloc(sizeof(char *) * 16);

  for (i = 15; i >= 0; i--) {

    int soma = vaiUm + (((*b1)[i]) - 48) + ((b2[i]) - 48);

    if (soma == 0) {
      resp[i] = '0';
      vaiUm = 0;
    } else if (soma == 1) {
      resp[i] = '1';
      vaiUm = 0;
    } else if (soma == 2) {
      resp[i] = '0';
      vaiUm = 1;
    } else if (soma == 3) {
      resp[i] = '1';
      vaiUm = 1;
    }
  }

  *b1 = resp;

  return vaiUm;
}

int checksum_verify(char *check_bin, char *address, char *control,
                    char *protocol, char **data_bin, int bytes_msg) {

  char *dem = " ";
  char *resp = "0000000000000000\0";
  char *byte_um = "0000000000000001\0";

  char *bytes_soma = (char *)malloc(sizeof(char *) * 16);
  char *msg = (char *)malloc(sizeof(char *) * bytes_msg * 9);
  char *check = (char *)malloc(sizeof(char *) * 17);
  char *pr = (char *)malloc(sizeof(char *) * 17);

  int len;
  char *bytes;
  char *tk;

  int count = 1;
  int vaiUm = 0;

  int i, j;

  strcpy(msg, "");
  for (i = 0; i < bytes_msg; i++) {
    strcat(msg, data_bin[i]);
    if (i < bytes_msg - 1)
      strcat(msg, " ");
  }

  for (i = 0, j = 0; i < 17; i++, j++) {
    if (i == 8) {
      check[i] = ' ';
      i++;
    }
    check[i] = check_bin[j];
  }

  for (i = 0, j = 0; i < 17; i++, j++) {
    if (i == 8) {
      pr[i] = ' ';
      i++;
    }
    pr[i] = protocol[j];
  }

  len = strlen(check) + strlen(address) + strlen(control) + strlen(pr) +
        strlen(msg);

  bytes = (char *)malloc(sizeof(char *) * (len + 3));

  tk = NULL;

  strcpy(bytes, check);
  strcat(bytes, " ");

  strcat(bytes, address);
  strcat(bytes, " ");

  strcat(bytes, control);
  strcat(bytes, " ");

  strcat(bytes, pr);
  strcat(bytes, " ");

  strcat(bytes, msg);

  if (bytes_msg % 2 != 0) {
    strcat(bytes, " 00000000\0");
  }

  tk = strtok(bytes, dem);

  while (tk != NULL) {
    if (count == 1) {
      strcpy(bytes_soma, tk);
      count = 2;
    } else {
      strcat(bytes_soma, tk);
      count = 1;

      /*printf("\n  %s\n+ %s", resp, bytes_soma);*/
      vaiUm = sum(&resp, bytes_soma, vaiUm);
      /*printf("\n  %s\n", resp);*/
    }

    tk = strtok(NULL, dem);
  }

  if (vaiUm == 1) {
    vaiUm = sum(&resp, byte_um, 0);
  }

  return !strcmp(resp, "1111111111111111");
}

int binToDec(char *bin, int len) {
  int dec = 0;
  int d2 = 1;

  int i;
  for (i = len - 1; i >= 0; i--) {
    dec += (bin[i] - 48) * d2;
    d2 *= 2;
  }

  return dec;
}

char *binToHex(char *bin) {
  char *resp = (char *)malloc(sizeof(char) * 4);

  int dec = binToDec(bin, 16);
  int hex = 0;

  int i;
  for (i = 3; i >= 0; i--) {
    hex = dec % 16;
    dec /= 16;

    if (hex >= 10) {
      resp[i] = hex + 55;
    } else {
      resp[i] = hex + 48;
    }
  }

  return resp;
}

char **substring(char **string, int start, int end) {
  char **resp = (char **)malloc(sizeof(char **) * (end - start));

  int i;
  for (i = start; i < end; i++) {
    resp[i - start] = (char *)malloc(sizeof(char *) * 8);
    strcpy(resp[i - start], string[i]);
  }

  return resp;
}

char *concat(char **bin, int len) {
  char *resp = (char *)malloc(sizeof(char *) * len * 8);
  int i;

  strcpy(resp, "");
  for (i = 0; i < len; i++) {
    strcat(resp, bin[i]);
  }

  return resp;
}

void normalizar_input(char ****bytes_normalizados, int *palavras, char **input,
                      int *qtd_bytes, int *campos) {
  char *flag = "01111110\0";
  char *escape = "01111101\0";
  int in, i, k;

  (*palavras)++;
  campos[*palavras] = 0;
  in = 1;

  for (i = 1, k = 0; i < (*qtd_bytes); i++) {
    if (strcmp(input[i - 1], escape) == 0 || strcmp(input[i], flag) != 0) {
      in = 0;
      strcpy((*bytes_normalizados)[*palavras][campos[*palavras]], input[i]);
      campos[*palavras] = campos[*palavras] + 1;
      k++;
    } else {
      if (in == 0) {
        (*palavras)++;
        campos[*palavras] = 0;
        in = 1;
      }
    }
  }

  *qtd_bytes = k;
}

void print(char **bytes_normalizados, int qtd_bytes, int campos, int index,
           int palavras) {

  int address = binToDec(bytes_normalizados[0], 8);
  int control = binToDec(bytes_normalizados[1], 8);

  char *protocol;
  char **data_bin;
  char *data;
  char *check_bin, *check_hex;
  int len, i, k, check;
  char *pr = (char *)malloc(sizeof(char *) * 16);

  char *escape = "01111101\0";

  strcpy(pr, bytes_normalizados[2]);
  strcat(pr, bytes_normalizados[3]);
  protocol = binToHex(pr);

  data_bin = substring(bytes_normalizados, 4, qtd_bytes - 2);
  len = qtd_bytes - 2 - 4 + 1;

  data = (char *)malloc(sizeof(char *) * len);
  for (i = 0, k = 0; i < len - 1; i++) {
    if (strcmp(data_bin[i], escape) != 0) {
      data[k] = binToDec(data_bin[i], 8);
      k++;
    } else {
      if (strcmp(data_bin[i - 1], escape) == 0) {
        data[k] = binToDec(data_bin[i], 8);
        k++;
      }
    }
  }

  printf("| PPP Frame %d control fields |\n\n", index);
  printf("Address: %d\n\nControl: %d\n\nProtocol: %s\n\n", address, control,
         protocol);

  check_bin = (char *)malloc(sizeof(char *) * 17);
  check_hex = (char *)malloc(sizeof(char *) * 5);

  strcpy(check_bin,
         concat(substring(bytes_normalizados, qtd_bytes - 2, qtd_bytes), 2));
  check_bin[16] = '\0';

  strcpy(check_hex, binToHex(check_bin));
  check_hex[4] = '\0';

  printf("Checksum: %s (Binary %s)\n\n", check_hex, check_bin);

  printf("Data: %s\n\n", data);

  check = checksum_verify(check_bin, bytes_normalizados[0],
                          bytes_normalizados[1], pr, data_bin, len - 1);

  if (index == palavras - 1) {
    if (check == 1)
      printf("Data integrity: ok.\n");
    else
      printf("Data integrity: not ok.\n");
  } else {
    if (check == 1)
      printf("Data integrity: ok.\n\n");
    else
      printf("Data integrity: not ok.\n\n");
  }
}

int main() {
  char **bytes, ***bytes_normalizados;
  char input[50000];
  int len, qtd_bytes, i, j, palavras = -1, campos[100];

  scanf("%s", input);

  len = strlen(input);
  qtd_bytes = len / 8;

  bytes = (char **)malloc(sizeof(char **) * 30000);
  for (i = 0; i < 30000; i++) {
    bytes[i] = (char *)malloc(sizeof(char *) * 9);
  }

  for (i = 0; i < qtd_bytes; i++) {
    for (j = 0; j < 8; j++) {
      bytes[i][j] = input[j + (i * 8)];
    }
    bytes[i][8] = '\0';
  }

  bytes_normalizados = (char ***)malloc(sizeof(char ***) * 30);
  for (i = 0; i < 30; i++) {
    bytes_normalizados[i] = (char **)malloc(sizeof(char **) * 30000);
    for (j = 0; j < 30000; j++) {
      bytes_normalizados[i][j] = (char *)malloc(sizeof(char *) * 9);
    }
  }

  normalizar_input(&bytes_normalizados, &palavras, bytes, &qtd_bytes, campos);

  for (i = 0; i < palavras; i++) {
    print(bytes_normalizados[i], qtd_bytes, campos[i], i, palavras);
  }

  free(bytes);
  free(bytes_normalizados);
  return 0;
}