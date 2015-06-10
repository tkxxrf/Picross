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
	
};