# Bresenhams line and a spinning cube

## Preface

This project was made as a demonstration for the presentation I 
gave on my second year CS algorithms class.

We were given an objective to make a presentation about any
usefull(and not really) algorithm we can find that was not present in our course. 
So no binary searches, basic sorting algorithms etc. While many of my classmates
went the rout of different "tree centric" algorithms or very sophisticated high level things
I chose a much simpler "closer to the earth" approach.

I asked myself "What is the most simple but still impressive thing a computer can do 
that everyone takes for granted?", well i thought about 3d graphics. You see it 
everywhere nowadays games, websites, art. Arter a few hours of researching 
I stopped myself with a thought: "This is not a presentation! Thats at least 
a lecture worth of information!". Then I got en enlightentment. Lines! 
You need lines for everything! 3D, 2D, raster, vector, lines everywhere!
How a computer draws a line between 2 points? A quick google search 
pointed me at Bresenhams line algorithm, fast, simple, elegant and used to this day. And here I was.

## About the code

After I spent hours reading about 3d graphics I couldn't just forget everything I've learned, so after finishing working on my Power Point presentation, Implementing the basics of 3d was just a matter of time.

I don't remember why all the files were .cpp but all the code was written in C style. I was young and naive. For archival purposes this branch will contain almost untouched version of the original files. And I will refactor everything to suit modern C++ standarts in another branch.

## Build

### Windows

Project was build and should work with [cmake](https://cmake.org/) 3.30.2 and [Visual Studio 2022](https://visualstudio.microsoft.com/).

Project also requires SDL2 developement library present.

You can download it [here](https://github.com/libsdl-org/SDL/releases/tag/release-2.30.11). For Visual Studio download *SDL2-devel-2.30.11-VC.zip*, unzip it into "3rdparty" folder and rename to **SDL2**
Your folder structure should look like this:

```
.
├── 3rdparty
│   ├── .gitignore
│   └── SDL2
│       ├── cmake
│       ├── i686-w64-mingw32
│       ├── x86_64-w64-mingw32
│       └── ...
├── CMakeLists.txt
├── README.md
├── src
│   ├── Bresenham.cpp
│   └── ...
└── ...

```

Then navigate to a project folder and run

```
cmake -S . -B build
cmake --build build
cmake --install build
```

After executing the last command a bin folder with the executables should appear in a root directory.

Running the executables requires SDL2.dll to be present on your PATH or in the same folder as .exes. It can be found in *SDL2-devel-2.30.11-VC* under lib/x64 (or x32 if you are using 32 bit OS for some reason) folder. Copy SDL2.dll to the bin folder.

Run the executables.