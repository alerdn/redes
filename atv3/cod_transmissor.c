#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *step1(char *cod, char *k);
int *step2(char *msg);
int *step3(int *msg2);

void nrz(char *cod, int length, int *msg) {
  char arr[8];

  printf("%s %d ", cod, length * 8);
  for (int i = 1; i <= length; i++) {
    for (int j = 7; j >= 0; j--) {
      arr[j] = (msg[i] % 10) == 1 ? 'A' : 'B';
      msg[i] /= 10;
    }

    printf("%s", arr);
  }
}

void manchester(char *cod, char k, int length, int *msg) {
  char arr[16];

  printf("%s %c %d ", cod, k, length * 16);
  for (int i = 1; i <= length; i++) {
    for (int j = 15; j >= 0; j--) {

      arr[j] = ((msg[i] % 10) == 1 ? 'A' : (k == 'A' ? 'A' : 'B'));
      k = (k == 'A' ? 'B' : 'A');
      //k = (k == 'A' ? 'B' : 'A');

      msg[i] /= 10;
      printf("%d\n", j);
    }

    printf("%s\n", arr);
  }
}

int main() {
  char *cod = (char *)malloc(sizeof(char *) * 20);
  char k;
  char *msg = step1(cod, &k);
  int *msg2 = step2(msg);
  int *msg3 = step3(msg2);

  printf("c: %s\nk: %c\n", cod, k);

  if (strcmp(cod, "NRZ") == 0) {
    nrz(cod, msg2[0], msg3);
  } else if (strcmp(cod, "Manchester") == 0) {
    manchester(cod, k, msg2[0], msg3);
  }

  printf("\n");

  free(cod);
  free(msg);
  free(msg2);
  free(msg3);
  return 0;
}

char *step1(char *cod, char *k) {
  char *msg;

  msg = (char *)malloc(sizeof(char) * 80);
  scanf("%s ", cod);

  if (strcmp(cod, "Manchester") == 0) {
    scanf("%c ", k);
  }

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

  int i = 0;
  for (i; i < length; i++) {
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