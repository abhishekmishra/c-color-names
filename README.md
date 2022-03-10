# c-color-names
ANSI C API for the excellent collection of colors in [color-names](https://github.com/meodai/color-names) package.

### Docs
For detailed documentation see color_names.h

### Sample Usage
Include color_names.h in program and build with color_names.c.

```c
uint8_t r, g, b;
int found = color_name_get_rgb("red", &r, &g, &b);
if (found == 1)
{
    printf("color name red, rgb triple = [%hu, %hu, %hu].\n",
            r, g, b);
}

// output :-
// color name red, rgb triple = [255, 0, 0].
```
