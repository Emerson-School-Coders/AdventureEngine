//
//  Adventure Engine for *nix
//  CubanWarfare
//
//  Created by Homework User on 1/26/17.
//  Copyright © 2017 JackMacWindows. All rights reserved.
//

#define ENGINETYPE 1
#include "Engine.hpp"
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <termios.h>
#include <curses.h>

std::string buttons[4] = {"1", "2", "3", "4"};
std::string enginetype = "nix";

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

int getNumber() {
    char retval = getch();
    if (retval == '1') return 1;
    else if (retval == '2') return 2;
    else if (retval == '3') return 3;
    else if (retval == '4') return 4;
    else return getNumber();
}

void clearS() {
    clear();
}
