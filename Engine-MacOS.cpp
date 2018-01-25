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
#include <curses.h>

std::string buttons[4] = {"1", "2", "3", "4"};
std::string enginetype = "nix";

void initScreen() {
    initscr();
    //raw();			  // line-buffering off, echo off, etc.
    nonl();			  // NL conversions off
    intrflush( stdscr, FALSE );	  // we want ^C, etc...
    (void) keypad( stdscr, TRUE );  // extended keys ON
    curs_set( 1 );		  // make sure the cursor is visible
}

void print(std::string text) {
    waddstr(stdscr, text.c_str());
    wrefresh(stdscr);
}

std::string input(std::string text) {
    char * outstr = (char*)malloc(256);
    print(text);
    getstr(outstr);
    return std::string(outstr);
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

int getNumber(bool anyNum) {
    int c;
    if (!anyNum) {
        while (true) {
            raw();
            // wait for the user to press a single key
            flushinp();
            c = wgetch( stdscr );
            noraw();
            if (c == '1') return 1;
            else if (c == '2') return 2;
            else if (c == '3') return 3;
            else if (c == '4') return 4;
            else if (c == '8') return 5;
        }
    } else {
        raw();
        // wait for the user to press a single key
        flushinp();
        wgetch( stdscr );
        noraw();
        return 0;
    }
}

void clearS() {
    clear();
}

void exitScreen() {
    print("\n\n\nExiting...");
    sleep(1);
    noraw();
    nl();
    endwin();
    system("stty sane");
}
