// Cube Program.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Cube_Program.h"
#include "Cube.h"
#include <iostream>
#include <string>
#include <Windows.h>

//Entry point for the application
int main()
{
	CLI();
	return 0;
}

void CLI()
{
	Cube cube;
	std::string input = "";

	try {
		cube = Cube(r, w);
	}
	catch (std::invalid_argument) {
		std::cout << "Failed to initialize cube. Exiting..." << std::endl;
		std::cin.get();
		return;
	}

	std::cout << "Welcome to the cube program. Type /help for a list of commands." << std::endl;

	while (input != "exit") {
		std::cout << "---------------" << std::endl;
		Draw(cube);
		std::cout << "---------------" << std::endl;
		std::cin >> input;
		if (input == "/help") {
			std::cout << "This is a list of commands for the cube program." << std::endl << std::endl;
			std::cout << "F: Rotate the front face clockwise." << std::endl;
			std::cout << "F': Rotate the front face counterclockwise." << std::endl;
			std::cout << "B: Rotate the back face clockwise." << std::endl;
			std::cout << "B': Rotate the back face counterclockwise." << std::endl;
			std::cout << "U: Rotate the top face clockwise." << std::endl;
			std::cout << "U': Rotate the top face counterclockwise." << std::endl;
			std::cout << "D: Rotate the downward face clockwise." << std::endl;
			std::cout << "D': Rotate the downward face counterclockwise." << std::endl;
			std::cout << "L: Rotate the left side clockwise." << std::endl;
			std::cout << "L': Rotate the left side counterclockwise" << std::endl;
			std::cout << "R: Rotate the right side clockwise." << std::endl;
			std::cout << "R': Rotate the right side counterclockwise." << std::endl;
			std::cout << "fitness: Returns the fitness score of the current cube." << std::endl;
			std::cout << "scramble: Performs 30 random operations on the cube to randomize it." << std::endl;
			std::cout << "reset: Sets the cube back into the solved position." << std::endl;
			std::cout << "exit: Closes the program." << std::endl;
		}
		else if (input == "F" || input == "f") {
			cube.Front();
		}
		else if (input == "F'" || input == "f'") {
			cube.FrontPrime();
		}
		else if (input == "B" || input == "b") {
			cube.Back();
		}
		else if (input == "B'" || input == "b'") {
			cube.BackPrime();
		}
		else if (input == "U" || input == "u") {
			cube.Up();
		}
		else if (input == "U'" || input == "u'") {
			cube.UpPrime();
		}
		else if (input == "D" || input == "d") {
			cube.Down();
		}
		else if (input == "D'" || input == "d'") {
			cube.DownPrime();
		}
		else if (input == "L" || input == "l") {
			cube.Left();
		}
		else if (input == "L'" || input == "l'") {
			cube.LeftPrime();
		}
		else if (input == "R" || input == "r") {
			cube.Right();
		}
		else if (input == "R'" || input == "r'") {
			cube.RightPrime();
		}
		else if (input == "fitness") {
			std::cout << cube.Fitness() << std::endl;
		}
		else if (input == "scramble") {
			std::cout << cube.Scramble() << std::endl;
		}
		else if (input == "reset") {
			cube = Cube();
		}
		else if (input == "exit") {
			return;
		}
		else {
			std::cout << "Invalid command. Type /help for a list of commands." << std::endl;
		}
	}
}

void Draw(Cube a)
{
	//top row
	DrawTopHelper(a);
	//middle row
	DrawMidHelper(a);
	//bottom row
	DrawBotHelper(a);
}

void DrawTopHelper(Cube a)
{
	Side *sides = a.GetSides();
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	char colours[6] = { 'r', 'b', 'w', 'o', 'g', 'y' };
	int colourCodes[6] = { 0x4C, 0x19, 0x7F, 0xCE, 0x2A, 0x6E };

	SetConsoleTextAttribute(hConsole, 15);
	std::cout << "    ";
	for (int i = 0; i < 3; i++) {
		SetConsoleTextAttribute(hConsole, colourCodes[*(sides[a.GetBackFace()].upRow[2 - i])]);
		std::cout << colours[*(sides[a.GetBackFace()].upRow[2 - i])];
	}
	SetConsoleTextAttribute(hConsole, 15);
	std::cout << std::endl;

	std::cout << "    ";
	SetConsoleTextAttribute(hConsole, colourCodes[*(sides[a.GetLeftFace()].upRow[1])]);
	std::cout << colours[*(sides[a.GetLeftFace()].upRow[1])];
	SetConsoleTextAttribute(hConsole, colourCodes[sides[a.GetUpFace()].face[1][1]]);
	std::cout << colours[sides[a.GetUpFace()].face[1][1]];
	SetConsoleTextAttribute(hConsole, colourCodes[*(sides[a.GetRightFace()].upRow[1])]);
	std::cout << colours[*(sides[a.GetRightFace()].upRow[1])];
	SetConsoleTextAttribute(hConsole, 15);
	std::cout << std::endl;

	std::cout << "    ";
	for (int i = 0; i < 3; i++) {
		SetConsoleTextAttribute(hConsole, colourCodes[*(sides[a.GetFrontFace()].upRow[i])]);
		std::cout << colours[*(sides[a.GetFrontFace()].upRow[i])];
	}
	SetConsoleTextAttribute(hConsole, 15);
	std::cout << std::endl << std::endl;

	//cleanup
	delete[] sides;
}

void DrawMidHelper(Cube a)
{
	Side *sides = a.GetSides();
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	char colours[6] = { 'r', 'b', 'w', 'o', 'g', 'y' };
	int colourCodes[6] = { 0x4C, 0x19, 0x7F, 0xCE, 0x2A, 0x6E };

	for (int i = 0; i < 3; i++) {
		SetConsoleTextAttribute(hConsole, colourCodes[*(sides[a.GetUpFace()].leftRow[2 - i])]);
		std::cout << colours[*(sides[a.GetUpFace()].leftRow[2 - i])];
	}
	SetConsoleTextAttribute(hConsole, 15);
	std::cout << " ";
	for (int i = 0; i < 3; i++) {
		SetConsoleTextAttribute(hConsole, colourCodes[*(sides[a.GetUpFace()].downRow[i])]);
		std::cout << colours[*(sides[a.GetUpFace()].downRow[i])];
	}
	SetConsoleTextAttribute(hConsole, 15);
	std::cout << " ";
	for (int i = 0; i < 3; i++) {
		SetConsoleTextAttribute(hConsole, colourCodes[*(sides[a.GetUpFace()].rightRow[i])]);
		std::cout << colours[*(sides[a.GetUpFace()].rightRow[i])];
	}
	SetConsoleTextAttribute(hConsole, 15);
	std::cout << " ";
	for (int i = 0; i < 3; i++) {
		SetConsoleTextAttribute(hConsole, colourCodes[*(sides[a.GetUpFace()].upRow[2 - i])]);
		std::cout << colours[*(sides[a.GetUpFace()].upRow[2 - i])];
	}
	SetConsoleTextAttribute(hConsole, 15);
	std::cout << std::endl;

	SetConsoleTextAttribute(hConsole, colourCodes[*(sides[a.GetBackFace()].rightRow[1])]);
	std::cout << colours[*(sides[a.GetBackFace()].rightRow[1])];
	SetConsoleTextAttribute(hConsole, colourCodes[sides[a.GetLeftFace()].face[1][1]]);
	std::cout << colours[sides[a.GetLeftFace()].face[1][1]];
	SetConsoleTextAttribute(hConsole, colourCodes[*(sides[a.GetFrontFace()].leftRow[1])]);
	std::cout << colours[*(sides[a.GetFrontFace()].leftRow[1])];
	SetConsoleTextAttribute(hConsole, 15);
	std::cout << " ";

	SetConsoleTextAttribute(hConsole, colourCodes[*(sides[a.GetLeftFace()].rightRow[1])]);
	std::cout << colours[*(sides[a.GetLeftFace()].rightRow[1])];
	SetConsoleTextAttribute(hConsole, colourCodes[sides[a.GetFrontFace()].face[1][1]]);
	std::cout << colours[sides[a.GetFrontFace()].face[1][1]];
	SetConsoleTextAttribute(hConsole, colourCodes[*(sides[a.GetRightFace()].leftRow[1])]);
	std::cout << colours[*(sides[a.GetRightFace()].leftRow[1])];
	SetConsoleTextAttribute(hConsole, 15);
	std::cout << " ";

	SetConsoleTextAttribute(hConsole, colourCodes[*(sides[a.GetFrontFace()].rightRow[1])]);
	std::cout << colours[*(sides[a.GetFrontFace()].rightRow[1])];
	SetConsoleTextAttribute(hConsole, colourCodes[sides[a.GetRightFace()].face[1][1]]);
	std::cout << colours[sides[a.GetRightFace()].face[1][1]];
	SetConsoleTextAttribute(hConsole, colourCodes[*(sides[a.GetBackFace()].leftRow[1])]);
	std::cout << colours[*(sides[a.GetBackFace()].leftRow[1])];
	SetConsoleTextAttribute(hConsole, 15);
	std::cout << " ";

	SetConsoleTextAttribute(hConsole, colourCodes[*(sides[a.GetRightFace()].rightRow[1])]);
	std::cout << colours[*(sides[a.GetRightFace()].rightRow[1])];
	SetConsoleTextAttribute(hConsole, colourCodes[sides[a.GetBackFace()].face[1][1]]);
	std::cout << colours[sides[a.GetBackFace()].face[1][1]];
	SetConsoleTextAttribute(hConsole, colourCodes[*(sides[a.GetLeftFace()].leftRow[1])]);
	std::cout << colours[*(sides[a.GetLeftFace()].leftRow[1])];
	SetConsoleTextAttribute(hConsole, 15);
	std::cout << std::endl;

	for (int i = 0; i < 3; i++) {
		SetConsoleTextAttribute(hConsole, colourCodes[*(sides[a.GetDownFace()].leftRow[i])]);
		std::cout << colours[*(sides[a.GetDownFace()].leftRow[i])];
	}
	SetConsoleTextAttribute(hConsole, 15);
	std::cout << " ";
	for (int i = 0; i < 3; i++) {
		SetConsoleTextAttribute(hConsole, colourCodes[*(sides[a.GetDownFace()].upRow[i])]);
		std::cout << colours[*(sides[a.GetDownFace()].upRow[i])];
	}
	SetConsoleTextAttribute(hConsole, 15);
	std::cout << " ";
	for (int i = 0; i < 3; i++) {
		SetConsoleTextAttribute(hConsole, colourCodes[*(sides[a.GetDownFace()].rightRow[2 - i])]);
		std::cout << colours[*(sides[a.GetDownFace()].rightRow[2 - i])];
	}
	SetConsoleTextAttribute(hConsole, 15);
	std::cout << " ";
	for (int i = 0; i < 3; i++) {
		SetConsoleTextAttribute(hConsole, colourCodes[*(sides[a.GetDownFace()].downRow[2 - i])]);
		std::cout << colours[*(sides[a.GetDownFace()].downRow[2 - i])];
	}
	SetConsoleTextAttribute(hConsole, 15);
	std::cout << std::endl << std::endl;

	//cleanup
	delete[] sides;
}

void DrawBotHelper(Cube a)
{
	Side *sides = a.GetSides();
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	char colours[6] = { 'r', 'b', 'w', 'o', 'g', 'y' };
	int colourCodes[6] = { 0x4C, 0x19, 0x7F, 0xCE, 0x2A, 0x6E };

	SetConsoleTextAttribute(hConsole, 15);
	std::cout << "    ";
	for (int i = 0; i < 3; i++) {
		SetConsoleTextAttribute(hConsole, colourCodes[*(sides[a.GetFrontFace()].downRow[i])]);
		std::cout << colours[*(sides[a.GetFrontFace()].downRow[i])];
	}
	SetConsoleTextAttribute(hConsole, 15);
	std::cout << std::endl;

	std::cout << "    ";
	SetConsoleTextAttribute(hConsole, colourCodes[*(sides[a.GetLeftFace()].downRow[1])]);
	std::cout << colours[*(sides[a.GetLeftFace()].downRow[1])];
	SetConsoleTextAttribute(hConsole, colourCodes[sides[a.GetDownFace()].face[1][1]]);
	std::cout << colours[sides[a.GetDownFace()].face[1][1]];
	SetConsoleTextAttribute(hConsole, colourCodes[*(sides[a.GetRightFace()].downRow[1])]);
	std::cout << colours[*(sides[a.GetRightFace()].downRow[1])];
	SetConsoleTextAttribute(hConsole, 15);
	std::cout << std::endl;

	SetConsoleTextAttribute(hConsole, 15);
	std::cout << "    ";
	for (int i = 0; i < 3; i++) {
		SetConsoleTextAttribute(hConsole, colourCodes[*(sides[a.GetBackFace()].downRow[2 - i])]);
		std::cout << colours[*(sides[a.GetBackFace()].downRow[2 - i])];
	}
	SetConsoleTextAttribute(hConsole, 15);
	std::cout << std::endl;

	//cleanup
	delete[] sides;
}
