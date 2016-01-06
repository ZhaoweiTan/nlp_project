#include<stdio.h>
#include<string.h>

int main()
{
    char line[1024];
    while(fgets(line, 1024, stdin))
    {
        char word[1024];
        int offset = 0;
        while (sscanf(line+offset, "%s", word) != EOF)
        {
            offset += strlen(word)+1;
        }
        printf("%s\n", word);
    }

    return 0;
}
