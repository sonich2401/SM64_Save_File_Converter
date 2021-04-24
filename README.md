# SM64_Save_File_Converter
A file save converter that takes a .eep file save from an emulator and converts it to a SM64-Pc Port readable save file

#Compiling
  - Linux
    To compile, use the provieded make file. 
    There should be some ld warnings and those are expected. 
    It is a warning that (as of the current version of gcc) doesn't effect the program at all.
  - Windows
    As of the current Commit, there is no full windows support. 
    There is C functions that have safty checks 
    in linux but not in Windows. I wrote some bad string copy code and
    now it will crash because of run-time exception settings on msvc.
    I do plan to fix this in the future
  - MacOS
    As of now, I do not have the means nessisary to compile code
    for a Mac. I am just lazy and dont want to install clang or
    xcode. If you have a compiler and are willing to compile my program
    then be my guest.
