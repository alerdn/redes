#include <stdio.h>
#include <math.h>

float a(double t, int r, int k);
float b(double t, int r, int p, int k);
float c(double t, int r, int p, int k);
float d(double t, int r, int p, int k);

int main() {
    double tempo_total; /* segundos */
    double t; /* tamanho, MB 10^6 * 8 */
    int r; /* RTT, ms */
    int p; /* KB */
    int k; /* k x RTT */
    char s; /* situação A, B, C ou D */

    scanf("%lf %d %d %d %c", &t, &r, &p, &k, &s);

    switch(s) {
        case 'A':
           tempo_total = a(t, r, k);
           break;
        case 'B':
            tempo_total = b(t, r, p, k);
            break;
        case 'C':
            tempo_total = c(t, r, p, k);
            break;
        case 'D':
            tempo_total = d(t, r, p, k);
            break;
    }

    printf("Tempo de transmissão: %f\n", tempo_total);

    return 0;
}

float a(double t, int r, int k) {
    double l; /* largura de banda */
    double rtt = r*pow(10, -3);
    double handshake = k*rtt;

    scanf("%lf", &l);

    
    return handshake + (rtt/2) + (t*8 / l);
}

float b(double t, int r, int p, int k) {
    double l;
    double rtt = r*pow(10, -3);
    double handshake = k*rtt;
    int pacotes = t / (p*pow(10, -3));

    scanf("%lf", &l);
    
    return handshake + (rtt/2) + (rtt*(pacotes-1)) + (t*8 / l);
}

float c(double t, int r, int p, int k) {
    int q;
    double rtt = r*pow(10, -3);
    double handshake = k*rtt;
    int pacotes = t / (p*pow(10, -3));

    scanf("%d", &q);
    
    return handshake + (((pacotes/q)-1)*rtt) + (1 * (rtt/2));
}

float d(double t, int r, int p, int k) {
    double rtt = r*pow(10, -3);
    double handshake = k*rtt;
    int pacotes = (t / (p*pow(10, -3))) - 1;
    double s = 0;
    int toSend;
    int d2 = 500;
    int count = 1;

    while(pacotes > 0) {
        pacotes -= d2;
        toSend = d2 > pacotes ? d2+pacotes : d2;
        s += toSend*rtt;
        count++;
        d2 *= 2;
        
        printf("to send %d, at %f\n", toSend, s);
    }

    return handshake + s + (1 * (rtt/2));
}