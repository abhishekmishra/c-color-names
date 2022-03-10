/*

############### c-color-names License

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

############### color-names License

MIT License

Copyright (c) 2017 David Aerne

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
#include <string.h>
#include <stdint.h>
#include <ctype.h>

#define COLOR_NAMES_DIST_CSV_FILE "color-names/dist/colornames.bestof.csv"
#define COLOR_NAMES_FILE_HAS_HEADER 1
#define COLOR_HEX_LEN 7

#define COLOR_NAMES_TEMPLATE_FNAME "color_names.template.c"
#define COLOR_NAMES_C_FNAME "color_names.c"
#define COLOR_NAMES_TEMPLATE_MARKER_BEGIN "// generated color names begin"
#define COLOR_NAMES_TEMPLATE_MARKER_END "// generated color names end"
#define MAX_TEMPLATE_LINE_LEN 1024

typedef enum
{
    COLOR_NAMES = 1,
    COLOR_HEX_STR,
    COLOR_HEX_NUM
} out_col_t;

int csv_counts(size_t *rows, size_t *maxlen_colorname);
void color_hex_to_triple(char *hex, uint8_t *r, uint8_t *g, uint8_t *b);
int csv_color_names_write(FILE *c_file, size_t total_rows, out_col_t type);
int write_color_names_c_program();

int main(int argc, char *argv[])
{
    int res = write_color_names_c_program();
    return res;
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
        int prev = 0, c = 0;
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
            prev = c;
        }
        if (prev != 0)
        {
            *rows += 1;
        }
        fclose(color_names_file);
    }

    // account for the header row
    if (*rows > 0)
    {
        *rows -= 1;
    }
    return 0;
}

// int count = 0;

uint8_t getNumFromHexStr(char *inp)
{
    // if (count < 3)
    // {
    //     printf("%s = %d, %hu\n", inp, strtoul(inp, NULL, 16), (uint8_t)strtoul(inp, NULL, 16));
    // }
    return (uint8_t)strtoul(inp, NULL, 16);
}

void color_hex_to_triple(char *hex, uint8_t *r, uint8_t *g, uint8_t *b)
{
    char rstr[3], gstr[3], bstr[3];
    rstr[0] = hex[1];
    rstr[1] = hex[2];
    gstr[0] = hex[3];
    gstr[1] = hex[4];
    bstr[0] = hex[5];
    bstr[1] = hex[6];

    rstr[2] = '\0';
    gstr[2] = '\0';
    bstr[2] = '\0';

    *r = getNumFromHexStr(rstr);
    *g = getNumFromHexStr(gstr);
    *b = getNumFromHexStr(bstr);

    // if (count < 3)
    // {
    //     printf("%s -> [%hu, %hu, %hu]\n",
    //            hex, r, g, b);
    //     count += 1;
    // }
}

int csv_color_names_write(FILE *c_file, size_t total_rows, out_col_t type)
{
    FILE *color_names_file;
    size_t col = 0, col_len = 0;
    size_t rows = 0;

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
        char colval[1024];
        memset(colval, 0, 1024);
        uint8_t r, g, b;

        while ((c = getc(color_names_file)) != EOF)
        {
            // putchar(c);
            if (c == '\n')
            {
                // if the second column
                if (col == 1)
                {
                    if (type == COLOR_HEX_STR && rows > 0)
                    {
                        fprintf(c_file, "\"%s\"%s\n", colval, (rows != total_rows) ? "," : "");
                    }
                    if (type == COLOR_HEX_NUM && rows > 0)
                    {
                        color_hex_to_triple(colval, &r, &g, &b);
                        fprintf(c_file, "{%hu, %hu, %hu}%s\n", r, g, b, (rows != total_rows) ? "," : "");
                    }
                }
                rows += 1;
                col = 0;
                col_len = 0;
                memset(colval, 0, 1024);
            }
            else if (c == ',')
            {
                // if the first column
                if (col == 0)
                {
                    if (type == COLOR_NAMES && rows > 0)
                    {
                        for(int i = 0; i < strlen(colval); i++){
                          colval[i] = tolower(colval[i]);
                        }

                        fprintf(c_file, "\"%s\"%s\n", colval, (rows != total_rows) ? "," : "");
                    }
                }
                col += 1;
                col_len = 0;
                memset(colval, 0, 1024);
            }
            else
            {
                colval[col_len] = c;
                col_len += 1;
            }
        }

        // if the second column
        if (col == 1)
        {
            if (type == COLOR_HEX_STR && rows > 0)
            {
                fprintf(c_file, "\"%s\"%s\n", colval, (rows != total_rows) ? "," : "");
            }
            if (type == COLOR_HEX_NUM && rows > 0)
            {
                color_hex_to_triple(colval, &r, &g, &b);
                fprintf(c_file, "{%hu, %hu, %hu}%s\n", r, g, b, (rows != total_rows) ? "," : "");
            }
        }

        fclose(color_names_file);
    }

    return 0;
}

int write_color_names_c_program()
{
    int res;
    size_t rows, maxlen_colorname;
    FILE *template_file, *c_file;

    // Step 1: get the row count and max color name length
    res = csv_counts(&rows, &maxlen_colorname);
    if (res == 0)
    {
        printf("Num rows (excluding header) = %zd, longest color name length = %zd.\n", rows, maxlen_colorname);
    }
    else
    {
        printf("FATAL: error processing color names csv file.\n");
        return res;
    }

    // Step 2: open template file for reading
    template_file = fopen(COLOR_NAMES_TEMPLATE_FNAME, "r");
    if (template_file == NULL)
    {
        printf("FATAL: unable to open template file at %s!\n",
               COLOR_NAMES_TEMPLATE_FNAME);
        return 1;
    }

    // open c file for writing
    c_file = fopen(COLOR_NAMES_C_FNAME, "w");
    if (c_file == NULL)
    {
        printf("FATAL: unable to open c file at %s for writing!\n",
               COLOR_NAMES_C_FNAME);
        return 1;
    }

    char line[MAX_TEMPLATE_LINE_LEN + 1];
    memset(line, 0, MAX_TEMPLATE_LINE_LEN + 1);
    size_t line_count = 0, line_pos = 0;
    int c, in_gen_region = 0, wrote_colors = 0;

    while ((c = getc(template_file)) != EOF)
    {
        // putchar(c);
        if (c == '\n' || c == '\r')
        {
            if (strcmp(line, COLOR_NAMES_TEMPLATE_MARKER_END) == 0)
            {
                printf("MARKER END\n");
                in_gen_region = 0;
            }

            if (in_gen_region == 0)
            {
                printf("%3zd: %s\n", line_count, line);
                fprintf(c_file, "%s\n", line);
            }
            else
            {
                if (wrote_colors == 0)
                {
                    fprintf(c_file, "#define NUM_COLORS\t%zd\n\n", rows);
                    fprintf(c_file, "static const char COLOR_NAMES[%zd][%zd] = {\n", rows, maxlen_colorname + 1);
                    csv_color_names_write(c_file, rows, COLOR_NAMES);
                    fprintf(c_file, "};\n\n");

                    fprintf(c_file, "static const char COLOR_RGB_HEXSTR[%zd][%d] = {\n", rows, COLOR_HEX_LEN + 1);
                    csv_color_names_write(c_file, rows, COLOR_HEX_STR);
                    fprintf(c_file, "};\n\n");

                    fprintf(c_file, "static const char COLOR_RGB_TRIPLE[%zd][%d][3] = {\n", rows, COLOR_HEX_LEN + 1);
                    csv_color_names_write(c_file, rows, COLOR_HEX_NUM);
                    fprintf(c_file, "};\n\n");

                    wrote_colors = 1;
                }
            }

            if (strcmp(line, COLOR_NAMES_TEMPLATE_MARKER_BEGIN) == 0)
            {
                printf("MARKER BEGIN\n");
                in_gen_region = 1;
            }

            line_count += 1;
            memset(line, 0, MAX_TEMPLATE_LINE_LEN + 1);
            line_pos = 0;
        }
        else
        {
            line[line_pos] = c;
            line_pos += 1;
            if (line_pos > (MAX_TEMPLATE_LINE_LEN + 1))
            {
                printf("Fatal: no more space in buffer!\n");
                return 2;
            }
        }
    }

    // handle the last line if there was no newline
    printf("%3zd: %s\n", line_count, line);
    if (in_gen_region == 0)
    {
        fprintf(c_file, "%s\n", line);
    }

    fclose(c_file);
    fclose(template_file);

    return 0;
}