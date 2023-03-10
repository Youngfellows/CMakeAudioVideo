#ifndef BITMAP_FILE_HEADER_H
#define BITMAP_FILE_HEADER_H

/*bmp file header*/
typedef struct
{
    unsigned short bfType;      /*bitmap type*/
    unsigned int bfSize;        /* Size of file */
    unsigned short bfReserved1; /* Reserved */
    unsigned short bfReserved2; /* ... */
    unsigned int bfOffBits;     /* Offset to bitmap data */
} BitmapFileHeader;

#endif