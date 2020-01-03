#ifndef SUDOKU_H
#define SUDOKU_H

#include<iostream>
#include<string>
#include<fstream>
#include<cmath>
#include<ctime>
#include<algorithm>
#include<vector>
#include<chrono>
#include<iomanip>

using namespace std;
using namespace std::chrono;



class Sudoku {



public:

	//variables:

	int AnswerGrid[9][9];

	int PartialGrid[9][9];

	int numGuesses[9];

	vector<int> RemGrid;

	int Hints = 81;

	int Comparisons = 0;

	int BackTracking = 0;

	int HighestSolutions = 0;



	//functions:

	Sudoku();//

	int GenRandNum();//

	bool selectUnassignedLocation(int&, int&);//

	bool usedInColumn(int, int);//

	bool usedInRow(int, int);//

	bool usedInSubGrid(int, int, int);//
	
	bool validToPlace(int, int, int);//

	void PrintAnswerGrid(ofstream&);//

	void PrintPartialGrid(ofstream&);//

	void randFirstGrid();//

	void copyGrid();

	bool SolveGrid();

	void createPartialGrid();

	void NumberOfSolutions(int&);

	void PrintMetrics(ofstream&);

	void PrintPartialFile(ofstream&);//

	


};









#endif

