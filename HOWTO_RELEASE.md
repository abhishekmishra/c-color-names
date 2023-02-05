<p style="text-align: center"> <u> Table of Contents </u> </p>

- [1. Setup build](#1-setup-build)
  - [1.1. Pre-requisites](#11-pre-requisites)
- [2. Update color-names submodule to release tag](#2-update-color-names-submodule-to-release-tag)

# 1. Setup build

## 1.1. Pre-requisites

* `Cmake`: for build generation
* `make (optional)`: for triggering various build targets. If make is not
  available - look at the targets in Makefile and run the commands
  for the task.

```bash
# checkout repo/tag
$ git clone git@github.com:abhishekmishra/c-color-names.git

# setup cmake build for your platform
# and build it
$ make genbuild build

# run sanity tests
$ make test
```

# 2. Update color-names submodule to release tag

```bash
# switch to submodule dir
$ cd color-names

# update to tag <tag>
$ git checkout <tag>

# go to parent dir
$ cd ..

# run the gen target to update the generated color-names.c
# if running this or the first time make sure
# "make genbuild build" has been run.
$ make gen

# run tests to do some sanity checks on generated code
$ make test

# check-in changes
$ git add color-names; git commit -m "update to <tag>"; git push
```