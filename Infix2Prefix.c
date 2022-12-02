#include <stdio.h>
#include <stdlib.h>

char* Infix2Prefix(char* infix)
{
    int len = strlen(infix);
    char* prefix = (char*)malloc(sizeof(char) * (len + 1));
    prefix[len] = '\0';
    
    return prefix;
}

int main(int argc, char** argv)
{
    char* infix = "1+2*3";
    char* prefix = Infix2Prefix(infix);

    printf("Infix:  %s\n", infix);
    printf("Prefix: %s\n", prefix);

    return 0;
}
