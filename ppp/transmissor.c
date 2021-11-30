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
  int length = msg2[0] + 1;
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
  char flag[9] = "01111110\0";
  char escape[9] = "01111101\0";

  char *cpy = (char*)malloc(sizeof(char*)*strlen(msg));
  strcpy(cpy, msg);

  char *tk = strtok(cpy, dem);

  while (tk != NULL) {
    if(strcmp(tk, flag) == 0) {
      printf("%s %s", escape, tk); 
    } else if (strcmp(tk, escape) == 0) { 
      printf("%s %s", escape, tk); 
    } else {
       printf("%s ", tk); 
    }

    tk = strtok(NULL, dem);
  }
}

int convert(char *msg) {
  char *dem = " ";
  char *tk = strtok(msg, dem);

  int dec = 0;

  while (tk != NULL) {
    int d2 = 1;
    int num = 0;

    int i;
    for (i = 7; i >= 0; i--) {
      num += (tk[i] - 48) * d2;
      d2 *= 2;
    }

    dec += num;

    tk = strtok(NULL, dem);
  }

  return dec;
}

void checksum(char *address, char *control, char *protocol, char *msg, int bytes_msg) {
  char *dem = " ";
  char *bytes_soma = (char*)malloc(sizeof(char*) * 16);
  int len =  strlen(address) + strlen(control) + strlen(protocol) + strlen(msg);
  
  // +3 espaços em branco; +8 para zeros ao fim, se precisar.
  char *bytes = (char*)malloc(sizeof(char*) * (len + 11));

  strcpy(bytes, address);
  strcat(bytes, " ");

  strcat(bytes, control);
  strcat(bytes, " ");

  strcat(bytes, protocol);
  strcat(bytes, " ");

  strcat(bytes, msg);

  printf("bytes msg: %d\n", bytes_msg);
  if (bytes_msg % 2 != 0) {
    strcat(bytes, "00000000");
  }

  printf("%s\n", bytes);

  char *tk = strtok(bytes, dem);
  int count = 1;

  while (tk != NULL) {
    if (count % 2 != 0) {
      bytes_soma = tk;
      count++;
    } else {
      strcat(bytes_soma, tk);
      count--;

      printf("bytes soma: %s\n", bytes_soma);
    }

    tk = strtok(NULL, dem);
  }
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

  // Mensagem  
  payload_corrigido(msg3);

  printf("[checksum aqui] ");

  printf("%s ", flag);

  printf("\n\n");
  checksum(address, control, pr, msg3, msg2[0]);

  free(hex);
  free(msg);
  free(msg2);
  free(msg3);
  return 0;
}