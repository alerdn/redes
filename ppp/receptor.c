#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void normalizar_input(char **bytes, char ***bytes_normalizados) {
  (*bytes_normalizados) = bytes;
}

int checksum_verify(char *check_bin) { return 0; }

int main() {
  char **bytes, **bytes_normalizados;
  char input[50000], *protocol, *checksum, *check_bin, *data;
  int len, qtd_bytes, i, j;
  int address, control;

  printf("input: ");
  scanf("%s", input);
  printf("\n");

  len = strlen(input);
  qtd_bytes = len / 8;

  bytes = (char **)malloc(sizeof(char **) * qtd_bytes);

  for (i = 0; i < qtd_bytes; i++) {
    bytes[i] = (char *)malloc(sizeof(char *) * 8);
    for (j = 0; j < 8; j++) {
      bytes[i][j] = input[j + (i * 8)];
    }
  }

  normalizar_input(bytes, &bytes_normalizados);

  address = 200;
  control = 3;
  protocol = "C021";

  checksum = "CDSA";
  check_bin = "0001011100001111";

  data = "Redes";

  /* vvv Suponhamos que os dados já foram normalizados vvv */

  printf("Dados normalizados\n");
  for (i = 0; i < qtd_bytes; i++) {
    printf("%s ", bytes_normalizados[i]);
  }
  printf("\n");

  printf("| PPP Frame 0 control fields |\n");

  printf("Address: %d\nControl: %d\nProtocol: %s\n", address, control,
         protocol);

  printf("Checksum: %s (Binary %s)\n", checksum, check_bin);

  printf("Data: %s\n", data);

  if (checksum_verify(check_bin) == 1)
    printf("Data integrity: ok.\n");
  else
    printf("Data integrity: not ok.\n");

  return 0;
}