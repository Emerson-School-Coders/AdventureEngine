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
#include <json/json.h>

#endif /* Interpreter_hpp */

class AdventureFile {
    Json::Reader reader;
    Json::Value root;
public:
    bool open(std::string file);
    std::string getFirstId();
    std::string getName();
    bool doPath(std::string id);
};
