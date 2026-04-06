#include "guess.h"
#include <stdio.h>
#include <string.h>

void InitGraphics() {
    initgraph(500, 600);
    setbkcolor(RGB(240, 240, 245));
    cleardevice();
    settextstyle(20, 0, _T("music"));
}

void DrawButton(Button btn) {
    setfillcolor(btn.color);
    fillrectangle(btn.x, btn.y, btn.x + btn.width, btn.y + btn.height);
    setlinecolor(RGB(50, 50, 50));
    rectangle(btn.x, btn.y, btn.x + btn.width, btn.y + btn.height);
    settextcolor(RGB(255, 255, 255));
    settextstyle(18, 0, _T("music"));
    setbkmode(TRANSPARENT);
    int textW = textwidth(btn.text);
    int textH = textheight(btn.text);
    int textX = btn.x + (btn.width - textW) / 2;
    int textY = btn.y + (btn.height - textH) / 2;
    outtextxy(textX, textY, btn.text);
}

void DrawMainMenu() {
    cleardevice();
    settextcolor(RGB(0, 0, 0));
    settextstyle(36, 0, _T("bold"));
    int titleW = textwidth(_T("Guess the Number"));
    int titleX = (500 - titleW) / 2;
    outtextxy(titleX, 60, _T("Guess the Number"));
    settextstyle(22, 0, _T("bold"));
    settextcolor(RGB(20, 20, 20));
    outtextxy(100, 130, _T("Please select game mode:"));
    setbkmode(TRANSPARENT);
    Button btn1 = {100, 200, 300, 60, "Mode 1: Only one guess", RGB(100, 200, 100)};
    Button btn2 = {100, 280, 300, 60, "Mode 2: Guess until correct", RGB(100, 150, 200)};
    Button btn3 = {100, 360, 300, 60, "Mode 3: Max 10 guesses", RGB(200, 150, 100)};
    DrawButton(btn1);
    DrawButton(btn2);
    DrawButton(btn3);
    settextstyle(14, 0, _T("music"));
    settextcolor(BLUE);
    outtextxy(100, 450, _T("Game Rules:"));
    outtextxy(120, 470, _T("1. Computer randomly generates an integer between 1 and 100"));
    outtextxy(120, 490, _T("2. You need to guess the number within limited attempts"));
    outtextxy(120, 510, _T("3. Each guess will be hinted as too high or too low"));
    outtextxy(120, 530, _T("4. The number of attempts varies by mode"));
}

void DrawGameScreen() {
    cleardevice();
    settextcolor(RGB(0, 0, 0));
    settextstyle(24, 0, _T("bold"));
    char modeText[50];
    if (gameMode == MODE_ONCE) strcpy(modeText, "Mode 1: Only one guess");
    else if (gameMode == MODE_UNLIMITED) strcpy(modeText, "Mode 2: Guess until correct");
    else strcpy(modeText, "Mode 3: Max 10 guesses");
    outtextxy(150, 30, modeText);
    settextstyle(18, 0, _T("music"));
    char attemptText[50];
    sprintf(attemptText, "Attempt %d", attempt);
    outtextxy(200, 80, attemptText);
    setfillcolor(RGB(255, 255, 255));
    fillrectangle(150, 150, 350, 200);
    setlinecolor(RGB(100, 100, 100));
    rectangle(150, 150, 350, 200);
    settextstyle(28, 0, _T("Arial"));
    settextcolor(RGB(0, 0, 0));
    if (historyCount > 0) {
        char lastGuess[10] = "";
        char *p = strchr(history[historyCount-1], ':');
        if (p) {
            p += 2;
            int i = 0;
            while (i < 3 && p[i] >= '0' && p[i] <= '9') {
                lastGuess[i] = p[i];
                i++;
            }
            outtextxy(180, 160, lastGuess);
        } else outtextxy(180, 160, _T(" "));
    } else {
        outtextxy(180, 160, _T(" "));
    }
    settextstyle(14, 0, _T("music"));
    settextcolor(RGB(0, 0, 0));
    outtextxy(150, 210, _T("Click [Enter Number] button to start guessing"));
    Button btnBack = {350, 500, 100, 40, "Back", RGB(200, 100, 100)};
    Button btnInput = {350, 400, 100, 40, "Enter Number", RGB(100, 200, 100)};
    Button btnReset = {350, 450, 100, 40, "Reset", RGB(200, 150, 100)};
    DrawButton(btnBack);
    DrawButton(btnInput);
    DrawButton(btnReset);
    settextstyle(14, 0, _T("music"));
    settextcolor(BLUE);
    outtextxy(50, 250, _T("History:"));
    int startY = 280;
    int maxDisplay = 8;
    int startIdx = (historyCount > maxDisplay) ? historyCount - maxDisplay : 0;
    for (int i = startIdx; i < historyCount && i < startIdx + maxDisplay; i++) {
        outtextxy(70, startY, history[i]);
        startY += 25;
    }
    if (gameMode == MODE_10_TIMES) {
        char rem[50];
        sprintf(rem, "Remaining attempts: %d", maxAttempts - attempt + 1);
        settextcolor(RGB(0, 0, 0));
        outtextxy(150, 120, rem);
    }
}

void DrawResultScreen(int result) {
    cleardevice();
    settextcolor(RGB(0, 0, 0));
    settextstyle(28, 0, _T("bold"));
    if (result == 1) {
        int w = textwidth(_T("Correct!"));
        outtextxy((500 - w)/2, 100, _T("Correct!"));
        settextstyle(20, 0, _T("Arial"));
        char ans[50];
        sprintf(ans, "Answer: %d", magic);
        w = textwidth(ans);
        outtextxy((500 - w)/2, 160, ans);
        char att[50];
        sprintf(att, "Total attempts: %d", attempt);
        w = textwidth(att);
        outtextxy((500 - w)/2, 200, att);
        PlayWinnerSound();
    } else {
        int w = textwidth(_T("Game Over!"));
        outtextxy((500 - w)/2, 100, _T("Game Over!"));
        settextstyle(20, 0, _T("Arial"));
        char ans[50];
        sprintf(ans, "Correct answer: %d", magic);
        w = textwidth(ans);
        outtextxy((500 - w)/2, 160, ans);
        if (gameMode == MODE_ONCE) {
            w = textwidth(_T("Only one guess mode ended"));
            outtextxy((500 - w)/2, 200, _T("Only one guess mode ended"));
        } else if (gameMode == MODE_10_TIMES) {
            w = textwidth(_T("10 chances used up"));
            outtextxy((500 - w)/2, 200, _T("10 chances used up"));
        }
        PlayDeadSound();
    }
    int btnW = 150;
    int btnX = (500 - btnW) / 2;
    Button btnAgain = {btnX, 350, btnW, 50, "Play Again", RGB(100, 200, 100)};
    Button btnMenu  = {btnX, 420, btnW, 50, "Back to Menu", RGB(200, 150, 100)};
    DrawButton(btnAgain);
    DrawButton(btnMenu);
}

int IsButtonClicked(Button btn, int x, int y) {
    return (x >= btn.x && x <= btn.x + btn.width &&
            y >= btn.y && y <= btn.y + btn.height);
}