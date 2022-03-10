/*
MIT License

Copyright (c) 2022 Abhishek Mishra <https://github.com/abhishekmishra>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <stdio.h>
#include <stdlib.h>

#define COLOR_NAMES_DIST_CSV_FILE "color-names/dist/colornames.bestof.csv"
#define COLOR_NAMES_FILE_HAS_HEADER 1
#define COLOR_HEX_LEN 7

int csv_counts(size_t *rows, size_t *maxlen_colorname);

int main(int argc, char *argv[])
{
    size_t rows, maxlen_colorname;

    // get the row count and max color name length
    csv_counts(&rows, &maxlen_colorname);
    printf("Num rows (excluding header) = %zd, longest color name length = %zd.\n", rows, maxlen_colorname);

    
}

int csv_counts(size_t *rows, size_t *maxlen_colorname)
{
    FILE *color_names_file;
    size_t col = 0, col_len = 0;
    *rows = 0;
    *maxlen_colorname = 0;

    color_names_file = fopen(COLOR_NAMES_DIST_CSV_FILE, "r");
    if (color_names_file == NULL)
    {
        printf("FATAL: unable to open colornames file at %s!"
               "Have you checked out the submodule?\n",
               COLOR_NAMES_DIST_CSV_FILE);
        return 1;
    }
    else
    {
        int c;
        while ((c = getc(color_names_file)) != EOF)
        {
            // putchar(c);
            if (c == '\n')
            {
                *rows += 1;
                col = 0;
                col_len = 0;
            }
            else if (c == ',')
            {
                // if the first column (color name column is ending)
                // check if its length is greater than the largest yet.
                if (col == 0)
                {
                    if (col_len > *maxlen_colorname)
                    {
                        *maxlen_colorname = col_len;
                    }
                }
                col += 1;
                col_len = 0;
            }
            else
            {
                col_len += 1;
            }
        }
        fclose(color_names_file);
    }

    // account for the header row
    if (rows > 0) {
        rows -= 1;
    }
    return 0;
}