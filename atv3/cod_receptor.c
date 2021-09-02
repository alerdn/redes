#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *step1(char *cod, char *k, int *len);
int *step2(char *msg, char k, int len);
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
  int *msg2 = step2(msg, k, len);

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

int *step2(char *msg, char k, int len) {
  int *msg2 = (int *)malloc(sizeof(int) * (len + 1));
  int num = 0;
  int d10;
  int pos;

  // Quer dizer que é Manchester
  if (k == 'A' || k == 'B') {
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
  } else {
    for (int i = 0; i < len / 8; i++) {
      num = 0;
      d10 = 10000000;
      for (int j = 0; j < 8; j++) {
        num += msg[(i * 8) + j] == 'A' ? 1 * d10 : 0;
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