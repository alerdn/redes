#include <stdio.h>
#include <math.h>

int main() {
    double temp_total; /* s */
    double t = 1; /* tamanho, MB 10^6 * 8 */
    int r = 100; /* RTT, ms */
    int p; /* KB */
    int k = 2; /* k x RTT */
    double l; /* largura banda, Mbps */
    int q; /* pacotes */
    double handshake = k*r*pow(10, -3);

    /*
    t  r  p k s

    1 100 1 2 A
    
    l
    1.5
    */
    /*printf("ms to s: %f\n", 100*pow(10, -3));
    printf("MB to Mb %d\n", 1*8);
    printf("Mb / Kb: %f\n", (1*8) / ((1*8)*pow(10, -3)));
    printf("Mb / Mbps: %f\n", (1*8) / 1.5);

    printf("handshack: %f\n", handshake);*/

    printf("Tempo de transmissão: %f\n", ( handshake + (r*pow(10, -3)) + ( t*8 / 1.5)));


    return 0;
}