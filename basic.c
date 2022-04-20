#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char    *push_line(char *remains)
{
    int i;
    char *array;

    i = 0;
    while (remains[i] && remains[i] != '\n')
        i++;
    if (!(array = (char *)malloc(sizeof(char) * (i + 1))))
        return (NULL);
    i = 0;
    while (remains[i] && remains[i] != '\n')
    {
        array[i] = remains[i];
        i++;
    }
    array[i] = '\0';
    return (array);
}


char    *cut_next_line(char *remains)
{
    int i;
    int j;
    char *array;

    i = 0;
    j = 0;
    while (remains[i] && remains[i] != '\n')
        i++;
    if (!remains[i])
    {
        free(remains);
        return (NULL);
    }
    if (!(array = (char *)malloc(sizeof(char) * (strlen(remains) - i + 1))))
        return (NULL);
    i++;
    while (remains[i])
    {
        array[j] = remains[i];
        i++;
        j++;
    }
    array[j] = '\0';
    free(remains);
    return (array);
}

int main(void)
{
    /*push_line("kekw");
    printf("%s\n", push_line);*/

    cut_next_line("kekw");
    printf("%s\n", cut_next_line);
}