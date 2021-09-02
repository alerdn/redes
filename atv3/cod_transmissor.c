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

void fourb5b(char *cod, int length, int *msg) {
  char arr[11];
  char part[5];

  char *fourb[16] = {"0000", "0001", "0010", "0011", "0100", "0101",
                     "0110", "0111", "1000", "1001", "1010", "1011",
                     "1100", "1101", "1110", "1111"};

  char *fiveb[16] = {"11110", "01001", "10100", "10101", "01010", "01011",
                     "01110", "01111", "10010", "10011", "10110", "10111",
                     "11010", "11011", "11100", "11101"};

  printf("%s %d ", cod, length * 10);
  for (int i = 1; i <= length; i++) {

    for (int k = 1; k >= 0; k--) {

      for (int j = 3; j >= 0; j--) {

        // Transformando int em char de acordo com a tabela ASCII | 1 => '1'
        part[j] = (msg[i] % 10) + 48;

        msg[i] /= 10;
      }
      part[4] = '\0';

      for (int l = 0; l < 16; l++) {
        if (strcmp(part, fourb[l]) == 0) {

          for (int p = 0; p < 5; p++) {
            arr[(5 * k) + p] = fiveb[l][p];
          }

          break;
        }
      }
    }

    for (int i = 0; i < 10; i++) {
      arr[i] = arr[i] == '1' ? 'A' : 'B';
    }

    printf("%s", arr);
  }
}

int main() {
  char *cod = (char *)malloc(sizeof(char *) * 20);
  char k;
  char *msg = step1(cod, &k);
  int *msg2 = step2(msg);
  int *msg3 = step3(msg2);

  if (strcmp(cod, "NRZ") == 0) {
    nrz(cod, msg2[0], msg3);
  } else if (strcmp(cod, "Manchester") == 0) {
    manchester(cod, k, msg2[0], msg3);
  } else if (strcmp(cod, "4b5b") == 0) {
    fourb5b(cod, msg2[0], msg3);
  }

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