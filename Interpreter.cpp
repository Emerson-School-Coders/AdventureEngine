//
//  Adventure Interpreter
//  CubanWarfare
//
//  Created by Homework User on 1/26/17.
//  Copyright © 2017 JackMacWindows. All rights reserved.
//

#include "Interpreter.hpp"

bool findKey(std::map<std::string, std::string> m, std::string key) {
    std::map<std::string, std::string>::iterator it = m.find(key);
    if (it != m.end())
    {
        //element found;
        return true;
    }
    return false;
}

bool AdventureFile::open(std::string file) {
    std::string jsonDocument = readFile(file);
    if (jsonDocument == "E-1") return false;
    if (!this->reader.parse(jsonDocument, this->root)) {print(this->reader.getFormatedErrorMessages()); return false;}
    initScreen();
    return true;
}

std::string AdventureFile::getFirstId() {
	this->variables = {};
	return this->root["main"].asString();
}

std::string AdventureFile::getName() {
    return this->root["name"].asString();
}

std::string AdventureFile::doPath(std::string id) {
    Json::Value currentPath = this->root["paths"][id];
    clearS();
    
	if (currentPath.isMember("prerequisites")) {
        Json::Value::Members vars = currentPath["prerequisites"].getMemberNames();
        for (std::string variable : vars) {
            if (findKey(variables, variable)) {
                if (variables[variable] != currentPath["prerequisites"][variable].asString()) return currentPath["failedRequirements"].asString();
            }
            else return currentPath["failedRequirements"].asString();
        }
    }
    
    if (currentPath.isMember("image")) print(currentPath["image"].asString() + "\n\n");
    
    std::string currentString = currentPath["text"].asString();
    std::vector<size_t> positions;
    std::vector<size_t> stops;
    size_t pos = currentString.find("\\(", 0);
	while (pos != std::string::npos) {
    	positions.push_back(pos);
    	pos = currentString.find("\\(",pos+1);
	}
	for (size_t fp : positions) {
		size_t pp = currentString.find(")", fp);
		if (pp == std::string::npos) break;
		std::string varName = currentString.substr(fp + 2, pp - fp - 2);
		currentString.replace(fp, pp - fp + 1, this->variables[varName]);
	}
    print(currentString + "\n");
    
    if (currentPath.isMember("variables")) {
        Json::Value::Members vars = currentPath["variables"].getMemberNames();
        for (std::string variable : vars) this->variables[variable] = currentPath["variables"][variable].asString();
    }
    
    if (currentPath.isMember("special")) {
        if (currentPath["special"] == "goodend") {
            print("\n\t\t\tThe end. Press any option to exit. ");
            getNumber(true);
            return "";
        }
        else if (currentPath["special"] == "badend") {
            print("\n\t\t\tThe end. Press " + buttons[0] + " to restart, or any other choice to exit. ");
            int choice = getNumber();
            if (choice == 1) return this->getFirstId();
            else return "";
        }
        else if (currentPath["special"] == "anykey") {
            print("Press any key to continue.\n");
            getNumber(true);
            return currentPath["actions"][0].asString();
        }
        else print("Runtime warning: Unknown special path!\n");
    }
    
    int paths = currentPath["actions"].size();
    for (int i = 0; i < paths; i++) {
        print("Press " + buttons[i] + " to " + currentPath["names"][i].asString() + ".\n");
    }
    
    int num = getNumber();
    if (num == 5) {
        std::map<std::string, std::string>::iterator it;
        print("variables:\n");
        for (it = this->variables.begin(); it != this->variables.end(); it++) print(it->first + ": " + it->second + "\n");
        num = getNumber();
    }
    if (num == 0) return "";
    if (!currentPath["actions"].isValidIndex(num-1)) return id;
    else return currentPath["actions"][num-1].asString();
}
