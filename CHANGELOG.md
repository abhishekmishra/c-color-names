# CHANGELOG
This file documents major changes in every release of the project. 
The project follows [Semantic Versioning](https://semver.org/). There is a 
section for each release - which lists major changes made in the release.

**0.1.0-alpha.2**  2023-02-07 Abhishek Mishra  <abhishekmishra3@gmail.com>

- This is a maintenance release which bumps the version of the color-names
  library to the latest one **v10.19.0**.

**0.1.0-alpha.1**  2023-02-07 Abhishek Mishra  <abhishekmishra3@gmail.com>

- This is the second alpha release of `c-color-names` and includes several
  important new features and minor fixes.
- A **Doxygen** based documentation site is now setup which is also hosted
  online on github pages.
- The documentation is updated to use latest build procedure and example code.
- New methods are added to the public API for getting colors using HSV and RGB.
- The `color-names` dependency is updated to latest release and new code
  generated.

**0.1.0-alpha.0**  2022-12-18 Abhishek Mishra  <abhishekmishra3@gmail.com>

- This is the first alpha release of the `c-color-names` library. The program 
  has been around for some time as it is used in some of my hobby projects.
- The goal of the program is to provide a simple C API to the color names 
  defined in the nodejs project 
  [color-names](https://github.com/meodai/color-names).
- Specifically for now it exposes the color names defined in 
  **color-names/dist/colornames.bestof.csv**.
- The API documentation is provided in `color_names.h`.
- The API is provisional-only for now, and there may be breaking changes in 
  the coming releases.
- Once the API is considered stable I will make a **beta** release.
