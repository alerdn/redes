#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN_BIN 50000
#define CARAC 30000
#define WORDS 30

int binTodec(int *bin){
	int potenc = 1, i, decimal = 0;
	
	for(i=7; i>=0; i--){
		decimal += bin[i]*potenc;
		potenc = potenc * 2;
	}

	return decimal;
}

void binTohexa(int *prot, char *protocol){
	int i;
	
	for(i=0; i<4; i++){
		if(prot[(i*4)] == 0 && prot[(i*4)+1] == 0 && prot[(i*4)+2] == 0 && prot[(i*4)+3] == 0)
			protocol[i] = '0';
		else if(prot[(i*4)] == 0 && prot[(i*4)+1] == 0 && prot[(i*4)+2] == 0 && prot[(i*4)+3] == 1)
	    		protocol[i] = '1';
		else if(prot[(i*4)] == 0 && prot[(i*4)+1] == 0 && prot[(i*4)+2] == 1 && prot[(i*4)+3] == 0)
	    		protocol[i] = '2';
		else if(prot[(i*4)] == 0 && prot[(i*4)+1] == 0 && prot[(i*4)+2] == 1 && prot[(i*4)+3] == 1)
	    		protocol[i] = '3';
		else if(prot[(i*4)] == 0 && prot[(i*4)+1] == 1 && prot[(i*4)+2] == 0 && prot[(i*4)+3] == 0)
	    		protocol[i] = '4';
		else if(prot[(i*4)] == 0 && prot[(i*4)+1] == 1 && prot[(i*4)+2] == 0 && prot[(i*4)+3] == 1)
	    		protocol[i] = '5';
		else if(prot[(i*4)] == 0 && prot[(i*4)+1] == 1 && prot[(i*4)+2] == 1 && prot[(i*4)+3] == 0)
	    		protocol[i] = '6';
		else if(prot[(i*4)] == 0 && prot[(i*4)+1] == 1 && prot[(i*4)+2] == 1 && prot[(i*4)+3] == 1)
	    		protocol[i] = '7';
		else if(prot[(i*4)] == 1 && prot[(i*4)+1] == 0 && prot[(i*4)+2] == 0 && prot[(i*4)+3] == 0)
	    		protocol[i] = '8';
		else if(prot[(i*4)] == 1 && prot[(i*4)+1] == 0 && prot[(i*4)+2] == 0 && prot[(i*4)+3] == 1)
	    		protocol[i] = '9';
		else if(prot[(i*4)] == 1 && prot[(i*4)+1] == 0 && prot[(i*4)+2] == 1 && prot[(i*4)+3] == 0)
	    		protocol[i] = 'A';
		else if(prot[(i*4)] == 1 && prot[(i*4)+1] == 0 && prot[(i*4)+2] == 1 && prot[(i*4)+3] == 1)
	    		protocol[i] = 'B';
		else if(prot[(i*4)] == 1 && prot[(i*4)+1] == 1 && prot[(i*4)+2] == 0 && prot[(i*4)+3] == 0)
	    		protocol[i] = 'C';
		else if(prot[(i*4)] == 1 && prot[(i*4)+1] == 1 && prot[(i*4)+2] == 0 && prot[(i*4)+3] == 1)
	    		protocol[i] = 'D';
		else if(prot[(i*4)] == 1 && prot[(i*4)+1] == 1 && prot[(i*4)+2] == 1 && prot[(i*4)+3] == 0)
	    		protocol[i] = 'E';
		else if(prot[(i*4)] == 1 && prot[(i*4)+1] == 1 && prot[(i*4)+2] == 1 && prot[(i*4)+3] == 1)
	    		protocol[i] = 'F';
	}
}

void concatenation(int *vec1, int *vec2, int *concat){
	int i;
	
	for(i=0; i<8; i++){
		concat[i] = vec1[i];
		concat[i+8] = vec2[i];
	}
}

int sum(int *vec1, int *vec2, int *resp){
	int i, goOne=0;
	
	for(i=15; i>=0; i--){
		if((vec1[i] == 0 && vec2[i] == 0)){
			if(goOne == 1)
				resp[i] = 1;
			else
				resp[i] = 0;	
			goOne = 0;
		}else if((vec1[i] == 1 && vec2[i] == 0) || (vec1[i] == 0 && vec2[i] == 1)){
			if(goOne == 1){
				resp[i] = 0;
				goOne = 1;
			}else{
				resp[i] = 1;
				goOne = 0;
			}
		}else if(vec1[i] == 1 && vec2[i] == 1){
			if(goOne == 1){
				resp[i] = 1;
				goOne = 1;
			}else{
				resp[i] = 0;
				goOne = 1;
			}
		}
	}
	return goOne;
}

void join(int *resp, int *x){
	int i;

	for(i=0; i<16; i++)
		resp[i] = x[i];	
}

void comp1(int *resp, int *check, int goOne){
	int v1[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1};
	
	if(goOne == 1)
		sum(resp, v1, check);
	else
		join(check, resp);
}

int check(int entrada[CARAC][8], int *ccks, int *prot, int campos, int semEscape[CARAC][8], int index_semEscape){
	int i, adControl[16], check_aux[16], resp[16], goOne, x[16], concat[16], sum_ccks[16], aux=0;
	
	concatenation(entrada[0], entrada[1], adControl);
	
	goOne = sum(adControl, prot, check_aux);
	
	comp1(check_aux, resp, goOne);
	
	for(i=0; i<index_semEscape; i=i+2){
		concatenation(semEscape[i], semEscape[i+1], concat);
		goOne = sum(resp, concat, x);
		comp1(x, resp, goOne);
	}
	
	goOne = sum(resp, ccks, sum_ccks);
	
	for(i=0; i<16; i++){
		if(sum_ccks[i] != 1)
			aux = 1;
	}
	
	if(aux == 0)
		return 1;
	else
		return 0;
}

int equal(int *vec1, int *vec2){
	int aux=0, j=0;
	
	while(j<8){
		if(vec1[j] != vec2[j])
			aux = 1;
		j++;
	}
	if(aux == 0)
		return 1;
	else 
		return 0;
}

void charToworld(int entrada[CARAC][8], int campo, int semEscape[CARAC][8], int *index_semEscape){
	int escape[8] = {0,1,1,1,1,1,0,1};
	int i, j=0;
	
	for(i=4; i<campo-2; i++){
		if(equal(entrada[i], escape) == 0){
			j=0;
			while(j<8){
				semEscape[*index_semEscape][j] = entrada[i][j];
				j++;
			}
			(*index_semEscape)++;
		}else{
			if(equal(entrada[i-1], escape) == 1){
				j=0;
				while(j<8){
					semEscape[*index_semEscape][j] = entrada[i][j];
					j++;
				}
				(*index_semEscape)++;
			}
		}
		
	}	
}

void receptor(int entrada[CARAC][8], int campos, int index_out, int words){
	
	char protocol[4], checksum[4];
	int i, verify, index_semEscape=0, adress, control, ccks[16], prot[16], payload[CARAC], semEscape[CARAC][8];

	adress = binTodec(entrada[0]);
	
	control = binTodec(entrada[1]);
	
	concatenation(entrada[2], entrada[3], prot);
	
	binTohexa(prot, protocol);
	
	charToworld(entrada, campos, semEscape, &index_semEscape);
	
	for(i=0; i<index_semEscape; i++)
		payload[i] = binTodec(semEscape[i]);
	
	concatenation(entrada[campos-2], entrada[campos-1], ccks);
	
	binTohexa(ccks, checksum);
	
	if(index_semEscape%2 != 0){
		for(i=0; i<8; i++)
			semEscape[index_semEscape][i] = 0;
		index_semEscape++;
	}
	
	verify = check(entrada, ccks, prot, campos, semEscape, index_semEscape);
	
	printf("| PPP Frame %d control fields |\n\n", index_out);
	printf("Address: %d\n\n", adress);
	printf("Control: %d\n\n", control);
	printf("Protocol: ");
	for(i=0; i<4; i++)
		printf("%c", protocol[i]);
		
	printf("\n\nChecksum: ");
	for(i=0; i<4; i++)
		printf("%c", checksum[i]);
	printf(" (Binary ");
	for(i=0; i<16; i++)	
		printf("%d", ccks[i]);
	printf(")");
	printf("\n\nData: ");
	
	for(i=0; i<index_semEscape; i++)
		printf("%c", payload[i]);	
		
	
	if(index_out == words-1){
		if(verify == 1)
			printf("\n\nData integrity: ok.\n");
		else
			printf("\n\nData integrity: not ok.\n");
	}else{
		if(verify == 1)
			printf("\n\nData integrity: ok.\n\n");
		else
			printf("\n\nData integrity: not ok.\n\n");
	}
	
}

void preProcessing(int input_with_preproc[WORDS][6251][8], int *words, int input[CARAC][8], int bytes, int *campos){
	int flag[8] = {0,1,1,1,1,1,1,0};
	int escape[8] = {0,1,1,1,1,1,0,1};
	int entrou, j, i;
	
	(*words)++;
	campos[*words] = 0;
	entrou = 1;
	
	for(i=1; i<bytes; i++){
		if(equal(input[i-1], escape) == 1 || equal(input[i], flag) == 0){
			entrou = 0;
			for(j=0; j<8; j++){
				input_with_preproc[*words][campos[*words]][j] = input[i][j];
			}
			campos[*words] = campos[*words] + 1;
		}else{
			if(entrou == 0){
				(*words)++;
				campos[*words] = 0;
				entrou = 1;
			}
		}
	}	
	
}
int main(){
	int i, j, n, bytes, input[CARAC][8], input_with_preproc[WORDS][6251][8], words=-1, campos[100];
	char s[LEN_BIN];
	
	scanf("%s", s);
	n = strlen(s);
	
	bytes = n/8;
	
	for(i=0; i<bytes; i++){
		for(j=0; j<8; j++){
			if(s[(i*8)+j] == '0')
				input[i][j] = 0;
			else
				input[i][j] = 1;
		}
	}
	
	preProcessing(input_with_preproc, &words, input, bytes, campos);
	
	for(i=0; i<words; i++){
		receptor(input_with_preproc[i], campos[i], i, words);
	}
	
	return 0;
}
