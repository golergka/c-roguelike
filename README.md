# c-roguelike

This is a small experimental project about writing game logic code in C.

* No dynamic memory allocation
* Multiple decoupled threads for different purposes
* No classes or class-like structures; using ordinary C structs instead
* Separate (and potentially intercahngeable) input, render and game logic code

The ideal goal is to find a way to write game logic with computer performance of C and programmer performance of C#.

# Building

On OS X, the project can be built with a simple `make` command in the root directory. I haven't tested the project on other systems.
