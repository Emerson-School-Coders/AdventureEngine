# AdventureEngine
A cross-platform JSON game interpreter written in C++.

# Current platforms & engine files
 * 3DS: use `Engine-3DS.cpp`
 * Mac: use `Engine-nix.cpp`
 * Linux: use `Engine-nix.cpp`
 * Windows: use `Engine-Windows.cpp`

If you would like to add another platform, create a pull request adding a new `Engine.cpp` file for the platform.

# How to use
Include `Interpreter.hpp` in your main source file, and compile `Interpreter.cpp`, `jsoncpp.cpp` (unless you are linking a prebuilt jsoncpp), the `Engine.cpp` file for the platform you are building for (refer to above for files), and your main source file. I have included a sample launcher in this repository to test.

# JSON format
* `name (string)`\*: The name of the adventure
* `main (string)`\*: The main path (the path to start on)
* `paths (object)`\*: The paths that can be run
    * `<path name> (object)`\*
      * `text (string)`\*: The text to be displayed on screen
      * `image (string)`: An image to be displayed above the text
      * `special (string)`: Can be `goodend` or `badend` for endings, or `anykey` for a "press any key" prompt (first action will be executed)
      * `names (array)`\* : A description of what the button does ("do x" would be displayed as "Press 1 to do x"), can be omitted when `special` is used
      * `actions (array)`\* : The paths to go on when a button is pressed, can be omitted when `special` is an ending
      * `variables (object)`: Variables to set when running the path
      * `prerequisites (object)`: Variables that must be a value to run the path
      * `failedRequirements (string)` (required if `prerequisites` is specified): What path to use if the prerequisites fail

\*required

# Adventure API
 * `Engine.hpp`: cross platform interface
    * `void print(std::string text)`: Prints the text to screen (without newline)
    * `std::string input(std::string text = "> ")`: Get text input
    * `std::string readFile(std::string file)`: Read an entire file
    * `bool writeFile(std::string file, std::string text)`: Write text to a file
    * `int getNumber(bool anyNum = false)`: Read a number (1-4 if !anyNum, any number if anyNum)
    * `void clearS()`: Clear the screen
    * `void initScreen()`: Initialize the screen (call when program starts)
    * `void exitScreen()`: End the screen (call when program ends)
 * `Interpreter.hpp`: Adventure file interpreter
    * `class AdventureFile`: Adventure file interpreter class
       * `std::map<std::string, std::string> variables`: Currently set variables
       * `bool open(std::string file)`: Open a file and interpret it
       * `std::string getFirstId()`: Get the first path to be run
       * `std::string getName()`: Get the name of the file
       * `std::string doPath(std::string id)`: Run a path, returns the id of the next path to be run or `""`
