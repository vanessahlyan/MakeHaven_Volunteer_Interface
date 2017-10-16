#include <cs50.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <string.h>
#include <ctype.h>

typedef wchar_t emoji;

emoji get_emoji(string prompt);

int main(void)
{
    // Set locale according to environment variables
    setlocale(LC_ALL, "");

    // Prompt user for code point
    emoji c = get_emoji("Code point: ");

    // Print character
    printf("%lc\n", c);
}

emoji get_emoji(string prompt)
{
    while (true)
    {
        string unicode = get_string("%s", prompt);

        if (unicode == NULL)
        {
            return 1;
        }

        //check if first two characters are U and + respectively
        if (unicode[0] == 'U' && unicode[1] == '+' )
        {
            //check the remaining characters to see if they are hexadecimal representation
            for (int i = 2; i < strlen(unicode); i++)
            {
                if ((toupper(unicode[i]) >= 'A' && toupper(unicode[i]) <= 'F') || (isdigit(unicode[i]) != 0))
                {
                    wchar_t *output = malloc(sizeof(wchar_t));
                    *output = mbstowcs(output, unicode, strlen(unicode));
                    return *output;
                    free(output);
                }
                else
                {
                    return 1;
                }
            }
        }
        //if input doesn't conform to unicode format
        printf("Retry.\n");
    }
}