//
//  Adventure Main
//  CubanWarfare
//
//  Created by Homework User on 1/26/17.
//  Copyright © 2017 JackMacWindows. All rights reserved.
//

#include "Interpreter.hpp"
#include <vector>
#include <tuple>
#ifdef _WIN32
#include <Windows.h>
#endif
#ifdef __ARM_ARCH_6__ //3ds doesn't have a macro defined, if compiled on armv6 add a <3ds.h> file that is empty
#include <3ds.h>
#endif
#ifdef __APPLE__
#include <dirent.h>
#endif

AdventureFile warfare;
std::vector<std::string> files;

int main(int argc, const char * argv[]) {
    print("Adventure Launcher\nLoading list...\n");
    std::string pathPrefix;
#ifdef __APPLE__
    DIR *dpdf;
    struct dirent *epdf;
    dpdf = opendir(std::string(std::string(argv[0]).substr(0, std::string(argv[0]).find_last_of("/")) + "/games").c_str());
    if (dpdf != NULL) while ((epdf = readdir(dpdf))) files.push_back(std::string(epdf->d_name));
    else {print("Could not open directory"); return 1;}
    closedir(dpdf);
    pathPrefix = std::string(std::string(argv[0]).substr(0, std::string(argv[0]).find_last_of("/")) + "/games").c_str();
#endif
#ifdef __unix__
    DIR *dpdf;
    struct dirent *epdf;
    dpdf = opendir(std::string(std::string(argv[0]).substr(0, std::string(argv[0]).find_last_of("/")) + "/games").c_str());
    if (dpdf != NULL) while ((epdf = readdir(dpdf))) files.push_back(std::string(epdf->d_name));
    closedir(dpdf);
    pathPrefix = std::string(std::string(argv[0]).substr(0, std::string(argv[0]).find_last_of("/")) + "/games").c_str();
#endif
#ifdef _WIN32
    WIN32_FIND_DATA FindFileData;
    HANDLE hFind;
    hFind = FindFirstFile(".\\games", &FindFileData);
    if (hFind == INVALID_HANDLE_VALUE) {
        printf ("FindFirstFile failed (%d)\n", GetLastError());
        return 1;
    }
    files[0] = std::string(FindFileData.cFileName);
    while (GetLastError() != ERROR_NO_MORE_FILES) {
        FindNextFile(hFind, FindFileData);
        files.push_back(std::string(FindFileData.cFileName));
    }
    FindClose(hFind);
    pathPrefix = ".\\games";
#endif
#ifdef CONSOLE_RED
    Handle dirHandle;
    FS_DirectoryEntry entry;
    
    //Create an archive object
    FS_Archive sdmcArchive;
    
    //Open the SD card into the archive object
    FSUSER_OpenArchive( &sdmcArchive, ARCHIVE_SDMC, fsMakePath(PATH_EMPTY, ""));
    
    //Get a directory from the SD card archive ('/' in this case)
    FSUSER_OpenDirectory(&dirHandle, sdmcArchive, fsMakePath(PATH_ASCII, "/3ds/AdventureLauncher/games"));
    
    //Init some vars for storing directory listing data
    u32 entriesRead;
    static char name[1024];
    
    //Debug to show the function has gone this far
    for (;;){
        
        //Reset entries var
        entriesRead=0;
        
        //Read the next item in the directory
        FSDIR_Read(dirHandle, &entriesRead, 1, (FS_DirectoryEntry*)&entry);
        
        //If there is a next item
        if (entriesRead) {
            //also from lpp-3ds, converts a utf-8 to a string
            utf2ascii(&name[0], entry.name);
            files.push_back(std::string(name) + "." + std::string(entry.shortExt));
        } else break;
    }
    //Close handles and archives.
    FSDIR_Close(dirHandle);
    svcCloseHandle(dirHandle);
    FSUSER_CloseArchive(&sdmcArchive);
    pathPrefix = "/3ds/AdventureLauncher/games";
#endif
    std::vector<std::pair<std::string, std::string>> names;
    for (std::string file : files) {
        if (file.substr(file.find(".")) == ".json") {
            warfare.open(pathPrefix + file);
            names.push_back(std::make_pair(warfare.getName(), file));
        }
    }
    clearS();
    print("Here are your options. Type the number to select it:\n");
    int i = 1;
    for (std::tuple<std::string, std::string> name : names) {
        print(std::to_string(i) + ". " + std::get<0>(name) + "\n");
        i++;
    }
#ifdef CONSOLE_RED
    print("Press any letter button to open the keyboard.");
    getNumber();
#endif
    std::string choice = input();
    print(choice);
    int number;
    try {
        number = stoi(choice);
    } catch (const std::invalid_argument& ia) {
        print("No number in string.\nExiting...\n");
        goto Exit;
    }
    print("Starting " + std::get<0>(names[number-1]) + "...\n\n");
    warfare.open(std::get<1>(names[number]));
    warfare.doPath(warfare.getFirstId());
Exit:
#ifdef CONSOLE_RED
    fsExit();
    gfxExit();
#endif
    return 0;
}
