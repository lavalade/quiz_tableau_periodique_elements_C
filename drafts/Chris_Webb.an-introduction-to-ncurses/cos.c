
/**
 * Il faut l’option  -lm  pour  math.h  cf
 * https://stackoverflow.com/questions/47769375/makefile-undefined-reference-to-cos
 *
 * gcc cos.c -lm -o cos.x && ./cos.x
 **/

#include <math.h>
#include <stdio.h>

int main(void) {
    float x = 42.;
    printf("%.6f\n", x);
    for (unsigned short i = 0; i < 12; ++i) {
        x = cos(x);
        printf("%.6f\n", x);
    }
    return 0;
}
