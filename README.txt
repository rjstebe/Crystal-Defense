Felix Chen (fchen2@wpi.edu), Ryan Stebe (rjstebe@wpi.edu)

Team Anthill
Crystal Defense
2022

This game and its engine was developed and tested on a Windows machine and we developed using Visual
Studio.

All the necessary .h and .cpp files are in the main folder along with this readme and the project
solution. Loading the solution in Microsoft Visual Studio and building should build the code
successfully.

We took care to try to use c and c++ code that works on any common operating system, but if they have
something similar to windows that requires setting _CRT_SECURE_NO_WARNING in order to use them, then
it probably won't work there.

In order to keep the solution working, we had to keep all of the engine files in the same folder so
that they would import correctly as the engine used was not in the format of a compiled package.
