#include"Sudoku.h"




Sudoku::Sudoku() {


	for (int i = 0; i < 9; i++) {


		numGuesses[i] = i + 1;


	}

	for (int i = 0; i < 81; i++) {


		RemGrid.push_back(i);

	}

	


	for (int i = 0; i < 9; i++) {

		for (int j = 0; j < 9; j++) {

			PartialGrid[i][j] = 0;



		}



	}
	



}


int Sudoku::GenRandNum() {


	return rand() % 9 + 1;


}



bool Sudoku :: selectUnassignedLocation(int& row, int& col) {


	for (row = 0; row < 9; row++) {

		for (col = 0; col < 9; col++) {



			if (PartialGrid[row][col] == 0) {

				return true;


			}



		}





	}

	return false;

}




bool Sudoku::usedInColumn(int col, int number) {

	for (int row = 0; row < 9; row++) {


		if (PartialGrid[row][col] == number) {


			return true;
		}


	}


	return false;




}





bool Sudoku::usedInRow(int row, int number) {

	for (int col = 0; col < 9; col++) {


		if (PartialGrid[row][col] == number) {


			return true;
		}


	}


	return false;

}




bool Sudoku::usedInSubGrid(int row, int col, int number) {



	for (int i = 0; i < 3; i++) {

		for (int j = 0; j < 3; j++) {


			if (PartialGrid[i + row][j + col] == number) {


				return true;
			}







		}


	}


	return false;


}




bool Sudoku::validToPlace(int row, int col, int number) {



	return !usedInRow(row, number) && !usedInColumn(col, number) && !usedInSubGrid(row - row % 3, col - col % 3, number);


}





void Sudoku::randFirstGrid() {

	int number;//holds random number


	for (int i = 0; i < 3; i++) {//row


		for (int j = 0; j < 3; j++) {//col

			
			do {

				number = GenRandNum();//generate random number

			} while ((!validToPlace(i, j, number)));//generates until it is valid to place then places number
			

			PartialGrid[i][j] = number;

			
			

			

			

		}




	}

	


}


void Sudoku::PrintAnswerGrid(ofstream& file) {


	for (int i = 0; i < 9; i++) {

		for (int j = 0; j < 9; j++) {



			cout << AnswerGrid[i][j] << " ";
			file << AnswerGrid[i][j] << " ";



		}

		cout << endl;
		file << endl;



	}



}


void Sudoku::PrintPartialGrid(ofstream& file) {


	for (int i = 0; i < 9; i++) {

		for (int j = 0; j < 9; j++) {



			cout << PartialGrid[i][j] << " ";
			file << PartialGrid[i][j] << " ";

			if (PartialGrid[i][j] == 0) {//counts number of hints within partial grid

				Hints--;

			}


		}

		cout << endl;
		file << endl;



	}

	

}



void Sudoku::copyGrid() {

	for (int i = 0; i < 9; i++) {

		for (int j = 0; j < 9; j++) {



			AnswerGrid[i][j] = PartialGrid[i][j];//copies grid to answer grid to hold it


		}



	}







}


bool Sudoku::SolveGrid() {

	
	int row = 0;
	int col = 0;

	

		if (!selectUnassignedLocation(row, col)) {//if not unassigned return true

			return true;
		}


		for (int number = 0; number < 9; number++) {//loop through 1-9

			if (validToPlace(row, col, numGuesses[number])) {//if number is valid to place


				PartialGrid[row][col] = numGuesses[number];//assigns



				if (SolveGrid()) {//recrusive call


					return true;
				}


				PartialGrid[row][col] = 0;//assign to zero if solve grid if statement is not triggered



			}



		}
	
	return false;


}



void Sudoku::NumberOfSolutions(int& Solutions) {

	int row = 0;
	int col = 0;


	if (!selectUnassignedLocation(row, col)) {//

		Solutions++;
		return;
		
	}

	for (int i = 0; i < 9 && Solutions < 2; i++) {


		if (validToPlace(row, col, numGuesses[i])) {

			PartialGrid[row][col] = numGuesses[i];

			NumberOfSolutions(Solutions);

			BackTracking++;//Metric-backtracking
		}

		PartialGrid[row][col] = 0;

		Comparisons++;//Metrics-comparisons
		


	}



}


void Sudoku::createPartialGrid() {


	for (int i = 0; i < 81; i++) {


		int position = rand() % RemGrid.size();//generate random position to access

		


		int first = RemGrid.at(position) / 9;//calculate position within 2-D array
		int second = RemGrid.at(position) % 9;

		int holder = PartialGrid[first][second];//hold value at spot

		PartialGrid[first][second] = 0; //first unassign location then check if you can do that with following checks

		int solutions = 0;//initialize number of solutions

		NumberOfSolutions(solutions);//call on function passing solutions as reference

		if (HighestSolutions < solutions) {//captures highest solution

			HighestSolutions = solutions;


		}

		if (solutions != 1) {//if number of solutions is not 1, put value back into is place

			PartialGrid[first][second] = holder;//is number of hints

			

		}

		RemGrid.at(position) = RemGrid.at(RemGrid.size() - 1);//essentially swapping values at end of vector and position


		RemGrid.pop_back();//taking off the end value of the vector


	}

}




void Sudoku::PrintMetrics(ofstream& file) {

	float Ratio = 0.0;

	cout << "Number of Hints: " << Hints << endl;
	file << "Number of Hints: " << Hints << endl;

	cout << "Numbers of Backtracking: " << BackTracking << endl;
	file << "Numbers of Backtracking: " << BackTracking << endl;

	cout << "Number of Comparisons: " << Comparisons << endl;
	file << "Number of Comparisons: " << Comparisons << endl;

	cout << "Highest number of solutions found: " << HighestSolutions << endl;
	file << "Highest number of solutions found: " << HighestSolutions << endl;

	cout << fixed;
	cout << setprecision(2);
	Ratio = Comparisons / Hints;

	cout << "Comparisons to Hints given ratio: " << Ratio << endl;
	file << "Comparisons to Hints given ratio: " << Ratio << endl;



}


void Sudoku::PrintPartialFile(ofstream& file) {

	for (int i = 0; i < 9; i++) {

		for (int j = 0; j < 9; j++) {


			if (PartialGrid[i][j] > 0) {//Print the file into file if value is assigned


				file << i + 1 << " " << j + 1 << " " << PartialGrid[i][j] << endl; //"row col value"


			}

		}

	}



}
