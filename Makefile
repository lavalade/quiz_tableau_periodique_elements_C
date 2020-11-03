# 2020:10:13@17:36:01, Création :
#     lava@macta
#     /Users/lava/quiz/quiz_tableau_periodique_elements/qtpe_c/Makefile

# Mode emploi succinct mais assez complet et avec des exemples :
# https://www.cs.swarthmore.edu/~newhall/unixhelp/howto_makefiles.html

CC = gcc
CFLAGS = -g -Wall
TARGET = quiz

all: $(TARGET)

$(TARGET): main.o tpe.o utils.o wchar_to_ascii.o
	$(CC) $(CFLAGS) -o $(TARGET) $^

main.o: main.c
	$(CC) $(CFLAGS) -c $^

tpe.o: tpe.c
	$(CC) $(CFLAGS) -c $^

utils.o: utils.c
	$(CC) $(CFLAGS) -c $^

wchar_to_ascii.o: wchar_to_ascii.c
	$(CC) $(CFLAGS) -c $^

clean:
	rm -v $(TARGET) *.o 2> /dev/null
