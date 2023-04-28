NOME=beale

CFILES=$(wildcard ./src/*.c)

HFILES=$(wildcard ./include/*.h)

OBJ=$(subst .c,.o,$(subst src,objetos,$(CFILES)))

CC=gcc

CFLAGS=-c -W -Wall -I ./include -std=c99

RM = rm -rf

all: object_dir $(NOME)
 
$(NOME): $(OBJ)
	$(CC) $^ -o $@ 
 
./objetos/%.o: ./src/%.c ./include/%.h
	$(CC) $< $(CFLAGS) -o $@
 
./objetos/beale.o: ./src/beale.c $(HFILES)
	$(CC) $< $(CFLAGS) -o $@
 
object_dir:
	@mkdir -p objetos
 
clean:
	$(RM) ./objetos/*.o $(NOME) *~
 
purge: clean
	$(RM) ./objetos
	
test:
	./$(NOME) -e -b LivroCifra.txt -m MensagemOriginal.txt -o MensagemCodificada.txt -c ArquivoDeChaves.txt
	./$(NOME) -d -i MensagemCodificada.txt -c ArquivoDeChaves.txt -o MensagemDecodificada.txt
	./$(NOME) -d -i MensagemCodificada.txt -b LivroCifra.txt -o MensagemDecodificada2.txt

check:
	diff -w MensagemOriginal.txt MensagemDecodificada.txt
	diff -w MensagemOriginal.txt MensagemDecodificada2.txt

.PHONY: all clean