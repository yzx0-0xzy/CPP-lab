//Connect4 人机对战
#include <iostream>
#include <vector>

using namespace std;
const int N_max = 1000;
const int M_max = 1000;
int N;//N*M的棋盘，棋盘的下标从0开始
int M;//N*M的棋盘，棋盘的下标从0开始
struct Point {
	int x, y;
};
int level_m[3][3] = { 100,200,400,100,200,800,200,400,10000 }, level;

//ai函数,传入棋盘数组和可下棋点的坐标数组，返回ai下子点
Point Ai(vector<int> cb[], vector<Point> xy) {
	const int m1 = level_m[level][0], m2= level_m[level][1], m3 = level_m[level][2];
	const int c1 = 220, c2 = 450, c3 = 100000;
	int num = xy.size();
	vector<int> computerWin, myWin;
	computerWin.resize(num), myWin.resize(num);

	for (int Pnum = 0; Pnum < num; ++Pnum) {
		int xi = xy[Pnum].x, yi = xy[Pnum].y;

		//竖向
		for (int i = xi - 3; i <= xi; ++i) {
			if (i < 0 || i + 3 >= N) continue;

			int cnt = 0;
			for (int j = 0; j < 4; ++j) {
				if (cb[i + j][yi] == 2) {
					++cnt;
				}
				if (cb[i + j][yi] == 1) {
					cnt = 5;
				}
			}
			if (cnt == 1) computerWin[Pnum] += c1;
			if (cnt == 2) computerWin[Pnum] += c2;
			if (cnt == 3) computerWin[Pnum] += c3;

			cnt = 0;
			for (int j = 0; j < 4; ++j) {
				if (cb[i + j][yi] == 1) {
					++cnt;
				}
				if (cb[i + j][yi] == 2) {
					cnt = 5;
				}
			}
			if (cnt == 1) myWin[Pnum] += m1;
			if (cnt == 2) myWin[Pnum] += m2;
			if (cnt == 3) myWin[Pnum] += m3;
		}

		//横向
		for (int i = yi - 3; i <= yi; ++i) {
			if (i < 0 || i + 3 >= M) continue;

			int cnt = 0;
			for (int j = 0; j < 4; ++j) {
				if (cb[xi][i + j] == 2) {
					++cnt;
				}
				if (cb[xi][i + j] == 1) {
					cnt = 5;
				}
			}
			if (cnt == 1) computerWin[Pnum] += c1;
			if (cnt == 2) computerWin[Pnum] += c2;
			if (cnt == 3) computerWin[Pnum] += c3;

			cnt = 0;
			for (int j = 0; j < 4; ++j) {
				if (cb[xi][i + j] == 1) {
					++cnt;
				}
				if (cb[xi][i + j] == 2) {
					cnt = 5;
				}
			}
			if (cnt == 1) myWin[Pnum] += m1;
			if (cnt == 2) myWin[Pnum] += m2;
			if (cnt == 3) myWin[Pnum] += m3;
		}

		//斜线
		for (int k = -3; k <= 0; ++k) {
			int _x = xi + k, _y = yi + k;
			if (_x < 0 || _x + 3 >= N) continue;
			if (_y < 0 || _y + 3 >= M) continue;

			int cnt = 0;
			for (int j = 0; j < 4; ++j) {
				if (cb[_x + j][_y + j] == 2) {
					++cnt;
				}
				if (cb[_x + j][_y + j] == 1) {
					cnt = 5;
				}
			}
			if (cnt == 1) computerWin[Pnum] += c1;
			if (cnt == 2) computerWin[Pnum] += c2;
			if (cnt == 3) computerWin[Pnum] += c3;

			cnt = 0;
			for (int j = 0; j < 4; ++j) {
				if (cb[_x + j][_y + j] == 1) {
					++cnt;
				}
				if (cb[_x + j][_y + j] == 2) {
					cnt = 5;
				}
			}
			if (cnt == 1) myWin[Pnum] += m1;
			if (cnt == 2) myWin[Pnum] += m2;
			if (cnt == 3) myWin[Pnum] += m3;

		}
		
		//反斜线
		for (int k = -3; k <= 0; ++k) {
			int _x = xi + k, _y = yi - k;
			if (_x < 0 || _x + 3 >= N) continue;
			if (_y-3 < 0 || _y >= M) continue;

			int cnt = 0;
			for (int j = 0; j < 4; ++j) {
				if (cb[_x + j][_y - j] == 2) {
					++cnt;
				}
				if (cb[_x + j][_y - j] == 1) {
					cnt = 5;
				}
			}
			if (cnt == 1) computerWin[Pnum] += c1;
			if (cnt == 2) computerWin[Pnum] += c2;
			if (cnt == 3) computerWin[Pnum] += c3;

			cnt = 0;
			for (int j = 0; j < 4; ++j) {
				if (cb[_x + j][_y - j] == 1) {
					++cnt;
				}
				if (cb[_x + j][_y - j] == 2) {
					cnt = 5;
				}
			}
			if (cnt == 1) myWin[Pnum] += m1;
			if (cnt == 2) myWin[Pnum] += m2;
			if (cnt == 3) myWin[Pnum] += m3;

		}
	}

	int max = -1, pos;
	for (int i = 0; i < num; ++i) {
		if (max < computerWin[i]) {
			max = computerWin[i];
			pos = i;
		}
		if (max < myWin[i]) {
			max = myWin[i];
			pos = i;
		}
	}
	return xy[pos];
}

//输出棋盘
void print(vector<int> cb[]) {
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			cout << cb[i][j];
		}
		cout << endl;
	}
}

//查找可以下棋的所有点	传入棋盘数组，返回可下棋点的数组
vector<Point> find(vector<int> cb[]) {
	vector<Point> ans;
	for (int i = 0; i <M; ++i) {
		int pos = N - 1;
		while (pos>=0 && cb[pos][i] != 0) --pos;
		if (pos < 0) continue;
		else ans.push_back({ pos,i });
	}
	return ans;
}

//传入棋盘cb和y，返回当前y列可以下棋的点的纵坐标
int getOrdinate(vector<int> cb[], int y) {
	if (y >= M || y < 0) return -1;
	int pos = N - 1;
	while (pos >= 0 && cb[pos][y] != 0) --pos;
	return pos;
}

//下棋，传入棋盘，下棋点，下棋方（1为人，2位计算机）
void Play(vector<int> cb[], Point point, int who) {
	cb[point.x][point.y] = who;
}

//判断是否分出了输赢，传入棋盘cb，下棋方player（1或2），返回1为player获胜
bool ifWin(vector<int> cb[], int player) {
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M - 3; ++j) {
			//横向
			bool judge = 1;
			for (int k = 0; k < 4; ++k) {
				if (cb[i][j + k] != player) judge = 0;
			}
			if (judge) return 1;
		}
	}

	for (int i = 0; i < M; ++i) {
		for (int j = 0; j < N - 3; ++j) {
			//竖向
			int judge = 1;
			for (int k = 0; k < 4; ++k) {
				if (cb[j + k][i] != player) judge = 0;
			}
			if (judge) return 1;
		}
	}

	for (int i = 0; i < N - 3; ++i) {
		for (int j = 0; j < M - 3; ++j) {
			//斜线
			bool judge = 1;
			for (int k = 0; k < 4; ++k) {
				if (cb[i + k][j + k] != player) judge = 0;
			}
			if (judge) return 1;

			//反斜线
			judge = 1;
			for (int k = 0; k < 4; ++k) {
				if (cb[i + k][j + 3 - k] != player) judge = 0;
			}
			if (judge) return 1;
		}
	}
	return 0;
}

int main() {
	cout << "Input the size of the chessboard(N*M, Separated by space):" << endl;
	cin >> N >> M;
	cout << "Input the difficulty level(1,2,3):" << endl;
	cin >> level;
	--level;
	vector<int> ChessBoard[N_max];
	for (int i = 0; i < N; ++i) ChessBoard[i].resize(M, 0);
	print(ChessBoard);
	int y;
	while (cin >> y) {
		int x = getOrdinate(ChessBoard, y);
		if (x<0) {
			cout << "WRONG SUBSCRIPT\n";
			continue;
		}
		system("cls");
		Play(ChessBoard, { x, y }, 1);
		print(ChessBoard);
		if (ifWin(ChessBoard, 1)) {
			cout << "You win!" << endl;
			return 0;
		}

		vector<Point>  feasible = find(ChessBoard);//找出所有可以下棋的点
		if (feasible.size() == 0) {//没有则为平局
			cout << "Draw!" << endl;
			return 0;
		}
		Point aiPoint = Ai(ChessBoard, feasible);//ai函数选择的最佳下棋点
		system("cls");
		Play(ChessBoard, aiPoint, 2);
		print(ChessBoard);//ai下棋

		if (ifWin(ChessBoard, 2)) {
			cout << "Computer win!" << endl;
			return 0;
		}
	}
}