#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *step1(char *cod, char *k, int *len);
int *step2(char *msg, int len);
int *convert(int *msg, int len);
int *step3(int *msg2);

void nrz(char *cod, int length, int *msg) {
  int *msgFinal = convert(msg, length);

  for (int i = 0; i < length; i++) {
    printf("%c", msgFinal[i]);
  }
}

void manchester(char *cod, char k, int length, int *msg) {
  char arr[16];

  printf("%s %c %d ", cod, k, length * 16);
  for (int i = 1; i <= length; i++) {
    for (int j = 16; j > 0; j = j - 2) {

      arr[j - 2] = ((msg[i] % 10) == 1 ? (k == 'A' ? 'B' : 'A')
                                       : (k == 'A' ? 'A' : 'B'));
      k = (k == 'A' ? 'B' : 'A');
      arr[j - 1] = ((msg[i] % 10) == 1 ? (k == 'A' ? 'B' : 'A')
                                       : (k == 'A' ? 'A' : 'B'));
      k = (k == 'A' ? 'B' : 'A');

      msg[i] /= 10;
    }

    for (int i = 0; i < 16; i++) {
      printf("%c", arr[i]);
    }
  }
}

int main() {
  char *cod = (char *)malloc(sizeof(char *) * 20);
  char k;
  int len;

  char *msg = step1(cod, &k, &len);
  int *msg2 = step2(msg, len);

  if (strcmp(cod, "NRZ") == 0) {
    nrz(cod, len, msg2);
  }

  /*if (strcmp(cod, "NRZ") == 0) {
    nrz(cod, msg2[0], msg3);
  } else if (strcmp(cod, "Manchester") == 0) {
    manchester(cod, k, msg2[0], msg3);
  }*/

  printf("\n");

  free(cod);
  free(msg);
  free(msg2);
  return 0;
}

char *step1(char *cod, char *k, int *len) {
  char *msg;

  msg = (char *)malloc(sizeof(char) * 80);
  scanf("%s ", cod);

  if (strcmp(cod, "Manchester") == 0) {
    scanf("%c ", k);
  }

  scanf("%d ", len);

  scanf("%[^\n]s", msg);

  return msg;
}

int *step2(char *msg, int len) {
  int *msg2 = (int *)malloc(sizeof(int) * (len + 1));
  int num = 0;
  int d10;

  int i;
  for (i = 0; i < len / 8; i++) {
    num = 0;
    d10 = 10000000;
    for (int j = 0; j < 8; j++) {
      num += msg[(i * 8) + j] == 'A' ? 1 * d10 : 0;
      d10 /= 10;
    }

    msg2[i] = num;
  }

  return msg2;
}

int *convert(int *msg, int len) {
  int j;
  int d2;
  int num;
  int nTemp;

  num = 0;
  d2 = 1;

  for (j = 0; j < len; j++) {
    num = 0;
    d2 = 1;
    nTemp = msg[j];

    do {
      num += (nTemp % 10) * d2;
      d2 *= 2;
      nTemp /= 10;
    } while (nTemp > 0);

    msg[j] = num;
  }

  return msg;
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