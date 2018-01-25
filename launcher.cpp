#include <iostream>
#include <dirent.h>
#include "Interpreter.hpp"
/* uncomment if using 3DS
#define __3DS__
#include <3ds/applets/swkbd.h>
//*/

AdventureFile adv;

int main(int argc, const char * argv[]) {
	initScreen();
	if (argc > 1) {
		if (!adv.open(std::string(argv[1]))) {
			print("Error opening file\n");
			return 1;
		}
		std::string pathval = adv.doPath(adv.getFirstId());
		while (true) {
			if (pathval == "") {
				exitScreen();
				return 0;
			}
			pathval = adv.doPath(pathval);
		}
		exitScreen();
		return 0;
	}
	std::string inp;
	#ifndef __3DS__
	DIR *dir;
	struct dirent *ent;
	std::vector<std::string> files;
	if ((dir = opendir(".")) != NULL) {
  		/* print all the files and directories within directory */
  		while ((ent = readdir(dir)) != NULL) {
    		//printf("%s\n", ent->d_name);
    		if (std::string(ent->d_name).find(".json") != std::string::npos) files.push_back(std::string(ent->d_name));
  		}
  		closedir (dir);
	} else {
  		/* could not open directory */
  		print("Could not open directory\n");
  		exitScreen();
  		return 2;
	}
	print("Choose an option, or type a path (exit with q):\n");
	int i = 1;
	for (std::string f : files) {
		AdventureFile name;
		name.open(f);
		print(std::to_string(i) + ". " + name.getName() + "\n");
		i++;
	}
	inp = input();
	#endif
	#ifdef __3DS__
	print("Type a path:\n");
	SwkbdState keyboard;
    char* buf;
    swkbdInit(&keyboard, SWKBD_TYPE_NORMAL, 2, 32);
    swkbdSetButton(&keyboard, SWKBD_BUTTON_RIGHT, "Run", true);
    swkbdSetButton(&keyboard, SWKBD_BUTTON_LEFT, "Cancel", false);
    if (swkbdInputText(&keyboard, buf, 32) == SWKBD_BUTTON_LEFT) {
    	exitScreen();
    	return 3;
    }
    inp = std::string(buf);
    #endif
    std::string fpath;
    #ifndef __3DS__
    try {
    	int fnum = std::stoi(inp);
    	print(std::to_string(fnum));
    	fpath = files[fnum - 1];
    } catch (const std::invalid_argument& e) {
    	#endif
    	fpath = inp;
    	#ifndef __3DS__
    }
    #endif
    if (fpath == "q") {
    	exitScreen();
    	return 4;
    }
    if (!adv.open(fpath)) {
		print("Error opening file " + fpath + "\n");
		exitScreen();
		return 1;
	}
	std::string pathval = adv.doPath(adv.getFirstId());
	while (true) {
		if (pathval == "") {
			exitScreen();
			return 0;
		}
		pathval = adv.doPath(pathval);
	}
	exitScreen();
	return 0;
}
