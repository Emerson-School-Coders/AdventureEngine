//
//  Adventure Interpreter
//  CubanWarfare
//
//  Created by Homework User on 1/26/17.
//  Copyright © 2017 JackMacWindows. All rights reserved.
//

#ifndef Interpreter_hpp
#define Interpreter_hpp
#include "Engine.hpp"
#include <json/json.h>
class AdventureFile {
    Json::Reader reader;
    Json::Value root;
public:
    bool open(std::string file);
    std::string getFirstId();
    std::string getName();
    bool doPath(std::string id);
};

#endif /* Interpreter_hpp */
