#include <iostream>
#include <vector>

class Board{
	public:
		std::vector<std::vector<int> > board;
		std::vector<bool> topComplete;
		std::vector<std::vector<int> > topClues;
		std::vector<bool> sideComplete;
		std::vector<std::vector<int> > sideClues;
		int sizeTop;
		int sizeSide;
	
	Board(std::vector<std::vector<int> > board_, std::vector<std::vector<int> > Clues1, std::vector<std::vector<int> > Clues2){
		board = board_;
		topComplete = std::vector<bool>(board_[0].size(),false);
		sizeTop = board_[0].size();
		sideComplete = std::vector<bool>(board_.size(),false);
		sizeSide = board_.size();
		topClues = Clues1;
		sideClues = Clues2;
	}
	
	bool update(int x, int y, int value){
		x--;
		y--;
		if (x>sizeTop || y>sizeSide) return false;
		//if (board[y][x] != 0) return false;
		if (value != 0 && value != 1 && value != 2) return false;
		board[y][x] = value;
		completeCol(x);
		completeRow(y);
		return true;
	}
	
	void completeCol(int x){
		int count = 0;
		int cluenum = 0;
		for (int i=0; i<sizeSide; i++){
			if (board[i][x] == 1){
				count++;
			}
			else {
				count = 0;
			}
			if (topClues[x][cluenum]==count) {
				if (cluenum == topClues[x].size()){
					topComplete[x] = true;
					return;
				}
				cluenum++;
				count = 0;
			}
		}
		topComplete[x] = false;
	}
	
	void completeRow(int y){
		int count = 0;
		int cluenum = 0;
		for (int i=0; i<sizeTop; i++){
			if (board[y][i] == 1){
				count++;
			}
			else {
				count = 0;
			}
			if (sideClues[y][cluenum]==count) {
				if (cluenum == sideClues[y].size()){
					sideComplete[y] = true;
					return;
				}
				cluenum++;
				count = 0;
			}
		}
		sideComplete[y] = false;
	}
	
	bool solved(){
		for (int i=0; i<sizeTop; i++){
			if (!topComplete[i]) return false;
		}
		for (int j=0; j<sizeSide; j++){
			if (!sideComplete[j]) return false;
		}
		return true;
	}
	
};