# Update color-names submodule to release tag

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