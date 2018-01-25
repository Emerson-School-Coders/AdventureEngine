//
//  Adventure Interpreter
//  CubanWarfare
//
//  Created by Homework User on 1/26/17.
//  Copyright © 2017 JackMacWindows. All rights reserved.
//

#ifndef Interpreter_hpp
#define Interpreter_hpp
#ifndef Engine_hpp
#include "Engine.hpp"
#endif
#include "json/json.h"
#include <map>

class AdventureFile {
    Json::Reader reader;
    Json::Value root;
    std::map<std::string, std::string> variables;
public:
    bool open(std::string file);
    std::string getFirstId();
    std::string getName();
    std::string doPath(std::string id);
};

#endif /* Interpreter_hpp */
