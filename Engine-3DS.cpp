//
//  Adventure Engine for 3DS
//  CubanWarfare
//
//  Created by Homework User on 1/28/17.
//  Copyright © 2017 JackMacWindows. All rights reserved.
//

#define ENGINETYPE 2
#include "Engine.hpp"
#include <3ds.h>
#include <stdio.h>
#include <stdlib.h>

std::string buttons[4] = {"A", "B", "X", "Y"}
bool init = false;
std::string enginetype = "3ds";

void initScreen() {
    gfxInit();
    consoleInit(GFX_TOP, NULL);
    init = true;
}

void print(std::string text) {
    if (!init) initScreen();
    printf(text.c_str());
}

std::string input(std::string text) {
    SwkbdState keyboard;
    char* buf;
    swkbdInit(&keyboard, SWKBD_TYPE_NORMAL, 2, 32);
    swkbdSetButton(&keyboard, SWKBD_BUTTON_RIGHT, "OK", true);
    swkbdSetButton(&keyboard, SWKBD_BUTTON_LEFT, "Cancel", false);
    if (swkbdInputText(&keyboard, buf, 32) == SWKBD_BUTTON_LEFT) return input();
    return std::string(buf);
}

std::string readFile(std::string file) {
    FILE *filep = fopen(file.c_str(), "r");
    u8* buffer;
    if (filep == NULL) return "E-1";
    fseek(filep, 0, SEEK_END);
    off_t size = ftell(filep);
    fseek(filep, 0, SEEK_SET);
    buffer = malloc(size);
    if (!buffer) goto return "E-1";
    off_t bytesRead = fread(buffer, 1, size, filep);
    fclose(filep);
    return std::string(buffer);
}

bool writeFile(std::string file, std::string text) {
    FILE *filep = fopen(file.c_str(), "w");
    if (filep == NULL) return false;
    fwrite(file.c_str(), 1, file.length(), filep);
    fclose(filep);
    return true;
}

int getNumber() {
    while (true) {
        hidScanInput();
        u32 kDown = hidKeysDown();
        if (kDown & KEY_A) return 1;
        else if (kDown & KEY_B) return 2;
        else if (kDown & KEY_X) return 3;
        else if (kDown & KEY_Y) return 4;
        else if (kDown & KEY_START) return 0;
    }
}

void clearS() {
    consoleClear();
}
