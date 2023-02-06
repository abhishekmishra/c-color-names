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
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "color_names.h"

// generated color names begin
#define NUM_COLORS 2

static const char COLOR_NAMES[2][6] = {
    "red",
    "black"};

static const char COLOR_RGB_HEXSTR[2][8] = {
    "#ff0000",
    "#000000"};

static const uint8_t COLOR_RGB_TRIPLE[2][3] = {
    {255, 0, 0},
    {0, 0, 0}};

static const uint8_t COLOR_HSV_TRIPLE[2][3] = {
    {0, 100, 100},
    {0, 0, 0}};

// generated color names end

#define FLOAT_EPSILON 0.01f

int compare_float(float x, float y)
{
    if(fabs(x - y) < FLOAT_EPSILON)
    {
        return 1; //they are same
    }
    else
    {
        return 0; //they are not same
    }
}

int get_color_index(const char *color_name, size_t *index)
{
    for (size_t i = 0; i < NUM_COLORS; i++)
    {
        if (strcmp(COLOR_NAMES[i], color_name) == 0)
        {
            *index = i;
            return 1;
        }
    }

    // not found
    return 0;
}

int get_rgb_index(uint8_t r, uint8_t g, uint8_t b, size_t *index)
{
    for (size_t i = 0; i < NUM_COLORS; i++)
    {
        if (COLOR_RGB_TRIPLE[i][0] == r
            && COLOR_RGB_TRIPLE[i][1] == g
            && COLOR_RGB_TRIPLE[i][2] == b)
        {
            *index = i;
            return 1;
        }
    }

    // not found
    return 0;
}

int get_hsv_index(float h, float s, float v, size_t *index)
{
    for (size_t i = 0; i < NUM_COLORS; i++)
    {
        if (compare_float(COLOR_HSV_TRIPLE[i][0], h)
            && compare_float(COLOR_HSV_TRIPLE[i][1], s)
            && compare_float(COLOR_HSV_TRIPLE[i][2], v))
        {
            *index = i;
            return 1;
        }
    }

    // not found
    return 0;
}

int get_hex_index(const char *color_hex, size_t *index)
{
    for (size_t i = 0; i < NUM_COLORS; i++)
    {
        if (strcmp(COLOR_RGB_HEXSTR[i], color_hex) == 0)
        {
            *index = i;
            return 1;
        }
    }

    // not found
    return 0;
}

int color_name_exists(const char *color_name)
{
    if (color_name != NULL)
    {
        size_t idx;
        return get_color_index(color_name, &idx);
    }
    else
    {
        return 0;
    }
}

int color_name_get_rgb_string(const char *color_name, char* color_hex_str)
{
    size_t idx;
    int found = 0;

    if (color_name == NULL)
    {
        return 0;
    }

    found = get_color_index(color_name, &idx);

    if (found == 0)
    {
        return 0;
    }
    else
    {
        strcpy(color_hex_str, COLOR_RGB_HEXSTR[idx]);
        return 1;
    }
}

int color_name_get_rgb(const char *color_name, uint8_t *r, uint8_t *g, uint8_t *b)
{
    size_t idx;
    int found = 0;

    if (color_name == NULL)
    {
        return 0;
    }

    found = get_color_index(color_name, &idx);

    if (found == 0)
    {
        return 0;
    }
    else
    {
        *r = COLOR_RGB_TRIPLE[idx][0];
        *g = COLOR_RGB_TRIPLE[idx][1];
        *b = COLOR_RGB_TRIPLE[idx][2];
        return 1;
    }
}

const char* color_name_find_rgb(uint8_t r, uint8_t g, uint8_t b)
{
    size_t idx;
    int found = 0;

    found = get_rgb_index(r, g, b, &idx);

    if (found == 0)
    {
        return NULL;
    }
    else
    {
        return COLOR_NAMES[idx];
    }
}

int color_name_get_hsv(const char *color_name, float *h, float *s, 
    float *v)
{
    size_t idx;
    int found = 0;

    if (color_name == NULL)
    {
        return 0;
    }

    found = get_color_index(color_name, &idx);

    if (found == 0)
    {
        return 0;
    }
    else
    {
        *h = COLOR_HSV_TRIPLE[idx][0];
        *s = COLOR_HSV_TRIPLE[idx][1];
        *v = COLOR_HSV_TRIPLE[idx][2];
        return 1;
    }
}

const char* color_name_find_hsv(float h, float s, float v)
{
    size_t idx;
    int found = 0;

    found = get_hsv_index(h, s, v, &idx);

    if (found == 0)
    {
        return NULL;
    }
    else
    {
        return COLOR_NAMES[idx];
    }
}

const char* color_name_find_hex(const char* hex)
{
    size_t idx;
    int found = 0;

    // return NULL if hex is NULL or not 7 chars in length
    if (hex == NULL || strlen(hex) != 7)
    {
        return NULL;
    }

    found = get_hex_index(hex, &idx);

    if (found == 0)
    {
        return NULL;
    }
    else
    {
        return COLOR_NAMES[idx];
    }

}