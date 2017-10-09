# Questions

## What's `stdint.h`?

'stdint.h' is a C standard library header file containing a set of typedefs and macros that specify exact-width integer types as well as define their min and max values. It allows users to make integer variables of custom sizes and make their code universal.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

You can fill up an exact amount of space in a file, such as for bitmap headers.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

A 'BYTE' consists of 1 byte = 8bits.
A 'DWORD' consists of 4 bytes = 32 bits.
A 'LONG' consists of 4 bytes = signed 32 bits.
A 'WORD' consists of 2 bytes = 16 bits.

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

in ASCII, the first two bytes of any BMP file must be a 'B' then an 'M'

## What's the difference between `bfSize` and `biSize`?

bfSize is the total number of bytes in the bmp file, including the image, the file header, and the info header.
biSize is the number of bytes in the info header.

## What does it mean if `biHeight` is negative?
The bitmap is top-down with the origin at the upper-left corner, instead of the lower-left.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount specifies the BMP's color depth.

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

if there is not enough memory or the file cannot be found, then fopen cannot open the file and will return NULL.

## Why is the third argument to `fread` always `1` in our code?

The third argument specifies how many elements we want to read. It's always 1 in our code because we're only reading one file.

## What value does line 65 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?
(4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4
=(4 - (3 * 3) % 4) % 4
=3

'Copy.c' assigns 3 to padding if 'bi.biWidth' is '3'.

## What does `fseek` do?

'fseek' allows us to change the cursor location in a file.

## What is `SEEK_CUR`?

'SEEK_CUR' indicates the current position in a file.
