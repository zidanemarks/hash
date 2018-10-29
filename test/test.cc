///test
#include "benchmark.h"
#include <stdlib.h>
#include <assert.h>



int main(int argc, char **argv){

    assert(argc > 2);

    switch(argc){

         case 1:
             LaunchAllTest();
         case 2:
             LaunchTest(argv[1]);

     }

    return 0;
}