// Helper functions for music

#include <cs50.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "helpers.h"
#include <math.h>


// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    //access individual characters in the string
    int numerator = fraction[0] - 48; //subtract 48 bcuz the ascii value for '0' is 48
    double numerator_as_double = 1.0 * numerator;

    int denominator = fraction[2] - 48;

    double value_of_function = numerator_as_double / denominator;

    double number_of_eighths = value_of_function / (.125);
    return number_of_eighths;
}



//Calculates frequency (in Hz) of a note
int frequency(string note)
{
    //Let n = number of semitones from A4 to the note, initialize n as 0
    int n = 0;

    //if the note is not an accidental
    if (strlen(note) == 2)
    {
        char letter = note[0];
        int octave = note[1] - 48;
        //subtracted 48 bcuz the ascii value for '0' is 48

        //adjust n by the (difference between the octaves)* (number of semitones in an octave)
        n += (octave - 4) * 12;


        //then, adjust n by difference between semitones within the octave using a switch function
        switch (letter)
        {
            case 'C':
                n += -9;
                break;
            case 'D':
                n += -7;
                break;
            case 'E':
                n += -5;
                break;
            case 'F':
                n += -4;
                break;
            case 'G':
                n += -2;
                break;
            case 'A':
                n += 0;
                break;
            case 'B':
                n += 2;
                break;
        }

    }


    //if the note is an accidental
    else if (strlen(note) == 3)
    {
        char letter = note[0];
        int octave = note[2] - 48;
        //subtracted 48 bcuz the ascii value for '0' is 48

        //adjust n by the (difference between the octaves)* (number of semitones in an octave)
        n += (octave - 4) * 12;


        //then, adjust n by difference between semitones within the octave
        //if the note is a sharp
        if (note[1] == '#')
        {
            switch (letter)
            {
                case 'C':
                    n += -8;
                    break;
                case 'D':
                    n += -6;
                    break;
                case 'E':
                    n += -4;
                    break;
                case 'F':
                    n += -3;
                    break;
                case 'G':
                    n += -1;
                    break;
                case 'A':
                    n += 1;
                    break;
                case 'B':
                    n += -9;
                    break;
            }


        }



        //if the note is a flat
        else if (note[1] == 'b')
        {
            switch (letter)
            {
                case 'C':
                    n += 2;
                    break;
                case 'D':
                    n += -8;
                    break;
                case 'E':
                    n += -6;
                    break;
                case 'F':
                    n += -5;
                    break;
                case 'G':
                    n += -3;
                    break;
                case 'A':
                    n += -1;
                    break;
                case 'B':
                    n += 1;
                    break;
            }
        }

        else
        {
            printf("Invalid input");
        }
    }

    else
    {
        printf("Invalid input");
    }


    //calculating frequency given n
    double frequency = pow(2, n / 12.0) * 440;
    return round(frequency);

}



// Determines whether a string represents a rest
bool is_rest(string s)
{
    if (strlen(s) == 0)
    {
        return true;
    }

    else
    {
        return false;
    }
}


