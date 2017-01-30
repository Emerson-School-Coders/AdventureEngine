//
//  Adventure Engine for Windows
//  CubanWarfare
//
//  Created by Homework User on 1/26/17.
//  Copyright © 2017 JackMacWindows. All rights reserved.
//

#define ENGINETYPE 3
#include "Engine.hpp"
#include <iostream>
#include <fstream>
#include <Windows.h>

std::string buttons[4] = {"1", "2", "3", "4"};
std::string enginetype = "win";

void print(std::string text) {
    std::cout << text;
    std::cout.flush();
}

std::string input(std::string text) {
    std::string output;
    std::cout << text;
    std::cin >> output;
    return output;
}

std::string readFile(std::string file) {
    std::ifstream in;
    std::string output;
    in.open(file.c_str());
    if (!in.is_open()) return "E-1";
    while (!in.eof()) {
        std::string get;
        std::getline(in, get);
        output = output + get + "\n";
    }
    in.close();
    return output;
    //return "{\"name\": \"name\"}";
}

bool writeFile(std::string file, std::string text) {
    std::ofstream out;
    out.open(file.c_str());
    if (!out.is_open()) return false;
    out << text;
    out.close();
    return true;
}

char getch() {
    HANDLE handle = GetStdHandle(STD_INPUT_HANDLE);
    DWORD events;
    INPUT_RECORD buffer;
    PeekConsoleInput( handle, &buffer, 1, &events );
    if(events > 0)
    {
        ReadConsoleInput(handle, &buffer, 1, &events);
        return buffer.Event.KeyEvent.wVirtualKeyCode;
    }
    else return 0;
}

int getNumber() {
    char retval = getch();
    if (retval == '1') return 1;
    else if (retval == '2') return 2;
    else if (retval == '3') return 3;
    else if (retval == '4') return 4;
    else return getNumber();
}

void clearS() {
    HANDLE                     hStdOut;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD                      count;
    DWORD                      cellCount;
    COORD                      homeCoords = { 0, 0 };
    
    hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
    if (hStdOut == INVALID_HANDLE_VALUE) return;
    
    /* Get the number of cells in the current buffer */
    if (!GetConsoleScreenBufferInfo( hStdOut, &csbi )) return;
    cellCount = csbi.dwSize.X *csbi.dwSize.Y;
    
    /* Fill the entire buffer with spaces */
    if (!FillConsoleOutputCharacter(
                                    hStdOut,
                                    (TCHAR) ' ',
                                    cellCount,
                                    homeCoords,
                                    &count
                                    )) return;
    
    /* Fill the entire buffer with the current colors and attributes */
    if (!FillConsoleOutputAttribute(
                                    hStdOut,
                                    csbi.wAttributes,
                                    cellCount,
                                    homeCoords,
                                    &count
                                    )) return;
    
    /* Move the cursor home */
    SetConsoleCursorPosition( hStdOut, homeCoords );
}
