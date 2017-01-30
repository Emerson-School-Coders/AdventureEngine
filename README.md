# AdventureEngine
A cross-platform engine/interpreter written in C++. Include `Interpreter.hpp` in your main source file, and compile both the interpreter and the engine for the platform you are building for.

# JSON Format
* `name`: The name of the adventure
* `main`: The main path (the path to start on)
* `paths`: The paths (dictionary)  
    *`text`: The text to be displayed on screen
    *`image` (optional): An image to be displayed above the text
    *`special`: Can be `goodend` or `badend` for endings
    *`names`: The names of the actions to do (array)
    *`actions`: The paths to go on when a button is pressed (array)
