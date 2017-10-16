# Fair and Balanced

## Questions

1. Yes because 16 + 26 = 42 = 3 + 39

2. Yes because 0 + 0 = 0 = 0 + 0

3.

```c
#include <cs50.h>
bool balanced(int array[], int n);
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
```

## Debrief

1. I looked back on the notes I took on function declaration and definition in Discussion Section in week 2.

2. I spent 15 minutes on this problem's questions.
