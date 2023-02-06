cmake_minimum_required ( VERSION 3.20 )

project ( c-color-names VERSION 0.1.0 LANGUAGES C )

# turn of warnings on windows which suggest platform specific functions
add_compile_definitions(_CRT_SECURE_NO_WARNINGS)

# check include math library
# https://stackoverflow.com/a/63037953
include(CheckLibraryExists)

CHECK_LIBRARY_EXISTS(m sin "" HAVE_LIB_M)

if (HAVE_LIB_M)
  set(EXTRA_LIBS ${EXTRA_LIBS} m)
endif (HAVE_LIB_M)

set( C_COLOR_NAMES_GEN_SOURCES
    color_names_gen.c
)

add_executable( c-color-names-gen ${C_COLOR_NAMES_GEN_SOURCES} )
target_link_libraries( c-color-names-gen ${EXTRA_LIBS} )

add_executable( c-color-names-test color_names.c color_names_test.c)
target_link_libraries( c-color-names-test ${EXTRA_LIBS} )
