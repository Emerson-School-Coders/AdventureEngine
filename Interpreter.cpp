//
//  Adventure Interpreter
//  CubanWarfare
//
//  Created by Homework User on 1/26/17.
//  Copyright © 2017 JackMacWindows. All rights reserved.
//

#include "Interpreter.hpp"

bool AdventureFile::open(std::string file) {
    std::string jsonDocument = readFile(file);
    if (jsonDocument == "E-1") return false;
    if (!this->reader.parse(jsonDocument, this->root)) {print(this->reader.getFormatedErrorMessages()); return false;}
    return true;
}

std::string AdventureFile::getFirstId() {
    return this->root["main"].asString();
}

std::string AdventureFile::getName() {
    return this->root["name"].asString();
}

bool AdventureFile::doPath(std::string id) {
    Json::Value currentPath = this->root["paths"][id];
    clearS();
    if (currentPath.isMember("image")) print(currentPath["image"].asString() + "\n\n");
    print(currentPath["text"].asString() + "\n");
    if (currentPath.isMember("special")) {
        if (currentPath["special"] == "goodend") {
            print("\t\t\tThe end. Press any option to exit. ");
            getNumber();
            return false;
        }
        else if (currentPath["special"] == "badend") {
            print("\t\t\tThe end. Press " + buttons[0] + " to restart, or any other choice to exit. ");
            int choice = getNumber();
            if (choice == 1) this->doPath(this->getFirstId());
            else return false;
        }
        else print("Runtime warning: Unknown special path!\n");
    }
    int paths = currentPath["actions"].size();
    for (int i = 0; i < paths; i++) {
        print("Press " + buttons[i] + " to " + currentPath["names"][i].asString() + ".\n");
    }
    int num = getNumber();
    if (num == 0) return false;
    return doPath(currentPath["actions"][num-1].asString());
}
