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

	FILE *entrada = fopen(argv[1], "rb");
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
	unsigned char lidos[4];
	unsigned char envio[TAM_DADOS];
	unsigned char aguardo[TAM_DADOS];
	unsigned char temp[32];
	unsigned char codigo[TAM_TOTAL];
	
	// variaveis de tamanho
	int tamLidos = 0;
	int tamAguardo = 0;
	int tamTemp = 0;
	
	// outras variáveis
	int finalTemp;
	int ultimoBloco;

	// inicia a codificação e transferencia de dados
	while (1) {
		zeraVetor (codigo, TAM_TOTAL);
		
		// lê os bytes do arquivo de entrada
		if (tamAguardo >= 8) {
			tamLidos = fread(lidos, 1, 3, entrada);
		} else {
			tamLidos = fread(lidos, 1, 4, entrada);
		}
		
		tamTemp = 8 * tamLidos;
		coletaBits (temp, lidos, tamLidos);
		
		// verifica se é o último bloco e envia sem codificação
		ultimoBloco = tamTemp + tamAguardo;
		if (ultimoBloco < TAM_DADOS) {
			preparaEnvio (envio, aguardo, temp, tamAguardo, ultimoBloco);
			for (int i = 0; i < ultimoBloco; i++) {
				fputc(envio[i] ? '1' : '0', saida);
			}
			break;
		}
		
		// seleciona os bits que serão enviados pro arquivo saida
		preparaEnvio (envio, aguardo, temp, tamAguardo, TAM_DADOS);
		
		// calcula o novo tamanho de tamAguardo e
		finalTemp = TAM_DADOS - tamAguardo;
		tamAguardo = tamTemp - finalTemp;
		
		// guarda os bits que sobraram nesse loop em aguardo
		for (int i = finalTemp; i < tamTemp; i++) {
			aguardo[i - finalTemp] = temp[i];
		}
		
		// posiciona os bits de dados 
		for (int i = 0; i < TAM_DADOS; i++) {
			codigo[DADOS[i]] = envio[i];
		}
		
		// calcula o valor dos bits de paridade
		codigo[0] = hammingCode (codigo, P1);
		codigo[1] = hammingCode (codigo, P2);
		codigo[3] = hammingCode (codigo, P4);
		codigo[7] = hammingCode (codigo, P8);
		codigo[15] = hammingCode (codigo, P16);
		
		// escrita em arquivo
		for (int i = 0; i < TAM_TOTAL; i++) {
			fputc (codigo[i] ? '1' : '0', saida);
		}
		fputc (' ', saida);
	}

	fclose(entrada);
	fclose(saida);
	printf("Leitura e cópia por pacotes de 26 bits concluída.\n");
	return 0;
}
