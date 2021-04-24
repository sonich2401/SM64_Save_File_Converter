# SM64_Save_File_Converter
A file save converter that takes a .eep file save from an emulator and converts it to a SM64-Pc Port readable save file

# Compiling
#### Linux
    To compile, use the provieded make file. 
#### Windows
    As of the current Commit, there is no full windows support. 
    There is C functions that have safty checks 
    in linux but not in Windows. I wrote some bad string copy code and
    now it will crash because of run-time exception settings on msvc.
    I do plan to fix this in the future
#### MacOS
    As of now, I do not have the means nessisary to compile code
    for a Mac. I am just lazy and dont want to install clang or
    xcode. If you have a compiler and are willing to compile my program
    then be my guest.

# Usage
#### Command Line
    For linux, simply run the program with ./SM64FM <save file> <out_file>
    For Windows open the run.bat file and it will ask you questions to answer to run the program
        P.S.
            You can use the same linux command above in windows command prompt just get rid of the ./
    For MacOS follow the linux instructions above
#### Backdoor
    Using return codes, you are able to use this program as a driver of sorts. 
    Simply include the header file named backdoor.h into your program and it will
    define all of the nessisary macros. To trigger the backdoor make the first argument
    -yop and it will start the backdoor mode. See below for more details
# Backdoor
#### Requriements
    To start the backdoor you need to have argument one be -yop
    after that, your required to supply 6 arguments.
    
    type: The command that you want to send the program. Example: 0 = get star data, 1 = set star data, 3 = get coin data
    
    Arg1: the first arguemnt for the disired command. All commands require this
    
    Arg2: the second argument for the disired command. Only certain commands require this but you must provie this arguemnt with dummy data for the program to run
    
    Arg3: the third arguemnt for the disired command. Only certain commands requre this but you must provie this arguemnt with dummy data for the program to run
    
    In File: This is required and specifies what file to load into the program
    
    Out file: This is not required but you must provie this arguemnt with dummy data for the program to run
#### Commands
    In construction
    
