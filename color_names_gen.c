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
#include <math.h>

/** path to the color names csv file **/
#define COLOR_NAMES_DIST_CSV_FILE "color-names/dist/colornames.bestof.csv"

/** whether the file has header **/
#define COLOR_NAMES_FILE_HAS_HEADER 1

/** length of the hex string of form #rrggbb **/
#define COLOR_HEX_LEN 7

/** name of the color_names.c template file **/
#define COLOR_NAMES_TEMPLATE_FNAME "color_names.template.c"

/** output c file name **/
#define COLOR_NAMES_C_FNAME "color_names.c"

/** begin marker in the template **/
#define COLOR_NAMES_TEMPLATE_MARKER_BEGIN "// generated color names begin"

/** end marker in the template **/
#define COLOR_NAMES_TEMPLATE_MARKER_END "// generated color names end"

/** max line length in the template file **/
#define MAX_TEMPLATE_LINE_LEN 1024

/** max value of RGB individual values **/
#define MAX_COLOR_CHANNEL_VALUE 255.0

/** max value of HSV individual values **/
#define MAX_HSV_CHANNEL_VALUE 100.0

/** see https://stackoverflow.com/a/3437484/9483968 **/
#define max(a,b) \
    ({ __typeof__ (a) _a = (a); \
        __typeof__ (b) _b = (b); \
        _a > _b ? _a : _b; })

#define min(a,b) \
    ({ __typeof__ (a) _a = (a); \
        __typeof__ (b) _b = (b); \
        _a < _b ? _a : _b; })

typedef enum
{
    COLOR_NAMES = 1,
    COLOR_HEX_STR,
    COLOR_RGB,
    COLOR_HSV
} out_col_t;

/**
 * Get the row count and length of the longest color name
 * from the csv color-names file
 * 
 * @param rows output var for row count
 * @param maxlen_colorname output var for length of longest color name
 * @return 
 */
int csv_counts(size_t *rows, size_t *maxlen_colorname);

/**
 * convert hex string to rgb triple
 * HSV conversion implementation is based on the article at
 * https://mattlockyer.github.io/iat455/documents/rgb-hsv.pdf
 * h value range modified to be 360 deg based on
 * https://www.geeksforgeeks.org/program-change-rgb-color-model-hsv-color-model/
 * 
 * @param hex hex string
 * @param r red output var
 * @param g green output var
 * @param b blue output var
 */
void color_hex_to_rgb(char *hex, uint8_t *r, uint8_t *g, uint8_t *b);

/**
 * convert hex string to rgb triple
 * 
 * @param hex hex string
 * @param h hue output var
 * @param s saturation output var
 * @param v value output var
 */
void color_hex_to_hsv(char *hex, float *h, float *s, float *v);

/**
 * Write color names column to the output c file.
 * 
 * @param c_file the output file handle
 * @param total_rows total rows to write
 * @param type the column type to write
 * 
 * @return error code
 */ 
int csv_color_names_write(FILE *c_file, size_t total_rows, out_col_t type);

/**
 * util method that writes the c program
 * 
 * @return error code
 */
int write_color_names_c_program();

// some hsv value tests
void test_hsv()
{
    float h, s, v;

    char* colors[] = {
        "#ff0000",
        "#00ff00",
        "#0000ff",
        "#880000",
        "#008800",
        "#000088",
        "#884400",
        "#008844",
        "#440088",
        "#884422",
        "#228844",
        "#442288",
        "#000000",
        "#111111",
        "#888888",
        "#eeeeee",
        "#ffffff",
        "#202124", //noble black
        NULL
    };

    int i = 0;
    while (colors[i] != NULL)
    {
        char *col = colors[i];
        color_hex_to_hsv(col, &h, &s, &v);
        printf("%s = hsv (%f, %f, %f)\n", col, h, s, v);
        i += 1;
    }
}

/** ************* MAIN ***************
 *  write the color_names.c program
 */
int main(int argc, char *argv[])
{

    int res = write_color_names_c_program();

    // uncomment to run hsv test
    test_hsv();

    return res;
}

int csv_counts(size_t *rows, size_t *maxlen_colorname)
{
    FILE *color_names_file;
    size_t col = 0, col_len = 0;
    *rows = 0;
    *maxlen_colorname = 0;

    // read file to establish num rows and column length etc.

    // Open the color names csv file
    color_names_file = fopen(COLOR_NAMES_DIST_CSV_FILE, "r");

    // if the file is NULL, print an error and return error code
    // else start reading the file.
    if (color_names_file == NULL)
    {
        printf("FATAL: unable to open colornames file at %s!"
               "Have you checked out the submodule?\n",
               COLOR_NAMES_DIST_CSV_FILE);
        return 1;
    }
    else
    {
        // set previous char and current char to 0
        int prev = 0, c = 0;

        // read one character from the file till EOF
        while ((c = getc(color_names_file)) != EOF)
        {
            // putchar(c);

            // if the character is newline, increment the row count,
            // reset the column count to 0 and column length to 0
            if (c == '\n')
            {
                *rows += 1;
                col = 0;
                col_len = 0;
            }
            else if (c == ',')
            {
                // if char is comma then the current column is done

                // if the first column (color name column is ending)
                // check if its length is greater than the largest yet.
                if (col == 0)
                {
                    if (col_len > *maxlen_colorname)
                    {
                        *maxlen_colorname = col_len;
                    }
                }
                
                // increment the column count and reset column length to 0
                col += 1;
                col_len = 0;
            }
            else
            {
                // if character is neither line separator or column separator
                // then increment the column length
                col_len += 1;
            }
            prev = c;
        }

        // if the previous char is 0, i.e. this is the first character
        // then increment the row count.
        if (prev != 0)
        {
            *rows += 1;
        }

        // close the file
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

void color_hex_to_rgb(char *hex, uint8_t *r, uint8_t *g, uint8_t *b)
{
    // create 3 null-terminated strings of
    // the r, g, and b pairs
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

    // get the numeric value from the strings
    // for r, g, b
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

void color_hex_to_hsv(char *hex, float *h, float *s, float *v)
{
    uint8_t r, g, b;
    float rs, gs, bs; // scaled values
    float max_color, min_color, delta;

    // get the rgb value from the hex string
    color_hex_to_rgb(hex, &r, &g, &b);

    // get the scaled rgb values
    rs = r / MAX_COLOR_CHANNEL_VALUE;
    gs = g / MAX_COLOR_CHANNEL_VALUE;
    bs = b / MAX_COLOR_CHANNEL_VALUE;

    // get the max and min values
    max_color = max(rs, max(gs, bs));
    min_color = min(rs, min(gs, bs));
    delta = max_color - min_color;

    // calculate the HUE
    if (delta == 0)
    {
        *h = 0;
    }
    else 
    {
        if(max_color == rs)
        {
            *h = fmod((60 * ((gs - bs) / delta) + 360), 360);
        }
        if(max_color == gs)
        {
            *h = fmod((60 * ((rs - bs) / delta) + 120), 360);
        }
        if(max_color == bs)
        {
            *h = fmod((60 * ((rs - gs) / delta) + 240), 360);
        }
    }

    *v = max_color * MAX_HSV_CHANNEL_VALUE;
    
    if(*v == 0)
    {
        *s = 0;
    }
    else
    {
        float sval = delta / max_color;
        sval = sval * MAX_HSV_CHANNEL_VALUE;
        *s = sval;
    }
}

int csv_color_names_write(FILE *c_file, size_t total_rows, out_col_t type)
{
    FILE *color_names_file;
    size_t col = 0, col_len = 0;
    size_t rows = 0;

    // Read the csv file to write the values into the color_names c file.

    // open the color names csv
    color_names_file = fopen(COLOR_NAMES_DIST_CSV_FILE, "r");

    // if the file is NULL print and error and return error code
    // else start reading the file
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
        float h, s, v;

        // read one character from file till it is not EOF
        while ((c = getc(color_names_file)) != EOF)
        {
            // putchar(c);

            if (c == '\n')
            {
                // if the character is a newline the row is ended

                // if the second column then print the hex string, rgb, or hsv
                // based on the value type passed in the call to the function
                // also check if the rows>0 to only do this when reading the
                // data rows. (rows = 0 is the header row)
                if (col == 1)
                {
                    if (type == COLOR_HEX_STR && rows > 0)
                    {
                        fprintf(c_file, "\"%s\"%s\n", 
                            colval, (rows != total_rows) ? "," : "");
                    }
                    if (type == COLOR_RGB && rows > 0)
                    {
                        color_hex_to_rgb(colval, &r, &g, &b);
                        fprintf(c_file, "{%hu, %hu, %hu}%s\n", 
                            r, g, b, (rows != total_rows) ? "," : "");
                    }
                    if (type == COLOR_HSV && rows > 0)
                    {
                        color_hex_to_hsv(colval, &h, &s, &v);
                        fprintf(c_file, "{%f, %f, %f}%s\n", 
                            h, s, v, (rows != total_rows) ? "," : "");
                    }
                }
                rows += 1;
                col = 0;
                col_len = 0;
                memset(colval, 0, 1024);
            }
            else if (c == ',')
            {
                // if the first column write the color name if that is
                // the column value passed to the function.
                if (col == 0)
                {
                    if (type == COLOR_NAMES && rows > 0)
                    {
                        // convert column value (color name) to lowercase
                        for(int i = 0; i < strlen(colval); i++)
                        {
                            colval[i] = tolower(colval[i]);
                        }

                        fprintf(c_file, "\"%s\"%s\n", 
                            colval, (rows != total_rows) ? "," : "");
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

        // if the second column then print the hex string, rgb, or hsv
        // based on the value type passed in the call to the function
        // also check if the rows>0 to only do this when reading the
        // data rows. (rows = 0 is the header row)
        if (col == 1)
        {
            if (type == COLOR_HEX_STR && rows > 0)
            {
                fprintf(c_file, "\"%s\"%s\n", 
                    colval, (rows != total_rows) ? "," : "");
            }
            if (type == COLOR_RGB && rows > 0)
            {
                color_hex_to_rgb(colval, &r, &g, &b);
                fprintf(c_file, "{%hu, %hu, %hu}%s\n", 
                    r, g, b, (rows != total_rows) ? "," : "");
            }
            if (type == COLOR_HSV && rows > 0)
            {
                color_hex_to_hsv(colval, &h, &s, &v);
                fprintf(c_file, "{%f, %f, %f}%s\n", 
                    h, s, v, (rows != total_rows) ? "," : "");
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
        printf("Num rows (excluding header) = %zd, \
            longest color name length = %zd.\n", rows, maxlen_colorname);
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
                    fprintf(c_file, "static const char \
                        COLOR_NAMES[%zd][%zd] = {\n", rows, 
                        maxlen_colorname + 1);
                    csv_color_names_write(c_file, rows, COLOR_NAMES);
                    fprintf(c_file, "};\n\n");

                    fprintf(c_file, "static const char \
                        COLOR_RGB_HEXSTR[%zd][%d] = {\n", rows, 
                        COLOR_HEX_LEN + 1);
                    csv_color_names_write(c_file, rows, COLOR_HEX_STR);
                    fprintf(c_file, "};\n\n");

                    fprintf(c_file, "static const uint8_t \
                        COLOR_RGB_TRIPLE[%zd][3] = {\n", rows);
                    csv_color_names_write(c_file, rows, COLOR_RGB);
                    fprintf(c_file, "};\n\n");

                    fprintf(c_file, "static const float \
                        COLOR_HSV_TRIPLE[%zd][3] = {\n", rows);
                    csv_color_names_write(c_file, rows, COLOR_HSV);

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
