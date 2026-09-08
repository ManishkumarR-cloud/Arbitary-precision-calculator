#include "sign.h"

int get_sign(char **str) {
    int sign = +1;
    if ((*str)[0] == '-') {
        sign = -1;
        (*str)++;   // skip the sign
    } else if ((*str)[0] == '+') {
        (*str)++;   // skip the sign
    }
    return sign;
}
