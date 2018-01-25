# AdventureEngine
A cross-platform engine/interpreter written in C++. Include `Interpreter.hpp` in your main source file, and compile both the interpreter and the engine for the platform you are building for, as well as jsoncpp.

# JSON Format
* `name (string)`: The name of the adventure
* `main (string)`: The main path (the path to start on)
* `paths (object)`: The paths that can be run
    * `<path name> (object)`
      * `text (string)`\*: The text to be displayed on screen
      * `image (string)`: An image to be displayed above the text
      * `special (string)`: Can be `goodend` or `badend` for endings, or `anykey` for a "press any key" prompt (first action will be executed).
      * `names (array)`\* (if `special` is not specified): A description of what the button does ("do x" would be displayed as "Press 1 to do x")
      * `actions (array)`\* (if `special` is not an ending): The paths to go on when a button is pressed (array)
      * `variables (object)`: Variables to set when running the path
      * `prerequisites (object)`: Variables that must be a value to run the path
      * `failedRequirements (string)`\* (if `prerequisites` is specified): What path to use if the prerequisites fail

\*required
