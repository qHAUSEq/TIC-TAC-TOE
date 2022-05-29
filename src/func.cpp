#include "Header.h"

const int n = 3, y = 5, x = 12, q = 9;
int num = 0;
char ch;
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

void ConsoleShrift()
{
	CONSOLE_FONT_INFOEX fontInfo;
	fontInfo.cbSize = sizeof(fontInfo);
	GetCurrentConsoleFontEx(hStdOut, TRUE, &fontInfo);

	fontInfo.dwFontSize.Y = 20;
	SetCurrentConsoleFontEx(hStdOut, TRUE, &fontInfo);
}
void ConsoleCursorVisible(bool show, short size)
{
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(hStdOut, &structCursorInfo);
	structCursorInfo.bVisible = show;
	structCursorInfo.dwSize = size;
	SetConsoleCursorInfo(hStdOut, &structCursorInfo);
}
void GoToXY(int xpos, int ypos)
{
	COORD scrn;
	scrn.X = xpos; scrn.Y = ypos;
	SetConsoleCursorPosition(hStdOut, scrn);
}

enum ConsoleColor {
	Black, Blue, Green, Cyan, Red, Magenta, Brown, LightGray, DarkGray,
	LightBlue, LightGreen, LightCyan, LightRed, LightMagenta, Yellow, White
};
void SetColor(int text, int background)
{
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}


void StartFunc()
{
link:

	system("cls");

	string menu[n]{ " START vs PLAYER2 "," START vs BOT ", " EXIT " };
	char save[q]{ '*', '*', '*', '*', '*', '*', '*', '*', '*' };
	int active_menu = 0;

	while (true)
	{
		Print_StringMenu(menu, &active_menu);

		ch = _getch();
		if (ch == -32) ch = _getch();
		switch (ch)
		{
		case UP:
		{
			--active_menu;
			break;
		}
		case DOWN:
		{
			++active_menu;
			break;
		}
		case ENTER:
		{
			switch (active_menu)
			{
			case 0:
			{
				PlaywithUser(save);
				goto link;
			}
			case 1:
			{
				PlaywithBot(save);
				goto link;
			}
			case 2:
			{
				exit(0);
			}
			}
			break;
		}
		case ESCAPE:
		{
			exit(0);
		}
		}
		system("cls");
	}
}



void PlaywithUser(char save[])
{
	system("cls");

	SetColor(Blue, 0);
	cout << "\nThe first move for the crosses (player one), second move for zeros (Player two) \n"
		<< "Use arrows to move ";
	SetColor(Red, 0);
	cout << " \74- -\76 \30 \31\n";
	SetColor(Blue, 0);
	cout << "To put a cross or a zero, press ";
	SetColor(Red, 0);
	cout << " ENTER\n\n";
	SetColor(Yellow, 0);

	int qty[q];
	int active_menu = 0, move = 1;
	bool arr[3]{ false, false, false };
	bool edit = true;

	string player1, player2;
	cout << "Enter the nickname of the first player: ";
	cin >> player1;
	cout << "Enter the nickname of the second player: ";
	cin >> player2;

link2:

	bool even = false, uneven = false, winner = false;

	system("cls");

	while (edit)
	{
		SetColor(Yellow, 0);
		GoToXY(13, 15);
		cout << move << " move." << endl;
		if (move % 2 == 0)
		{
			cout << "\t  Player turn: ";
			SetColor(Cyan, 0);
			cout << player2 << endl;
			SetColor(Yellow, 0);

			even = true;
		}
		else
		{
			cout << "\t  Player turn: ";
			SetColor(Red, 0);
			cout << player1 << endl;
			SetColor(Yellow, 0);

			even = false;
		}
		SetColor(Blue, 0);
		cout << "\n\nIf you want to leave in main menu, press ";
		SetColor(Red, 0);
		cout << "ESCAPE \n\n";
		SetColor(Yellow, 0);

		Print_Field(&active_menu, qty);
		Print_X(&active_menu, save);
		Print_O(&active_menu, save);
		check_(save, &edit, player1, player2, move, arr);

		ch = _getch();
		if (ch == -32) ch = _getch();
		switch (ch)
		{
		case UP:
		{
			active_menu -= 3;
			break;
		}
		case DOWN:
		{
			active_menu += 3;
			break;
		}
		case RIGHT:
		{
			++active_menu;
			break;
		}
		case LEFT:
		{
			--active_menu;
			break;
		}
		case ENTER:
		{
			if (even == false)
			{
				for (int i = 0; i < q; i++)
				{
					if (qty[i] == active_menu && save[i] == '*')
					{
						save[i] = 'X';
						Print_X(&active_menu, save);
						i++;
					}
					if (qty[i] == active_menu && save[i] != '*') goto link2;
				}
			}
			else
			{
				for (int i = 0; i < q; i++)
				{
					if (qty[i] == active_menu && save[i] == '*')
					{
						save[i] = '0';
						Print_O(&active_menu, save);
						i++;
					}
					if (qty[i] == active_menu && save[i] != '*') goto link2;
				}
			}

			move++;
			goto link2;
		}
		case ESCAPE:
		{
			edit = false; break;
		}
		}
	}
}
void PlaywithBot(char save[])
{
	system("cls");

	bool arr[n]{ false, false, false };
	bool edit = false;
	pick_difficulty(arr);

	SetColor(Blue, 0);
	cout << "\nThe first move for the crosses, second move for zeros \n"
		<< "Use arrows to move ";
	SetColor(Red, 0);
	cout << " \74- -\76 \30 \31\n";
	SetColor(Blue, 0);
	cout << "To put a cross or a zero, press ";
	SetColor(Red, 0);
	cout << " ENTER\n\n";
	SetColor(Yellow, 0);

	int qty[q];
	int active_menu = 0, move = 1;
	bool bot = false; edit = true;

	string player1, player2;
	cout << "Enter the nickname of the player: ";
	cin >> player1;

	pick_move(&player1, &player2, &bot);

link2:

	bool even = false, uneven = false;

	system("cls");

	while (edit)
	{
		Print_Field(&active_menu, qty);
		Print_X(&active_menu, save);
		Print_O(&active_menu, save);
		check_(save, &edit, player1, player2, move, arr);
		if (edit == false) break;
		if (bot)
		{
			Bot_AI(arr, &bot, &move, save, player1);
			goto link2;
		}

		SetColor(Yellow, 0);
		GoToXY(13, 15);
		cout << move << " moves " << endl;
		if (move % 2 == 0)
		{
			cout << "\t  Player turn: ";
			SetColor(Cyan, 0);
			cout << player2 << endl;
			SetColor(Yellow, 0);

			even = false;
		}
		else
		{
			cout << "\t  Player turn: ";
			SetColor(Red, 0);
			cout << player1 << endl;
			SetColor(Yellow, 0);

			even = true;
		}

		SetColor(Blue, 0);
		cout << "\n\nIf you want to leave in main menu, press ";
		SetColor(Red, 0);
		cout << "ESCAPE \n\n";
		SetColor(Yellow, 0);

		ch = _getch();
		if (ch == -32) ch = _getch();
		switch (ch)
		{
		case UP:
		{
			active_menu -= 3;
			break;
		}
		case DOWN:
		{
			active_menu += 3;
			break;
		}
		case RIGHT:
		{
			++active_menu;
			break;
		}
		case LEFT:
		{
			--active_menu;
			break;
		}
		case ENTER:
		{
			if (even)
			{
				for (int i = 0; i < q; i++)
				{
					if (qty[i] == active_menu && save[i] == '*')
					{
						save[i] = 'X';
						Print_X(&active_menu, save);
						i++;
					}
					if (qty[i] == active_menu && save[i] != '*') goto link2;
				}
			}
			else
			{
				for (int i = 0; i < q; i++)
				{
					if (qty[i] == active_menu && save[i] == '*')
					{
						save[i] = '0';
						Print_O(&active_menu, save);
						i++;
					}
					if (qty[i] == active_menu && save[i] != '*') goto link2;
				}
			}

			bot = true;
			move++;
			goto link2;
		}
		case ESCAPE:
		{
			edit = false; break;
		}
		}
	}
}

void Print_StringMenu(string Menu[], int* active_menu)
{
	for (int i = num; i < n; i++)
	{
		if (*active_menu == n || *active_menu == -1)
		{
			i = 0;
			*active_menu = 0;
		}
		if (i == *active_menu)
		{
			SetColor(Green, 0);
			cout << "=>";
		}
		else SetColor(Yellow, 0);
		SetColor(Yellow, 0);
		cout << Menu[i] << endl;
	}
}
void Print_Field(int* active_menu, int qty[])
{
	char square[y][x]{ "\311\315\315\315\315\315\315\315\315\315\273", "\272         \272", "\272         \272", "\272         \272", "\310\315\315\315\315\315\315\315\315\315\274" };
	int x2 = 0, y2 = 0, qt = 0;

	for (int i = num; i < q; i++)
	{
		y2 = 0;
		if (*active_menu == q || *active_menu == q + 1 || *active_menu == q + 2 || *active_menu == -1 || *active_menu == -2 || *active_menu == -3)
		{
			i = 0;
			*active_menu = 0;
		}
		if (i == *active_menu)
		{
			SetColor(Green, 0);
		}
		else SetColor(Yellow, 0);

		if (i == 0) GoToXY(x2, y2);
		if (i == 1) GoToXY(x2 = 11, y2);
		if (i == 2) GoToXY(x2 = 22, y2);
		if (i == 3) GoToXY(x2 = 0, y2 = 5);
		if (i == 4) GoToXY(x2 = 11, y2 = 5);
		if (i == 5) GoToXY(x2 = 22, y2 = 5);
		if (i == 6) GoToXY(x2 = 0, y2 = 10);
		if (i == 7) GoToXY(x2 = 11, y2 = 10);
		if (i == 8) GoToXY(x2 = 22, y2 = 10);
		for (int l = 0; l < y; l++)
		{
			if (i == 0) GoToXY(x2, y2++);
			if (i == 1) GoToXY(x2, y2++);
			if (i == 2) GoToXY(x2, y2++);
			if (i == 3) GoToXY(x2, y2++);
			if (i == 4) GoToXY(x2, y2++);
			if (i == 5) GoToXY(x2, y2++);
			if (i == 6) GoToXY(x2, y2++);
			if (i == 7) GoToXY(x2, y2++);
			if (i == 8) GoToXY(x2, y2++);
			for (int j = 0; j < x; j++)
			{
				cout << square[l][j];
			}
			cout << endl;
		}
		qty[i] = qt; // Для определения номера квадрата
		qt++;
	}
}
void Print_X(int* active_menu, char save[])
{
	char X[3][10]{ "  \134/   ", "  /\134   " };
	int x2 = 2, y2 = 1;

	for (int l = num; l < q; l++)
	{
		if (l == *active_menu)
		{
			SetColor(Green, 0);
		}
		else SetColor(Red, 0);

		if (save[l] == 'X')
		{
			y2 = 1; x2 = 2;
			if (l == 0) GoToXY(x2, y2);
			if (l == 1) GoToXY(x2 = 13, y2);
			if (l == 2) GoToXY(x2 = 24, y2);
			if (l == 3) GoToXY(x2, y2 = 6);
			if (l == 4) GoToXY(x2 = 13, y2 = 6);
			if (l == 5) GoToXY(x2 = 24, y2 = 6);
			if (l == 6) GoToXY(x2, y2 = 11);
			if (l == 7) GoToXY(x2 = 13, y2 = 11);
			if (l == 8) GoToXY(x2 = 24, y2 = 11);
			for (int i = 0; i < 3; i++)
			{
				if (l == 0) GoToXY(x2, y2++);
				if (l == 1) GoToXY(x2, y2++);
				if (l == 2) GoToXY(x2, y2++);
				if (l == 3) GoToXY(x2, y2++);
				if (l == 4) GoToXY(x2, y2++);
				if (l == 5) GoToXY(x2, y2++);
				if (l == 6) GoToXY(x2, y2++);
				if (l == 7) GoToXY(x2, y2++);
				if (l == 8) GoToXY(x2, y2++);
				for (int j = 0; j < 10; j++)
				{
					cout << X[i][j];
				}
				cout << endl;
			}
		}
	}
}
void Print_O(int* active_menu, char save[])
{
	char O[5][7]{ "\311\315\315\315\273", "\272   \272", "\310\315\315\315\274" };
	int x2 = 3, y2 = 1;

	for (int l = num; l < q; l++)
	{
		if (l == *active_menu)
		{
			SetColor(Green, 0);
		}
		else SetColor(Cyan, 0);

		if (save[l] == '0')
		{
			int x2 = 3, y2 = 1;
			if (l == 0) GoToXY(x2, y2);
			if (l == 1) GoToXY(x2 = 14, y2);
			if (l == 2) GoToXY(x2 = 25, y2);
			if (l == 3) GoToXY(x2, y2 = 6);
			if (l == 4) GoToXY(x2 = 14, y2 = 6);
			if (l == 5) GoToXY(x2 = 25, y2 = 6);
			if (l == 6) GoToXY(x2, y2 = 11);
			if (l == 7) GoToXY(x2 = 14, y2 = 11);
			if (l == 8) GoToXY(x2 = 25, y2 = 11);
			for (int i = 0; i < 5; i++)
			{
				if (l == 0) GoToXY(x2, y2++);
				if (l == 1) GoToXY(x2, y2++);
				if (l == 2) GoToXY(x2, y2++);
				if (l == 3) GoToXY(x2, y2++);
				if (l == 4) GoToXY(x2, y2++);
				if (l == 5) GoToXY(x2, y2++);
				if (l == 6) GoToXY(x2, y2++);
				if (l == 7) GoToXY(x2, y2++);
				if (l == 8) GoToXY(x2, y2++);
				for (int j = 0; j < 7; j++)
				{
					cout << O[i][j];
				}
				cout << endl;
			}
		}
	}
}

void pick_move(string* player1, string* player2, bool* bot)
{
	string pick[2]{ " BOT ", " PLAYER " };
	bool edit = true;
	int active_menu = 0;

	cout << "\nWho will go first? " << endl;

	while (edit)
	{
		for (int i = num; i < 2; i++)
		{
			if (active_menu == 2 || active_menu == -1)
			{
				i = 0;
				active_menu = 0;
			}
			if (i == active_menu)
			{
				SetColor(Green, 0);
			}
			else SetColor(Yellow, 0);
			cout << pick[i];
		}

		ch = _getch();
		if (ch == -32) ch = _getch();
		switch (ch)
		{
		case LEFT:
		{
			--active_menu;
			break;
		}
		case RIGHT:
		{
			++active_menu;
			break;
		}
		case ENTER:
		{
			switch (active_menu)
			{
			case 0:
			{
				*player2 = *player1;
				*player1 = "[BOT] Ranvy";
				*bot = true;

				edit = false;
				break;
			}
			case 1:
			{
				*player2 = "[BOT] Rose";

				edit = false;
				break;
			}
			}
		}
		case ESCAPE:
		{
			edit = false;
			break;
		}
		}
		printf("%c[2K", 27); printf("\r");
	}
}
void pick_difficulty(bool arr[])
{
	string diff[n]{ " EASY ", " MEDIUM ", " HARD " };
	bool edit = true;
	int active_menu = 0;

	while (edit)
	{
		cout << "\nChoose game difficulty: \n\n";

		Print_StringMenu(diff, &active_menu);

		ch = _getch();
		if (ch == -32) ch = _getch();
		switch (ch)
		{
		case UP:
		{
			--active_menu;
			break;
		}
		case DOWN:
		{
			++active_menu;
			break;
		}
		case ENTER:
		{
			switch (active_menu)
			{
			case 0:
			{
				arr[0] = true;
				edit = false;
				break;
			}
			case 1:
			{
				arr[1] = true;
				edit = false;
				break;
			}
			case 2:
			{
				arr[2] = true;
				edit = false;
				break;
			}
			}
		}
		case ESCAPE:
		{
			edit = false;
			break;
		}
		}
		system("cls");
	}
}

void Bot_AI(bool arr[], bool* bot, int* move, char save[], string player1)
{
	bool random = true;
	int t = 0;

	if ((arr[0] || arr[1]) && *bot && *move == 1)
	{
		Random_answer(save, player1);
	}
	if (arr[0] && *move > 1 && *bot)
	{
		Random_answer(save, player1);
	}

	if (arr[1] && *move > 1 && *bot)
	{
		if (player1 == "[BOT] Ranvy")
		{
			if (random)
			{
				if (save[1] == 'X' && save[2] == 'X' && t == 0 && save[0] == '*') { save[0] = 'X'; t++; }
				if (save[0] == 'X' && save[2] == 'X' && t == 0 && save[1] == '*') { save[1] = 'X'; t++; }
				if (save[1] == 'X' && save[0] == 'X' && t == 0 && save[2] == '*') { save[2] = 'X'; t++; }

				if (save[0] == '0' && save[1] == '0' && t == 0 && save[2] == '*') { save[2] = 'X'; t++; }
				if (save[1] == '0' && save[2] == '0' && t == 0 && save[0] == '*') { save[0] = 'X'; t++; }
				if (save[0] == '0' && save[2] == '0' && t == 0 && save[1] == '*') { save[1] = 'X'; t++; }

				if (save[3] == '0' && save[4] == '0' && t == 0 && save[5] == '*') { save[5] = 'X'; t++; }
				if (save[3] == '0' && save[5] == '0' && t == 0 && save[4] == '*') { save[4] = 'X'; t++; }
				if (save[4] == '0' && save[5] == '0' && t == 0 && save[3] == '*') { save[3] = 'X'; t++; }

				if (save[6] == '0' && save[7] == '0' && t == 0 && save[8] == '*') { save[8] = 'X'; t++; }
				if (save[6] == '0' && save[8] == '0' && t == 0 && save[7] == '*') { save[7] = 'X'; t++; }
				if (save[7] == '0' && save[8] == '0' && t == 0 && save[6] == '*') { save[6] = 'X'; t++; }

				if (save[0] == '0' && save[3] == '0' && t == 0 && save[6] == '*') { save[6] = 'X'; t++; }
				if (save[0] == '0' && save[6] == '0' && t == 0 && save[3] == '*') { save[3] = 'X'; t++; }
				if (save[3] == '0' && save[6] == '0' && t == 0 && save[0] == '*') { save[0] = 'X'; t++; }

				if (save[4] == '0' && save[7] == '0' && t == 0 && save[1] == '*') { save[1] = 'X'; t++; }
				if (save[1] == '0' && save[7] == '0' && t == 0 && save[4] == '*') { save[4] = 'X'; t++; }
				if (save[1] == '0' && save[4] == '0' && t == 0 && save[7] == '*') { save[7] = 'X'; t++; }

				if (save[5] == '0' && save[8] == '0' && t == 0 && save[2] == '*') { save[2] = 'X'; t++; }
				if (save[2] == '0' && save[8] == '0' && t == 0 && save[5] == '*') { save[5] = 'X'; t++; }
				if (save[2] == '0' && save[5] == '0' && t == 0 && save[8] == '*') { save[8] = 'X'; t++; }

				if (t == 0) random = false;
			}
			if (random == false)
			{
				Random_answer(save, player1);
			}
		}
		else
		{
			if (random)
			{
				if (save[0] == '0' && save[6] == '0' && t == 0 && save[3] == '*') { save[3] = '0'; t++; }
				if (save[3] == '0' && save[5] == '0' && t == 0 && save[4] == '*') { save[4] = '0'; t++; }
				if (save[3] == '0' && save[4] == '0' && t == 0 && save[5] == '*') { save[5] = '0'; t++; }

				if (save[0] == 'X' && save[1] == 'X' && t == 0 && save[2] == '*') { save[2] = '0'; t++; }
				if (save[1] == 'X' && save[2] == 'X' && t == 0 && save[0] == '*') { save[0] = '0'; t++; }
				if (save[0] == 'X' && save[2] == 'X' && t == 0 && save[1] == '*') { save[1] = '0'; t++; }

				if (save[3] == 'X' && save[4] == 'X' && t == 0 && save[5] == '*') { save[5] = '0'; t++; }
				if (save[3] == 'X' && save[5] == 'X' && t == 0 && save[4] == '*') { save[4] = '0'; t++; }
				if (save[4] == 'X' && save[5] == 'X' && t == 0 && save[3] == '*') { save[3] = '0'; t++; }

				if (save[6] == 'X' && save[7] == 'X' && t == 0 && save[8] == '*') { save[8] = '0'; t++; }
				if (save[6] == 'X' && save[8] == 'X' && t == 0 && save[7] == '*') { save[7] = '0'; t++; }
				if (save[7] == 'X' && save[8] == 'X' && t == 0 && save[6] == '*') { save[6] = '0'; t++; }

				if (save[0] == 'X' && save[3] == 'X' && t == 0 && save[6] == '*') { save[6] = '0'; t++; }
				if (save[0] == 'X' && save[6] == 'X' && t == 0 && save[3] == '*') { save[3] = '0'; t++; }
				if (save[3] == 'X' && save[6] == 'X' && t == 0 && save[0] == '*') { save[0] = '0'; t++; }

				if (save[4] == 'X' && save[7] == 'X' && t == 0 && save[1] == '*') { save[1] = '0'; t++; }
				if (save[1] == 'X' && save[7] == 'X' && t == 0 && save[4] == '*') { save[4] = '0'; t++; }
				if (save[1] == 'X' && save[4] == 'X' && t == 0 && save[7] == '*') { save[7] = '0'; t++; }

				if (save[5] == 'X' && save[8] == 'X' && t == 0 && save[2] == '*') { save[2] = '0'; t++; }
				if (save[2] == 'X' && save[8] == 'X' && t == 0 && save[5] == '*') { save[5] = '0'; t++; }
				if (save[2] == 'X' && save[5] == 'X' && t == 0 && save[8] == '*') { save[8] = '0'; t++; }

				if (t == 0) random = false;
			}
			if (random == false)
			{
				Random_answer(save, player1);
			}
		}
	}

	if (arr[2] && *move > 0 && *bot)
	{
		if (player1 == "[BOT] Ranvy")
		{
			if (random)
			{
				if (save[1] == 'X' && save[2] == 'X' && t == 0 && save[0] == '*') { save[0] = 'X'; t++; }
				//if (save[0] == 'X' && save[2] == 'X' && t == 0 && save[1] == '*') { save[1] = 'X'; t++; }
				if (save[1] == 'X' && save[0] == 'X' && t == 0 && save[2] == '*') { save[2] = 'X'; t++; }

				if (save[0] == 'X' && save[6] == 'X' && t == 0 && save[3] == '*') { save[3] = 'X'; t++; }
				if (save[3] == 'X' && save[5] == 'X' && t == 0 && save[4] == '*') { save[4] = 'X'; t++; }
				if (save[3] == 'X' && save[4] == 'X' && t == 0 && save[5] == '*') { save[5] = 'X'; t++; }

				if (save[4] == 'X' && save[2] == 'X' && t == 0 && save[6] == '*') { save[6] = 'X'; t++; }
				if (save[1] == 'X' && save[4] == 'X' && t == 0 && save[7] == '*') { save[7] = 'X'; t++; }
				if (save[6] == 'X' && save[7] == 'X' && t == 0 && save[8] == '*') { save[8] = 'X'; t++; }


				//if (save[0] == '0' && save[1] == '0' && t == 0 && save[2] == '*') { save[2] = 'X'; t++; }
				if (save[1] == '0' && save[2] == '0' && t == 0 && save[0] == '*') { save[0] = 'X'; t++; }
				if (save[0] == '0' && save[2] == '0' && t == 0 && save[1] == '*') { save[1] = 'X'; t++; }

				if (save[3] == '0' && save[4] == '0' && t == 0 && save[5] == '*') { save[5] = 'X'; t++; }
				if (save[3] == '0' && save[5] == '0' && t == 0 && save[4] == '*') { save[4] = 'X'; t++; }
				if (save[4] == '0' && save[5] == '0' && t == 0 && save[3] == '*') { save[3] = 'X'; t++; }

				if (save[6] == '0' && save[7] == '0' && t == 0 && save[8] == '*') { save[8] = 'X'; t++; }
				if (save[6] == '0' && save[8] == '0' && t == 0 && save[7] == '*') { save[7] = 'X'; t++; }
				if (save[7] == '0' && save[8] == '0' && t == 0 && save[6] == '*') { save[6] = 'X'; t++; }

				if (save[0] == '0' && save[3] == '0' && t == 0 && save[6] == '*') { save[6] = 'X'; t++; }
				if (save[0] == '0' && save[6] == '0' && t == 0 && save[3] == '*') { save[3] = 'X'; t++; }
				if (save[3] == '0' && save[6] == '0' && t == 0 && save[0] == '*') { save[0] = 'X'; t++; }

				if (save[4] == '0' && save[7] == '0' && t == 0 && save[1] == '*') { save[1] = 'X'; t++; }
				if (save[1] == '0' && save[4] == '0' && t == 0 && save[7] == '*') { save[7] = 'X'; t++; }
				//if (save[1] == '0' && save[7] == '0' && t == 0 && save[7] == '*') { save[4] = 'X'; t++; }

				if (save[5] == '0' && save[8] == '0' && t == 0 && save[2] == '*') { save[2] = 'X'; t++; }
				if (save[2] == '0' && save[8] == '0' && t == 0 && save[5] == '*') { save[5] = 'X'; t++; }
				if (save[2] == '0' && save[5] == '0' && t == 0 && save[8] == '*') { save[8] = 'X'; t++; }

				if (save[4] == '0' && save[8] == '0' && t == 0 && save[0] == '*') { save[0] = 'X'; t++; }
				if (save[0] == '0' && save[8] == '0' && t == 0 && save[4] == '*') { save[4] = 'X'; t++; }
				if (save[0] == '0' && save[4] == '0' && t == 0 && save[8] == '*') { save[8] = 'X'; t++; }

				if (save[4] == '0' && save[6] == '0' && t == 0 && save[2] == '*') { save[2] = 'X'; t++; }
				if (save[2] == '0' && save[6] == '0' && t == 0 && save[4] == '*') { save[4] = 'X'; t++; }
				if (save[2] == '0' && save[4] == '0' && t == 0 && save[6] == '*') { save[6] = 'X'; t++; }

				if (t == 0) random = false;
			}
			if (random == false)
			{
				Random_answer(save, player1);
			}
		}
		else
		{
			if (random)
			{
				if (save[1] == '0' && save[2] == '0' && t == 0 && save[0] == '*') { save[0] = '0'; t++; }
				if (save[0] == '0' && save[2] == '0' && t == 0 && save[1] == '*') { save[1] = '0'; t++; }
				if (save[1] == '0' && save[0] == '0' && t == 0 && save[2] == '*') { save[2] = '0'; t++; }

				if (save[0] == '0' && save[6] == '0' && t == 0 && save[3] == '*') { save[3] = '0'; t++; }
				if (save[3] == '0' && save[5] == '0' && t == 0 && save[4] == '*') { save[4] = '0'; t++; }
				if (save[3] == '0' && save[4] == '0' && t == 0 && save[5] == '*') { save[5] = '0'; t++; }

				//if (save[0] == '0' && save[3] == '0' && t == 0 && save[6] == '*') { save[6] = '0'; t++; }
				if (save[1] == '0' && save[4] == '0' && t == 0 && save[7] == '*') { save[7] = '0'; t++; }
				if (save[6] == '0' && save[7] == '0' && t == 0 && save[8] == '*') { save[8] = '0'; t++; }


				if (save[0] == 'X' && save[1] == 'X' && t == 0 && save[2] == '*') { save[2] = '0'; t++; }
				if (save[1] == 'X' && save[2] == 'X' && t == 0 && save[0] == '*') { save[0] = '0'; t++; }
				if (save[0] == 'X' && save[2] == 'X' && t == 0 && save[1] == '*') { save[1] = '0'; t++; }

				if (save[3] == 'X' && save[4] == 'X' && t == 0 && save[5] == '*') { save[5] = '0'; t++; }
				if (save[3] == 'X' && save[5] == 'X' && t == 0 && save[4] == '*') { save[4] = '0'; t++; }
				if (save[4] == 'X' && save[5] == 'X' && t == 0 && save[3] == '*') { save[3] = '0'; t++; }

				if (save[6] == 'X' && save[7] == 'X' && t == 0 && save[8] == '*') { save[8] = '0'; t++; }
				if (save[6] == 'X' && save[8] == 'X' && t == 0 && save[7] == '*') { save[7] = '0'; t++; }
				if (save[7] == 'X' && save[8] == 'X' && t == 0 && save[6] == '*') { save[6] = '0'; t++; }

				if (save[0] == 'X' && save[3] == 'X' && t == 0 && save[6] == '*') { save[6] = '0'; t++; }
				if (save[0] == 'X' && save[6] == 'X' && t == 0 && save[3] == '*') { save[3] = '0'; t++; }
				if (save[3] == 'X' && save[6] == 'X' && t == 0 && save[0] == '*') { save[0] = '0'; t++; }

				if (save[4] == 'X' && save[7] == 'X' && t == 0 && save[1] == '*') { save[1] = '0'; t++; }
				if (save[1] == 'X' && save[7] == 'X' && t == 0 && save[4] == '*') { save[4] = '0'; t++; }
				if (save[1] == 'X' && save[4] == 'X' && t == 0 && save[7] == '*') { save[7] = '0'; t++; }

				if (save[5] == 'X' && save[8] == 'X' && t == 0 && save[2] == '*') { save[2] = '0'; t++; }
				//if (save[2] == 'X' && save[8] == 'X' && t == 0 && save[5] == '*') { save[5] = '0'; t++; }
				if (save[2] == 'X' && save[5] == 'X' && t == 0 && save[8] == '*') { save[8] = '0'; t++; }

				if (save[4] == 'X' && save[8] == 'X' && t == 0 && save[0] == '*') { save[0] = '0'; t++; }
				if (save[0] == 'X' && save[8] == 'X' && t == 0 && save[4] == '*') { save[4] = '0'; t++; }
				if (save[0] == 'X' && save[4] == 'X' && t == 0 && save[8] == '*') { save[8] = '0'; t++; }

				if (save[4] == 'X' && save[6] == 'X' && t == 0 && save[2] == '*') { save[2] = '0'; t++; }
				if (save[2] == 'X' && save[6] == 'X' && t == 0 && save[4] == '*') { save[4] = '0'; t++; }
				if (save[2] == 'X' && save[4] == 'X' && t == 0 && save[6] == '*') { save[6] = '0'; t++; }

				if (t == 0) random = false;
			}
			if (random == false)
			{
				Random_answer(save, player1);
			}
		}
	}
	(*move)++;
	*bot = false;
}

void Random_answer(char save[], string fmove)
{
	srand(static_cast<unsigned>( time ( NULL ) ) );
	int r;
	int active_menu = 0;

	for (int i = 0; i < q; )
	{
		r = rand() % 9 + 0;
		if (save[r] == '*')
		{
			active_menu = r;
			if (fmove == "[BOT] Ranvy")
			{
				save[r] = 'X';
				Print_X(&active_menu, save);
			}
			else
			{
				save[r] = '0';
				Print_O(&active_menu, save);
			}
			break;
		}

	}
}

void check_(char save[], bool* edit, string player1, string player2, int move, bool arr[])
{
	bool winner = false;
	string game_ = " Against the player ", d = " unknown ";
	if (player1 == "[BOT] Ranvy" || player2 == "[BOT] Rose") game_ = " Against the bot ";
	if (arr[0] == true) d = " EASY ";
	if (arr[1] == true) d = " MEDIUM ";
	if (arr[2] == true) d = " HARD ";

	std::ofstream gamemode("..\\log\\log.txt", std::ios_base::app);
	std::ofstream diff("..\\log\\log.txt", std::ios_base::app);
	std::ofstream win("..\\log\\log.txt", std::ios_base::app);
	std::ofstream qmove("..\\log\\log.txt", std::ios_base::app);
	std::ofstream date("..\\log\\log.txt", std::ios_base::app);

	GoToXY(13, 16);
	if ((save[0] == '0' && save[1] == '0' && save[2] == '0') || (save[0] == '0' && save[4] == '0' && save[8] == '0') || (save[0] == '0' && save[3] == '0' && save[6] == '0') || (save[3] == '0' && save[4] == '0' && save[5] == '0') || (save[6] == '0' && save[7] == '0' && save[8] == '0') || (save[2] == '0' && save[4] == '0' && save[6] == '0') || (save[1] == '0' && save[4] == '0' && save[7] == '0') || (save[2] == '0' && save[5] == '0' && save[8] == '0'))
	{

		winner = true;

		SetColor(Yellow, 0);
		cout << "\nQty move: " << move << endl;
		SetColor(LightMagenta, 0);
		cout << "Congratulations! ";
		SetColor(Cyan, 0);
		cout << player2;
		SetColor(LightMagenta, 0);
		cout << " - Winner " << endl;
		SetColor(Yellow, 0);

		gamemode << " \n\nGamemode: " << game_;
		diff << "        Difficulty: " << d;
		win << "        Winner:" << player2;
		qmove << "        Qty moves: " << move;
		date << "        Date & time: " << __DATE__ << " " << __TIME__;

		Sleep(5000);
		gamemode.close();
		win.close();
		qmove.close();
		date.close();
		*edit = false;
	}
	if ((save[0] == 'X' && save[1] == 'X' && save[2] == 'X') || (save[0] == 'X' && save[4] == 'X' && save[8] == 'X') || (save[0] == 'X' && save[3] == 'X' && save[6] == 'X') || (save[3] == 'X' && save[4] == 'X' && save[5] == 'X') || (save[6] == 'X' && save[7] == 'X' && save[8] == 'X') || (save[2] == 'X' && save[4] == 'X' && save[6] == 'X') || (save[1] == 'X' && save[4] == 'X' && save[7] == 'X') || (save[2] == 'X' && save[5] == 'X' && save[8] == 'X'))
	{

		winner = true;
		SetColor(Yellow, 0);
		cout << "\nQty move: " << move << endl;
		SetColor(LightMagenta, 0);
		cout << "Congratulations! ";
		SetColor(Red, 0);
		cout << player1;
		SetColor(LightMagenta, 0);
		cout << " - Winner " << endl;
		SetColor(Yellow, 0);

		gamemode << " \n\nGamemode: " << game_;
		diff << "        Difficulty: " << d;
		win << "        Winner:" << player1;
		qmove << "        Qty moves: " << move;
		date << "        Date & time: " << __DATE__ << " " << __TIME__;

		Sleep(5000);
		gamemode.close();
		win.close();
		qmove.close();
		date.close();
		*edit = false;
	}
	if (move > 9 && winner == false)
	{
		SetColor(Yellow, 0);
		cout << "\nQty move: " << move << endl;
		SetColor(LightMagenta, 0);
		cout << "This is so sadly... We have a draw... " << endl;

		gamemode << " \n\nGamemode: " << game_;
		diff << "        Difficulty: " << d;
		win << "        Winner: this is Draw";
		qmove << "        Qty moves: " << move;
		date << "        Date & time: " << __DATE__ << " " << __TIME__;

		Sleep(5000);
		gamemode.close();
		win.close();
		qmove.close();
		date.close();
		*edit = false;
	}
}