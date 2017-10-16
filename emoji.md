# Emoji

## Questions

1. The unicode of Jack-o-lantern is 0x1F383, and its hexadecimal representation is 0xF0 0x9F 0x8E 0x83. Since the hexadecimal representation begins with 0xF0, jack-o-lantern takes 4 bytes according to the rule for UTF-8 encoded strings mentioned in the website cited below.

2. Jack-o-lantern cannot be represented in C with a char because char can only store one byte. In contrast, wchar_t can store up to 4 bytes, which is enough for jack-o-lantern.

3.

```c
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
```

## Debrief

1. The website https://stackoverflow.com/questions/5290182/how-many-bytes-does-one-unicode-character-take helped me answer question 1. https://stackoverflow.com/questions/246806/i-want-to-convert-stdstring-into-a-const-wchar-t helped me answer question 2.

2. I spent five hours on this problem's questions.
