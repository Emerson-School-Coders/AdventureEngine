//
//  Adventure Engine
//  CubanWarfare
//
//  Created by Homework User on 1/26/17.
//  Copyright © 2017 JackMacWindows. All rights reserved.
//

#ifndef Engine_hpp
#define Engine_hpp

//#define ENGINETYPE
#include <string>

extern std::string buttons[4];
extern std::string enginetype;

extern void print(std::string text);
extern std::string input(std::string text = "> ");
extern std::string readFile(std::string file);
extern bool writeFile(std::string file, std::string text);
extern int getNumber(bool anyNum = false);
extern void clearS();
extern void initScreen();
extern void exitScreen();

#endif /* Engine_hpp */
