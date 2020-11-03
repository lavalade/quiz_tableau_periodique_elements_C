/**
 * 2020-11-01,21:29:41, Création :
 *     lava@macta
 *     /Users/lava/dev/C/wchar_to_ascii/wchar_to_ascii.h
 **/


bool in(wchar_t input, const wchar_t *letter_like);
char wchr_to_chr(wchar_t input);
void wcstr_to_str(wchar_t *wcstr, char *str);
void wcstr_to_ascii(wchar_t *wcstr, wchar_t *asciistr);
void AZ_to_az(wchar_t wcstr[]);
