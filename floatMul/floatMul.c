#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#define EXP_SZ 8
#define FRAC_SZ 23



int main(int argc, char *argv[]) {

    // float value = *(float *) &binary; // you are not allowed to do this.
    // unsigned int binary = *(unsigned int*) &value; // you are not allowed to do this.

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    float product = 1.0;


    for(int i = 0; i < 2; i++){

      char buff;
      char sign = 0;
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
      }

      if( e != 0 && e != 255){
        m =  m + 1;
        e = e - 127;
      }
      else{
        e = 1 - 127;
      }
      double number = ldexp ( m, e );
      number = sign ? -number : number;
      product = product*number;
      fscanf(fp, "%c", &buff);

    }

    // printf("%f\n", product);

    //part 2




    bool sign = product<0.0;
    printf("%d_",sign);

    double fraction = sign ? -product : product;

    unsigned short bias = (1<<(EXP_SZ-1))-1;

    signed int exp = 0;

    unsigned short e = 0;

      if(fraction >= 1.0){
        // printf("a\n");
        for ( int i = 1; i <= 127; i++){

          if ( fraction < 2 ) break;

          fraction = fraction/2;
          exp = i;

        }
         e = exp + bias;
      }
      else if(fraction < 1.0 && fraction != 0.0 ){
        // printf("b\n");
        for ( int i = -1; i >= -127; i--){

          if ( fraction >= 1) break;

          fraction = fraction*2;
          exp = i;
        }
        e = exp + bias;

      }
      else{
         e = 0;
      }

      if ( e == 0) fraction = fraction/2;

      for (int i = 7; i >= 0; i--) {
        /* code */
        printf("%d", 0b1 & e>>i);
      }

      printf("_");

    bool frac_array[FRAC_SZ+1]; // one extra LSB bit for rounding

      for ( int frac_index=FRAC_SZ; 0<=frac_index; frac_index-- ) {

        if(fraction >= 1) fraction = (fraction -1);

          if( 2* (fraction) >= 1){
            frac_array[frac_index] = true;
          }
          else{
            frac_array[frac_index] = false;
          }

          fraction = fraction*2;
      }



    for ( int frac_index=FRAC_SZ-1; 0<=frac_index; frac_index-- ) {

          bool frac_bit = frac_array[frac_index+1]; // skipping the extra LSB bit for rounding
          printf("%d", frac_bit);
          // assert (frac_bit == (1&ref_bits>>frac_index)); // validate your result against the reference
      }














    //
    //
    //
    // // SETUP
    //
    // // first, read the binary number representation of multiplier
    // /* ... */
    //
    // // notice that you are reading two different lines; caution with reading
    // /* ... */
    //
    // // first, read the binary number representation of multiplcand
    // /* ... */
    //
    // float product = *(float *) &multiplier * *(float *) &multiplicand; // you are not allowed to print from this.
    // unsigned int ref_bits = *(unsigned int *) &product; // you are not allowed to print from this. But you can use it to validate your solution.
    //
    // // SIGN
    // /* ... */
    // printf("%d_",sign);
    // assert (sign == (1&ref_bits>>(EXP_SZ+FRAC_SZ)));
    //
    // // EXP
    // // get the exp field of the multiplier and multiplicand
    // /* ... */
    // // add the two exp together
    // /* ... */
    // // subtract bias
    // /* ... */
    //
    // // FRAC
    // // get the frac field of the multiplier and multiplicand
    // /* ... */
    // // assuming that the input numbers are normalized floating point numbers, add back the implied leading 1 in the mantissa
    // /* ... */
    // // multiply the mantissas
    // /* ... */
    //
    // // overflow and normalize
    // /* ... */
    //
    // // rounding
    // /* ... */
    //
    // // move decimal point
    // /* ... */
    //
    // // PRINTING
    // // print exp
    // for ( int bit_index=EXP_SZ-1; 0<=bit_index; bit_index-- ) {
    //     bool trial_bit = 1&exp>>bit_index;
    //     printf("%d",trial_bit);
    //     assert (trial_bit == (1&ref_bits>>(bit_index+FRAC_SZ)));
    // }
    // printf("_");
    //
    // // print frac
    // for ( int bit_index=FRAC_SZ-1; 0<=bit_index; bit_index-- ) {
    //     bool trial_bit = 1&frac>>bit_index;
    //     printf("%d",trial_bit);
    //     assert (trial_bit == (1&ref_bits>>(bit_index)));
    // }

    return(EXIT_SUCCESS);

}
