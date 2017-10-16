#include <string.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        return 1;
    }

    char buffer[5];
    strcpy(buffer, argv[1]);
    return 0;
}