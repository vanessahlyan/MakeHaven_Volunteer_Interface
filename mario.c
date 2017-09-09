#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int h;
    do
    {
        h = get_int("Choose a height for the pyramids among integers from 0 to 23: ");
    }

    while (h < 0 || h > 23);

    for (int i = 0; i < h; i++)
    {

        //print h-1-i spaces for the left
        printf("%*s", h - 1 - i, "");
        //print i+1 hashes for left
        for (int a = 0; a < i + 1; a++)
        {
            printf("#");
        }

        //print 2 spaces for gap
        printf("  ");

        //print i+1 hashes for right
        for (int a = 0; a <= i; a++)
        {
            printf("#");
        }

        printf("\n");
    }

}