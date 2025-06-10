CC = gcc
CFLAGS = -Wall

ENCODE_SOURCE = ./codigo/codifica.c
ENCODE_OBJECT = ./codigo/codifica.o
ENCODE_EXEC = ./codigo/codifica

DECODE_SOURCE = ./codigo/decodifica.c
DECODE_OBJECT = ./codigo/decodifica.o
DECODE_EXEC = ./codigo/decodifica

LIB_SOURCE = ./codigo/hamLib.c
LIB_OBJECT = ./codigo/hamLib.o

ENTRADA = texto.txt
INTERMEDIARIO = texto.hamming
SAIDA = texto.dec

# compila codificação
encode: $(ENCODE_EXEC)
$(ENCODE_EXEC): $(LIB_OBJECT) $(ENCODE_OBJECT) 
	$(CC) $(CFLAGS) -o $@ $^

$(LIB_OBJECT): $(LIB_SOURCE)
	$(CC) $(CFLAGS) -c $< -o $@

$(ENCODE_OBJECT): $(ENCODE_SOURCE)
	$(CC) $(CFLAGS) -c $< -o $@

# Cria o arquivo de saída se não existir
encode_run: $(ENCODE_EXEC)
	test -f $(INTERMEDIARIO) || touch $(INTERMEDIARIO)
	./$(ENCODE_EXEC) $(ENTRADA) $(INTERMEDIARIO)


# compila decodificação
decode: $(DECODE_EXEC)
$(DECODE_EXEC): $(LIB_OBJECT) $(DECODE_OBJECT) 
	$(CC) $(CFLAGS) -o $@ $^

$(DECODE_OBJECT): $(DECODE_SOURCE)
	$(CC) $(CFLAGS) -c $< -o $@

# Cria o arquivo de saída se não existir
decode_run: $(DECODE_EXEC)
	test -f $(SAIDA) || touch $(SAIDA)
	./$(DECODE_EXEC) $(INTERMEDIARIO) $(SAIDA)


# Limpar os arquivos objeto e executavel
clean:
	rm -f $(ENCODE_EXEC) $(DECODE_EXEC) $(ENCODE_OBJECT) $(DECODE_OBJECT) $(LIB_OBJECT)

# Limpar todos os arquivos gerados
purge:
	rm -f $(ENCODE_EXEC) $(DECODE_EXEC) $(ENCODE_OBJECT) $(DECODE_OBJECT) $(LIB_OBJECT) $(SAIDA) $(INTERMEDIARIO)
