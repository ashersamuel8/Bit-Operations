#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define EXP_SZ 8
#define FRAC_SZ 23

int main(int argc, char *argv[]) {

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    // SETUP

    // first, read the binary number representation of float point number
    char buff;
    char sign = 0;
    // unsigned int binary = 0;
    int e = 0;
    float m = 0.0;


    for (int i=EXP_SZ+FRAC_SZ; 0<=i; i--) { // read MSB first as that is what comes first in the file
        /* ... */
        fscanf(fp, "%c", &buff);

        // binary>>i = buff - 48;
        if( i == EXP_SZ+FRAC_SZ ){
          if(buff - 48) sign = 1;
        }
        else if(i >= FRAC_SZ){
          e = e + (buff - 48)* pow(2, i - 23);
        }
        else{
            m =  m + (buff - 48)* pow(2, i - 23);
            // printf("%d %d %lf\n",i,(0b1 & binary>>i), m);
        }
        // printf("%d\n",buff - 48);

    }
    // printf("%d\n", binary);

    // printf("%f\n", m);
    // printf("%d\n", e);

    if( e != 0 && e != 255){
      m =  m + 1;
      e = e - 127;
    }
    else{
      e = 1 - 127;
    }
    // else{
    //
    // }


    // printf("%f\n", m);
    // printf("%d\n", e);

    // https://www.tutorialspoint.com/c_standard_library/c_function_ldexp.htm
    double number = ldexp ( m, e );
    number = sign ? -number : number;
    printf("%e\n", number);

    return EXIT_SUCCESS;

}
