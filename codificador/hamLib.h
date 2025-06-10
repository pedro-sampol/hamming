#ifndef __hamLib__
#define __hamLib__

#define TAM_DADOS 26
#define TAM_TOTAL 31

extern const int P1[];
extern const int P2[];
extern const int P4[];
extern const int P8[];
extern const int P16[];
extern const int DADOS[];

void coletaBits (unsigned char temp[], unsigned char lidos[], int tamLidos);

int hammingCode (unsigned char codigo[], const int P[]);

void zeraVetor (unsigned char vetor[], int n);

void preparaEnvio (unsigned char envio[], unsigned char aguardo[], 
				   unsigned char temp[], int tamAguardo, int tamEnvio);

#endif
