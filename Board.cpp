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
	
	bool updateLine(int x1, int y1, int x2, int y2, int val){
		/*
		x1--;
		y1--;
		x2--;
		y2--;
		*/
		if (x1==x2){
			if (y1>y2){
				return updateLineCol(x2,y2,x1,y1,val);
			}
			else{
				return updateLineCol(x1,y1,x2,y2,val);
			}
		}
		else{
			if (x1>x2){
				return updateLineRow(x2,y2,x1,y1,val);
			}
			else {
				return updateLineRow(x1,y1,x2,y2,val);
			}
		}
	}
	
	bool updateLineCol(int x1, int y1, int x2, int y2, int val) {
		bool success = true;
		for (int i=y1; i<=y2; i++){
			success = update(x1,i,val) && success;
		}
		return success;
	}
	
	bool updateLineRow(int x1, int y1, int x2, int y2, int val) {
		bool success = true;
		for (int i=x1; i<=x2; i++){
			success = update(i,y1,val) && success;
		}
		return success;
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
				cluenum++;
				if (cluenum == topClues[x].size()){
					topComplete[x] = true;
					return;
				}
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
				cluenum++;
				if (cluenum == sideClues[y].size()){
					sideComplete[y] = true;
					return;
				}
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