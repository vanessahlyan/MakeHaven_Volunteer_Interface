# Z++

## Questions

1.

```
function subtract($x, $y)
{
    return (add($x, -$y))
}
```

2.

```
function multiply($x, $y)
{
    $count <- 0
    $result <- 0

    if (0 < $y)
    {
        while ($count < $y)
        {
            //keep adding x until your count gets to y times
            result <- add($result, $x)
            count <- add($count, 1)
        }
    }


    if ($y < 0)
    {
        while ($y < $count)
        {
            //keep subtracting x as your count gets more and more negative and reaches y
            result <- subtract($result, $x)
            count <- subtract($count, 1)
        }
    }
    return ($result)
}
```


3.

```
//use recursion
function multiply($x, $y)
{
    //base cases of the recursion
    //express if (true) under the constraints of the Z++ language: when y is 0, the subtraction yields 0, not 0 is equivalent to true
    if (not(subtract($y, 0)))
    {
        return (0);
    }

    if (not(subtract($x, 0)))
    {
        return (0);
    }


    //recursive cases
    if (0 < $y)
    {
       //add x to the existing result every time
       //the subtraction will eventually bring y to 0 when we can refer to the base case
       return (add($x, multiply($x, subtract($y, 1))));
    }

    if ($y < 0)
    {
        //subtract x from the existing result every time
        //the addition will eventually bring y from a negative number to 0
        return subtract(multiply($x, add($y, 1)), $x);
    }

```


## Debrief

1. I found last year's sample exam helpful in answering this problem's questions.

2. I spent 35 minutes on this problem's questions.
