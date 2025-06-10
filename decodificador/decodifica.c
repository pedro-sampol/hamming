#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "hamLib.h"

int main(int argc, char *argv[]) {
	// checa erros na chamada da função
	if (argc != 3) {
		fprintf(stderr, "Uso: %s <arquivo_entrada> <arquivo_saida>\n", argv[0]);
		return 1;
	}

	FILE *entrada = fopen(argv[1], "r");
	if (!entrada) {
		perror("Erro ao abrir arquivo de entrada");
		return 2;
	}

	FILE *saida = fopen(argv[2], "wb");
	if (!saida) {
		perror("Erro ao abrir arquivo de saída");
		fclose(entrada);
		return 3;
	}

	// vetores para a manipulação dos dados
	unsigned char lidos[TAM_TOTAL];
	unsigned char temp[TAM_DADOS];
	unsigned char envio[32];
	unsigned char aguardo[8];
	unsigned char bytes[4];

	// variaveis de tamanho
	int tamLidos = 0;
	int tamAguardo = 0;
	int tamEnvio = 0;
	int numBytes = 0;
	
	int finalTemp, bit;
	
	// inicia a decodificação e transferencia de dados
	while (1) {	
		zeraVetor (bytes, 4);
		tamLidos = 0;
		bit = 0;
		
		// transforma ASCII nos bits 0 e 1
		while (bit != ' ' && bit != EOF) {
			bit = fgetc(entrada);
			if (bit == '0') {
				lidos[tamLidos] = 0;
				tamLidos++;
			} else if (bit == '1') {
				lidos[tamLidos] = 1;
				tamLidos++;
			} 
		}
		if (tamLidos < 31) break;
		
		// calcula quantos bytes serão enviados
		numBytes = (TAM_DADOS + tamAguardo) / 8;
		tamEnvio = numBytes * 8;
		
		// corrige erros no arquivo intermediario
		hammingDecode (lidos);
		
		// exclui os bits de paridade
		for (int i = 0; i < TAM_DADOS; i++) {
			temp[i] = lidos[DADOS[i]];
		}
		
		// seleciona os bits que serão enviados pro arquivo saida
		preparaEnvio (envio, aguardo, temp, tamAguardo, tamEnvio);
		
		// guarda os bits que sobraram nesse loop em aguardo
		tamAguardo = (TAM_DADOS + tamAguardo) % 8;		
		finalTemp = TAM_DADOS - tamAguardo;		
		for (int i = finalTemp; i < TAM_DADOS; i++) {
			aguardo[i - finalTemp] = temp[i];
		}
		
		// junta os bits em envio formando bytes para a escrita
		montaByte (bytes, envio, numBytes);

		// escrita em arquivo
		for (int i = 0; i < numBytes; i++) {
			fputc (bytes[i], saida);
		}
	}
	
	// ultima iteração
	numBytes = (tamLidos + tamAguardo) / 8;
	tamEnvio = numBytes * 8;
	preparaEnvio (envio, aguardo, lidos, tamAguardo, tamLidos+tamAguardo);
	montaByte (bytes, envio, numBytes);
	for (int i = 0; i < numBytes; i++) {
		fputc (bytes[i], saida);
	}
	
	// fecha arquivos
	fclose(entrada);
	fclose(saida);
	return 0;
}
