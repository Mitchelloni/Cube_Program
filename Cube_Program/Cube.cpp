#include "stdafx.h"
#include "Cube.h"
#include <iostream>
#include <cmath>
#include <ctime>
#include <string>
#include <Windows.h>

Side::Side(Colour f)
{
	for (int i = 0; i < 3; i++) {
		face[i][0] = f;
		face[i][1] = f;
		face[i][2] = f;
	}
}

Cube::Cube(Colour front, Colour up)
{
	try {
		Orient(front, up);
	}
	catch (std::invalid_argument) {
		throw;
	}

	//init
	for (int i = 0; i < 6; i++)
		sides[i] = Side((Colour)i);

	//set up row pointers
	RowHelper(sides, frontFace, rightFace, upFace);
}

Side * Cube::GetSides()
{
	//init
	Side *toReturn = new Side[6];
	for (int i = 0; i < 6; i++)
		toReturn[i] = Side((Colour)i);

	//set up row pointers
	RowHelper(toReturn, frontFace, rightFace, upFace);

	//copy sides
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 3; j++) {
			*(toReturn[i].downRow[j]) = *(sides[i].downRow[j]);
			*(toReturn[i].rightRow[j]) = *(sides[i].rightRow[j]);
			*(toReturn[i].upRow[j]) = *(sides[i].upRow[j]);
			*(toReturn[i].leftRow[j]) = *(sides[i].leftRow[j]);
		}
	}

	return toReturn;
}

void Cube::RowHelper(Side rowArray[6], Colour front, Colour right, Colour up)
{
	Colour back = (Colour)((front + 3) % 6);
	Colour down = (Colour)((up + 3) % 6);
	Colour left = (Colour)((right + 3) % 6);

	for (int i = 0; i < 3; i++) {
		//set up front side
		rowArray[front].downRow[i] = &rowArray[down].face[i][2];
		rowArray[front].rightRow[i] = &rowArray[right].face[0][i];
		rowArray[front].upRow[i] = &rowArray[up].face[i][0];
		rowArray[front].leftRow[i] = &rowArray[left].face[2][i];

		//set up right side
		rowArray[right].downRow[i] = &rowArray[down].face[2][2 - i];
		rowArray[right].rightRow[i] = &rowArray[back].face[0][i];
		rowArray[right].upRow[i] = &rowArray[up].face[2][i];
		rowArray[right].leftRow[i] = &rowArray[front].face[2][i];

		//set up top side
		rowArray[up].downRow[i] = &rowArray[front].face[i][2];
		rowArray[up].rightRow[i] = &rowArray[right].face[i][2];
		rowArray[up].upRow[i] = &rowArray[back].face[2 - i][2];
		rowArray[up].leftRow[i] = &rowArray[left].face[2 - i][2];

		//set up back side
		rowArray[back].downRow[i] = &rowArray[down].face[2 - i][0];
		rowArray[back].rightRow[i] = &rowArray[left].face[0][i];
		rowArray[back].upRow[i] = &rowArray[up].face[2 - i][2];
		rowArray[back].leftRow[i] = &rowArray[right].face[2][i];

		//set up left side
		rowArray[left].downRow[i] = &rowArray[down].face[0][i];
		rowArray[left].rightRow[i] = &rowArray[front].face[0][i];
		rowArray[left].upRow[i] = &rowArray[up].face[0][2 - i];
		rowArray[left].leftRow[i] = &rowArray[back].face[2][i];

		//set up down side
		rowArray[down].downRow[i] = &rowArray[back].face[2 - i][0];
		rowArray[down].rightRow[i] = &rowArray[right].face[2 - i][0];
		rowArray[down].upRow[i] = &rowArray[front].face[i][0];
		rowArray[down].leftRow[i] = &rowArray[left].face[i][0];
	}
}

void Cube::Orient(Colour front, Colour up)
{
	//check for valid params
	if (abs(front - up) == 3 || front == up) {
		throw std::invalid_argument("Invalid front and top orientation");
	}

	frontFace = front;
	upFace = up;
	
	//ugly plz find mathy way instead of big logic
	switch (frontFace) {
	    case r:
			if (upFace == b) {
				rightFace = y;
			} 
			else if (upFace == y) {
				rightFace = g;
			} 
			else if (upFace == g) {
				rightFace = w;
			} 
			else if (upFace == w) {
				rightFace = b;
			}
			break;
		case b:
			if (upFace == w) {
				rightFace = o;
			} 
			else if (upFace == o) {
				rightFace = y;
			} 
			else if (upFace == y) {
				rightFace = r;
			} 
			else if (upFace == r) {
				rightFace = w;
			}
			break;
		case w:
			if (upFace == o) {
				rightFace = b;
			} 
			else if (upFace == b) {
				rightFace = r;
			} 
			else if (upFace == r) {
				rightFace = g;
			} 
			else if (upFace == g) {
				rightFace = o;
			}
			break;
		case o:
			if (upFace == g) {
				rightFace = y;
			} 
			else if (upFace == y) {
				rightFace = b;
			} 
			else if (upFace == b) {
				rightFace = w;
			} 
			else if (upFace == w) {
				rightFace = g;
			}
			break;
		case g:
			if (upFace == y) {
				rightFace = o;
			} 
			else if (upFace == o) {
				rightFace = w;
			} 
			else if (upFace == w) {
				rightFace = r;
			} 
			else if (upFace == r) {
				rightFace = y;
			}
			break;
	}
	backFace = (Colour)((frontFace + 3) % 6);
	downFace = (Colour)((upFace + 3) % 6);
	leftFace = (Colour)((rightFace + 3) % 6);
}


void Cube::Front()
{
	Colour tmp;
	char colours[6] = { 'r', 'b', 'w', 'o', 'g', 'y' };

	tmp = sides[frontFace].face[0][0];
	sides[frontFace].face[0][0] = sides[frontFace].face[2][0];
	sides[frontFace].face[2][0] = sides[frontFace].face[2][2];
	sides[frontFace].face[2][2] = sides[frontFace].face[0][2];
	sides[frontFace].face[0][2] = tmp;

	tmp = sides[frontFace].face[1][0];
	sides[frontFace].face[1][0] = sides[frontFace].face[2][1];
	sides[frontFace].face[2][1] = sides[frontFace].face[1][2];
	sides[frontFace].face[1][2] = sides[frontFace].face[0][1];
	sides[frontFace].face[0][1] = tmp;

	for (int i = 0; i < 3; i++) {
		tmp = *(sides[frontFace].downRow[i]);
		*(sides[frontFace].downRow[i]) = *(sides[frontFace].rightRow[i]);
		*(sides[frontFace].rightRow[i]) = *(sides[frontFace].upRow[2 - i]);
		*(sides[frontFace].upRow[2 - i]) = *(sides[frontFace].leftRow[2 - i]);
		*(sides[frontFace].leftRow[2 - i]) = tmp;
	}
}

void Cube::FrontPrime()
{
	Colour tmp;
	Colour colours[6] = { r, b, w, o, g, y };

	tmp = sides[frontFace].face[0][0];
	sides[frontFace].face[0][0] = sides[frontFace].face[0][2];
	sides[frontFace].face[0][2] = sides[frontFace].face[2][2];
	sides[frontFace].face[2][2] = sides[frontFace].face[2][0];
	sides[frontFace].face[2][0] = tmp;

	tmp = sides[frontFace].face[1][0];
	sides[frontFace].face[1][0] = sides[frontFace].face[0][1];
	sides[frontFace].face[0][1] = sides[frontFace].face[1][2];
	sides[frontFace].face[1][2] = sides[frontFace].face[2][1];
	sides[frontFace].face[2][1] = tmp;

	for (int i = 0; i < 3; i++) {
		tmp = *(sides[frontFace].downRow[i]);
		*(sides[frontFace].downRow[i]) = *(sides[frontFace].leftRow[2 - i]);
		*(sides[frontFace].leftRow[2 - i]) = *(sides[frontFace].upRow[2 - i]);
		*(sides[frontFace].upRow[2 - i]) = *(sides[frontFace].rightRow[i]);
		*(sides[frontFace].rightRow[i]) = tmp;
	}
}

void Cube::Back()
{
	Colour tmpF = frontFace;

	Orient(backFace, upFace);
	Front();
	Orient(tmpF, upFace);
}

void Cube::BackPrime()
{
	Colour tmpF = frontFace;

	Orient(backFace, upFace);
	FrontPrime();
	Orient(tmpF, upFace);
}

void Cube::Up()
{
	Orient(upFace, frontFace);
	Front();
	Orient(upFace, frontFace);
}

void Cube::UpPrime()
{
	Orient(upFace, frontFace);
	FrontPrime();
	Orient(upFace, frontFace);
}

void Cube::Down()
{
	Orient(downFace, frontFace);
	Front();
	Orient(upFace, backFace);
}

void Cube::DownPrime()
{
	Orient(downFace, frontFace);
	FrontPrime();
	Orient(upFace, backFace);
}

void Cube::Right()
{
	Orient(rightFace, upFace);
	Front();
	Orient(leftFace, upFace);
}

void Cube::RightPrime()
{
	Orient(rightFace, upFace);
	FrontPrime();
	Orient(leftFace, upFace);
}

void Cube::Left()
{
	Orient(leftFace, upFace);
	Front();
	Orient(rightFace, upFace);
}

void Cube::LeftPrime()
{
	Orient(leftFace, upFace);
	FrontPrime();
	Orient(rightFace, upFace);
}

std::string Cube::Scramble()
{
	typedef void (Cube::*Move)(void);
	Move moves[12] = { &Cube::Front, &Cube::FrontPrime, &Cube::Back, &Cube::BackPrime, &Cube::Up, &Cube::UpPrime, &Cube::Down, &Cube::DownPrime, &Cube::Left, &Cube::LeftPrime, &Cube::Right, &Cube::RightPrime };
	int tmp;
	std::string text;
	std::string moveString[12] = { "F", "F'", "B", "B'", "U", "U'", "D", "D'", "L", "L'", "R", "R'" };
	srand(time((int)NULL));

	for (int i = 0; i < 30; i++) {
		tmp = (rand() % 12);
		(this->*moves[tmp])();
		text += moveString[tmp] + " ";
	}
	return text;
}

int Cube::Fitness()
{
	int score = 0;

	//check front face cross.
	if (sides[frontFace].face[1][0] == frontFace && *(sides[frontFace].downRow[1]) == downFace)
		score++;
	if (sides[frontFace].face[2][1] == frontFace && *(sides[frontFace].rightRow[1]) == rightFace)
		score++;
	if (sides[frontFace].face[1][2] == frontFace && *(sides[frontFace].upRow[1]) == upFace)
		score++;
	if (sides[frontFace].face[0][1] == frontFace && *(sides[frontFace].leftRow[1]) == leftFace)
		score++;

	//check back face cross
	if (sides[backFace].face[1][0] == backFace && *(sides[backFace].downRow[1]) == downFace)
		score++;
	if (sides[backFace].face[2][1] == backFace && *(sides[backFace].rightRow[1]) == leftFace)
		score++;
	if (sides[backFace].face[1][2] == backFace && *(sides[backFace].upRow[1]) == upFace)
		score++;
	if (sides[backFace].face[0][1] == backFace && *(sides[backFace].leftRow[1]) == rightFace)
		score++;

	//check front face corners
	if (sides[frontFace].face[0][0] == frontFace && *(sides[frontFace].leftRow[2]) == leftFace && *(sides[frontFace].downRow[0]) == downFace)
		score++;
	if (sides[frontFace].face[2][0] == frontFace && *(sides[frontFace].downRow[2]) == downFace && *(sides[frontFace].rightRow[0]) == rightFace)
		score++;
	if (sides[frontFace].face[2][2] == frontFace && *(sides[frontFace].rightRow[2]) == rightFace && *(sides[frontFace].upRow[0]) == upFace)
		score++;
	if (sides[frontFace].face[0][2] == frontFace && *(sides[frontFace].upRow[2]) == upFace && *(sides[frontFace].leftRow[0]) == leftFace)
		score++;

	//check back face corners
	if (sides[backFace].face[0][0] == backFace && *(sides[backFace]).leftRow[2] == rightFace && *(sides[backFace].downRow[0]) == downFace)
		score++;
	if (sides[backFace].face[2][0] == backFace && *(sides[backFace].downRow[2]) == downFace && *(sides[backFace].rightRow[0]) == leftFace)
		score++;
	if (sides[backFace].face[2][2] == backFace && *(sides[backFace].rightRow[2]) == leftFace && *(sides[backFace].upRow[0]) == upFace)
		score++;
	if (sides[backFace].face[0][2] == backFace && *(sides[backFace].upRow[2]) == upFace && *(sides[backFace].leftRow[0]) == rightFace)
		score++;

	//check side pieces
	if (sides[leftFace].face[1][0] == leftFace && *(sides[leftFace].downRow[1]) == downFace) {
		score++;
	}
	if (sides[leftFace].face[1][2] == leftFace && *(sides[leftFace].upRow[1]) == upFace) {
		score++;
	}
	if (sides[rightFace].face[1][0] == rightFace && *(sides[rightFace].downRow[1]) == downFace) {
		score++;
	}
	if (sides[rightFace].face[1][2] == rightFace && *(sides[rightFace].upRow[1]) == upFace) {
		score++;
	}

	return score;
}
