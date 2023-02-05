# C-COLOR-NAMES Documentation           {#mainpage}

[TOC]

ANSI C API for the excellent collection of colors in the
[color-names](https://github.com/meodai/color-names) package.

**NOTE: This library is still under development. The public API is unstable 
till the library reaches beta status. There will be breaking changes in public 
API if needed.**

# Usage

## Install

The recommended method of using this library is to copy two source files into
your own codebase, and include it in the build.
1. `color_names.h`: header file
2. `color.names.c`: implementaion file

## Use

Include color_names.h in program and and make sure to build with color_names.c.

```c
#include <stdio.h>
#include <stdlib.h>
#include "color_names.h"

int main(int argc, char* argv[])
{
    // declare 8-bit integers to hold r,g,b values
    // range of r,g,b values is [0, 255]
    uint8_t r, g, b;
 
    // fetch the r,g,b values for color 'red'
    int found = color_name_get_rgb("red", &r, &g, &b);
 
    // if the color name 'red' was found, print the r,g,b values
    if (found == 1)
    {
        printf("color name red, rgb triple = [%hu, %hu, %hu].\n",
                r, g, b);
    }

    exit(0);
}

// output :-
// color name red, rgb triple = [255, 0, 0].
```

# API

The public API of the library is provided by 
[color_names.h](@ref color_names.h).

# Install & Build

If you wish to build the project locally for experimentation or to make
any changes, setup a local development environment as described in 
[BUILD](@ref docs/Build.md).

# Release Notes
* The current release is 
  [v0.1.0-alpha.0](https://github.com/abhishekmishra/c-color-names/releases/tag/v0.1.0-alpha.0)
* Release notes for all releases are at [CHANGELOG](@ref CHANGELOG.md).

# License
* The library is released under the __MIT License__. See the `LICENSE` file
  in the source for details.