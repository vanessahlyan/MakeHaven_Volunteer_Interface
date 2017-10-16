#include <cs50.h>
#include <stdio.h>
bool balanced(int array[], int n);
int main(void)
{
    int my_array[5] = {16, 26, 39, 3, 39};
    printf("%d\n", balanced(my_array, 5));
}


bool balanced(int array[], int n)
{
    int left_sum = 0;
    int right_sum = 0;

    for (int index = 0; index < n/2; index++)
    {
        left_sum += array[index];
        right_sum += array[n-1-index];
    }

    if (left_sum == right_sum)
    {
        return true;
    }
    else
    {
        return false;
    }
}