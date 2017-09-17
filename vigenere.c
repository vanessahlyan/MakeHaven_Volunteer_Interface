#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


int main(int argc, string argv[])

{
    //check if there are 2 command line arguments
    if ((argc != 2) || argv < 0)
    {
        printf("Error! You must provide 2 arguments in the command line.");
        return 1;
    }


    //proceed if command line is valid
    else
    {
        string key = argv[1];
        int key_length = strlen(key);

        //check if every character in key is alphabetical
        for (int key_counter = 0; key_counter < key_length; key_counter++)
        {
            //if not all are alphabetical
            if (isalpha(key[key_counter]) == 0)
            {
                printf("Your key must only have alphabetical characters.\n");
                return 1;
            }
        }


        //get plain_text string
        string plaintext = get_string("Enter the plaintext: ");
        int plain_length = strlen(plaintext);
        printf("plaintext: %s\n", plaintext);
        printf("ciphertext: ");


        //loop through the plain_text, j is position in plain_text
        for (int plain_counter = 0, key_counter = 0; plain_counter < plain_length; plain_counter++)
        {
            char c = plaintext[plain_counter];
            //if character is not alphabetical, print the unciphered character
            if (isalpha(c) == 0)
            {
                printf("%c", c);
            }

            //if character is alphabetical, find ascii value of character, add key_counter by 1, add the shift
            else if (isalpha(c) != 0)
            {

                //find ascii value of key character
                char key_character = tolower(key[key_counter % key_length]);
                int alphabet_key = key_character - 97;

                //add key_counter by 1
                key_counter += 1;

                //check if character is lower case
                if (islower(c) != 0)
                {
                    //shifting by key
                    int new_alphabet_index = (c - 97 + alphabet_key) % 26;
                    int new_ascii_index = new_alphabet_index + 97;
                    //print new ciphered alphabetical character
                    printf("%c", new_ascii_index);
                }

                // check if character is upper case
                else if (isupper(c) != 0)
                {
                    //shifting by key
                    int new_alphabet_index = (c - 65 + alphabet_key) % 26;
                    int new_ascii_index = new_alphabet_index + 65;
                    //print new ciphered alphabetical character
                    printf("%c", new_ascii_index);
                }

            }

        }
        printf("\n");
        return 0;
    }


}



