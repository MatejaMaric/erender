# About this project:

Inspired by [thebennybox's 3D Software Rendering](https://www.youtube.com/playlist?list=PLEETnX-uPtBUbVOok816vTl1K9vV1GgH5) series but made using C++ and [SFML](https://www.sfml-dev.org/).
It also implements the barycentric rendering technique instead of the scanline technique. 

## How to build (using CMake):

### On GNU/Linux:

Since this project is using [SFML](https://www.sfml-dev.org/), you will need following dependencies:

- freetype
- x11
- xrandr
- udev
- opengl
- flac
- ogg
- vorbis
- vorbisenc
- vorbisfile
- openal
- pthread

Then run following commands in project directory:

    mkdir build && cd build
    ln -s ../model .  # Make example model available
    cmake ..
    make

### On Windows and Mac:

On Windows and Mac you don't have any dependencies, so you can use CMake without any worry.
**Just make sure `model` directory (where example model is located) is available where you built the executable.**
