#pragma once
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <conio.h>
#include <string>
#include <time.h>
constexpr auto UP = 72, DOWN = 80, LEFT = 75, RIGHT = 77, ENTER = 13, ESCAPE = 27, SPACE = 32;

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ifstream;
using std::getline;

void SetColor(int text, int background);
void ConsoleFontSize();
void ConsoleCursorVisible(bool show, short size);
void GoToXY(int xpos, int ypos);



void StartFunc();
void PlaywithUser(char save[]);
void PlaywithBot(char save[]);
void Print_StringMenu(string Menu[], int* active_menu);
void Print_Field(int* active_menu, int qty[]);
void Print_X(int* active_menu, char save[]);
void Print_O(int* active_menu, char save[]);
void pick_move(string* player1, string* player2, bool* bot);
void pick_difficulty(bool arr[]);
void Bot_AI(bool arr[], bool* bot, int* move, char save[], string player1);
void Random_answer(char save[], string fmove);
void check_(char save[], bool* edit, string player1, string player2, int move, bool arr[]);