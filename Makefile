.PHONY: all genbuild delbuild build run clean install help sln docs

# see https://gist.github.com/sighingnow/deee806603ec9274fd47
# for details on the following snippet to get the OS
# (removed the flags about arch as it is not needed for now)
OSFLAG :=
ifeq ($(OS),Windows_NT)
	OSFLAG = WIN32
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		OSFLAG = LINUX
	endif
	ifeq ($(UNAME_S),Darwin)
		OSFLAG = OSX
	endif
endif

all: clean build run

genbuild:
ifeq ($(OSFLAG),WIN32)
	cmake . -B ./build -DCMAKE_TOOLCHAIN_FILE=D:/vcpkg/scripts/buildsystems/vcpkg.cmake -DCMAKE_INSTALL_PREFIX=./install
else
	cmake . -B ./build -DCMAKE_TOOLCHAIN_FILE=${VCPKG_HOME}/scripts/buildsystems/vcpkg.cmake -DCMAKE_INSTALL_PREFIX=./install
endif

delbuild:
	rm -fR ./build

build:
	cmake --build ./build

run:
ifeq ($(OSFLAG),WIN32)
	./build/Debug/c-color-names-test
else
	./build/c-color-names-test
endif

gen:
ifeq ($(OSFLAG),WIN32)
	./build/Debug/c-color-names-gen
else
	./build/c-color-names-gen
endif


clean:
	cmake --build ./build --target clean

install:
	cmake --build ./build --target install

sln:
ifeq ($(OSFLAG),WIN32)
	cygstart ".\build\c-color-names-gen.sln"
else
	echo "No solution file available on this platform"
endif

docs:
	doxygen

help:
		@echo "********************************************************"
		@echo "  Makefile to build [c-color-names-gen]"
		@echo "  (generated by gen-makefile.lua script)"
		@echo "********************************************************"
		@echo "  (The project uses CMake. This Makefile provides"
		@echo "   convenient shortcuts to common build tasks.)"
		@echo ""
		@echo "  all:      Runs the clean, build, and run targets."
		@echo "  build:    Runs the cmake project build target."
		@echo "  run:      Runs the debug executable."
		@echo "  gen:      Generate new files from the color-names colors."
		@echo "  clean:    Runs the cmake project clean target."
		@echo "  install:  Runs the cmake project install target."
		@echo "  delbuild: Deletes the cmake build directory!"
		@echo "  genbuild: Generates the cmake build."
		@echo "  docs:     Generates the doxygen docs."
		@echo "********************************************************"
