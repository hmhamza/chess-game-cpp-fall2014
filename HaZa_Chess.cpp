#include "winbgim.h"                 
#include <Windows.h>                   
#include <iostream>                   
#include <math.h>
#include<fstream>
#include<cmath>

#include <mmsystem.h>
using namespace std;

struct Sqaure{
	int left, top, right, bottom;
	bool PieceColor;
	int PieceID;
};

class Board{
	Sqaure Grid[8][8];

public:

	Board(){

		int x1, y1, x2, y2, t1, t2;
		x1 = 426;	//L
		y1 = 103;	//T
		x2 = 487;	//R
		y2 = 164;	//B
		t1 = x1, t2 = x2;
		for (int i = 0; i < 8; i++, y1 += 61, y2 += 61, t1 = x1, t2 = x2){
			for (int j = 0; j < 8; j++, t1 += 61, t2 += 61){
				Grid[i][j].left = t1;
				Grid[i][j].top = y1;
				Grid[i][j].right = t2;
				Grid[i][j].bottom = y2;
				Grid[i][j].PieceID = -1;
				Grid[i][j].PieceColor = false;
			}

		}

	}

	void Set_Piece_By_Row_and_Col(int row, int col, const bool color, const int id){
		Grid[row][col].PieceColor = color;
		Grid[row][col].PieceID = id;
	}

	void Set_Piece_By_Click(int x, int y, const bool color, const int id){
		if (x<426 && x>920 && y<103 && y>588)
			//return false;
			return;
		else{
			for (int i = 0; i < 8; i++){
				if (y >= Grid[i][0].top&&y <= Grid[i][0].bottom){
					for (int j = 0; j < 8; j++){
						if (x >= Grid[i][j].left&&x <= Grid[i][j].right){
							Grid[i][j].PieceID = id;
							Grid[i][j].PieceColor = color;

							//return true;
						}
					}
				}
			}
		}
	}

	void Reset_Piece_By_Click(int x, int y){
		if (x<426 && x>920 && y<103 && y>588)
			//return false;
			return;
		else{
			for (int i = 0; i < 8; i++){
				if (y >= Grid[i][0].top&&y <= Grid[i][0].bottom){
					for (int j = 0; j < 8; j++){
						if (x >= Grid[i][j].left&&x <= Grid[i][j].right){
							Grid[i][j].PieceID = -1;
							//return true;
							return;
						}
					}
				}
			}
		}
	}

	void Reset_Piece_By_Row_and_Col(int row, int col){
		Grid[row][col].PieceID = -1;
	}

	bool Get_Coordinates_By_Row_and_Col(int row, int col, int &l, int &t, int &r, int &b){
		if (row<0 && row>7 && col<0 && col>7)
			return false;
		else{
			l = Grid[row][col].left;
			t = Grid[row][col].top;
			r = Grid[row][col].right;
			b = Grid[row][col].bottom;
			return true;
		}
	}

	bool Get_Coordinates_By_Click(int x, int y, int &l, int &t, int &r, int &b){
		if (x<426 && x>920 && y<103 && y>588)
			return false;
		else{
			for (int i = 0; i < 8; i++){
				if (y >= Grid[i][0].top&&y <= Grid[i][0].bottom){
					for (int j = 0; j < 8; j++){
						if (x >= Grid[i][j].left&&x <= Grid[i][j].right){
							l = Grid[i][j].left;
							t = Grid[i][j].top;
							r = Grid[i][j].right;
							b = Grid[i][j].bottom;
							return true;
						}
					}
				}
			}
		}
	}

	bool Get_PieceID_By_Click(int x, int y, int &id){
		if (x<426 && x>920 && y<103 && y>588)
			return false;
		else{
			for (int i = 0; i < 8; i++){
				if (y >= Grid[i][0].top&&y <= Grid[i][0].bottom){
					for (int j = 0; j < 8; j++){
						if (x >= Grid[i][j].left&&x <= Grid[i][j].right){
							id = Grid[i][j].PieceID;
							return true;
						}
					}
				}
			}
		}
	}

	int Get_PieceID_By_Row_and_Col(int row, int col){

		return Grid[row][col].PieceID;
	}


	bool Get_PieceColor_By_Row_and_Col(int row, int col){

		return Grid[row][col].PieceColor;
	}

	bool Get_PieceInfo(int x, int y, bool &color, int &id){
		if (x<426 && x>920 && y<103 && y>588)
			return false;
		else{
			for (int i = 0; i < 8; i++){
				if (y >= Grid[i][0].top&&y <= Grid[i][0].bottom){
					for (int j = 0; j < 8; j++){
						if (x >= Grid[i][j].left&&x <= Grid[i][j].right){
							color = Grid[i][j].PieceColor;
							id = Grid[i][j].PieceID;
							return true;
						}
					}
				}
			}
		}
	}

	bool Get_Row_and_Col_By_Click(int x, int y, int &row, int &col){
		if (x<426 && x>920 && y<103 && y>588)
			return false;
		else{
			for (int i = 0; i < 8; i++){
				if (y >= Grid[i][0].top&&y <= Grid[i][0].bottom){
					for (int j = 0; j < 8; j++){
						if (x >= Grid[i][j].left&&x <= Grid[i][j].right){
							row = i;
							col = j;
							return true;
						}
					}
				}
			}
		}
	}
};

Board ChessBoard;

class Piece{

protected:
	int PieceID;
	char PieceName[10];
	bool PieceColor;
	int left, top, right, bottom;
	char image_link[30];

public:
	
	int Get_PieceID(){
		return PieceID;
	}

	char* Get_PieceName(){
		return PieceName;
	}

	void Set_Coordinates(int l, int t, int r, int b){
		left = l;
		top = t;
		right = r;
		bottom = b;
		AdjustImageDimensions();
	}

	void AdjustImageDimensions(){
		left += 10;
		top += 10;
		right -= 10;
		bottom -= 10;
	}

	void Draw(){
		readimagefile(image_link, left, top, right, bottom);
	}

	virtual int Move(int x1, int y1, int x2, int y2, int &c_id){
		
		cout << "Move of Piece (Parent) class\n\n";
		return 0;
		/*int l, t, r, b;

		ChessBoard.Set_Piece_By_Click(x2, y2, PieceColor, PieceID);
		ChessBoard.Get_Coordinates_By_Click(x2, y2, l, t, r, b);
		Set_Coordinates(l, t, r, b);
		ChessBoard.Reset_Piece_By_Click(x1, y1);
		return 0;*/
	}
};

class King :public Piece{

public:

	King(bool b){

		strcpy_s(PieceName, "King");
		PieceID = 12;
		PieceColor = b;
		if (b){		//White

			ChessBoard.Get_Coordinates_By_Row_and_Col(7, 4, left, top, right, bottom);
			ChessBoard.Set_Piece_By_Row_and_Col(7, 4, b, PieceID);
			strcpy_s(image_link, "King-W.jpg");
		}
		else{		//Black
			ChessBoard.Get_Coordinates_By_Row_and_Col(0, 4, left, top, right, bottom);
			strcpy_s(image_link, "King-B.jpg");
			ChessBoard.Set_Piece_By_Row_and_Col(0, 4, b, PieceID);
		}
		AdjustImageDimensions();
		Draw();
	}

	int Move(int x1, int y1, int x2, int y2, int &c_id){
		int r1, c1, r2, c2, l, t, r, b, r_temp, c_temp, i;
		bool capture;

		ChessBoard.Get_Row_and_Col_By_Click(x1, y1, r1, c1);
		ChessBoard.Get_Row_and_Col_By_Click(x2, y2, r2, c2);

		if (ChessBoard.Get_PieceID_By_Row_and_Col(r2, c2) != -1 && ChessBoard.Get_PieceColor_By_Row_and_Col(r2, c2) != PieceColor)
			capture = true;
		else
			capture = false;

		if ((abs(r2 - r1) == 1 && (c2 == c1 || abs(c2 - c1) == 1)) || (r2 == r1 && abs(c2 - c1) == 1)){

			c_id = ChessBoard.Get_PieceID_By_Row_and_Col(r2, c2);
			ChessBoard.Get_Coordinates_By_Row_and_Col(r2, c2, l, t, r, b);
			Set_Coordinates(l, t, r, b);

			ChessBoard.Set_Piece_By_Row_and_Col(r2, c2, PieceColor, PieceID);
			ChessBoard.Reset_Piece_By_Row_and_Col(r1, c1);

			if (capture)
				return 1;
			else
				return 0;
		}

		else{
			readimagefile("black.jpg", 5, 145, 230, 190);
			rectangle(6, 146, 141, 170);
			outtextxy(10, 150, "Move not Possible");
			PlaySound("Buzz.wav", NULL, SND_ASYNC);
			return -1;
		}

	}

};

class Queen :public Piece{

public:
	Queen(bool b){

		strcpy_s(PieceName, "Queen");
		PieceID = 11;
		PieceColor = b;

		if (b){		//White

			ChessBoard.Get_Coordinates_By_Row_and_Col(7, 3, left, top, right, bottom);
			ChessBoard.Set_Piece_By_Row_and_Col(7, 3, b, PieceID);
			strcpy_s(image_link, "Queen-W.jpg");

		}
		else{		//Black
			ChessBoard.Get_Coordinates_By_Row_and_Col(0, 3, left, top, right, bottom);
			strcpy_s(image_link, "Queen-B.jpg");
			ChessBoard.Set_Piece_By_Row_and_Col(0, 3, b, PieceID);
		}
		AdjustImageDimensions();
		readimagefile(image_link, left, top, right, bottom);
	}

	int Move(int x1, int y1, int x2, int y2, int &c_id){

		int r1, c1, r2, c2, l, t, r, b, temp, r_temp, c_temp, i;
		bool capture;

		ChessBoard.Get_Row_and_Col_By_Click(x1, y1, r1, c1);
		ChessBoard.Get_Row_and_Col_By_Click(x2, y2, r2, c2);

		if (ChessBoard.Get_PieceID_By_Row_and_Col(r2, c2) != -1 && ChessBoard.Get_PieceColor_By_Row_and_Col(r2, c2) != PieceColor)
			capture = true;
		else
			capture = false;

		if (c1 == c2 && ((ChessBoard.Get_PieceID_By_Row_and_Col(r2, c2) == -1) || (ChessBoard.Get_PieceID_By_Row_and_Col(r2, c2) != -1 && ChessBoard.Get_PieceColor_By_Row_and_Col(r2, c2) != PieceColor))){

			if (r1 > r2)
				temp = r1 - 1;
			else
				temp = r2 - 1;
			for (i = 0; i < abs(r1 - r2) - 1; i++, temp--){
				if (ChessBoard.Get_PieceID_By_Row_and_Col(temp, c2) != -1)
					break;
			}

			if (i == abs(r1 - r2) - 1){
				c_id = ChessBoard.Get_PieceID_By_Row_and_Col(r2, c2);
				ChessBoard.Get_Coordinates_By_Row_and_Col(r2, c2, l, t, r, b);
				Set_Coordinates(l, t, r, b);

				ChessBoard.Set_Piece_By_Row_and_Col(r2, c2, PieceColor, PieceID);
				ChessBoard.Reset_Piece_By_Row_and_Col(r1, c1);
				if (capture)
					return 1;
				else
					return 0;
			}
			else{
				readimagefile("black.jpg", 5, 145, 230, 190);
				rectangle(6, 146, 141, 170);
				outtextxy(10, 150, "Move not Possible");
				PlaySound("Buzz.wav", NULL, SND_ASYNC);
				return -1;
			}
		}

		else if (r1 == r2 && ((ChessBoard.Get_PieceID_By_Row_and_Col(r2, c2) == -1) || (ChessBoard.Get_PieceID_By_Row_and_Col(r2, c2) != -1 && ChessBoard.Get_PieceColor_By_Row_and_Col(r2, c2) != PieceColor))){

			if (ChessBoard.Get_PieceID_By_Row_and_Col(r2, c2) == -1)
				capture = false;
			else
				capture = true;
			if (c1 > c2)
				temp = c2 - 1;
			else
				temp = c1 + 1;
			for (i = 0; i < abs(c1 - c2) - 1; i++, temp++){
				if (ChessBoard.Get_PieceID_By_Row_and_Col(r2, temp) != -1)
					break;
			}

			if (i == abs(c1 - c2) - 1){
				c_id = ChessBoard.Get_PieceID_By_Row_and_Col(r2, c2);
				ChessBoard.Get_Coordinates_By_Row_and_Col(r2, c2, l, t, r, b);
				Set_Coordinates(l, t, r, b);

				ChessBoard.Set_Piece_By_Row_and_Col(r2, c2, PieceColor, PieceID);
				ChessBoard.Reset_Piece_By_Row_and_Col(r1, c1);
				if (capture)
					return 1;
				else
					return 0;
			}
			else{
				readimagefile("black.jpg", 5, 145, 230, 190);
				rectangle(6, 146, 141, 170);
				outtextxy(10, 150, "Move not Possible"); 
				PlaySound("Buzz.wav", NULL, SND_ASYNC);
				return -1;
			}
		}

		else if ((r1 < r2 && c1 > c2) || (r1 > r2 && c1 < c2)){		//Going to Top Right

			if (r1 < r2 && c1 > c2){
				c_temp = c2 + 1;
				r_temp = r2 - 1;
			}
			else{
				c_temp = c1 + 1;
				r_temp = r1 - 1;
			}

			for (i = 0; i < abs(r1 - r2) - 1; i++, r_temp--, c_temp++){
				if (ChessBoard.Get_PieceID_By_Row_and_Col(r_temp, c_temp) != -1)
					break;
			}

			if (i == abs(r1 - r2) - 1){
				c_id = ChessBoard.Get_PieceID_By_Row_and_Col(r2, c2);
				ChessBoard.Get_Coordinates_By_Row_and_Col(r2, c2, l, t, r, b);
				Set_Coordinates(l, t, r, b);

				ChessBoard.Set_Piece_By_Row_and_Col(r2, c2, PieceColor, PieceID);
				ChessBoard.Reset_Piece_By_Row_and_Col(r1, c1);
				if (capture)
					return 1;
				else
					return 0;
			}
			else{
				readimagefile("black.jpg", 5, 145, 230, 190);
				rectangle(6, 146, 141, 170);
				outtextxy(10, 150, "Move not Possible");
				PlaySound("Buzz.wav", NULL, SND_ASYNC);
				return -1;
			}
		}

		else if ((r1 < r2 && c1 < c2) || (r1 > r2 && c1 > c2)){		//Going to Top Left

			if (r1 < r2 && c1 < c2){
				c_temp = c2 - 1;
				r_temp = r2 - 1;
			}
			else{
				c_temp = c1 - 1;
				r_temp = r1 - 1;

			}

			for (i = 0; i < abs(r1 - r2) - 1; i++, r_temp--, c_temp--){
				if (ChessBoard.Get_PieceID_By_Row_and_Col(r_temp, c_temp) != -1)
					break;
			}

			if (i == abs(r1 - r2) - 1){
				c_id = ChessBoard.Get_PieceID_By_Row_and_Col(r2, c2);
				ChessBoard.Get_Coordinates_By_Row_and_Col(r2, c2, l, t, r, b);
				Set_Coordinates(l, t, r, b);

				ChessBoard.Set_Piece_By_Row_and_Col(r2, c2, PieceColor, PieceID);
				ChessBoard.Reset_Piece_By_Row_and_Col(r1, c1);
				if (capture)
					return 1;
				else
					return 0;
			}
			else{
				readimagefile("black.jpg", 5, 145, 230, 190);
				rectangle(6, 146, 141, 170);
				outtextxy(10, 150, "Move not Possible");
				PlaySound("Buzz.wav", NULL, SND_ASYNC);
				return -1;
			}
		}

		else{
			readimagefile("black.jpg", 5, 145, 230, 190);
			rectangle(6, 146, 141, 170);
			outtextxy(10, 150, "Move not Possible");
			PlaySound("Buzz.wav", NULL, SND_ASYNC);
			return -1;
		}

	}

};

class Bishop :public Piece{

public:
	Bishop(bool b, int n){

		strcpy_s(PieceName, "Bishop");
		PieceColor = b;

		if (b){
			if (n == 1){
				PieceID = 13;

				ChessBoard.Get_Coordinates_By_Row_and_Col(7, 5, left, top, right, bottom);
				ChessBoard.Set_Piece_By_Row_and_Col(7, 5, b, PieceID);
			}
			else{
				PieceID = 10;

				ChessBoard.Get_Coordinates_By_Row_and_Col(7, 2, left, top, right, bottom);
				ChessBoard.Set_Piece_By_Row_and_Col(7, 2, b, PieceID);
			}
			strcpy_s(image_link, "Bishop-W.jpg");
		}
		else{
			if (n == 1){
				PieceID = 13;

				ChessBoard.Get_Coordinates_By_Row_and_Col(0, 5, left, top, right, bottom);
				ChessBoard.Set_Piece_By_Row_and_Col(0, 5, b, PieceID);
			}
			else{
				PieceID = 10;

				ChessBoard.Get_Coordinates_By_Row_and_Col(0, 2, left, top, right, bottom);
				ChessBoard.Set_Piece_By_Row_and_Col(0, 2, b, PieceID);
			}
			strcpy_s(image_link, "Bishop-B.jpg");
		}
		AdjustImageDimensions();
		readimagefile(image_link, left, top, right, bottom);
	}

	int Move(int x1, int y1, int x2, int y2, int &c_id){
		int r1, c1, r2, c2, l, t, r, b, r_temp, c_temp, i;
		bool capture;

		ChessBoard.Get_Row_and_Col_By_Click(x1, y1, r1, c1);
		ChessBoard.Get_Row_and_Col_By_Click(x2, y2, r2, c2);

		if (abs(c1 - c2) == abs(r1 - r2) && ((ChessBoard.Get_PieceID_By_Row_and_Col(r2, c2) == -1) || (ChessBoard.Get_PieceID_By_Row_and_Col(r2, c2) != -1 && ChessBoard.Get_PieceColor_By_Row_and_Col(r2, c2) != PieceColor))){

			if (ChessBoard.Get_PieceID_By_Row_and_Col(r2, c2) == -1)
				capture = false;
			else
				capture = true;

			if ((r1 < r2 && c1 > c2) || (r1 > r2 && c1 < c2)){		//Going to Top Right
				if (r1 < r2 && c1 > c2){
					c_temp = c2 + 1;
					r_temp = r2 - 1;
				}
				else{
					c_temp = c1 + 1;
					r_temp = r1 - 1;
				}

				for (i = 0; i < abs(r1 - r2) - 1; i++, r_temp--, c_temp++){
					if (ChessBoard.Get_PieceID_By_Row_and_Col(r_temp, c_temp) != -1)
						break;
				}

				if (i == abs(r1 - r2) - 1){
					c_id = ChessBoard.Get_PieceID_By_Row_and_Col(r2, c2);
					ChessBoard.Get_Coordinates_By_Row_and_Col(r2, c2, l, t, r, b);
					Set_Coordinates(l, t, r, b);

					ChessBoard.Set_Piece_By_Row_and_Col(r2, c2, PieceColor, PieceID);
					ChessBoard.Reset_Piece_By_Row_and_Col(r1, c1);
					if (capture)
						return 1;
					else
						return 0;
				}
				else{
					readimagefile("black.jpg", 5, 145, 230, 190);
					rectangle(6, 146, 141, 170);
					outtextxy(10, 150, "Move not Possible");
					PlaySound("Buzz.wav", NULL, SND_ASYNC);
					return -1;
				}
			}

			else if ((r1 < r2 && c1 < c2) || (r1 > r2 && c1 > c2)){		//Going to Top Left

				if (r1 < r2 && c1 < c2){
					c_temp = c2 - 1;
					r_temp = r2 - 1;
				}
				else{
					c_temp = c1 - 1;
					r_temp = r1 - 1;

				}

				for (i = 0; i < abs(r1 - r2) - 1; i++, r_temp--, c_temp--){
					if (ChessBoard.Get_PieceID_By_Row_and_Col(r_temp, c_temp) != -1)
						break;
				}

				if (i == abs(r1 - r2) - 1){
					c_id = ChessBoard.Get_PieceID_By_Row_and_Col(r2, c2);
					ChessBoard.Get_Coordinates_By_Row_and_Col(r2, c2, l, t, r, b);
					Set_Coordinates(l, t, r, b);

					ChessBoard.Set_Piece_By_Row_and_Col(r2, c2, PieceColor, PieceID);
					ChessBoard.Reset_Piece_By_Row_and_Col(r1, c1);
					if (capture)
						return 1;
					else
						return 0;
				}
				else{
					readimagefile("black.jpg", 5, 145, 230, 190);
					rectangle(6, 146, 141, 170);
					outtextxy(10, 150, "Move not Possible");
					PlaySound("Buzz.wav", NULL, SND_ASYNC);
					return -1;
				}
			}
		}

		else{
			readimagefile("black.jpg", 5, 145, 230, 190);
			rectangle(6, 146, 141, 170);
			outtextxy(10, 150, "Move not Possible");
			PlaySound("Buzz.wav", NULL, SND_ASYNC);
			return -1;
		}

	}

};

class Knight :public Piece{

public:
	Knight(bool b, int n){

		strcpy_s(PieceName, "Knight");
		PieceColor = b;

		if (b){
			if (n == 1){
				PieceID = 14;

				ChessBoard.Get_Coordinates_By_Row_and_Col(7, 6, left, top, right, bottom);
				ChessBoard.Set_Piece_By_Row_and_Col(7, 6, b, PieceID);
			}
			else{
				PieceID = 9;

				ChessBoard.Get_Coordinates_By_Row_and_Col(7, 1, left, top, right, bottom);
				ChessBoard.Set_Piece_By_Row_and_Col(7, 1, b, PieceID);
			}
			strcpy_s(image_link, "Knight-W.jpg");
		}
		else{
			if (n == 1){
				PieceID = 14;

				ChessBoard.Get_Coordinates_By_Row_and_Col(0, 6, left, top, right, bottom);
				ChessBoard.Set_Piece_By_Row_and_Col(0, 6, b, PieceID);
			}
			else{
				PieceID = 9;

				ChessBoard.Get_Coordinates_By_Row_and_Col(0, 1, left, top, right, bottom);
				ChessBoard.Set_Piece_By_Row_and_Col(0, 1, b, PieceID);
			}
			strcpy_s(image_link, "Knight-B.jpg");
		}
		AdjustImageDimensions();
		readimagefile(image_link, left, top, right, bottom);
	}

	int Move(int x1, int y1, int x2, int y2, int &c_id){
		int r1, c1, r2, c2, l, t, r, b, r_temp, c_temp, i;
		bool capture;

		ChessBoard.Get_Row_and_Col_By_Click(x1, y1, r1, c1);
		ChessBoard.Get_Row_and_Col_By_Click(x2, y2, r2, c2);

		if (ChessBoard.Get_PieceID_By_Row_and_Col(r2, c2) != -1 && ChessBoard.Get_PieceColor_By_Row_and_Col(r2, c2) != PieceColor)
			capture = true;
		else
			capture = false;

		if ((r2 - r1 == -2 && c2 - c1 == 1) || (r2 - r1 == -1 && c2 - c1 == 2) || (r2 - r1 == 2 && c2 - c1 == 1) || (r2 - r1 == 2 && c2 - c1 == -1) || (r2 - r1 == 1 && c2 - c1 == -2) || (r2 - r1 == -1 && c2 - c1 == -2) || (r2 - r1 == -2 && c2 - c1 == -1) || (r2 - r1 == 1 && c2 - c1 == 2)){

			c_id = ChessBoard.Get_PieceID_By_Row_and_Col(r2, c2);
			ChessBoard.Get_Coordinates_By_Row_and_Col(r2, c2, l, t, r, b);
			Set_Coordinates(l, t, r, b);

			ChessBoard.Set_Piece_By_Row_and_Col(r2, c2, PieceColor, PieceID);
			ChessBoard.Reset_Piece_By_Row_and_Col(r1, c1);

			if (capture)
				return 1;
			else
				return 0;
		}

		else{
			readimagefile("black.jpg", 5, 145, 230, 190);
			rectangle(6, 146, 141, 170);
			outtextxy(10, 150, "Move not Possible");
			PlaySound("Buzz.wav", NULL, SND_ASYNC);
			return -1;
		}

	}

};

class Rook :public Piece{

public:
	Rook(bool b, int n){

		strcpy_s(PieceName, "Rook");
		PieceColor = b;

		if (b){
			if (n == 1){
				PieceID = 15;

				ChessBoard.Get_Coordinates_By_Row_and_Col(7, 7, left, top, right, bottom);
				ChessBoard.Set_Piece_By_Row_and_Col(7, 7, b, PieceID);
			}
			else{
				PieceID = 8;

				ChessBoard.Get_Coordinates_By_Row_and_Col(7, 0, left, top, right, bottom);
				ChessBoard.Set_Piece_By_Row_and_Col(7, 0, b, PieceID);
			}
			strcpy_s(image_link, "Rook-W.jpg");
		}
		else{
			if (n == 1){
				PieceID = 15;

				ChessBoard.Get_Coordinates_By_Row_and_Col(0, 7, left, top, right, bottom);
				ChessBoard.Set_Piece_By_Row_and_Col(0, 7, b, PieceID);
			}
			else{
				PieceID = 8;

				ChessBoard.Get_Coordinates_By_Row_and_Col(0, 0, left, top, right, bottom);
				ChessBoard.Set_Piece_By_Row_and_Col(0, 0, b, PieceID);
			}
			strcpy_s(image_link, "Rook-B.jpg");
		}
		AdjustImageDimensions();
		readimagefile(image_link, left, top, right, bottom);
	}

	int Move(int x1, int y1, int x2, int y2, int &c_id){
		int r1, c1, r2, c2, l, t, r, b, temp, i;
		bool capture;

		ChessBoard.Get_Row_and_Col_By_Click(x1, y1, r1, c1);
		ChessBoard.Get_Row_and_Col_By_Click(x2, y2, r2, c2);

		if (c1 == c2 && ((ChessBoard.Get_PieceID_By_Row_and_Col(r2, c2) == -1) || (ChessBoard.Get_PieceID_By_Row_and_Col(r2, c2) != -1 && ChessBoard.Get_PieceColor_By_Row_and_Col(r2, c2) != PieceColor))){

			if (ChessBoard.Get_PieceID_By_Row_and_Col(r2, c2) == -1)
				capture = false;
			else
				capture = true;
			if (r1 > r2)
				temp = r1 - 1;
			else
				temp = r2 - 1;
			for (i = 0; i < abs(r1 - r2) - 1; i++, temp--){
				if (ChessBoard.Get_PieceID_By_Row_and_Col(temp, c2) != -1)
					break;
			}

			if (i == abs(r1 - r2) - 1){
				c_id = ChessBoard.Get_PieceID_By_Row_and_Col(r2, c2);
				ChessBoard.Get_Coordinates_By_Row_and_Col(r2, c2, l, t, r, b);
				Set_Coordinates(l, t, r, b);

				ChessBoard.Set_Piece_By_Row_and_Col(r2, c2, PieceColor, PieceID);
				ChessBoard.Reset_Piece_By_Row_and_Col(r1, c1);
				if (capture)
					return 1;
				else
					return 0;
			}
			else{
				readimagefile("black.jpg", 5, 145, 230, 190);
				rectangle(6, 146, 141, 170);
				outtextxy(10, 150, "Move not Possible");
				PlaySound("Buzz.wav", NULL, SND_ASYNC);
				return -1;
			}
		}

		else if (r1 == r2 && ((ChessBoard.Get_PieceID_By_Row_and_Col(r2, c2) == -1) || (ChessBoard.Get_PieceID_By_Row_and_Col(r2, c2) != -1 && ChessBoard.Get_PieceColor_By_Row_and_Col(r2, c2) != PieceColor))){

			if (ChessBoard.Get_PieceID_By_Row_and_Col(r2, c2) == -1)
				capture = false;
			else
				capture = true;
			if (c1 > c2)
				temp = c2 - 1;
			else
				temp = c1 + 1;
			for (i = 0; i < abs(c1 - c2) - 1; i++, temp++){
				if (ChessBoard.Get_PieceID_By_Row_and_Col(r2, temp) != -1)
					break;
			}

			if (i == abs(c1 - c2) - 1){
				c_id = ChessBoard.Get_PieceID_By_Row_and_Col(r2, c2);
				ChessBoard.Get_Coordinates_By_Row_and_Col(r2, c2, l, t, r, b);
				Set_Coordinates(l, t, r, b);

				ChessBoard.Set_Piece_By_Row_and_Col(r2, c2, PieceColor, PieceID);
				ChessBoard.Reset_Piece_By_Row_and_Col(r1, c1);
				if (capture)
					return 1;
				else
					return 0;
			}
			else{
				readimagefile("black.jpg", 5, 145, 230, 190);
				rectangle(6, 146, 141, 170);
				outtextxy(10, 150, "Move not Possible");
				PlaySound("Buzz.wav", NULL, SND_ASYNC);
				return -1;
			}
		}

		else{
			readimagefile("black.jpg", 5, 145, 230, 190);
			rectangle(6, 146, 141, 170);
			outtextxy(10, 150, "Move not Possible");
			PlaySound("Buzz.wav", NULL, SND_ASYNC);
			return -1;
		}

	}


};

class Pawn :public Piece{

	bool inOwnHalf;
public:
	Pawn(bool b, int n){

		strcpy_s(PieceName, "Pawn");
		PieceColor = b;
		inOwnHalf = true;

		if (b){
			strcpy_s(image_link, "Pawn-W.jpg");

			if (n == 1){
				PieceID = 0;

				ChessBoard.Get_Coordinates_By_Row_and_Col(6, 0, left, top, right, bottom);
				ChessBoard.Set_Piece_By_Row_and_Col(6, 0, b, PieceID);
			}
			else if (n == 2){
				PieceID = 1;

				ChessBoard.Get_Coordinates_By_Row_and_Col(6, 1, left, top, right, bottom);
				ChessBoard.Set_Piece_By_Row_and_Col(6, 1, b, PieceID);
			}
			else if (n == 3){
				PieceID = 2;

				ChessBoard.Get_Coordinates_By_Row_and_Col(6, 2, left, top, right, bottom);
				ChessBoard.Set_Piece_By_Row_and_Col(6, 2, b, PieceID);
			}
			else if (n == 4){
				PieceID = 3;

				ChessBoard.Get_Coordinates_By_Row_and_Col(6, 3, left, top, right, bottom);
				ChessBoard.Set_Piece_By_Row_and_Col(6, 3, b, PieceID);
			}
			else if (n == 5){
				PieceID = 4;

				ChessBoard.Get_Coordinates_By_Row_and_Col(6, 4, left, top, right, bottom);
				ChessBoard.Set_Piece_By_Row_and_Col(6, 4, b, PieceID);
			}
			else if (n == 6){
				PieceID = 5;

				ChessBoard.Get_Coordinates_By_Row_and_Col(6, 5, left, top, right, bottom);
				ChessBoard.Set_Piece_By_Row_and_Col(6, 5, b, PieceID);
			}
			else if (n == 7){
				PieceID = 6;

				ChessBoard.Get_Coordinates_By_Row_and_Col(6, 6, left, top, right, bottom);
				ChessBoard.Set_Piece_By_Row_and_Col(6, 6, b, PieceID);
			}
			else if (n == 8){
				PieceID = 7;

				ChessBoard.Get_Coordinates_By_Row_and_Col(6, 7, left, top, right, bottom);
				ChessBoard.Set_Piece_By_Row_and_Col(6, 7, b, PieceID);
			}

		}
		else{
			strcpy_s(image_link, "Pawn-B.jpg");

			if (n == 1){
				PieceID = 0;

				ChessBoard.Get_Coordinates_By_Row_and_Col(1, 0, left, top, right, bottom);
				ChessBoard.Set_Piece_By_Row_and_Col(1, 0, b, PieceID);
			}
			else if (n == 2){
				PieceID = 1;

				ChessBoard.Get_Coordinates_By_Row_and_Col(1, 1, left, top, right, bottom);
				ChessBoard.Set_Piece_By_Row_and_Col(1, 1, b, PieceID);
			}
			else if (n == 3){
				PieceID = 2;

				ChessBoard.Get_Coordinates_By_Row_and_Col(1, 2, left, top, right, bottom);
				ChessBoard.Set_Piece_By_Row_and_Col(1, 2, b, PieceID);
			}
			else if (n == 4){
				PieceID = 3;

				ChessBoard.Get_Coordinates_By_Row_and_Col(1, 3, left, top, right, bottom);
				ChessBoard.Set_Piece_By_Row_and_Col(1, 3, b, PieceID);
			}
			else if (n == 5){
				PieceID = 4;

				ChessBoard.Get_Coordinates_By_Row_and_Col(1, 4, left, top, right, bottom);
				ChessBoard.Set_Piece_By_Row_and_Col(1, 4, b, PieceID);
			}
			else if (n == 6){
				PieceID = 5;

				ChessBoard.Get_Coordinates_By_Row_and_Col(1, 5, left, top, right, bottom);
				ChessBoard.Set_Piece_By_Row_and_Col(1, 5, b, PieceID);
			}
			else if (n == 7){
				PieceID = 6;

				ChessBoard.Get_Coordinates_By_Row_and_Col(1, 6, left, top, right, bottom);
				ChessBoard.Set_Piece_By_Row_and_Col(1, 6, b, PieceID);
			}
			else if (n == 8){
				PieceID = 7;

				ChessBoard.Get_Coordinates_By_Row_and_Col(1, 7, left, top, right, bottom);
				ChessBoard.Set_Piece_By_Row_and_Col(1, 7, b, PieceID);
			}

		}
		AdjustImageDimensions();
		readimagefile(image_link, left, top, right, bottom);
	}

	int Move(int x1, int y1, int x2, int y2, int &c_id){
		int r1, c1, r2, c2, l, t, r, b;

		ChessBoard.Get_Row_and_Col_By_Click(x1, y1, r1, c1);
		ChessBoard.Get_Row_and_Col_By_Click(x2, y2, r2, c2);

		if (c1 == c2 && abs(r1 - r2) == 1 && ChessBoard.Get_PieceID_By_Row_and_Col(r2, c2) == -1){		// 1 square ahead

			if ((PieceColor && r1 - r2 == 1) || (!PieceColor && r2 - r1 == 1)){
				ChessBoard.Get_Coordinates_By_Row_and_Col(r2, c2, l, t, r, b);
				Set_Coordinates(l, t, r, b);
				inOwnHalf = false;

				ChessBoard.Set_Piece_By_Row_and_Col(r2, c2, PieceColor, PieceID);
				ChessBoard.Reset_Piece_By_Row_and_Col(r1, c1);
				return 0;
			}

		}

		else if (inOwnHalf && c1 == c2 && abs(r1 - r2) == 2 && ChessBoard.Get_PieceID_By_Row_and_Col(r2, c2) == -1){ // 2 squares ahead

			if ((PieceColor && r1 - r2 == 2 && ChessBoard.Get_PieceID_By_Row_and_Col(r2 + 1, c2) == -1) || (!PieceColor && r2 - r1 == 2 && ChessBoard.Get_PieceID_By_Row_and_Col(r2 - 1, c2) == -1)){
				ChessBoard.Get_Coordinates_By_Row_and_Col(r2, c2, l, t, r, b);
				Set_Coordinates(l, t, r, b);
				inOwnHalf = false;

				ChessBoard.Set_Piece_By_Row_and_Col(r2, c2, PieceColor, PieceID);
				ChessBoard.Reset_Piece_By_Row_and_Col(r1, c1);
				return 0;
			}

		}

		else if (abs(c2 - c1) == 1 && abs(r1 - r2) == 1 && ChessBoard.Get_PieceID_By_Row_and_Col(r2, c2) != -1 && ChessBoard.Get_PieceColor_By_Row_and_Col(r2, c2) != PieceColor){

			if ((PieceColor && r1 - r2 == 1) || (!PieceColor && r2 - r1 == 1)){
				c_id = ChessBoard.Get_PieceID_By_Row_and_Col(r2, c2);
				ChessBoard.Get_Coordinates_By_Row_and_Col(r2, c2, l, t, r, b);
				Set_Coordinates(l, t, r, b);
				inOwnHalf = false;

				ChessBoard.Set_Piece_By_Row_and_Col(r2, c2, PieceColor, PieceID);
				ChessBoard.Reset_Piece_By_Row_and_Col(r1, c1);
				return 1;
			}

		}
		else{
			readimagefile("black.jpg", 5, 145, 230, 190);
			rectangle(6, 146, 141, 170);
			outtextxy(10, 150, "Move not Possible");
			PlaySound("Buzz.wav", NULL, SND_ASYNC);
			return -1;
		}

	}

};

class Player{

	char PlayerName[30];
	bool Color;		//White:true	Black:false
	Piece *myPieces[16];
	int c_left, c_top, c_right, c_bottom;

public:

	Player(char arr[], bool c, King &K, Queen &Q, Bishop &B1, Bishop &B2, Knight &Kn1, Knight &Kn2, Rook &R1, Rook &R2, Pawn &P1, Pawn &P2, Pawn &P3, Pawn &P4, Pawn &P5, Pawn &P6, Pawn &P7, Pawn &P8){

		strcpy_s(PlayerName, arr);
		Color = c;
		c_top = 103;
		c_bottom = 164;
		if (Color){
			c_left = 245;
			c_right = 306;
		}
		else{
			c_left = 985;
			c_right = 1046;
		}
		myPieces[K.Get_PieceID()] = &K;

		myPieces[Q.Get_PieceID()] = &Q;

		myPieces[B1.Get_PieceID()] = &B1;
		myPieces[B2.Get_PieceID()] = &B2;

		myPieces[Kn1.Get_PieceID()] = &Kn1;
		myPieces[Kn2.Get_PieceID()] = &Kn2;

		myPieces[R1.Get_PieceID()] = &R1;
		myPieces[R2.Get_PieceID()] = &R2;

		myPieces[P1.Get_PieceID()] = &P1;
		myPieces[P2.Get_PieceID()] = &P2;
		myPieces[P3.Get_PieceID()] = &P3;
		myPieces[P4.Get_PieceID()] = &P4;
		myPieces[P5.Get_PieceID()] = &P5;
		myPieces[P6.Get_PieceID()] = &P6;
		myPieces[P7.Get_PieceID()] = &P7;
		myPieces[P8.Get_PieceID()] = &P8;

	}

	void Set_Captured_piece(int id){
		myPieces[id]->Set_Coordinates(c_left, c_top, c_right, c_bottom);
		if (c_left == 245){
			c_left = 299;
			c_right = 360;
		}
		else if (c_left == 299){
			c_left = 245;
			c_right = 306;
			c_top += 61;
			c_bottom += 61;
		}
		else if (c_left == 985){
			c_left = 1039;
			c_right = 1107;
		}
		else if (c_left == 1039){
			c_left = 985;
			c_right = 1046;
			c_top += 61;
			c_bottom += 61;
		}
	}

	void Draw(){
		for (int i = 0; i < 16; i++)
			myPieces[i]->Draw();
	}

	int Turn(int &c_id){
		int x1, y1, x2, y2, id1, id2, top, left, right, bottom,ret;
		bool colour;

		readimagefile("black.jpg", 5, 75, 230, 120);
		rectangle(50, 66, 190, 90);
		if (Color)
			outtextxy(67, 70, "* White's Turn *");
		else
			outtextxy(67, 70, "* Black's Turn *");

		start:
		while (true){
		
			while (!ismouseclick(WM_LBUTTONDOWN) && !ismouseclick(WM_RBUTTONDOWN)){}
			if (ismouseclick(WM_RBUTTONDOWN)){
				getmouseclick(WM_RBUTTONDOWN, x1, y1);
				readimagefile("black.jpg", 1155, 145, 1275, 180);
				rectangle(1156, 146, 1274, 179);
				ChessBoard.Get_PieceInfo(x1, y1, colour, id1);
			
				if (colour && id1 != -1){
					outtextxy(1170,155,"White ");
					outtextxy(1215, 155, myPieces[id1]->Get_PieceName());
				}
				else{
					outtextxy(1170, 155, "Black ");
					outtextxy(1215, 155, myPieces[id1]->Get_PieceName());
				}
				continue;
			}
					
			getmouseclick(WM_LBUTTONDOWN, x1, y1);
			ChessBoard.Get_PieceInfo(x1, y1, colour, id1);
			if (x1<424 || x1>924 || y1<102 || y1>602){
				readimagefile("black.jpg", 5, 145, 230,190);
				rectangle(6, 146, 229, 170);
				outtextxy(10, 150, "Please remain within the board");
				PlaySound("Buzz.wav", NULL, SND_ASYNC);
			}
			else if (id1 == -1){
				readimagefile("black.jpg", 5, 145, 230, 190);
				rectangle(6, 146, 229, 170);
				outtextxy(10, 150, "Please choose a Piece to Move");
				PlaySound("Buzz.wav", NULL, SND_ASYNC);
			}
			else if (colour != Color){
				readimagefile("black.jpg", 5, 145, 230, 190);
				rectangle(6, 146, 229, 189);
				outtextxy(10, 150, "You can choose only your Piece");
				outtextxy(10, 167, "to Move");
				PlaySound("Buzz.wav", NULL, SND_ASYNC);
			}

			else{
				PlaySound("Pick.wav", NULL, SND_ASYNC | SND_ASYNC);
				break;
			}
		}

		while (true){
		
			while (!ismouseclick(WM_LBUTTONDOWN) && !ismouseclick(WM_RBUTTONDOWN)){}
			if (ismouseclick(WM_RBUTTONDOWN)){
				getmouseclick(WM_RBUTTONDOWN, x1, y1);
				readimagefile("black.jpg", 1155, 145, 1275, 180);
				rectangle(1156, 146, 1274, 179);

				ChessBoard.Get_PieceInfo(x1, y1, colour, id1);

				if (colour && id1 != -1){
					outtextxy(1170, 155, "White ");
					outtextxy(1215, 155, myPieces[id1]->Get_PieceName());
				}
				else{
					outtextxy(1170, 155, "Black ");
					outtextxy(1215, 155, myPieces[id1]->Get_PieceName());
				}
				continue;

			}
			
			getmouseclick(WM_LBUTTONDOWN, x2, y2);
			ChessBoard.Get_PieceInfo(x2, y2, colour, id2);
			if (x1<424 || x1>924 || y1<102 || y1>602){
				readimagefile("black.jpg", 5, 145, 230, 190);
				rectangle(6, 146, 229, 170);
				outtextxy(10, 150, "Please remain within the board");
				PlaySound("Buzz.wav", NULL, SND_ASYNC);
				goto start;
			}
			else if (colour == Color && id2 != -1){
				readimagefile("black.jpg", 5, 145, 230, 190);
				rectangle(6, 146, 187, 170);
				outtextxy(10, 150, "Choose correct destination");
				PlaySound("Buzz.wav", NULL, SND_ASYNC);
				goto start;
			}
			else
				break;
		}

		return myPieces[id1]->Move(x1, y1, x2, y2, c_id);
	
	}
};

void INTERFACE(){
	cleardevice();

	readimagefile("b7.jpg", 0, 0, 1350, 690);
	rectangle(245, 100, 365, 590);
	setfillstyle(SOLID_FILL, 0);
	floodfill(246, 101, getmaxcolor());

	rectangle(985, 100, 1105, 590);
	setfillstyle(SOLID_FILL, 15);
	floodfill(986, 101, getmaxcolor());

	readimagefile("bo.jpg", 375, 50, 975, 640);
	outtextxy(1115, 107, "* Right Click on a Piece to get its");
	outtextxy(1125, 125, "Info.");

}

int main(){
	int x1, y1,c_id, x;
	
	initwindow(1350, 690, "Chuss Chess");
	
	INTERFACE();


	bool Color = true;

	King myKing(Color);	Queen myQueen(Color); Bishop myBishop_1(Color, 1); Bishop myBishop_2(Color, 2); Knight myKnight_1(Color, 1); Knight myKnight_2(Color, 2); Rook myRook_1(Color, 1); Rook myRook_2(Color, 2); Pawn myPawn_1(Color, 1); Pawn myPawn_2(Color, 2); Pawn myPawn_3(Color, 3); Pawn myPawn_4(Color, 4); Pawn myPawn_5(Color, 5); Pawn myPawn_6(Color, 6); Pawn myPawn_7(Color, 7); Pawn myPawn_8(Color, 8); 
	
	Player P1("Hamza", true, myKing, myQueen, myBishop_1, myBishop_2, myKnight_1, myKnight_2, myRook_1, myRook_2, myPawn_1, myPawn_2, myPawn_3, myPawn_4, myPawn_5, myPawn_6, myPawn_7, myPawn_8);

	Color = false;

	King amyKing(Color); Queen amyQueen(Color); Bishop amyBishop_1(Color, 1); Bishop amyBishop_2(Color, 2); Knight amyKnight_1(Color, 1); Knight amyKnight_2(Color, 2); Rook amyRook_1(Color, 1); Rook amyRook_2(Color, 2); Pawn amyPawn_1(Color, 1); Pawn amyPawn_2(Color, 2); Pawn amyPawn_3(Color, 3); Pawn amyPawn_4(Color, 4); Pawn amyPawn_5(Color, 5); Pawn amyPawn_6(Color, 6); Pawn amyPawn_7(Color, 7); Pawn amyPawn_8(Color, 8);

	Player P2("Lodhi", false, amyKing, amyQueen, amyBishop_1, amyBishop_2, amyKnight_1, amyKnight_2, amyRook_1, amyRook_2, amyPawn_1, amyPawn_2, amyPawn_3, amyPawn_4, amyPawn_5, amyPawn_6, amyPawn_7, amyPawn_8);

	while (true){
		x = P1.Turn(c_id);
		while (x == -1)
			x = P1.Turn(c_id);
		if (x==0)
			PlaySound("Drop.wav", NULL, SND_ASYNC);
		
		if (x == 1)
			P2.Set_Captured_piece(c_id);

		INTERFACE();
		P1.Draw();
		P2.Draw();

		x = P2.Turn(c_id);
		while (x == -1)
			x = P2.Turn(c_id);

		if (x == 0)
			PlaySound("Drop.wav", NULL, SND_ASYNC);

		if (x == 1)
			P1.Set_Captured_piece(c_id);
		
		INTERFACE();

		P1.Draw();
		P2.Draw();
	}

	system("pause");
	return 0;
}
