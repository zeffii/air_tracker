// functions.cpp

#include <string>
#include "Functions.h"

using namespace std;


int find_int_in_array(int num_to_find, int numbers[], int arraysize){
    for(int i = 0; i < arraysize; i++){
         if(numbers[i] == num_to_find){ return 1; }
    }
    return 0;
}

// kb-key to note f.ex:  (Z->C(octave))  E->C(octave+1)