#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * step1() {
	char * msg;
	msg = (char*)malloc(sizeof(char) * 80);
	scanf("%[^\n]s", msg);	
	return msg;
}

int * step2(char * msg) {
	int length = strlen(msg);
	int * msg2 = (int*) malloc(sizeof(int) * (length+1));
	
	int i;
	msg2[0] = length;
	for (i = 0; i < length; i++){
		msg2[i+1] = msg[i];
	}
	
	return msg2;
}

int * step3(int * msg2) {
	int length = msg2[0]+1;
	int * msg3 = (int*) malloc(sizeof(int) * length);
	
	int i = 0;
	for(i; i < length; i++){	
		int d = msg2[i];
		int resp = 0;
		int m10 = 1;
		do {
			resp += (d%2)*m10;
			m10 *= 10;
			d /= 2;
		} while(d != 0);	
		
		msg3[i] = resp;
	}
	
	return msg3;
}

main() {
	
	char * msg = step1();
	int * msg2 = step2(msg);
	int * msg3 = step3(msg2);
	
	int i = 0;
	for(i; i < msg2[0]+1; i++){
		printf("%d ", msg3[i]);
	}
	
}