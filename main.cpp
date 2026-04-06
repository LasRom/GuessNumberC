#include "guess.h"
#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

int main() {
    srand((unsigned)time(NULL));
    InitGraphics();
    DrawMainMenu();
    PlayStartSound();

    while (true) {
        if (MouseHit()) {
            MOUSEMSG msg = GetMouseMsg();
            if (msg.uMsg == WM_LBUTTONDOWN) {
                int x = msg.x, y = msg.y;
                Button btn1 = {100, 200, 300, 60, "", RGB(100,200,100)};
                Button btn2 = {100, 280, 300, 60, "", RGB(100,150,200)};
                Button btn3 = {100, 360, 300, 60, "", RGB(200,150,100)};

                if (gameState == 0) {
                    if (IsButtonClicked(btn1, x, y)) {
                        gameMode = MODE_ONCE;
                        gameState = 1;
                        GenerateNumber();
                        attempt = 1;
                        historyCount = 0;
                        DrawGameScreen();
                    } else if (IsButtonClicked(btn2, x, y)) {
                        gameMode = MODE_UNLIMITED;
                        gameState = 1;
                        GenerateNumber();
                        attempt = 1;
                        historyCount = 0;
                        maxAttempts = 100;
                        DrawGameScreen();
                    } else if (IsButtonClicked(btn3, x, y)) {
                        gameMode = MODE_10_TIMES;
                        gameState = 1;
                        GenerateNumber();
                        attempt = 1;
                        historyCount = 0;
                        maxAttempts = 10;
                        DrawGameScreen();
                    }
                }
                else if (gameState == 1) {
                    Button btnBack  = {350,500,100,40,"",RGB(200,100,100)};
                    Button btnInput = {350,400,100,40,"",RGB(100,200,100)};
                    Button btnReset = {350,450,100,40,"",RGB(200,150,100)};
                    if (IsButtonClicked(btnBack, x, y)) {
                        gameState = 0;
                        DrawMainMenu();
                    } else if (IsButtonClicked(btnInput, x, y)) {
                        switch (gameMode) {
                            case MODE_ONCE:      ModeOnceFunction(); break;
                            case MODE_UNLIMITED: ModeUnlimitedFunction(); break;
                            case MODE_10_TIMES:  Mode10TimesFunction(); break;
                        }
                    } else if (IsButtonClicked(btnReset, x, y)) {
                        GenerateNumber();
                        attempt = 1;
                        historyCount = 0;
                        DrawGameScreen();
                    }
                }
                else if (gameState == 2) {
                    Button btnAgain = {175,350,150,50,"",RGB(100,200,100)};
                    Button btnMenu  = {175,420,150,50,"",RGB(200,150,100)};
                    if (IsButtonClicked(btnAgain, x, y)) {
                        gameState = 1;
                        GenerateNumber();
                        attempt = 1;
                        historyCount = 0;
                        DrawGameScreen();
                    } else if (IsButtonClicked(btnMenu, x, y)) {
                        gameState = 0;
                        DrawMainMenu();
                    }
                }
            }
        }
        Sleep(10);
    }
    closegraph();
    return 0;
}