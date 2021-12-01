#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *protocol(char *hex) {
  int len = strlen(hex);
  int base = 1;
  int dec_val = 0;
  char *resp = (char *)malloc(sizeof(char) * 18);

  int i;
  for (i = len - 1; i >= 0; i--) {
    if (hex[i] >= '0' && hex[i] <= '9') {
      dec_val += (hex[i] - 48) * base;
      base = base * 16;
    } else if (hex[i] >= 'A' && hex[i] <= 'F') {
      dec_val += (hex[i] - 55) * base;
      base = base * 16;
    }
  }

  for (i = 16; i >= 0; i--) {
    if (i == 8) {
      resp[i] = ' ';
      i--;
    }

    resp[i] = (dec_val % 2) + 48;
    dec_val /= 2;
  }
  resp[17] = '\0';

  return resp;
}

char *step1(char *p) {
  char *msg;

  msg = (char *)malloc(sizeof(char) * 1500);
  scanf("%s ", p);

  scanf("%[^\n]s", msg);

  return msg;
}

int *step2(char *msg) {
  int length = strlen(msg);
  int *msg2 = (int *)malloc(sizeof(int) * (length + 1));

  int i;
  msg2[0] = length;
  for (i = 0; i < length; i++) {
    msg2[i + 1] = msg[i];
  }

  return msg2;
}

char *step3(int *msg2) {
  int length = msg2[0]+1;
  char *msg3 = (char *)malloc(sizeof(char *) * length * 9);
  char *byte = (char *)malloc(sizeof(char *) * 9);
  int i, j;

  for (i = 1; i < length; i++) {
    int d = msg2[i];

    for (j = 7; j >= 0; j--) {
      byte[j] = (d % 2) + 48;
      d /= 2;
    }
    byte[8] = '\0';

    strcat(msg3, byte);
    strcat(msg3, " ");
  }

  return msg3;
}

void payload_corrigido(char *msg) {
  char *dem = " ";
  char *flag = "01111110\0";
  char *escape = "01111101\0";
  char *tk = NULL;

  char *cpy = (char *)malloc(sizeof(char *) * strlen(msg));
  strcpy(cpy, msg);

  tk = strtok(cpy, dem);

  while (tk != NULL) {
    if (strcmp(tk, flag) == 0) {
      printf("%s %s ", escape, tk);
    } else if (strcmp(tk, escape) == 0) {
      printf("%s %s ", escape, tk);
    } else {
      printf("%s ", tk);
    }

    tk = strtok(NULL, dem);
  }
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

void complemento(char *resp) {
  int i;
  for (i = 0; i < 16; i++) {
    if (i == 8)
      printf(" ");
    printf(resp[i] == '1' ? "0" : "1");
  }
  printf(" ");
}

void checksum(char *address, char *control, char *protocol, char *msg,
              int bytes_msg) {
  char *dem = " ";
  char *resp = "0000000000000000\0";
  char *byte_um = "0000000000000001\0";

  char *bytes_soma = (char *)malloc(sizeof(char *) * 16);

  int len = strlen(address) + strlen(control) + strlen(protocol) + strlen(msg);

  /* +3 espaços em branco; +8 para zeros ao fim, se precisar. */
  char *bytes = (char *)malloc(sizeof(char *) * (len + 11));

  char *tk = NULL;
  int count = 1;
  int vaiUm = 0;

  strcpy(bytes, address);
  strcat(bytes, " ");

  strcat(bytes, control);
  strcat(bytes, " ");

  strcat(bytes, protocol);
  strcat(bytes, " ");

  strcat(bytes, msg);

  if (bytes_msg % 2 != 0) {
    strcat(bytes, "00000000");
  }

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

  complemento(resp);
}

int main() {
  char flag[9] = "01111110\0";
  char address[9] = "11111111\0";
  char control[9] = "00000011\0";

  char *hex = (char *)malloc(sizeof(char *) * 4);

  char *msg = step1(hex);
  int *msg2 = step2(msg);
  char *msg3 = step3(msg2);

  char *pr = protocol(hex);

  printf("%s ", flag);
  printf("%s ", address);
  printf("%s ", control);
  printf("%s ", pr);

  /* Mensagem */
  payload_corrigido(msg3);

  checksum(address, control, pr, msg3, msg2[0]);

  printf("%s", flag);

  free(hex);
  free(msg);
  free(msg2);
  free(msg3);
  return 0;
}