# 3081 Lab03 - Classes and Debugging



## Goal

The primary goal of this lab is to introduce C++ debugging and to learn how to build C++ classes. You'll debug a provided image-editing program using GDB, then refactor the code into three classes, each split into a header and implementation file.

## What You Will Learn

1. How to add the debugging flag to your Makefile compilation targets
2. How to enter the gdb environment
3. How to use gdb commands to debug your programs
4. How to use a header only library.
5. How to load, modify, and save an image.
6. How to copy bytes of memory.
7. How to design a cohesive image class.
8. Simple image editing techniques.

### What's in lab03

- main.cpp:
  - This contains the main function for loading in an image, modifying it, and saving the result.  You will need to edit this.

- Makefile:
  - This makefile is provided to allow you an easy start to configure and build the executable (image_app).  You will need to edit this.

- README.md:
  - You're reading this now.

- data
  - The data folder contains images you will read into your program.

- output
  - Output files your program will generate.

### What You Will Add

- stb_image.h:
  - A single header file for reading images from the file system.

- stb_image_write.h:
  - A single header file for writing images to the file system.

- color.h:
  - Header for the Color class.

- color.cpp:
  - Implementation for the Color class.

- image.h:
  - Header for the Image class.

- image.cpp:
  - Implementation for the Image class.

- image_editor.h:
  - Header for the ImageEditor class.

- image_editor.cpp:
  - Implementation for the ImageEditor class.
---
### Prerequisites

We are going to use header only libraries for this lab.  Header only libraries are nice because you can place them directly in your code without having to link them.  In this case we will use stb_image and stb_image_write.  These are found at <https://github.com/nothings/> along with several other libraries.  Download the following header files and put them in the lab folder. 
- stb_image.h <https://github.com/nothings/stb/blob/master/stb_image.h> 
- stb_image_write.h <https://github.com/nothings/stb/blob/master/stb_image_write.h>

In case you are interested, here are many other useful header file libraries for C++: <https://github.com/nothings/single_file_libs>

---
### Configuring Debugging

Depending on the system, environment being used, or customized compiler options it is common to configure your makefile based on the specific machine.  For example, we may want to specify the specifically compiler that should be used.  We often use variables to accomplish this as we have seen in lab02.  Notice the top of the Makefile provided.  In order to compile the code so that it can be run inside the debugger, we set a flag in the Makefile. For each of the compilation statements in the makefile, we nadd the `-g` flag.  We can do this by adding -g to CXXFLAGS to tell the compiler to generate debug code. For example:

```
CXX=g++
CXXFLAGS = -std=c++17 -g
```

__What does all that mean?__
- `CXX` : The name of the compiler you would like to use
- `CXXFLAGS` : Specific compiler flags that tell how to build the program. `-g` tells the compiler that we want to generate debug information.

_Note_: When we enable debugging, the resulting application may not be optimized for performance.  Therefore, when releasing an executable into production, it should be built without the debugging flag.

We are now ready to start this lab.

## Part A - Debugging with GDB

The app we are using has a few bugs worth fixing.  This part of the lab will focus on using GDB to interrogate and fix the bugs.

1. First, build the example program with _make_.

    ````
    $ make
    ````
2. Then, run the program:
    ````
    $ ./image_app
    ````
    The program will say that you need to run with specific command line parameters, essentially a starting image (e.g. `data/dog.png`) and an operation (e.g. 'red').  Let's try the following:
    ````
    $ ./image_app dog.png red
    ````

    _What happened?_ You should have got a `segmentation fault`, which usually means we are trying to access memory that doesn't exist.

4. Start a debugging session on an executable file by typing _gdb --args <executable and arguments>_
    ````
    $ gdb --args ./image_app dog.png red
    ````

5. Once in the debugger session (the prompt will change to (**gdb**)). Then, execute the program with _run_.

6. The program _image_app_ will run and crash with the following output (your output may look slightly different):
    ````
    (gdb) run
    Starting program: /home/dan/class/csci3081-f26/lab03/image_app dog.png red
    [Thread debugging using libthread_db enabled]
    Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".

    Program received signal SIGSEGV, Segmentation fault.
    0x0000555555577805 in main (argc=3, argv=0x7fffffffdcd8) at main.cpp:106
    106       unsigned char testByte = loadedImage[0];
    ````

7. Attempt to discover where (and why) in the provided code, the fault is occurring.  Notice that the debugger output gives the exact line of code where the segfault occurs.  This is usually helpful in discovering the main problem.  In this case, it is failing on a test to see if the first byte of the image exists.

8. Fortunately, _gdb_ allows us to print out the values in the context of the line of code to interrogate the error with the _print_ command.  Try the following:

    ````
    (gdb) print loadedImage[0]
    Cannot access memory at address 0x0
    (gdb) print loadedImage
    $1 = (unsigned char *) 0x0
    (gdb) print width
    $2 = 0
    (gdb) print height
    $3 = 0
    (gdb) print components
    $4 = 4
    ````

    Based on these details, we can assume that the image was not correctly loaded in as it is a 0x0 image and the data is pointing to 0x0 (nullptr).

9. We can observe that `dog.png` is actually stored in `data/dog.png` from where the program is run.  Let's try loading from that location:

    ````
    $ ./image_app data/dog.png red
    $ ./image_app data/dog.png red_gradient
    ````

    Indeed, we get see an `output/red.png` and `output/red_gradient.png` image that shows the two different red component edits of the `data/dog.png` image.

10. Let's now try the other image `data/statue.png`:

    ````
    $ ./image_app data/statue.png red
    ````

    Again, we get: `segmentation fault (core dumped)`  Let's debug this in _gdb_ then _run_:

    ````
    $ gdb --args ./image_app data/statue.png red
    ...
    (gdb) run
    Starting program: /home/dan/class/csci3081-f26/lab03/image_app data/statue.png red
    [Thread debugging using libthread_db enabled]
    Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".

    Program received signal SIGSEGV, Segmentation fault.
    0x000055555557744a in get_pixel_color (pixel=0x7ffffffff980 <error: Cannot access memory at address 0x7ffffffff980>) at main.cpp:60
    60              1.0*pixel[3]/255
    ````

11. In this case, the line number is provided, but it's not obvious why this line is failing just by looking at it. This is where bt (backtrace) comes in  it shows the full chain of function calls that led here, so you can trace backward to find where things went wrong
    ````
    (gdb) bt
    #0  0x000055555557744a in get_pixel_color (pixel=0x7ffffffff980 <error: Cannot access memory at address 0x7ffffffff980>) at main.cpp:60
    #1  0x000055555557759f in edit (image=0x7fffffed1b80 "\001", width=640, height=640, components=4, operation="red") at main.cpp:72
    #2  0x00005555555778f7 in main (argc=3, argv=0x7fffffffdcd8) at main.cpp:118
    ````

    The backtrace shows that execution stopped in the function _get_pixel_color(...)_, which is called from the _edit(...)_ function. This function was called from _main()_.  The line numbers are provided for _main.cpp_ (your output may look slightly different).

    The above backtrace indicates that the error happened on line 60m 72, and 118 of _main.cpp_.  Look at these locations in _main.cpp_ to see if you can figure anything out.


12. Fortunately, _gdb_ allows users to navigate the backtrace by typing _up_ and _down_ — _up_ moves you out to the function that called the current one, _down_ moves back toward where the crash happened. Frame `#0` is where the crash occurred; let's move up from there to see who called this code:

    ````
    (gdb) up
    #1  0x000055555557759f in edit (image=0x7fffffed1b80 "\001", width=640, height=640, components=4, operation="red") at main.cpp:72
    72            Color color = get_pixel_color(pixel);
    ````

    We can now print out variables in the context of the _edit(...)_ function:

    ````
    (gdb) print pixel
    $1 = (unsigned char *) 0x7ffffffff980 <error: Cannot access memory at address 0x7ffffffff980>
    (gdb) print x
    $2 = 0
    (gdb) print y
    $3 = 483
    (gdb) print width
    $4 = 640
    (gdb) print height
    $5 = 640
    ````

    We can see what iteration of the double for loop is causing this error.  Any idea what might be going on here?  
    
13. It is not completely obvious, so lets go up the stack trace one more level (*Note:* you can also go down the stack traces with the _down_ command):

    ````
    (gdb) up
    #2  0x00005555555778f7 in main (argc=3, argv=0x7fffffffdcd8) at main.cpp:118
    118       edit(image, width, width, components, operation);
    ````

    Print out variables here:

    ````
    (gdb) print image[0]
    $11 = 1 '\001'
    (gdb) print operation
    $8 = "red"
    ...
    (gdb) print width
    $9 = 640
    ...
    ````

    This is a bug in the code.  When you find, it fix this code.look closely at the arguments passed to the edit() and compare to what the function expects

14. One more to go!  Use _gdb_, _bt_, _up_ and _down_ to find the cause of the following error:

    ````
    ./image_app dog.png
    terminate called after throwing an instance of 'std::logic_error'
    what():  basic_string: construction from null is not valid
    Aborted (core dumped)    
    ````
Use the same approach as above: run in gdb, let it crash, then use _bt_ to see the call stack, and _up_/_down_ with _print_ to inspect   variables at each frame.


    
    
<!-- Consider the following common errors, whilst many would not be applicable in this scenario, they may be the cause in future assignments:
 - **Virtual Methods** - Check to see whether methods are polymorphic.  Should some of the methods be declared virtual.\
 - **Arrays (Required - implement this change)** - Using double* arrays as arguments and return types is often not safe.  Bad things usually do happen!  For example is hard to tell how big the array is and we might accidently overwrite a pointer.  Change these into a std::vector<double> or user defined class (e.g. Vector3) instead of double*.  An added bonus of using std::vector<double> is you can get the size of the array.
 - **Virtual Destructors** - If a base class does not have a virtual destructor, subclass destructors will not be called.
 - **Referencing Parameters** - It is possible to send in a pointer or reference into a method or constructor and set the memory address, however, that parameter may go out of scope or get deleted elsewhere in the program.
 - **Unique Pointers** - If you are using dynamic memory, it's often a good idea to use a unique_ptr<type> instead of _new_ and _delete_ if possible.  This way, the pointer will be deleted by the unique_ptr and there will not be a memory leak.
 - **new / delete** - Remember anytime we add an object to the heap with _new_ we must also _delete_ it.  Also, be sure to use the correct forms of new and delete.  For example if you create an array with _new_ be sure to use _delete[]_ when you delete it.
 - **Casting** - Be sure to use static_cast<>, dynamic_cast<>, and reinterpret_cast<> correctly.

 **Note: You may fix these errors however you want.  Perhaps consider adding more polymorphic methods or changing method signitures (return types / parameters).** -->


## Part B - Creating Classes

### Modifying an Image

Open up `main.cpp` and navigate to the `main(...)` function.  It uses stb_image and stb_image_write to load in an image and save it.  Run the program:

```
% ./image_app data/statue.png red_gradient
```

**_What just happened?_** You should see an image, `data/red_gradient.png`, which is a color modification of `data/statue.png`.  Here we are changing the red value of the image from left to right.  The code is below is a simplified version of the _edit(...)_ function, which employs multiple operations:

```c++
  // Loop through the image pixels and modify values
  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      // Get the pixel as a byte array
      unsigned char* pixel = &image[(y*width + x)*4];

      // Edit these [red, green, blue, alpha / transparency] values below (values between 0 and 255):
      pixel[0] = 255*x/width;
      //pixel[1] = 0;      
      //pixel[2] = 0;
      //pixel[3] = 255;
    }
  }
```

Here we use a pointer `pixel` which points to a specific four byte array for the (x,y) location in the 2D image (stored as a 1D array indexed by `(y*width+x)*4`).  The number 4 represents the number of components (RGBA).

Notice that in _main.cpp_ we use the Color class, which is also defined in _main.cpp_.  The following milestones will help us understand how to create classes following a header (*.h) and implementation (*.cpp) standard.  Header files contain the interface or prototypes of a class and the _cpp_ files contain the actual implementation that is compiled.  Below are the milestones:

* [Milestone 1](#milestone-1---move-the-color-class) - Move the Color class (into separate header/implementation files)
* [Milestone 2](#milestone-2---create-the-image-class) - Create the Image class
* [Milestone 3](#milestone-3---create-the-imageeditor-class) - Create the ImageEditor class.

--- 

### Milestone 1 - Move the Color class

We will start by creating the following files:
 * _color.h_ - Contains the interface of the color class.
 * _color.cpp_ - Contains the implementation of the color class.

The interface contains the definition of the class, but not the details of the implementation.  You can contain implementation in the header.  Often, getter and setter implementations are contained in the header file.  Follow the steps below to move the Color class:

1. Create header guards to ensure that the Color class is not defined multiple times.  Edit _color.h_ with the following:
````
#ifndef COLOR_H_
#define COLOR_H_

// TODO: Copy Color class here

#endif
````

Header guards work by checking whether a unique identifier (e.g. `COLOR_H_`) has already been defined. The first time a file includes _color.h_, `COLOR_H_` is not yet defined, so the preprocessor defines it and includes everything between `#ifndef` and `#endif`. If another file also includes _color.h_, `COLOR_H_` is already defined, so the preprocessor skips the contents entirely — preventing the class from being declared twice.

2. Include _color.h_ in _main.cpp_:

````
#include "color.h"
````

(You'll add this same include to _image.cpp_ once you create it in Milestone 2.)

3. Copy the Color class into _color.h_ so that it replaces the `TODO` above.  Remove the color class from _main.cpp_.

4. Build and run the program.  It should execute as in Part A.

5. Now we need to move the implementation from the header to the implementation file (_color.cpp_).  Let's start by moving the constructor:

   In _color.h_, remove the implementation and use the constructor's prototype:
    ````
    class Color {
        ...
        Color(float red, float green, float blue, float alpha);
        ...
    };
    ````

    In _color.cpp_, add the implementation, scoped by the `Color` class with `Color::`

    ````
    Color::Color(float red, float green,float blue, float alpha) {
        r = red;
        g = green;
        b = blue;
        a = alpha;
    }
    ````

  Seperating the interface (_color.h_) from the implementation (_color.cpp_) means that any code that includes _color.h_ only needs to know **WHAT** `Color` does (they see that Color has a constructor which takes four floats: `red`, `green`, `blue`, and `alpha`), and not **HOW** it does it (the constructor sets the private members `r`, `g`, `b`, and `a` to `red`, `green`, `blue`, and `alpha` respectively). This is good practice to maintain for when you create more complex classes.

6. Build and run the program.  It should execute as in Part A.

7. For each other method, keep the prototype in _color.h_ and move the implementation to the _color.cpp_

8. Build and run the program.  It should execute as in Part A.

___
For **Milestone 1** have a TA verify the program works and the color class has been moved to the header and implementation files correctly.
___


### Milestone 2 - Create the Image class

Create a new `Image` class including the interface (image.h) and the implementation (image.cpp).  This image class should be able to do the following:
 * **Constructors**
   * `Image(width, height)` - Creates a "blank" image of a given width and height.
   * `Image(filename)` - Load an image from the hard drive if a string (or character array) is passed into the constructor.  **Hint:** Use stb_image (see _main.cpp_ in Part A).
 * **Methods**
   * `SaveAs(filename)`- A method that takes in a string (or character array) and saves the image.  **Hint:** Use stb_image_write (see _image.cpp_ once you've created it).
   * `GetHeight(), GetWidth(), GetComponentNum()` - for getting height, width, and number of components.  For now, we will hard code the number of components to 4 to handle RGBA images.
   * `GetPixel(x,y)` - method that returns a pixel value (it is up to you how you want to represent a pixel.  Perhaps it could return a color object or an array).
   * `SetPixel(x,y,pixel)`- method that sets a pixel value at a place on the image.  Again, it is up to you how you represent these objects.  There is freedom here.

Include _color.h_ in _image.cpp_ now that the file exists (this is the include mentioned back in Milestone 1, step 2).

We highly recommend that you refer to main.cpp to help you create and save images.  It is also recommended that you manage your own image buffer rather than using the data from stb_image directly.  This is so that you can create your own images using the `Image(width, height)` constructor that does not rely on stb_image.

*Note:* If done correctly, it is nice to move all the `#include stb_image*.h` into `image.cpp` so that other files are not dependent on these libraries. Make sure to move any `#define`s directly before the `#include`s alongside them when you move them into `image.cpp`.

#### Guidelines for building your image class

The following are guidelines for implementing your image class.  We will be reviewing your classes to make sure these are followed:

 * **Classes / Constructors / Methods** - You have freedom to design these image classes and any other class as you like.  We are interested in how you would solve the problem.
 * **Memory Management** - For now we can assume that you are storing a byte array of a fixed size (e.g. `unsigned char image[1228800]`).  When we discuss dynamic memory, we create images that can adapt to other sizes.
 * **Efficient** - Write as efficient and safe code.  For example, be sure to use a const reference wherever possible to save space on the stack and avoid copying too much information.
 * **Useful** - After creating your class, you add other methods to accomplish different task if you would like.

___
For **Milestone 2** have a TA verify the program works and the Image class is coded in the header and implementation files correctly.
___


### Milestone 3 - Create the ImageEditor class

Create a new `ImageEditor` class including the interface (image_editor.h) and the implementation (image_editor.cpp).  This image editor should implement the other functionality in main, so that main(...) can be simple and would only need to contain the following:

  ````
  // Use image editor to edit the image
  Image image(input);
  ImageEditor editor;
  editor.edit(image, operation);
  image.SaveAs(output);
  ````

 * **Methods**
   * `Edit(Image&, operation)`- Move the functionality from the `edit(...)` function into the image editor.
   * You may create other functions as well if they are helpful.

___
For **Milestone 3** have a TA verify the program works and the ImageEditor class is coded in the header and implementation files correctly.
___

## Reference
<details>
<summary>Command references (click to expand)</summary>

### unix level commands -- entered at the $ prompt:

| Command | Description |
|---|---|
| man gdb | to get help on gdb at the unix command level |
| g++ -g -o program filename.cpp | to compile & link with the debug (-g) option |
| gdb _ProgramName_ | to execute the debugger on executable _ProgramName_ |
| gdb --args _ProgramName \[input arguments\]_ | to execute the debugger on executable _ProgramName_, but with the arguments to the program set to _\[input arguments\]_.


### Basic gdb commands -- entered after the (gdb) prompt:
| Command | Description |
|---|---|
| help | to display a list of gdb commands |
| help _command_ | to get help on a specified gdb command |
| run | to run/execute the program starting from the beginning |
| backtrace | show the current stack (which function is being executed) |
| up | move up in the backtrace stack |
| down | move down in the backtrace stack |
| continue | to resume running/executing the program |
| next | to execute the current statement and stop at the next statement |
| step | same as next, but step into a function |
| list xx | list source lines starting at line xx |
| list | to list the next source lines |
| list xx,yy | to list sources lines from line xx to line yy |
| list filename:xx | to list source lines in the specified file starting at line xx |
| kill | to stop the execution of the program without leaving gdb |
| quit | to quit gdb and revert to the unix command level |
| break _functionname_ | to set a breakpoint at the start of a function (set this before typing run) |
| break classname::functionname | to set a breakpoint at the start of a member function |
| break filename:xx | to set a breakpoint at line xx in the specified file |
| break xx | to set a breakpoint at line xx in the current file |
| break 1 | to set a breakpoint at the first line in the current file (declaration or executable statement) |
| info break | to list all breakpoints (including those disabled); breakpoints are numbered #1, #2, #3, etc. |
| disable xx | to disable breakpoint #xx |
| enable xx | to enable breakpoint #xx |
| print v1 | to print the value of a specified variable |
| info source | to show the name of the current source file |
| info locals | to show local variables in the current frame |
| info sources | to list the name of all source files in use |
| set variable = value | to assign a new value to a specified variable |
| set args _\[input arguments\]_ | to set the program arguments to specified _\[input arguments\]_. *note*: If you have already started the program, this will NOT change the arguments. You will need to _kill_ the program then _run_ it again. |
| (return) | to re-execute the previous gdb command; this is particularly useful if the previous gdb command was next or step |

You can also execute many of these gdb commands by entering only the first letter of the command.

* The original source for this list is [here](https://www.bgsu.edu/arts-and-sciences/computer-science/cs-documentation/using-the-gdb-debugger.html).

### GDB Resources
There are many places to find additional documentation on GDB:

Command reference:   (http://www.yolinux.com/TUTORIALS/GDB-Commands.html)

Another tutorial: (http://www.cs.cmu.edu/~gilpin/tutorial/)

Search for "gdb tutorial" on the web: (http://lmgtfy.com/?q=gdb+tutorial)

If your output does not look like the above, you will need to continue debugging your program to get the correct output.  Most likely, there are other bugs in the program besides segfaults. 

</details>
