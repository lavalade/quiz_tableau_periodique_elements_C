# 2020:10:13@17:36:01, Création :
#     lava@macta
#     /Users/lava/quiz/quiz_tableau_periodique_elements/qtpe_c/Makefile

# Mode emploi succinct mais assez complet et avec des exemples :
# https://www.cs.swarthmore.edu/~newhall/unixhelp/howto_makefiles.html

CC = gcc
CFLAGS = -g -Wall
TARGET = quiz

all: $(TARGET)

$(TARGET): main.o tpe.o utils.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o tpe.o utils.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

tpe.o: tpe.c
	$(CC) $(CFLAGS) -c tpe.c

utils.o: utils.c
	$(CC) $(CFLAGS) -c utils.c

clean:
	rm -v $(TARGET) *.o
