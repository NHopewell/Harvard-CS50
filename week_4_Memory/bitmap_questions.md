# Questions

## What's `stdint.h`?

Including this header in your code file gives you access to type aliases which are just names for (in this  
case) integers of different sizes. Size is denoted by width in bits (for example 8, 16, 32, 64 bits). stdint  
also contains macros which are simply ways to give specificationsto these int type aliases. For instance, we  
can define the minimum and maximum value which can be put into one of these containers.  

A great reference here: https://en.wikibooks.org/wiki/C_Programming/stdint.h 


## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

'u' simply means unsigned (no negatives). uint8_t, uint16_t, and uint32_t simply refer to unsigned int  
conmtains of widths exactly 8, 16, and 32 bits. The same goes for int32_t except it supports signed nubers  
(where negatives are represented using the 2s position in the bit collection).  


## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

BYTE is an alias for uint8_t which is used for an int container of 8 bits or 1 byte.   
DWORD is an alias for uint32_t which is 32 bits or 4 bytes.  
LONG is an alias for int32_t which is 32 bits or 4 bytes.  
WORD is an alias for uint16_t which is 16 bits or 2 bytes. 


## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

The first 2 bytes of the BMP file format are the character "B" then the character "M" in ASCII encoding.

In decimal: 66 77

## What's the difference between `bfSize` and `biSize`?

biSize is the number of bytes the struc requires. bfSize is the size, in bytes, of the bitmap file. 

## What does it mean if `biHeight` is negative?

biHeight is the height of the bitmap file. If this value is negative, the bitmap is read top down with the upper left pixle as its origin. 

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount specifies the number of bits used to makeup each pixle. 

## Why might `fopen` return `NULL` in `copy.c`?

If there is an error, no file pointer will be returned and bey default NULL will be returned. 

## Why is the third argument to `fread` always `1` in our code?

The third arg specifies the number of elements (of size 'size') to read in. Each bitmap file has one header and one info header so we need to only read in 1 item, each the size of the teo strucs. 

## What value does `copy.c` assign to `padding` if `bi.biWidth` is `3`?

3

## What does `fseek` do?

The position (in numbert of bytes from start of file) to position the pointer. 

## What is `SEEK_CUR`?

SEEK_CUR is the current position of the pointer in the file.

