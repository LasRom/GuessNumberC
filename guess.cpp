#include "guess.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void GenerateNumber() {
    magic = rand() % 100 + 1;
}

int IsValidInput(int num) {
    return (num >= 1 && num <= 100);
}

void ModeOnceFunction() {
    char inputStr[10] = "";
    InputBox(inputStr, 10, _T("Please enter an integer between 1 and 100"), _T("Guess the Number"), "", 0, 0, false);
    if (strlen(inputStr) > 0) {
        guess = atoi(inputStr);
        if (!IsValidInput(guess)) {
            MessageBox(GetHWnd(), _T("Please enter an integer between 1 and 100!"), _T("Invalid input"), MB_OK);
            return;
        }
        if (guess == magic)
            sprintf(history[historyCount], "Attempt %d: %d -> Correct!", attempt, guess);
        else if (guess > magic)
            sprintf(history[historyCount], "Attempt %d: %d -> Too high!", attempt, guess);
        else
            sprintf(history[historyCount], "Attempt %d: %d -> Too low!", attempt, guess);
        historyCount++;
        if (guess == magic) {
            DrawResultScreen(1);
            gameState = 2;
        } else {
            DrawResultScreen(0);
            gameState = 2;
        }
    }
}

void ModeUnlimitedFunction() {
    char inputStr[10] = "";
    InputBox(inputStr, 10, _T("Please enter an integer between 1 and 100"), _T("Guess the Number"), "", 0, 0, false);
    if (strlen(inputStr) > 0) {
        guess = atoi(inputStr);
        if (!IsValidInput(guess)) {
            MessageBox(GetHWnd(), _T("Please enter an integer between 1 and 100!"), _T("Invalid input"), MB_OK);
            return;
        }
        if (guess == magic)
            sprintf(history[historyCount], "Attempt %d: %d -> Correct!", attempt, guess);
        else if (guess > magic)
            sprintf(history[historyCount], "Attempt %d: %d -> Too high!", attempt, guess);
        else
            sprintf(history[historyCount], "Attempt %d: %d -> Too low!", attempt, guess);
        historyCount++;
        if (guess == magic) {
            DrawResultScreen(1);
            gameState = 2;
        } else {
            attempt++;
            DrawGameScreen();
        }
    }
}

void Mode10TimesFunction() {
    if (attempt > maxAttempts) return;
    char inputStr[10] = "";
    InputBox(inputStr, 10, _T("Please enter an integer between 1 and 100"), _T("Guess the Number"), "", 0, 0, false);
    if (strlen(inputStr) > 0) {
        guess = atoi(inputStr);
        if (!IsValidInput(guess)) {
            MessageBox(GetHWnd(), _T("Please enter an integer between 1 and 100!"), _T("Invalid input"), MB_OK);
            return;
        }
        if (guess == magic)
            sprintf(history[historyCount], "Attempt %d: %d -> Correct!", attempt, guess);
        else if (guess > magic)
            sprintf(history[historyCount], "Attempt %d: %d -> Too high!", attempt, guess);
        else
            sprintf(history[historyCount], "Attempt %d: %d -> Too low!", attempt, guess);
        historyCount++;
        if (guess == magic) {
            DrawResultScreen(1);
            gameState = 2;
        } else {
            if (attempt >= maxAttempts) {
                DrawResultScreen(0);
                gameState = 2;
            } else {
                attempt++;
                DrawGameScreen();
            }
        }
    }
}