CC = gcc
CFLAGS = -Wall

C_SOURCE = codifica.c
C_OBJECT = codifica.o

LIB_SOURCE = hamLib.c
LIB_OBJECT = hamLib.o

EXECUTAVEL = codifica

ENTRADA = ../texto.txt
SAIDA = ../texto.hamming

# Alvo padrão
all: $(EXECUTAVEL)

# Compilar o executável
$(EXECUTAVEL): $(LIB_OBJECT) $(C_OBJECT) 
	$(CC) $(CFLAGS) -o $@ $^

# Gera o objeto das libs
$(LIB_OBJECT): $(LIB_SOURCE)
	$(CC) $(CFLAGS) -c $< -o $@

# Gera o objeto da main
$(C_OBJECT): $(C_SOURCE)
	$(CC) $(CFLAGS) -c $< -o $@
	
# Cria o arquivo de saída se não existir
run: $(EXECUTAVEL)
	test -f $(SAIDA) || touch $(SAIDA)
	./$(EXECUTAVEL) $(ENTRADA) $(SAIDA)

# Limpar os arquivos objeto e executavel
clean:
	rm -f $(EXECUTAVEL) $(C_OBJECT) $(LIB_OBJECT)

# Limpar todos os arquivos gerados
purge:
	rm -f $(EXECUTAVEL) $(C_OBJECT) $(LIB_OBJECT) $(SAIDA)
