Vector Field Visualizer
=====================

Aaron Blasdel
ablasdel@gmail.com

Program explanation:
The Vector Field Visualizer depicts an animated scene of particles floating in a cubic vector field. Each segment of the vector field visualizer space has an associated vector which is used to apply a force to particles. Each particle has a weight and heavier particles are slightly harder to move than lighter ones. (weight difference is denoted by particle size)

Compiling Directions:

navigate to extracted directory

type cmake CMakeLists.txt

type make

type ./Code/VectorFieldVisualizer

Enjoy Responsibly

Program interaction commands:

'-' key: removes a particle from the scene

'+' key: adds a particle to the scene

'[' key: changes the vector field (moves forward in the list)

']' key: changes the vector field (moves backward in the list)

'<' key: decreases particle movement speed (note negative movement speeds will invert the vector field)

'>' key: increases particle movement speed (note negative movement speeds will invert the vector field)

Left mouse button: Rotates the camera around the scene

Right mouse button: Zooms the camera in and out

This program uses some library files originally created by Professor Ken Joy of UC Davis's CIPIC graphics lab which were modified by Aaron Blasdel.
All other content solely created by Aaron Blasdel.
