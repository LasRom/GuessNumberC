#ifndef GUESS_H_INCLUDED
#define GUESS_H_INCLUDED

#include <windows.h>
#include <graphics.h>

// Режимы игры
#define MODE_ONCE       1
#define MODE_UNLIMITED  2
#define MODE_10_TIMES   3

// Структура кнопки
typedef struct {
    int x, y;
    int width, height;
    char text[50];
    COLORREF color;
} Button;

// Глобальные переменные (extern)
extern int gameMode;
extern int magic;
extern int guess;
extern int attempt;
extern int maxAttempts;
extern int gameState;
extern char history[100][100];
extern int historyCount;

// Прототипы функций отрисовки
void InitGraphics();
void DrawMainMenu();
void DrawGameScreen();
void DrawResultScreen(int result);
void DrawButton(Button btn);
int IsButtonClicked(Button btn, int x, int y);

// Прототипы игровых функций
void GenerateNumber();
int IsValidInput(int num);
void ModeOnceFunction();
void ModeUnlimitedFunction();
void Mode10TimesFunction();

// Прототипы звуковых функций
void PlayStartSound();
void PlayWinnerSound();
void PlayDeadSound();

#endif