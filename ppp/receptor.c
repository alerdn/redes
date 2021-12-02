#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void normalizar_input(char **bytes, char ***bytes_normalizados, int qtd_bytes) {
  char *flag = "01111110\0";
  char *escape = "01111101\0";
 
  int i, j;
  for (i = 1, j = 0; i < qtd_bytes; i++) {
    if (strcmp(bytes[i-1], escape) == 0 || strcmp(bytes[i], flag) != 0) {
      /*strcat((*bytes_normalizados)[j], bytes[i]);*/
      printf("%s ",bytes[i]);
      j++;
    } else continue;
  }
  (*bytes_normalizados) = bytes;
}

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
    strcat(msg, " ");
  }

  for (i = 0, j = 0; i < 17; i++, j++) {
    if (i == 8) {
      check[i] = ' ';
      i++;
    }
    check[i] = check_bin[j];
  }
  check[17] = '\0';

  for (i = 0, j = 0; i < 17; i++, j++) {
    if (i == 8) {
      pr[i] = ' ';
      i++;
    }
    pr[i] = protocol[j];
  }
  pr[17] = '\0';

  len = strlen(check) + strlen(address) + strlen(control) + strlen(pr) +
        strlen(msg);

  bytes = (char *)malloc(sizeof(char *) * (len + 11));

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
    strcat(bytes, "00000000");
  }

  printf("bytes %s", bytes);

  tk = strtok(bytes, dem);

  while (tk != NULL) {
    if (count == 1) {
      bytes_soma = tk;
      count = 2;
    } else {
      strcat(bytes_soma, tk);
      count = 1;

      vaiUm = sum(&resp, bytes_soma, vaiUm);
    }

    tk = strtok(NULL, dem);
  }

  if (vaiUm == 1) {
    vaiUm = sum(&resp, byte_um, 0);
  }

  printf("\nresp: %s\n", resp);

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
  char *resp = (char *)malloc(sizeof(char) * 5);

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

char **substring(char **string, int qtd_bytes, int start, int end) {
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

int main() {
  char **bytes, **bytes_normalizados, **data_bin;
  char input[50000], *protocol, pr[16], *check_hex, *check_bin, *data;
  int len, qtd_bytes, i, j;
  int address, control;

  scanf("%s", input);

  len = strlen(input);
  qtd_bytes = len / 8;

  bytes = (char **)malloc(sizeof(char **) * qtd_bytes);

  for (i = 0; i < qtd_bytes; i++) {
    bytes[i] = (char *)malloc(sizeof(char *) * 9);
    for (j = 0; j < 8; j++) {
      bytes[i][j] = input[j + (i * 8)];
    }
    bytes[i][8] = '\0';
  }

  normalizar_input(bytes, &bytes_normalizados, qtd_bytes);

  address = binToDec(bytes_normalizados[0], 8);
  control = binToDec(bytes_normalizados[1], 8);

  strcpy(pr, bytes_normalizados[2]);
  strcat(pr, bytes_normalizados[3]);
  protocol = binToHex(pr);

  data_bin = substring(bytes_normalizados, qtd_bytes, 4, qtd_bytes - 3);
  len = qtd_bytes - 3 - 4 + 1;

  data = (char *)malloc(sizeof(char *) * len);
  for (i = 0; i < len - 1; i++) {
    data[i] = binToDec(data_bin[i], 8);
  }
  data[len] = '\0';

  check_bin = concat(
      substring(bytes_normalizados, qtd_bytes, qtd_bytes - 3, qtd_bytes - 1),
      2);
  check_hex = binToHex(check_bin);

  printf("| PPP Frame 0 control fields |\n");

  printf("Address: %d\nControl: %d\nProtocol: %s\n", address, control,
         protocol);

  printf("Checksum: %s (Binary %s)\n", check_hex, check_bin);

  printf("Data: %s\n", data);

  if (checksum_verify(check_bin, bytes_normalizados[0], bytes_normalizados[1],
                      pr, data_bin, len - 1) == 1)
    printf("Data integrity: ok.\n");
  else
    printf("Data integrity: not ok.\n");

  return 0;
}