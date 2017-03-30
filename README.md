# EnveloppeConvexe

[GitHub Link](https://www.github.com/Anthilam/EnveloppeConvexe)

The goal of that project is to implements 3 different convex hull algorithms

## Prerequisites

You need to install thoses in order to launch the program :
* [Boost](http://www.boost.org/) - C++ Libraries
* [SDL2](https://www.libsdl.org/download-2.0.php) - Used to draw the scatter plot and the hull
* [Freetype](https://www.freetype.org/)

## Running the program

You have to uncomment the algorithm that you want to run in "pilote.c"
```
// Uncomment the algorithm you want to use and comment the others  :
  //jarvis_march(self, out);
  //graham_scan(self, out);
  quickhull(self, out);
```

Then, you can run the command :
```
cd src
./hull-generator N | ./hull-viewer ./pilote
```
N is the number of points in the scatter plot.

## Project status

- [x] Jarvis march
- [x] Graham scan
- [x] Quickhull
- [x] View is working
- [ ] Memory leaks (in Quickhull)

## Built with

*[Atom](https://atom.io/)
*[GEdit](https://help.gnome.org/users/gedit/stable/)
