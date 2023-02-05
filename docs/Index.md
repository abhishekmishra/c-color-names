# C-COLOR-NAMES Documentation           {#mainpage}

[TOC]

ANSI C API for the excellent collection of colors in the
[color-names](https://github.com/meodai/color-names) package.

**NOTE: This library is still under development. The public API is unstable 
till the library reaches beta status. There will be breaking changes in public 
API if needed.**


# Install & Build

## From source

```bash
# clone the repo and init the submodules
git clone https://github.com/abhishekmishra/c-color-names.git
cd c-color-names
git submodule init
git submodule update

# generate the cmake build, build the code, run the test program
make genbuild build run
```

## From release

```bash
# get the release
wget -c https://github.com/abhishekmishra/c-color-names/archive/refs/tags/v0.1.0-alpha.0.zip -O c-color-names.zip
unzip c-color-names.zip

# Now you can use color_names.h and color_names.c in your code.

# build the test binary (optional)
cd c-color-names-0.1.0-alpha.0
make genbuild build run
```

# API
The public API of the library is provided by 
[color_names.h](@ref color_names.h).

# Sample Usage
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

# Release Notes
* The current release is 
  [v0.1.0-alpha.0](https://github.com/abhishekmishra/c-color-names/releases/tag/v0.1.0-alpha.0)
* Release notes for all releases are at [CHANGELOG.md](CHANGELOG.md).

# License
* The library is released under the [MIT License](LICENSE).