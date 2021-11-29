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
    printf("hex[%d]: %c\n", i, hex[i]);
    if (hex[i] >= '0' && hex[i] <= '9') {
      dec_val += (hex[i] - 48) * base;
      base = base * 16;
    } else if (hex[i] >= 'A' && hex[i] <= 'F') {
      dec_val += (hex[i] - 55) * base;
      base = base * 16;
    }
  }

  printf("dec_val: %d\n", dec_val);

  for (i = 16; i >= 0; i--) {
    if (i == 8) {
      resp[i] = ' ';
      i--;
    }

    resp[i] = (dec_val % 2) + 48;
    printf("(%d mod 2) + 48: [resp[%d]] %c\n", dec_val, i, resp[i]);
    dec_val /= 2;
  }
  resp[17] = '\0';

  // printf("%s", resp);

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

int *step3(int *msg2) {
  int length = msg2[0] + 1;
  int *msg3 = (int *)malloc(sizeof(int) * length);

  for (int i = 0; i < length; i++) {
    int d = msg2[i];
    int resp = 0;
    int m10 = 1;
    do {
      resp += (d % 2) * m10;
      m10 *= 10;
      d /= 2;
    } while (d != 0);

    msg3[i] = resp;
  }

  return msg3;
}

int main() {
  char flag[9] = "01111110\0";
  char adress[9] = "11111111\0";
  char control[9] = "00000011\0";

  char *hex = (char *)malloc(sizeof(char *) * 4);

  char *msg = step1(hex);
  int *msg2 = step2(msg);
  int *msg3 = step3(msg2);

  char *pr = protocol(hex);
  int i;

  printf("%s ", flag);
  printf("%s ", adress);
  printf("%s ", control);
  printf("%s ", pr);

  // Mensagem
  for (i = 1; i < msg2[0]; i++) {
    printf("%d ", msg3[i]);
  }

  printf("[checksum aqui] ");

  printf("%s ", flag);

  free(hex);
  free(msg);
  free(msg2);
  free(msg3);
  return 0;
}