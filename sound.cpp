#include "guess.h"
#include <mmsystem.h>
#include <windows.h>
#pragma comment(lib, "winmm.lib")

static void PlaySoundFile(const wchar_t* filename) {
    wchar_t exePath[MAX_PATH];
    GetModuleFileNameW(NULL, exePath, MAX_PATH);
    wchar_t* lastSlash = wcsrchr(exePath, L'\\');
    if (lastSlash) {
        *(lastSlash + 1) = L'\0';
    } else {
        exePath[0] = L'\0';
    }
    wchar_t soundPath[MAX_PATH];
    wcscpy(soundPath, exePath);
    wcscat(soundPath, filename);
    PlaySoundW(soundPath, NULL, SND_FILENAME | SND_ASYNC);
}

void PlayStartSound() {
    PlaySoundFile(L"static/start.wav");
}

void PlayWinnerSound() {
    PlaySoundFile(L"static/winner.wav");
}

void PlayDeadSound() {
    PlaySoundFile(L"static/dead.wav");
}