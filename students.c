#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char *name;
    char *dorm;
}
student;

int cmp(const void *a, const void *b);

int main(void)
{
    student heads[] =
    {
        {"Stelios", "Branford"},
        {"Maria", "Cabot"},
        {"Anushree", "Ezra Stiles"},
        {"Brian", "Winthrop"}
    };
    printf("Before:\n");
    for (int i = 0; i < 4; i++)
    {
        printf("%s from %s\n", heads[i].name, heads[i].dorm);
    }
    qsort(heads, 4, sizeof(student), cmp);
    printf("After:\n");
    for (int i = 0; i < 4; i++)
    {
        printf("%s from %s\n", heads[i].name, heads[i].dorm);
    }
}

int cmp(const void *a, const void *b)
{
    //convert void pointers a & b to pointers to elements in the array (of strings),
    //dereference arg1 and arg2 to compare the strings(const char *)
    const char *arg1 = *(const char **) a;
    const char *arg2 = *(const char **) b;

    return (strcmp(arg1, arg2));
}
