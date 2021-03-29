# BashFlash
A terminal based flash card REPL.
## Building BashFlash
BashFlash uses CMake, so be sure to have this installed.
To build, run the following commands:
```bash
# If you cmake is not installed
sudo apt-get update
sudo apt-get install cmake
# Building bashflash
mkdir build && cd build
cmake ../
make
```
An executable should be made called "bashflash".
## Using BashFlash
bashflash just accepts two arguments: 
1. The path of the input csv file (required) in which it will parse to create flashcards.
2. An optional output csv file containing all of the flashcards you answered incorrectly. 
```bash
bashflash <input csv file> <optional output csv file>
```
The input csv file must be two columns (prompt and answer). 
I have included an example csv file (country-code.csv) which includes country codes and names for you to try!

