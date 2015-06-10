#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <iomanip>
#include "Board.cpp"

int findMaxClueLengthT(std::vector<std::vector<int> > clues){
	int max = 0;
	for (int i=0; i<clues.size(); i++){
		if (clues[i].size()>max){
			max = clues[i].size();
		}
	}
	return max;
}

int findMaxClueLengthS(std::vector<std::vector<int> > clues){
	int max = 0;
	for (int i=0; i<clues.size(); i++){
		int temp = 0;
		for (int j=0; j<clues[i].size(); j++){
			int num = clues[i][j];
			while (num!=0){
				temp++;
				num /= 10;
			}
		}
		if (temp>max){
			max = clues[i].size();
		}
	}
	return max;
}

void printBoard(Board b){
	int max1 = findMaxClueLengthT(b.topClues);
	int max2 = findMaxClueLengthS(b.sideClues);
	int max3 = findMaxClueLengthT(b.sideClues);
	//std::cout << max1 << " " << max2 << std::endl;
	for (int i=0; i<max1; i++){
		std::cout << std::string((max2+b.sideClues[i].size()-1),' ');
		for (int j=0; j<b.topClues.size(); j++){
			if (i+b.topClues[j].size()>=max1){
				std::cout << ' ' << std::setw(3) << b.topClues[j][b.topClues[j].size()+i-max1];
			}
			else{
				std::cout << "    ";
			}
		}
		std::cout << std::endl;
	}
	std::string top(b.sizeTop*4+1,'-');
	for (int i=0; i<max2+max3-1; i++){
		top.insert(0," ");
	}
	for (int i=0; i<b.sizeSide; i++){
		std::cout << top << std::endl;
		std::string temp = "";
		for (int j=0; j<b.sideClues[i].size(); j++){
			std::stringstream ss;
			ss << b.sideClues[i][j];
			std::string str = ss.str();
			temp.append(str);
			if (j+1!=b.sideClues[i].size()) temp.append(" ");
		}
		std::cout << std::setw(max2+max3-1) << std::right << temp;
		for (int j=0; j<b.sizeTop; j++){
			std::cout << "| " << b.board[i][j] << ' ';
		}
		std::cout << '|' << std::endl;
	}
	std::cout << top << std::endl;
}



int main(){
	std::string line;
	std::ifstream myfile("test.txt");
	std::vector<std::vector<int> > board;
	std::vector<std::vector<int> > clue1;
	std::vector<std::vector<int> > clue2;
	if (myfile.is_open()){
		std::getline(myfile,line);
		int top = std::atoi(line.c_str());
		std::getline(myfile,line);
		int side = std::atoi(line.c_str());
		for (int i=0; i<side; i++){
			board.push_back(std::vector<int>(top,0));
		}
		while (std::getline(myfile,line)){
			std::vector<int> Clues;
			std::vector<std::string> temp;
			std::istringstream iss(line);
			std::copy(std::istream_iterator<std::string>(iss),
				std::istream_iterator<std::string>(),
				std::back_inserter(temp));
			for (int i=0; i<temp.size();i++){
				int temp1 = std::atoi(temp[i].c_str());
				Clues.push_back(temp1);
				//std::cout << temp1 << " ";
			}
			//std::cout << std::endl;
			if (clue1.size()<top){
				clue1.push_back(Clues);
			}
			else{
				clue2.push_back(Clues);
			}
		}
	}
	myfile.close();
	/*
	for (int i=0; i<board.size();i++){
		for (int j=0; j<board[0].size(); j++){
			std::cout << board[i][j] << " ";
		}
		std::cout << std::endl;
	}
	*/
	//std::cout << clue1.size() << " " << clue2.size() << std::endl;
	Board b(board,clue1,clue2);
	printBoard(b);
	
}