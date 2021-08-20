#include <stdio.h>
#include <math.h>

int main() {
    int d; /* Km */
    int v; /* m/s */
    int t; /* bytes */
    double l; /* Mbps */
    double propagacao;
    
    scanf("%d %d %d", &d, &v, &t);

    propagacao = (double)(d*1000) / v;
    l = (t*8*pow(10,-6)) / propagacao;

    printf("O tempo de transmissão será equivalente ao retardo de propagação na largura de banda %.2fMbps\n", l);

    return 0;
}