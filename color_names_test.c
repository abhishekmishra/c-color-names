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
#include <string.h>
#include "color_names.h"

int main(int argc, char *argv[])
{
    uint8_t r, g, b;
    float h, s, v;
    int found = 0;
    char hexstr[8];
    memset(hexstr, 0, 8);

    // get color names for existing and non-existing colors
    printf("color name red exists = [%d].\n", color_name_exists("red"));
    printf("color name sad exists = [%d].\n", color_name_exists("sad"));

    // get the hex string for red
    found = color_name_get_rgb_string("red", hexstr);
    printf("color name red hexstr = [%s].\n",
           found == 0 ? "not found" : hexstr);

    // get rgb value for red
    found = color_name_get_rgb("red", &r, &g, &b);
    if (found == 1)
    {
        printf("color name red, rgb triple = [%hu, %hu, %hu].\n",
               r, g, b);
    }

    // get hsv value for red
    found = color_name_get_hsv("red", &h, &s, &v);
    if (found == 1)
    {
        printf("color name red, hsv triple = [%f, %f, %f].\n",
               h, s, v);
    }

    // color 'noble black'
    r = 32;
    g = 33;
    b = 36;

    // get the color name for given r,g,b value
    const char *c = color_name_find_rgb(r, g, b);
    if(c == NULL)
    {
        printf("color name for rgb [%hu, %hu, %hu] not found!\n", r, g, b);
    }
    else
    {
        printf("color name for rgb [%hu, %hu, %hu] is '%s'\n", r, g, b, c);
    }

    // color 'noble black'
    h = 225.0f;
    s = 11.11f;
    v = 14.11f;

    // get the color name for given h,s,v value
    c = color_name_find_hsv(h, s, v);
    if(c == NULL)
    {
        printf("color name for hsv [%f, %f, %f] not found!\n", h, s, v);
    }
    else
    {
        printf("color name for hsv [%f, %f, %f] is '%s'\n", h, s, v, c);
    }

    char *hex = "#202124"; // noble black

    // get the color name for given hex string
    c = color_name_find_hex(hex);
    if(c == NULL)
    {
        printf("color name for hex [%s] not found!\n", hex);
    }
    else
    {
        printf("color name for hex [%s] is '%s'\n", hex, c);
    }
}