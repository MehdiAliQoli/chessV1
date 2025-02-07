#include<iostream>
using namespace std;

int board[8][8] = {

	// 2 is black
	{2,2,2,2,2,2,2,2},
	{2,2,2,2,2,2,2,2},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1}
	// 1 is white

};
int legalmove[8][8] = { // 0 = illegal, 1 = move, 2 = capture
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0}
};
bool iswhiteturn = true;

class piece {
public : 
	bool  isWhite;
	bool isalive;
	int x, y; // {x, y}

};

class pawn : public piece {
public :
	bool isfirstmove;
	if (isWhite) { // white
	if (isfirstmove) {
		legalmove[x][y+2] = 1;
		legalmove[x][y+1] = 1;
	}
	else {
		if (board[x + 1][y] == 0) {
			legalmove[x + 1][y] = 1;
		}
		if (board[x + 1][y + 1] == 2) {
			legalmove[x + 1][y + 1] = 1;
		}
		if (board[x - 1][y + 1] == 2) {
			legalmove[x - 1][y + 1] = 1;
		}
	}
	}
	else { // black		
		if (isfirstmove) {
			legalmove[x][y - 2] = 1;
			legalmove[x][y - 1] = 1;
		}
		else {
			if (board[x][y - 1] == 0) {
				legalmove[x][y - 1] = 1;
			}
			if (board[x + 1][y - 1] == 1) {
				legalmove[x + 1][y - 1] = 1;
			}
			if (board[x - 1][y - 1] == 1) {
				legalmove[x - 1][y - 1] = 1;
			}
		}
	}

		memset(legalmove, 0, sizeof(legalmove));
};

class knight : public piece {
	public : 
		int isenemy;
		if (isWhite) {
			isenemy = 2;
		}
		else {
			isenemy = 1;
		}
		if (board[x + 2][y + 1] == 0  || board[x + 2][y + 1] == isenemy) {
			legalmove[x + 2][y + 1] = 1;
		}
		if (board[x + 2][y - 1] == 0 || board[x + 2][y - 1] == isenemy) {
			legalmove[x + 2][y - 1] = 1;
		}
		if (board[x - 2][y + 1] == 0 || board[x - 2][y + 1] == isenemy) {
			legalmove[x - 2][y + 1] = 1;
		} 
		if (board[x - 2][y - 1] == 0 || board[x - 2][y - 1] == isenemy) {
			legalmove[x - 2][y - 1] = 1;
		}
		if (board[x + 1][y + 2] == 0 || board[x + 1][y + 2] == isenemy) {
			legalmove[x + 1][y + 2] = 1;
		} 
		if (board[x + 1][y - 2] == 0 || board[x + 1][y - 2] == isenemy) {
			legalmove[x + 1][y - 2] = 1;
		}
		if (board[x - 1][y + 2] == 0 || board[x - 1][y + 2] == isenemy) {
			legalmove[x - 1][y + 2] = 1;
		}
		if (board[x - 1][y - 2] == 0 || board[x - 1][y - 2] == isenemy) {
			legalmove[x - 1][y - 2] = 1;
		}
		memset(legalmove, 0, sizeof(legalmove));
	};

class rook : public piece {
	public :
		int isenemy;
		if (isWhite) 
		{
			isenemy = 2;
		}
		else {
			isenemy = 1;
		}

		for (int i = 0; i < 7 - y; i++) {
			if (board[x][y + i] == 0) {
				legalmove[x][y + i] = 1;
			}
			else if (board[x][y + i] == isenemy) {
				legalmove[x][y + i] = 1;
				break;
			}
			else {
				break;
			}
		}
			
		

		for (int i = 0; i < y; i++) {
			if (board[x][y - i] == 0 || board[x][y - i] == isenemy) {
				legalmove[x][y - i] = 1;
			}
			else if (board[x][y - i] == isenemy) {
				legalmove[x][y - i] = 1;
				break;
			}
			else {
				break;
			}
		}
		for (int i = 0; i < 7 - x; i++) {
			if (board[x + i][y] == 0 || board[x + i][y] == isenemy) {
				legalmove[x + i][y] = 1;
			}
			else if (board[x + i][y] == isenemy) {
				legalmove[x + i][y] = 1;
				break;
			}
			else {
				break;
			}
		}
		for (int i = 0; i < x; i++) {
			if (board[x - i][y] == 0 || board[x - i][y] == isenemy) {
				legalmove[x - i][y] = 1;
			}
			else if (board[x - i][y] == isenemy) {
				legalmove[x - i][y] = 1;
				break;
			}
			else {
				break;
			}
		}

		memset(legalmove, 0, sizeof(legalmove));
	};

class bishop : public piece {
	public:
		int isenemy;
		if (isWhite) {
			isenemy = 2;
		}
		else {
			isenemy = 1;
		}
		for (int i = 0; i < 7 - x && i< 7-y; i++) {
			if (board[x + i][y + i] == 0 || board[x + i][y + i] == isenemy) {
				legalmove[x + i][y + i] = 1;
			}
			else if (board[x + i][y + i] == isenemy) {
				legalmove[x + i][y + i] = 1;
				break;
			}
			else {
				break;
			}
		}
		for (int i = 0; i < x && i<y; i++) {
			if (board[x - i][y - i] == 0 || board[x - i][y - i] == isenemy) {
				legalmove[x - i][y - i] = 1;
			}
			else if (board[x - i][y - i] == isenemy) {
				legalmove[x - i][y - i] = 1;
				break;
			}
			else {
				break;
			}
		}
		for (int i = 0; i < 7 - x && i< 7-y; i++) {
			if (board[x + i][y - i] == 0 || board[x + i][y - i] == isenemy) {
				legalmove[x + i][y - i] = 1;
			}
			else if (board[x + i][y - i] == isenemy) {
				legalmove[x + i][y - i] = 1;
				break;
			}
			else {
				break;
			}
		}
		for (int i = 0; i < x && i < y; i++) {
			if (board[x - i][y + i] == 0 || board[x - i][y + i] == isenemy) {
				legalmove[x - i][y + i] = 1;
			}
			else if (board[x - i][y + i] == isenemy) {
				legalmove[x - i][y + i] = 1;
				break;
			}
			else
			{
				break;
			}
		}
		memset(legalmove, 0, sizeof(legalmove));
	};

class queen : public piece {
	public : 
		int isenemy;
		if (isWhite) {
			isenemy = 2;
		}
		else {
			isenemy = 1;
		}

		for (int i = 0; i < 7 - y; i++) {
			if (board[x][y + i] == 0) {
				legalmove[x][y + i] = 1;
			}
			else if (board[x][y + i] == isenemy) {
				legalmove[x][y + i] = 1;
				break;
			}
			else {
				break;
			}
		}

	

	for (int i = 0; i < y; i++) {
		if (board[x][y - i] == 0 || board[x][y - i] == isenemy) {
			legalmove[x][y - i] = 1;
		}
		else if (board[x][y - i] == isenemy) {
			legalmove[x][y - i] = 1;
			break;
		}
		else {
			break;
		}
	}
	for (int i = 0; i < 7 - x; i++) {
		if (board[x + i][y] == 0 || board[x + i][y] == isenemy) {
			legalmove[x + i][y] = 1;
		}
		else if (board[x + i][y] == isenemy) {
			legalmove[x + i][y] = 1;
			break;
		}
		else {
			break;
		}
	}
	for (int i = 0; i < x; i++) {
		if (board[x - i][y] == 0 || board[x - i][y] == isenemy) {
			legalmove[x - i][y] = 1;
		}
		else if (board[x - i][y] == isenemy) {
			legalmove[x - i][y] = 1;
			break;
		}
		else {
			break;
		}
	}

		for (int i = 0; i < 7 - x && i < 7 - y; i++) {
			if (board[x + i][y + i] == 0 || board[x + i][y + i] == isenemy) {
				legalmove[x + i][y + i] = 1;
			}
			else if (board[x + i][y + i] == isenemy) {
				legalmove[x + i][y + i] = 1;
				break;
			}
			else {
				break;
			}
		}
		for (int i = 0; i < x && i < y; i++) {
			if (board[x - i][y - i] == 0 || board[x - i][y - i] == isenemy) {
				legalmove[x - i][y - i] = 1;
			}
			else if (board[x - i][y - i] == isenemy) {
				legalmove[x - i][y - i] = 1;
				break;
			}
			else {
				break;
			}
		}
		for (int i = 0; i < 7 - x && i < 7 - y; i++) {
			if (board[x + i][y - i] == 0 || board[x + i][y - i] == isenemy) {
				legalmove[x + i][y - i] = 1;
			}
			else if (board[x + i][y - i] == isenemy) {
				legalmove[x + i][y - i] = 1;
				break;
			}
			else {
				break;
			}
		}
		for (int i = 0; i < x && i < y; i++) {
			if (board[x - i][y + i] == 0 || board[x - i][y + i] == isenemy) {
				legalmove[x - i][y + i] = 1;
			}
			else if (board[x - i][y + i] == isenemy) {
				legalmove[x - i][y + i] = 1;
				break;
			}
			else
			{
				break;
			}
		}
		memset(legalmove, 0, sizeof(legalmove));
	};

class king : public piece {};	 // not implemented yet

int main() {



	return 0;
}