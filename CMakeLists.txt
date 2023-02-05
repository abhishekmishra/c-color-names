cmake_minimum_required ( VERSION 3.9 )

project ( c-color-names VERSION 0.1.0 LANGUAGES C )

# turn of warnings on windows which suggest platform specific functions
add_compile_definitions(_CRT_SECURE_NO_WARNINGS)

set( C_COLOR_NAMES_GEN_SOURCES
    color_names_gen.c
)

add_executable( c-color-names-gen ${C_COLOR_NAMES_GEN_SOURCES} )

add_executable( c-color-names-test color_names.c color_names_test.c)