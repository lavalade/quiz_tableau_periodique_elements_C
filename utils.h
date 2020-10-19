/**
 * 2020:10:18t23:47:36, Création :
 *     lava@macta
 *     /Users/lava/quiz/quiz_tableau_periodique_elements_C/utils.h
 **/

bool all(unsigned char *array);
void clear_input(char *answer,
                 char *answer_symbol,
                 char *answer_name,
                 char *toomuchspaces);
unsigned char minhhu(unsigned char x, unsigned char y);
unsigned char levenshein(char *solution, char *answer);
float mark(char *solution, char *answer);
float update_mean(float old_mean, unsigned char n, float new);
unsigned short sumhhu(unsigned char *array);
float meanf(float *marks);
void getdate_iso8601(char *date);
void inputstr(char *str, unsigned char maxlen);
