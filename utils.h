/**
 * 2020:10:18t23:47:36, Création :
 *     lava@macta
 *     /Users/lava/quiz/quiz_tableau_periodique_elements_C/utils.h
 **/

bool all(unsigned char *array);
void clear_input(wchar_t *answer,
                 wchar_t *answer_symbol,
                 wchar_t *answer_name);
unsigned char minhhu(unsigned char x, unsigned char y);
unsigned char levenshein(wchar_t *solution, wchar_t *answer);
float mark(wchar_t *solution, wchar_t *answer);
float update_mean(float old_mean, unsigned char n, float new);
unsigned short sumhhu(unsigned char *array);
float meanf(float *marks);
void getdate_iso8601(char *date);
void input_chars(char *str, unsigned char maxlen);
void input_wchars(wchar_t *wstr, unsigned char maxlen);
bool split(wchar_t *answer, wchar_t *answer_symbol, wchar_t *answer_name);
void archive_score(float symbol_mark_mean,
                   float name_mark_mean, 
                   unsigned short try_count_global,
                   unsigned short giveup_count_global,
                   unsigned short answered_count_global,
                   unsigned short duration);
