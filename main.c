#include<stdio.h>
#include"parser.h"

int main(){
    Instruction i = parseInstruction(NULL);

    printf("%d %d %d", i.iType, i.r1, i.r2);

    return 0;
}