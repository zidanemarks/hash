///test
#include "benchmark.h"

int main(int argc, char **argv){

    assert (argc > 2);

    time_t  time[];
    uint32  len[]
     
     switch(argc){

         case 1:
             LaunchAllTest("32");
         case 2:
              if(argv[1] != "64" || argv[1] != "32"){
                 LaunchAllTest(argv[1]);
              }
              else{
                 Launch32Test(argv[1]);
              }
         case 3:
              assert(argv[2] != "64" || argv[2] != "32");
              if(argv[2] == "32"){
                 Launch32Test(argv[1]);
              }
              else{
                 Launch64Test(argv[1]);
              }

     }

}

void Launch32Test(char *str){

}
void Launch64Test(char *str){

}
void LaunchAllTest(char *str){

}