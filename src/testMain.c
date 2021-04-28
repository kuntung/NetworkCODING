#include <stdio.h>
using namespace std;
 
int main(int argc, char ** argv)
{
    int i;
    printf("Argc = %d", argc);
    for (i = 0; i < argc; i++)
        printf("Argument %d is %s\n", i, argv[i]);
    return 0;
}
