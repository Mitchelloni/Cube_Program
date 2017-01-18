#pragma once
#include <string>

/**
Represents the six colours of the rubik's cube.
*/
typedef enum Colour
{
	r = 0, //red
	b = 1, //blue
	w = 2, //white
	o = 3, //orange
	g = 4, //green
	y = 5  //yellow
}Colour;

/**
Represents a single side of the rubik's cube.

             UPROW
            ^  ^  ^
            0  1  2
        < 2 [x][x][x] 2 >
LEFTROW < 1 [x][x][x] 1 > RIGHTROW
        < 0 [x][x][x] 0 >
             0  1  2
             v  v  v
             DOWNROW

The directions of the arrows represent in which way downRow, rightRow, upRow, and leftRow grow.
*/
class Side {

	public:
		//2D array representing the 3x3 grid of the side.
		Colour face[3][3];

		/***ROW POINTERS***/
		//Array of pointers to the row adjacent below the side.
		Colour * downRow[3];
		//Array of pointers to the row adjacent to the right of the side.
		Colour * rightRow[3];
		//Array of pointers to the row adjacent above the side.
		Colour * upRow[3];
		//Array of pointers to the row adjacent to the left of the side.
		Colour * leftRow[3];
		/***END ROW POINTERS***/

		/**
		Default constructor for side object.
		*/
		Side() {};

		/**
		Creates a 3x3 side of the cube with all the colours of the face set to f, and the adjacency arrays of pointers set to null.

		@param f The colour to be used for the colours of the face for the side.
		*/
		Side(Colour f);
};


/**
Represents a 3x3 Rubik's cube.

This represents the basic layout of the cube, where the letter represents the colour of the cube, and the coordinates in each side
represent the positioning of the colours in the array for each side.

                [0,2][1,2][2,2]
                [0,1][ U ][2,1]
                [0,0][1,0][2,0]

[0,2][1,2][2,2] [0,2][1,2][2,2] [0,2][1,2][2,2] [0,2][1,2][2,2]
[0,1][ L ][2,1] [0,1][ F ][2,1] [0,1][ R ][2,1] [0,1][ B ][2,1]
[0,0][1,0][2,0] [0,0][1,0][2,0] [0,0][1,0][2,0] [0,0][1,0][2,0]

                [0,2][1,2][2,2]
				[0,1][ D ][2,1]
				[0,0][1,0][2,0]

F = Front, B = Back, U = Up, D = Down, R = Right, L = Left.
*/
class Cube {

	private:
		//The colour of the side facing the user.
		Colour frontFace;
		//The colour of the side facing upwards with respect to the user.
	    Colour rightFace;
		//The colour of the side facing rightwards with respect to the user.
		Colour upFace;
		//The colour of the side facing away from the user.
		Colour backFace;
		//The colour of the side facing downwards with respect to the user.
		Colour leftFace;
		//The colour of the side facing leftwards with respect to the user.
		Colour downFace;
		//An array containing the 6 sides of the rubik's cube.
		Side sides[6];

		/**
		Orients the cube so that front is the new face and up is the new top.

		@param front The colour for the new frontFace.
		@param up: The colour for the new upFace.
		*/
		void Orient(Colour front, Colour up);

		/**
		Sets up the row pointers for each of the 6 sides in the sideArray.

		@param sideArray The array of 6 sides of the cube with row pointers to be set up.
		@param front The frontFace of the cube.
		@param right The rightSide of the cube.
		@param up The upSide of the cube.
		*/
		static void RowHelper(Side sideArray[6], Colour front, Colour right, Colour up);


	public:
		/**
		Creates a cube object with all sides in their solved position. Default is with red as front and white as the up.

		@param front The colour designated to be the face of the cube.
		@param up The colour designated to be the top of the cube.
		*/
		Cube(Colour front = r, Colour up = w);

		//Accessor Methods
		Colour GetFrontFace() { return frontFace; };
		Colour GetUpFace() { return upFace; };
		Colour GetRightFace() { return rightFace; };
		Colour GetBackFace() { return backFace; };
		Colour GetLeftFace() { return leftFace; };
		Colour GetDownFace() { return downFace; };

		/**
		Returns an array containing a copy of the 6 sides of the cube object.

		@return Returns a copy of the 6 sides of the cube as an array.
		CLEANUP: must be cleaned up with delete[]
		*/
		Side * GetSides();

		//Rotates the front face of the cube clockwise.
		void Front();

		//Rotates the front face of the cube counterclockwise.
		void FrontPrime();

		//Rotates the back face of the cube clockwise.
		void Back();

		//Rotates the back face of the cube counterclockwise.
		void BackPrime();

		//Rotates the top face of the cube clockwise.
		void Up();

		//Rotates the top face of the cube counterclockwise.
		void UpPrime();

		//Rotates the downward face of the cube clockwise.
		void Down();

		//Rotates the downward face of the cube counterclockwise.
		void DownPrime();

		//Rotates the right face of the cube clockwise.
		void Right();

		//Rotates the right face of the cube counterclockwise.
		void RightPrime();

		//Rotates the left face of the cube clockwise.
		void Left();

		//Rotates the left face of the cube counterclockwise.
		void LeftPrime();

		/**
		Performs a set of 30 random operations on the cube to scramble the layout and returns the sequence of operations as a string.

		@return Returns the sequence of operations performed on the cube as a string.
		*/
		std::string Scramble();

		/**
		Calculates the fitness score of the current cube position.

		@return An integer representing the fitness score of the cube. Increments by 1 for each piece in the correct position (ignores centre pieces), with 0 as the lowest score and 20 as the highest.
		*/
		int Fitness();
};
