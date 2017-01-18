#pragma once
#include "Cube.h"

//Provides a command line interface to manipulate and view a cube object.
void CLI();

//Used by the CLI function to represent the state of the cube in a CLI.
void Draw(Cube a);

//Helper functions for the Draw function.
void DrawTopHelper(Cube a);
void DrawMidHelper(Cube a);
void DrawBotHelper(Cube a);
