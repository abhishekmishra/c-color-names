# Build

[TOC]

# Build c-color-names

## Pre-requisites

* `Cmake`: for build generation
* `make (optional)`: for triggering various build targets. If make is not
  available - look at the targets in Makefile and run the commands
  for the task.

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

# generate the cmake build, build the code, run the test program
make genbuild build run
```

```bash
# checkout repo/tag
git clone git@github.com:abhishekmishra/c-color-names.git

# setup cmake build for your platform
# and build it
make genbuild build

# run sanity tests
make run
```

# Release

## Update color-names submodule to release tag

```bash
# switch to submodule dir
cd color-names

# update to tag <tag>
git checkout <tag>

# go to parent dir
cd ..

# run the gen target to update the generated color-names.c
# if running this or the first time make sure
# "make genbuild build" has been run.
make gen

# run tests to do some sanity checks on generated code
make run

# check-in changes
git add color-names; git commit -m "update to <tag>"; git push
```