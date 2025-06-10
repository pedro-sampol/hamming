#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "hamLib.h"

// bits verificação de cada bit de paridade
const int P1[16] = {0, 2, 4, 6, 8, 10, 12, 14, 
			  		16, 18, 20, 22, 24, 26, 28, 30};
			  
const int P2[16] = {1, 2, 5, 6, 9, 10, 13, 14, 
			 	    17, 18, 21, 22, 25, 26, 29, 30};
			  
const int P4[16] = {3, 4, 5, 6, 11, 12, 13, 14, 
			 		19, 20, 21, 22, 27, 28, 29, 30};
			  
const int P8[16] = {7, 8, 9, 10, 11, 12, 13, 14, 
				    23, 24, 25, 26, 27, 28, 29, 30};
			  
const int P16[16] = {15, 16, 17, 18, 19, 20, 21, 22,
			  		 23, 24, 25, 26, 27, 28, 29, 30};

// todos os bits de dados (que não são de paridade)
const int DADOS[26] = {2, 4, 5, 6, 8, 9, 10, 11, 12, 13, 14, 16, 17, 18, 
				 	   19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30};
	
				 
// retorna o valor dos bits de paridade
int hammingSum (unsigned char lidos[], const int P[]) {
	int soma = 0;
	for (int i = 0; i < 16; i++) {
		soma += lidos[P[i]];
	}
	return (soma % 2);
}


// corrige no maximo um erro se houver
void hammingDecode (unsigned char lidos[]) {
	int res = -1;
	if (hammingSum (lidos, P1)) res += 1;	
	if (hammingSum (lidos, P2)) res += 2;	
	if (hammingSum (lidos, P4)) res += 4;	
	if (hammingSum (lidos, P8)) res += 8;	
	if (hammingSum (lidos, P16)) res += 16;
	
	if (res != -1) {
		if (lidos[res]) {
			lidos[res] = 0;
		} else {
			lidos[res] = 1;
		}
	}
}


// coloca os bits em ordem no vetor envio
void preparaEnvio (unsigned char envio[], unsigned char aguardo[], 
				   unsigned char temp[], int tamAguardo, int tamEnvio) {
	// coloca os bits do loop passado no vetor de envio
	for (int i = 0; i < tamAguardo; i++) {
		envio[i] = aguardo[i];
	}
		
	// coloca os bits lidos nesse loop no vetor de envio
	for (int i = tamAguardo; i < tamEnvio; i++) {
		envio[i] = temp[i-tamAguardo];
	}
}


// zera o vetor
void zeraVetor (unsigned char vetor[], int n) {
	for (unsigned char i = 0; i < n; i++) {
		vetor[i] = 0;
	}
}


// remonta o byte com shift left e adicionando o bit
void montaByte (unsigned char bytes[], unsigned char envio[], int numBytes) {
	for (int i = 0; i < numBytes; i++) {
    	for (int j = 0; j < 8; j++) {
    		bytes[i] = (bytes[i] << 1) | envio[8*i + j];  
    	}
    }
}











