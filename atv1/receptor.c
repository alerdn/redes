#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int * step1() {
    static int msg[80];
    int i = 0;
    char c;

    while(scanf(" %d%c", &msg[i], &c) > 0) {
        i++;
        if (c == '\n') {
            break;
        }
    }
    
    return msg;
}

int * step2(int * msg) {
    int j;
    int d2;
    int num;
    int nTemp;

    num = 0;
    d2 = 1;
    nTemp = msg[0];

    do {
        num += (nTemp % 10) * d2;
        d2 *= 2;
        nTemp /= 10;
    } while(nTemp > 0);  
    
    /*msg[0] == length*/
    msg[0] = num;


    for (j = 1; j <= msg[0]; j++) {
        num = 0;
        d2 = 1;
        nTemp = msg[j];

        do {
            num += (nTemp % 10) * d2;
            d2 *= 2;
            nTemp /= 10;
        } while(nTemp > 0);  

        msg[j] = num;
    }

    return msg;
}

void step3(int * msg2) {
    int i;
    
    for (i = 1; i <= msg2[0]; i++) {
        printf("%c", msg2[i]);
    }
}

int main() {
    int * msg = step1();
    int * msg2 = step2(msg);
    step3(msg2);

    return 0;
}