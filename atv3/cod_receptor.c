#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *step1(char *cod, char *k, int *len);
int *step2(char *msg, char *cod, char k, int len);
int *convert(int *msg, int len);
int *step3(int *msg2);

void show(char *cod, int length, int *msg) {
  int *msgFinal = convert(msg, length);

  for (int i = 0; i < length; i++) {
    printf("%c", msgFinal[i]);
  }
}

int main() {
  char *cod = (char *)malloc(sizeof(char *) * 20);
  char k;
  int len;

  char *msg = step1(cod, &k, &len);
  int *msg2 = step2(msg, cod, k, len);

  show(cod, len, msg2);

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

int *step2(char *msg, char *cod, char k, int len) {
  int *msg2 = (int *)malloc(sizeof(int) * (len + 1));
  int num = 0;
  int d10;
  int pos;
  char part[6];
  char arr[8];

  if (strcmp(cod, "Manchester") == 0) {
    for (int i = 0; i < len / 16; i++) {
      num = 0;
      d10 = 10000000;
      for (int j = 0; j < 16; j++) {
        pos = (i * 16) + j;

        if (pos % 2 == 0) {
          num += (msg[pos] == 'A' ? (k == 'A' ? 0 : 1 * d10)
                                  : (k == 'A' ? d10 : 0));
          d10 /= 10;
        }
      }
      printf("n: %d\n", num);
      msg2[i] = num;
    }
  } else if (strcmp(cod, "NRZ") == 0) {
    for (int i = 0; i < len / 8; i++) {
      num = 0;
      d10 = 10000000;
      for (int j = 0; j < 8; j++) {
        num += msg[(i * 8) + j] == 'A' ? 1 * d10 : 0;
        d10 /= 10;
      }
      msg2[i] = num;
    }
  } else if (strcmp(cod, "4b5b") == 0) {
    char *fourb[16] = {"0000", "0001", "0010", "0011", "0100", "0101",
                       "0110", "0111", "1000", "1001", "1010", "1011",
                       "1100", "1101", "1110", "1111"};

    char *fiveb[16] = {"11110", "01001", "10100", "10101", "01010", "01011",
                       "01110", "01111", "10010", "10011", "10110", "10111",
                       "11010", "11011", "11100", "11101"};

    for (int i = 0; i < len / 10; i++) {
      num = 0;
      d10 = 10000000;

      for (int k = 0; k < 2; k++) {

        for (int j = 0; j < 5; j++) {
          part[j] = msg[(i * 10) + (k * 5) + j] == 'A' ? '1' : '0';
        }
        part[5] = '\0';
        
        for (int l = 0; l < 16; l++) {
          if (strcmp(part, fiveb[l]) == 0) {
            
            //printf("%s => %s\n", part, fourb[l]);
            for (int p = 0; p < 4; p++) {
              arr[(4 * k) + p] = fourb[l][p];
            }

            break;
          }
        }
      }

      for (int j = 0; j < 8; j++) {
        num += arr[j] == '1' ? d10 : 0;
        d10 /= 10;
      }
      msg2[i] = num;
    }
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