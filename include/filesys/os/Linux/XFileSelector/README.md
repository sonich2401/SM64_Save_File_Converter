# XFileSelector
A minimal dependency file selector for Xlib compatible OS'es

### Why did I make this?
I tried to find a file selector on Linux for my [Super Mario 64 Save File Converter](https://github.com/sonich2401/SM64_Save_File_Converter) but the ones that I found are not pre-installed on certian Linux distros. I wanted to have a file selector that works on any system with the least dependancies. Not only does it work on more devices, but it also takes up little memory/RAM and barely uses any CPU. I have a old laptop so those resources mean everything to me.

### Compiling
To build this program, you must use make. CD into the folder and type in
`make`
If you are including the source code in your project, you will need to link Xlib.
To do this do
```
g++ MyProject.cpp -lX11
```
Of course you would have to do this for all of the source files that are required for XFileSelector to work

#### WARNING: 
This will not compile on windows and if you do get it to compile it uses UNIX only headers so you would have to implement those functions yourselfs

### How to Use
You can use this in 2 ways. I wrote this in C++ because it was easier to take a OOP design for a GUI so this is not compatible with C. HOWEVER, you can include the executable in the folder of your C program and pipe the output of this program into yours. So, you can use this with C. You can get a executable from the Release tab.

### If you are going to use this from the command line, you can use it like so (C compatible)
```
./EXECUABLE_NAME "<TITLE OF WINDOW>"
```
This will make the size of the window 500 x 500. If you would like a different size, you can pass in 2 arguments after the title that you wish to display. Like so ...
```
./EXECUTABLE_NAME "<TITLE OF WINDOW>" <WIDTH> <HEIGHT>
```

#### WARNING:
If someone clicks the "Cancel" button, it will return the string "...END" which is an Invalid File name for UNIX file systems so it is safe to assume that this will never be a file on your hard drive. Look for this string if the user cancels the window

##### WARNING:
You MUST have the title of the window in quotes so that argv intruperites it as one argument

### The second way is to include it in your C++ program (Not C compatible)
You can include the source files in your project (other than main.cpp) to create the window yourself.
You can see how to create a window in main.cpp
This is how I would recomend setting up your folders
```
> MyProject
>  > XFileSelector
>  >  > utils
>  >  >  - FileUtils.cpp
>  >  >  - FileUtils.h
>  >  >  - MainWin.cpp
>  >  >  - Window.cpp
>  >  >  - Window.h
>  >  - FileSelect.cpp
>  >  - FileSelect.h
>  - MyProject.cpp (your file)
```
This way you can make windows like so in your project.
The way that you can get a return value from the window is by passing in an address to a std::string that is in main()
Once the window is closed, it will fill the std::string that you passed in with the selected file/folder that the user selected.
Lets take a look at what your "MyProject.cpp" could look like ...
```cpp
#include <string>
#include <iostream>

#include "XFileSelector/FileSelect.h"

int main() {
  int width = 500;
  int height = 500;
  FileSelect win("Select a File", {width, height}, true);
  
  std::string window_return;
  win.Start(&window_return);
  
  std::cout << window_return;
  return 0;
}
```
This will fill window_return with the selected file/folder and the std::cout will print the folder/file that was chosen.

## What can you expect the program to look like
I am using basic Xlib functions which is very restricting. There is 0 calls to OpenGL in my program (unless Xlib does that in the backend idk). This means that the file selector doesn't look very "Modern" but I have tried to give it a dark theme that looks acceptable.

To open a folder, double click the folder. Folders are marked in Light Blue. Files are white. You can see what file/folder is selected by seeing that the background of the button is Very Dark Grey.
Here is a screenshot of what it looks like
![Screenshot_2021-10-13_16-43-58](https://user-images.githubusercontent.com/34013705/137227652-b91e722c-8b1d-403d-9f2d-fc34143b1870.png)
It has all modern functionality including scrolling and quick links. Eventually, I hope to add buttons that allow you to create files and folders within this program just like modern file mangaers.
