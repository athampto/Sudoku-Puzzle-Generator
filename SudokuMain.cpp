#include"Sudoku.h"




int main() {

	auto start = high_resolution_clock::now();//starts clock
	ofstream MFile;
	ofstream GridFile;
	string fName;

	srand(time(NULL));

	Sudoku Puzzle;



	cout << "Please enter the name of the output file that will show the metrics and grids: " << endl;//metrics file
	cin >> fName;

	MFile.open(fName + ".txt");
	
	cout << "Please enter the name of the output file that will contain the partial grid to be solved: " << endl;//partial grid file "row col value"
	cin >> fName;

	GridFile.open(fName + ".txt");

	Puzzle.randFirstGrid();//randomize first sub grid

	Puzzle.SolveGrid();//solve grid -> gets solution grid

	Puzzle.copyGrid();//saves solution grid
	cout << "Solution Grid: " << endl;
	MFile << "Solution Grid: " << endl;

	Puzzle.PrintAnswerGrid(MFile);//prints solution grid

	Puzzle.createPartialGrid();//deletes values from solution grid ->creates Partial Grid

	cout << endl << endl;
	cout << "Partial Grid: " << endl;
	MFile << "Partial Grid: " << endl;

	auto stop = high_resolution_clock::now();//ends clock

	auto duration = duration_cast<seconds>(stop - start);//computes difference for the duration from the start to stop

	Puzzle.PrintPartialGrid(MFile);//prints the partial grid to file and screen

	Puzzle.PrintMetrics(MFile);//prints metrics to screen and file
	cout << "Time it took to create solution and partial grids: " << duration.count() << " seconds" << endl;
	MFile << "Time it took to create solution and partial grids: " << duration.count() << " seconds" << endl;

	Puzzle.PrintPartialFile(GridFile);//prints partial grid file in the form of "row column value" for solver to read and solve

	system("pause");
	return 0;

}
