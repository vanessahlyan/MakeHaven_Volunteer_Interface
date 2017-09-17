#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


int main(int argc, string argv[])

{
    if ((argc != 2) || argv < 0)
    {
        printf("Error! You must provide 2 arguments in the command line.");
        return 1;
    }

    else
    {

        //get an integer value for the key
        int key = atoi(argv[1]);

        //get the plaintext string
        string plaintext = get_string("Enter the plaintext: ");
        int plaintext_length = strlen(plaintext);

        printf("plaintext: %s\n", plaintext);
        printf("ciphertext: ");

        //going through all elements of the plaintext
        for (int i = 0; i < plaintext_length; i++)
        {
            char c = plaintext[i];

            //check if character is alphabetical
            if (isalpha(c) == 0)
            {
                //print unciphered character
                printf("%c", c);
            }

            else if (isalpha(c) != 0)
            {
                //check if character is lower case
                if (islower(c) != 0)
                {
                    //switching to alphabetical index and shifting by key
                    int alphabet_index = (c - 97 + key) % 26;
                    //switching back to ascii index
                    int new_ascii_index = alphabet_index + 97;
                    //print new ciphered alphabetical character
                    printf("%c", new_ascii_index);

                }


                //check if character is upper case
                else if (isupper(c) != 0)
                {
                    //switching to alphabetical index and shifting by key
                    int alphabet_index = (c - 65 + key) % 26;
                    //switching back to ascii index
                    int new_ascii_index = alphabet_index + 65;
                    //print new ciphered alphabetical character
                    printf ("%c", new_ascii_index);
                }



            }

        }
        printf("\n");
        return 0;
    }


}



