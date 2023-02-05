# Update color-names submodule to release tag

```bash
# switch to submodule dir
$ cd color-names

# update to tag <tag>
$ git checkout <tag>

# go to parent dir
$ cd ..

# check-in changes
$ git add color-names; git commit -m "update to <tag>"; git push
```