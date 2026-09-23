# 3081 Lab03 - Classes and Debugging

## What You Will Learn

1. How to add the debugging flag to your Makefile compilation targets
2. How to enter the gdb environment
3. How to use gdb commands to debug your programs
4. How to use a header only library.
5. How to load, modify, and save an image.
6. How to copy bytes of memory.
7. How to design a cohesive image class.
8. How to load, modify, copy, and save images.
9. Simple image editing techniques.

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


### Goal

<hr>
  **The primary goal of this lab is to introduce C++ debugging and to learn how to build C++ classes.**
<hr>

### Prerequisites

We are going to use header only libraries for this lab.  Header only libraries are nice because you can place them directly in your code without having to link them.  In this case we will use stb_image and stb_image_write.  These are found at <https://github.com/nothings/> along with several other libraries.  You will need to download the following header files and put them in the lab folder:

- stb_image.h <https://github.com/nothings/stb/blob/master/stb_image.h>
- stb_image_write.h <https://github.com/nothings/stb/blob/master/stb_image_write.h>

In case you are interested, here are many other useful header file libraries for C++: <https://github.com/nothings/single_file_libs>

### Configuring Debugging

Depending on the system, environment being used, or customized compiler options it is common to configure your makefile based on the specific machine.  For example, we may want to specify the specifically compiler that should be used.  We often use variables to accomplish this as we have seen in lab02.  Notice the top of the Makefile provided.  In order to compile the code so that it can be run inside the debugger, we set a flag in the Makefile. For each of the compilation statements in the makefile, we nadd the `-g` flag.  We can do this by adding -g to CXXFLAGS to tell the compiler to generate debug code. For example:

```
CXX=g++
CXXFLAGS = -std=c++11 -g
```

__What does all that mean?__
- `CXX` : The name of the compiler you would like to use
- `CXXFLAGS` : Specific compiler flags that tell how to build the program. `-g` tells the compiler that we want to generate debug information.

_Note_: When we enable debugging, the resulting application may not be optimized for performance.  Therefore, when releasing an executable into production, it should be built without the debugging flag.

We are now ready to start this lab.


### Modifying an Image

Create a folder named `data`.  Add an image of your choice and name it: `data/input.png`.

Open up `image.cc` and notice how it uses stb_image and stb_image_write to load in an image and save it.  You will use this in Checkpoint 2. Notice that the program saves a new image as `data/output.png`.    Run the program:

```
% ./image_app
```

**_What just happened?_** You should see an image, `data/output.png`, which is a color modification of `data/input.png`.  Here we are changing the red value of the image from left to right:

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

Change the program to edit the RGBA pixel values and a create new image (output.png) based on your original image (input.png).  We want to see fun and interesing renditions of your original image.  You should prototype interesting and creative modifications.  You will submit your original and modified image to Discord (see below).

### Add Changes to Repo Locally and On Server

You need to _stage_ all changes to the repository, which prepares those items to be permanently part of the repository. 
When you _commit_ those changes, they are saved to your local repository, which lives in your cselabs account (or your
personal computer if that is what you are working on). When you _push_ those changes, they will be copied to the repo on the server. The difference between
_commit_ and _push_ is what separates git from centralized version control systems.

```bash
% git status
% git add -A
% git status
% git commit -m "Adding lab03 deliverables"
% git push
```

**_What just happened?_** Double-checking the files to be staged using the _git status_ command. All of the tracked changes are staged with `git add -A`.  The second _git status_ command shows the staged changes.  Those staged changes were committed to your local repository and tagged with the message that follows `-m`, then pushed to the server in your remote repository.

### Submitting your Lab

Submit your work by completing the two tasks below:
 - Complete the Lab 03 Gradescope assignment (you may take this multiple times).
 - In the Discord channel `#lab03-memory` post your _original_ (input.png) and _modified_ (output.png) pictures to share with the class (make sure they are appropriate).  Enjoy and be creative!

THIS LAB IS COMPLETE.

Congratulations!



# Iteration 1: Checkpoint 2 - Image Editing
_(Due Thurs, Sept. 30, 2021 @ 11:59)_

This extended lab checkpoint uses the results above as a starting place for image editing in our project.  You may use the code in `image.cc` from the lab to help you get started.  Your goal is to create an Image class that stores and modifies the memory for an image.  You will also create an application that uses your image class to create and modify images.

## What You Will Learn

1. How to manage dynamically allocated memory in a class (e.g the Big Three).
2. How to copy bytes of memory.
3. How to design a cohesive image class.
4. How to load, modify, copy, and save images.
5. Simple image editing techniques.

### Getting Started

Navigate to lab02_memory/checkpoint2 in one of the development environments (VOLE / CSE Labs, SSH, Docker):

```bash
% cd x500-repo/labs/lab03_memory/checkpoint2
```

### What's in labs/lab03_memory/checkpoint2

- Makefile:
  - This makefile is provided to automate the building of your project.  You may edit this if you need.

- main.cc:
  - This file contains the main method with no implementation.  It does contain comments corresponding to the image editing requirements in this write-up.

### What You Will Add

- image.h:
  - A single header file for reading images from the file system.

- image.cc:
  - A single header file for writing images to the file system.

- Other Necessary Files 
  - any other file or classes needed to read in images (e.g. stb_image.h and stb_image_write.h).  You are welcome to add other classes that could be helpful.  For example, you may want to create a Color class that edits pixel values, but this is not required.

### Goal

<hr>
  **The primary goal of this checkpoint is for you to create a dynamic image class that handles the loading, editing access, and saving functionality.**
<hr>

### Getting Started

Navigate to lab02_memory/checkpoint2 in one of the development environments (VOLE / CSE Labs, SSH, Docker).  You can run the program with the following commands using the provided `Makefile` and `main.cc`.

```bash
% cd x500-repo/labs/lab03_memory/checkpoint2
% make
% ./image_processor
```

Create a new `Image` class including the interface (image.h) and the implementation (image.cc).  This image class should be able to do the following:
 * **Constructors**
   * `Image(width, height)` - Creates a "blank" image of a given width and height.
   * `Image(filename)` - Load an image from the hard drive if a string (or character array) is passed into the constructor.  **Hint:** Use stb_image (see image.cc in Lab03 above).
 * **Methods**
   * `SaveAs(filename)`- A method that takes in a string (or character array) and saves the image.  **Hint:** Use stb_image_write (see image.cc in Lab03 above).
   * `GetHeight(), GetWidth(), GetComponentNum()` - for getting height, width, and number of components.  For now, we will hard code the number of components to 4 to handle RGBA images.
   * `GetPixel(x,y)` - method that returns a pixel value (it is up to you how you want to represent a pixel.  Perhaps it could return a color object or an array).
   * `SetPixel(x,y,pixel)`- method that sets a pixel value at a place on the image.  Again, it is up to you how you represent these objects.  There is freedom here.

We highly recommend that you refer to image.cc (from Lab03) to help you create and save images.  It is also recommended that you manage your own image buffer similar to image.cc rather than using the data from stb_image.  This is so that you can create your own images using the `Image(width, height)` constructor that does not rely on stb_image.

### Guidelines for building your image class

The following are guidelines for implementing your image class.  We will be reviewing your classes to make sure these are followed:

 * **Classes / Constructors / Methods** - You have freedom to design these image classes and any other class as you like.  We are interested in how you would solve the problem.
 * **Memory Management** - Be sure to use best practices for dynamic memory management (No memory leaks, the Big Three, etc...).  You may also use smart pointers if you use them correctly (more detail to come).
 * **Efficient** - Write as efficient and safe code.  For example, be sure to use a const reference wherever possible to save space on the stack and avoid copying too much information.  In fact, you may want to go back and modify your Vector3 class to include const references whenever you pass a value that is larger than a pointer.  
 * **Useful** - After creating your class, you will need to accomplish the tasks in `main.cc` detailed in the next section.  These are also commented in the `main.cc` to help with implementation.

### Editing Images

Create a data folder to store your input and output *.png images (copy the images from <https://github.umn.edu/umn-csci-3081-f21/examples/tree/main/data/images>).  Then follow these steps:

1. Inside your main() method, load in “data/statue.png” (found here: <https://github.umn.edu/umn-csci-3081-f21/examples/blob/main/data/images/statue.png>) using the Image class.  Print out the width and height.  Save a new file as “data/statue_copy.png”.  Verify that the new image is a copy of the old one.
2. Next create a new image by specifying the width = 256 and height = 256 in the constructor.  Set each pixel color to Color(1, 0, 0, 1), which is red.  Save the image as “data/red.png”.  Verify that the image created is completely red.
3. Finally, create a gradient image from left to right (width = 256, height = 32) that increases the green intensity.  So at the left the intensity is black and the right it is green.  Save the image as “data/green_gradient.png”.  Verify the image looks similar to the following gradient:

![](https://github.umn.edu/umn-csci-3081-f21/examples/blob/main/data/images/green_gradient.png?raw=true)

**Optional:** Feel free to add more.  Consider resizing an image or try applying a threshold filter.  To apply a threshold filter, iterate through the pixels and set any pixel to black if red is less than 0.5 and white if red is greater than 0.5.

### Submitting your Checkpoint 2 (staring Monday, 9/27/2021)

Submit your work by uploading the following files to Gradescope for the Checkpoint2 assignment (which will be available starting Monday evening, September 27, 2021).  We will inspect your code quality (no memory leaks, efficient memory paradignms, secure, etc...) and design in grading this assignment.

 - Makefile
 - image.h
 - image.cc
 - main.cc
 - Any other file relavent to this checkpoint and your design.

You are welcome to keep changing and submitting this checkpoint up to the deadline.

THIS CHECKPOINT IS COMPLETE.

Congratulations!

## Milestone 2 - Download multiple zoom levels

For this milestone, you will need to be able to download one tile from each specified zoom level.  The tile should include the Mercator location defined (e.g. the Keller Lab).  To accomplish this, run the following:

```
% ./map_zoom World_Imagery 12 8
```

This should download the files ```12.png```, ```13.png```, ... , ```19.png```.  The ```12.png``` image should show Minneapolis and ```19.png``` should show Keller Lab.

___
:white_check_mark: **Answer** look at [main.cpp](main.cpp) in the solution.
___

**Hint:** It is important to remember that the Mercator coordinates are between 0 and 1, so to get the tile, you can multiply by the number of dimensions in the zoom level.  For example, if you have a zoom level of 2, this means there are 2^2=4 in each dimension.  So if your x is 0.77, then your tile is 4*0.73=2.92, so your x-tile would be 2.

___
For **Milestone 2** have a TA verify that you can dynamically zoom in to the Keller Lab from any starting point to any zoom level (up to 19).
___


# 3081 Lab04 Polymorphism and Debugging with GDB
_(Due **Tuesday**, October 5, 2021 @ 11:59)_

## What You Will Learn
1. How to add the debugging flag to your Makefile compilation targets
2. How to enter the gdb environment
3. How to use gdb commands to debug your programs
4. How to detect memory inefficiencies using Valgrind
5. Become familiar with polymorphism and virtual methods.

### Retrieve class materials and merge into your personal repository

  > _This is the same as in previous labs._

  Navigate to your repository.

      $ cd <path_to_your_repository's_root_folder>

  Pull the updated materials into your _support-code_ branch. Ensure you are in the _support-code_ branch by executing the _git status_ command.

      $ git status

  The output should begin with the branch you are currently on. If it says _On branch support-code_,
  you're all set. If you are still in _main_, checkout the _support-code_ branch.

      $ git checkout support-code

  Check for updates from the shared-upstream repository.

      $ git pull upstream support-code

  Add any updates into your own work in the _main_ branch.

      $ git checkout main
      $ git merge support-code

#### Merge conflicts?

If you encounter any errors during the pull or merge steps above, you may need to resolve a merge conflict. Git will tell you which files have merge conflicts.

It is recommended that you use a merge tool to help you handle these conflicts. The editor 'atom' has been recommended by the TAs [for resolving conflicts](https://flight-manual.atom.io/using-atom/sections/github-package/#resolve-conflicts)

### What's in Lab04?

This file:

 - README.md

Other files to be used and modified IF NECESSARY:

 - entity.h/.cc
 - drone.h/.cc
 - robot.h/.cc
 - tree.h/.cc
 - main.cc
 - Makefile

### Debugging with GDB

1. First, build the example program with _make_.

    ````
    $ make
    ````
2. Then, run the program:
    ````
    $ ./entity_app
    ````
    See that the program quits in a Segmentation Fault. In the following steps, we will try to diagnose the problem.

3. You need to compile the code so that it can be run inside the debugger. This is a flag that can be set in the Makefile. For each of the compilation statements in the makefile, we need the `-g` flag.  We can do this by adding -g to CXXFLAGS to tell the compiler to generate debug code. For example:

    ````
    CXXFLAGS = -std=c++11 -g
    ````

    Now, recreate the executable, with the debugging flags used this time.

    ````
	$ make clean
	$ make
	````

4. Start a debugging session on an executable file by typing _gdb <executable>_
    ````
    $ gdb entity_app
    ````

5. Once in the debugger session (the prompt will change to (**gdb**)). Then, execute the program with _run_.
6. The program _entity_app_ will run and crash with the following output (your output may look slightly different):
    ````
    (gdb) run
    Starting program: /home/user/repo/labs/lab04_polymorphism/entity_app 
    warning: Error disabling address space randomization: Operation not permitted

    Program received signal SIGSEGV, Segmentation fault.
    0x000055c43e2c805b in Tree::Tree (this=0x55c43ff72f50, name="Oak", x=50, y=50)
        at tree.h:11
    9	        pos[0] = x;
    ````

7. Attempt to discover where (and why) in the provided code, the fault is occurring.
In this case, the line number causing the error is provided. If the location is not in the provided code, use the _gdb bt_ command (bt stands for "backtrace") to determine where the fault occurs. Type _bt_ now to see the where the execution stopped in each method:
    ````
    (gdb) bt
    #0  0x0000557bef78e0ab in Tree::Tree (this=0x557bf0c4af50, name="Oak", x=50, 
        y=50) at tree.h:11
    #1  0x0000557bef78d918 in main (argc=1, argv=0x7ffe5db81d18) at main.cc:38
    ````

    The backtrace shows that execution stopped in the method _Tree(name, x, y)_ constructor. This constructor was called from _main()_ on line 38 of _main.cc_.

    The above backtrace indicates that the error happened on line 11 of _tree.h_. Edit the file, and look at line 11. Why is this causing an error?

    Let's fix this error by modifying the code in _tree.h_.  We can use gdb to print out the variables using the debugger.  Try the following:

    ````
    (gdb) print x
    $1 = 50
    (gdb) print y
    $2 = 50
    (gdb) print pos
    $3 = (double *) 0x0
    ````

    On line 11 of Tree.h, it appears we are trying to set values into the _pos_ array, which is NULL.  The easiest solution is to create the array on the stack instead of an uninitalized pointer.  Instead of `double* pos` we can define it as `double pos[2]`.  Recompile _entity_app_ with _make_, and run the program again.

8. We see another segfault, so let's start the debugger (steps 4-6).  Now we get the following output when we type _bt_ for viewing the backtrace:

    ````
    (gdb) bt
    #0  __GI_raise (sig=sig@entry=6) at ../sysdeps/unix/sysv/linux/raise.c:51
    #1  0x00007fb8048e3921 in __GI_abort () at abort.c:79
    #2  0x00007fb80492c967 in __libc_message (action=action@entry=do_abort, 
        fmt=fmt@entry=0x7fb804a59b0d "%s\n") at ../sysdeps/posix/libc_fatal.c:181
    #3  0x00007fb8049339da in malloc_printerr (
        str=str@entry=0x7fb804a57d20 "free(): invalid size") at malloc.c:5342
    #4  0x00007fb80493af1c in _int_free (have_lock=0, p=0x7ffc388ffc10, 
        av=0x7fb804c8ec40 <main_arena>) at malloc.c:4171
    #5  __GI___libc_free (mem=0x7ffc388ffc20) at malloc.c:3134
    #6  0x000055d95b797de3 in main (argc=1, argv=0x7ffc388ffd58) at main.cc:69

    ````

    Fortunately, _gdb_ allows users to navigate the backtrace by typing _up_ and _down_.  When output looks like the above, often it is easiest to look for the highest file in your code.  In this case it is _main.cc:69_.  Let's traverse the backtrace to this location with the _up_ command.  We want to go up 6 levels in the backtrace to #6:

    ````
    (gdb) up 6
    #6  0x000055d95b797de3 in main (argc=1, argv=0x7ffc388ffd58) at main.cc:68
    68	      delete entities[i];
    ````

    Now that we are at this level of the backtrace, we can use _print_ to find out more information.  For example, we can print the entities and the specific entity we are trying to delete by printing i.  We can also print other information:

    ````
    (gdb) print entities
    $25 = std::vector of length 6, capacity 8 = {0x7ffd392430e0, 0x562288ec2f50, 
      0x562288ec2fa0, 0x562288ec3020, 0x562288ec2eb0, 0x562288ec30a0}
    (gdb) print i          
    $26 = 0
    (gdb) print entities[0]
    $27 = (Entity *) 0x7ffd392430e0
    (gdb) print entities[0]->GetName()
    $28 = "Entity"
    ````

    Notice how the _up_, _down_, and _print_ commands help us find out more information.  In this case, the problem appears to be with trying to delete a the first entity in the vector.  Fix the problem, recompile _entity_app_ with _make_, and run the program again.  You may fix the problem howevever you like.

    There are several causes of "Segmentation faults" in this program. Use _gdb_ to help to identify and fix each issue until it runs correctly (see step 7). You might find the commands _up_ and _print_ particularly useful.

9. In this program there is a base class called Entity.  MovableEntity and Tree inherit directly from Entity.  Drone and Robot inherit from MoveableEntity.  A robot moves around in a circle of a specified radius and a drone moves in a direction at a specified velocity.  A tree stays in one place.  When your program is running correctly, running the executable should output the following:

    ````
    Time = 0:
    --------------
    Drone-A, 0, 0, 0
    Oak, 50, 50
    Johnny-Five, 1, 0
    Maple, 100, 100
    Drone-X, 0, 0, 0
    Dave, 4, 0

    Time = 0.1:
    --------------
    Drone-A, 0.0707107, 0.0707107, 0.1
    Oak, 50, 50
    Johnny-Five, 0.995004, 0.0998334
    Maple, 100, 100
    Drone-X, 0.1, 0, 0.1
    Dave, 3.98002, 0.399334

    Time = 0.2:
    --------------
    Drone-A, 0.141421, 0.141421, 0.2
    Oak, 50, 50
    Johnny-Five, 0.980067, 0.198669
    Maple, 100, 100
    Drone-X, 0.2, 0, 0.2
    Dave, 3.92027, 0.794677

    Simulation Complete
    ````

    If your output does not look like the above, you will need to continue debugging your program to get the correct output.  Most likely, there are other bugs in the program besides segfaults.  Consider the following common errors to look for:

     - **Virtual Methods** - Check to see whether methods are polymorphic.  Should some of the methods be declared virtual.
     - **Arrays (Required - implement this change)** - Using double* arrays as arguments and return types is often not safe.  Bad things usually do happen!  For example is hard to tell how big the array is and we might accidently overwrite a pointer.  Change these into a std::vector<double> or user defined class (e.g. Vector3) instead of double*.  An added bonus of using std::vector<double> is you can get the size of the array.
     - **Virtual Destructors** - If a base class does not have a virtual destructor, subclass destructors will not be called.
     - **Referencing Parameters** - It is possible to send in a pointer or reference into a method or constructor and set the memory address, however, that parameter may go out of scope or get deleted elsewhere in the program.
     - **Unique Pointers** - If you are using dynamic memory, it's often a good idea to use a unique_ptr<type> instead of _new_ and _delete_ if possible.  This way, the pointer will be deleted by the unique_ptr and there will not be a memory leak.
     - **new / delete** - Remember anytime we add an object to the heap with _new_ we must also _delete_ it.  Also, be sure to use the correct forms of new and delete.  For example if you create an array with _new_ be sure to use _delete[]_ when you delete it.
     - **Casting** - Be sure to use static_cast<>, dynamic_cast<>, and reinterpret_cast<> correctly.
	
     **Note: You may fix these errors however you want.  Perhaps consider adding more polymorphic methods or changing method signitures (return types / parameters).**

10. If you're familiar with Java, you know that the jvm handles recycling the memory dynamically allocated in the heap. However, in C/C++ the memory is not recycled automatically, meaning your program is prone to memory leakage where your programs can run out memory. All the memory that is allocated dynamically must be recycled using  [`free(void*)`](http://www.cplusplus.com/reference/cstdlib/free/) which should be used when using `malloc`,`calloc` which are used in the C programming language memory calls. Since we are programming in C++ these should not be used in this class.

    In C++, the `new` operator is used to dynamically allocate memory. When using the `new` operator you need to use `delete ptrName`. Click [`here`](https://www.geeksforgeeks.org/g-fact-30/) for more information. When dynamically allocating an array using `new [] ` you need to use `delete [] ptrName`. Click [`here`](http://www.cplusplus.com/reference/new/operator%20delete[]/) for more information. **Note: `delete/delete[]` are specific to C++ while `free` works on both C/C++.**  

    With this information, you might be thinking, how can I detect possible memory leaks?  

    This is where using `Valgrind` is helpful in detecting memory leaks. Click [here](https://valgrind.org/docs/manual/quick-start.html) to reference the manual. The Valgrind tool suite provides a number of debugging and profiling tools that help you make your programs faster and more correct. The most popular of these tools is called **Memcheck**. Memcheck helps you by identifying possible memory-related issues in your C/C++ programs.

> ### Note: Step 10 depends on the successful completion of step 9, so please make sure you finish step 9 before completing this step. 

### To run Valgrind on your program follow the steps below:

  * Make sure valgrind is installed in your system (valgrind is by default installed on CSE machines and the docker environment) by typing `valgrind` in your command prompt. If you're using your own linux machine, on command prompt run `sudo apt install valgrind`.
  
  * Make sure you compile your code in debugging mode, just like the steps above in running gdb.
  
  * Then, assuming your program `program` needs two arguments `arg1 arg2`to run on the command prompt (e.g. `./program arg1 arg2`), simply run `valgrind --leak-check=yes ./program arg1 arg2`

    After running valgrind, if the end of your output looks like below, then you've completed the coding part of the lab!

    ````
    % valgrind --leak-check=yes ./entity_app 

    ==1660== Memcheck, a memory error detector
    ==1660== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
    ==1660== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
    ==1660== Command: ./entity_app
    ==1660== 

    Drone-A, 0.0707107, 0.0707107, 0.1
    Oak, 50, 50
    Johnny-Five, 0.995004, 0.0998334
    Maple, 100, 100a
    Drone-X, 0.1, 0, 0.1
    Dave, 3.98002, 0.399334

    Time = 0.2:
    --------------
    Drone-A, 0.141421, 0.141421, 0.2
    Oak, 50, 50
    Johnny-Five, 0.980067, 0.198669
    Maple, 100, 100
    Drone-X, 0.2, 0, 0.2
    Dave, 3.92027, 0.794677

    Time = 0.3:
    --------------
    Drone-A, 0.212132, 0.212132, 0.3
    Oak, 50, 50
    Johnny-Five, 0.955336, 0.29552
    Maple, 100, 100
    Drone-X, 0.3, 0, 0.3
    Dave, 3.82135, 1.18208

    Time = 0.4:
    --------------
    Drone-A, 0.282843, 0.282843, 0.4
    Oak, 50, 50
    Johnny-Five, 0.921061, 0.389418
    Maple, 100, 100
    Drone-X, 0.4, 0, 0.4
    Dave, 3.68424, 1.55767

    Simulation Complete
    ==1661== 
    ==1661== HEAP SUMMARY:
    ==1661==     in use at exit: 0 bytes in 0 blocks
    ==1661==   total heap usage: 16 allocs, 16 frees, 74,280 bytes allocated
    ==1661== 
    ==1661== All heap blocks were freed -- no leaks are possible
    ==1661== 

    ````

    If not, don't worry: all you need to do is delete all the dynamically allocated memory using the **appropriate** deallocation methods. Here's a [link](http://cs.ecs.baylor.edu/~donahoo/tools/valgrind/messages.html) that talks about some common error messages on Valgrind Memcheck.

    When your output looks like the output in step 9 and there are no memory leaks from step 10, you have completed the coding part of the lab!

### Pushing Results

Making sure no additional files are being pushed.

    $ git status

This should list all the files that have changed and/or are untracked. If other files are also listed as being ready to stage for commit, you may need to update your .gitignore to make sure you don't push those files(*.o,executables).

### Add Changes to Repo both Locally and on the Server

[This text is the same as in previous labs.] You need to _stage_ all changes to the repository, which prepares those items to
be permanently part of the repository. When you _commit_ those changes, they are saved to your local repository, which lives in your cselabs account (or your
personal computer if that is what you are working on). When you _push_ those changes, they will be copied to the repo on the server. The difference between
_commit_ and _push_ is what separates git from centralized version control systems.

    $ git status
    $ git add -A
    $ git commit -m "add(lab07): Adding lab04 deliverables"
    $ git push

**_What just happened?_** Double-checking the files to be staged using the _git status_ command. All of the tracked changes are staged with `git add -A`. Those staged changes were committed to your local repository and tagged with the message that follows `-m`, then pushed to the server in your remote repository.

### Submitting your Lab
_(Gradescope submission will be available on Monday, October 4th, 2021)_

Submit your work by uploading the following files to Gradescope for the Lab04 assignment.  Your code will be automatically graded and your score recorded.

 - entity.h/.cc
 - drone.h/.cc
 - robot.h/.cc
 - tree.h/.cc
 - main.cc
 - Makefile

You are welcome to keep changing and submitting this lab up to the deadline.  Gradescope will recompile and test your code.  If for some reason the automated feedback does not work for you, TAs can also manually verify your submission.

THIS LAB IS COMPLETE.

Congratulations!


## References

### unix level commands -- entered at the $ prompt:

| Command | Description |
|---|---|
| man gdb | to get help on gdb at the unix command level |
| g++ -g -o program filename.cpp | to compile & link with the debug (-g) option |
| gdb _ProgramName_ | to execute the debugger on executable _ProgramName_ |


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
| (return) | to re-execute the previous gdb command; this is particularly useful if the previous gdb command was next or step |

You can also execute most gdb commands by entering only the first letter of the command.

* The original source for this list is [here](https://www.bgsu.edu/arts-and-sciences/computer-science/cs-documentation/using-the-gdb-debugger.html).

### GDB Resources
There are many places to find additional documentation on GDB:

Command reference:   (http://www.yolinux.com/TUTORIALS/GDB-Commands.html)

Another tutorial: (http://www.cs.cmu.edu/~gilpin/tutorial/)

Search for "gdb tutorial" on the web: (http://lmgtfy.com/?q=gdb+tutorial)


# Iteration 1: Checkpoint 3 - Image Filters
_(Due Thursday, October 7, 2021 @ 11:59)_

This extended lab checkpoint continues to investigate polymorphism by adding image filtering to our image processing project.  Use the skills you learned in Lab04 to help debug your code and build more stable software.  In this checkpoint, your goal is to create a set of image filters using inheritence and polymorphism.

## What You Will Learn

1. How to read a UML diagram and use it to create a class structure.
2. How to override virtual methods.
3. How to call methods from a base class.
4. Examples of how to use unique pointers, vectors, and maps.
5. How to create simple image filters.

### Getting Started

Navigate to lab04_polymorphism/checkpoint3 in one of the development environments (VOLE / CSE Labs, SSH, Docker):

```bash
% cd x500-repo/labs/lab04_polymorphism/checkpoint3
```

### What's in labs/lab04_polymorphism/checkpoint3

- Makefile:
  - This makefile is provided to automate the building of your project.  You may edit this if you need.

- main.cc:
  - This file contains the main application that handles image processing (loading in an image, filtering it, and saving the results).  You may edit this file to meet your needs.

### What You Will Add

- filter.h

- greyscale_filter.h/.cc

- threshold_filter.h/.cc

- mean_blur_filter.h/.cc

- Other Necessary Files 
  - Any other file or classes needed to read in images (e.g. image.h/.cc, stb_image.h, and stb_image_write.h).  You are welcome to add other classes that could be helpful.

### Goal

<hr>
  **The primary goal of this checkpoint is for you to create a set of filters that can be applied to images.  To do this, you will need to use inheritence and polymorphism.**
<hr>

### Getting Started

Navigate to lab04_polymorphism/checkpoint3 in one of the development environments (VOLE / CSE Labs, SSH, Docker).  Copy your code from Checkpoint 2 and import the stbi_image libraries along with the Image class you created.  Include any additional files you may have created for Checkpoint 2.

You can run the program with the following commands using the provided `Makefile` and `main.cc`.  **Note:** Initially the program will not compile because you will need to add the filter code.

```bash
% cd x500-repo/labs/lab03_memory/checkpoint2
% make
% ./image_processor
```

### Study the Filter UML

Study the UML below depicting a simple Filter inheritance hierarchy:

<img src="checkpoint3/Filters.png" alt="" width="1000"/>

The diagram shows Filter as a base class and three derived classes.  Each subclass overrides the Apply(...) method.  This is shown as psuedocode in the UML class diagram.  We will implement all of these classes:

 * **Filter** - The Filter class is an abstract class that defines the pure virtual method Apply(original, filtered).  Original is a set of input images and filtered is a set of output images.  For the filters we will write in this checkpoint, we only need to use the first image, however, for future filters we may need more than one input or output images.
 * **GreyScaleFilter** - Changes the image into a grey scale image based on image luminance (see calculation below).  It takes each pixel, calculates the luminance by aggregrating each component, and sets a new output pixel that uses this luminance value for red, green, and blue.
 * **ThresholdFilter** - Calculates the luminance for each pixel and sets the output pixel as black or write depending on the threshold value passed in through the constructor.
 * **MeanBlurFilter** - This is actually a convolution filter (which we will talk about soon in class).  For each pixel, it takes an average of all surrounding pixels including itself.  So, since there are 9 pixels total in the neighborhood, we add all pixels together and divide by 9.0.  This math should be done using floating point arithmetic verses integer arithmetic.

### Working with Colors

It is recommended that you create a Color class to handle the calculations needed for adding colors together and multiplying by constants.  Colors can be added, subtracted, and multiplied by scalars (e.g. +, -, and * operators).  It is sometimes easier to treat the red, green, blue, and alpha channels as numbers between 0 and 1, rather than between 0 and 255.  Therefore, to translate a pixel value from a byte to a floating point value you can use the following formula: `color.red = 1.0(pixel.red)/255.0`.  To change it back into a byte, you can use: `pixel.red = color.red*255`.  Instead of working with raw bytes, consider using this Color class in `Image::GetPixel(...)` and `Image::SetPixel(...)`.  It may make this project much more manageable.

You can calculate the luminance with the following function:

```c++
float GetLuminance() {
     return 0.2126*red + 0.7152*green + 0.0722*blue;
}
```

For more information on the theory behind this calculation, please refer to <https://en.wikipedia.org/wiki/Luma_(video)>.  

### Apply the Filters

After creating the filters and including them in _main.cc_, you should be able to use them to filter images.  You can build and run with the following command:

```bash
% make clean
% make
% ./image_processor <inputPath> <filterType> <outputPath>
```

The input path can be any path to a PNG file.  The output path is a PNG where the output is saved.  Finally, the filter type allows us to specify the specific filter operation we would like to accomplish.  In _main.cc_ there is a map (similar to a dictionary in Javascript or Python), which maps strings to Filters.  The filter type that is passed in will find the associated filter and call Apply(...).  Since Apply(...) is a vitual method, it will call the overriden Apply(...) method in the subclass though polymorphism.

The following are examples that show how to filter images:

```bash
% # Apply a threshold filter
% ./image_processor data/statue.png threshold data/statue-threshold.png
% # Apply a threshold at 0.25
% ./image_processor data/statue.png threshold-low data/statue-threshold-low.png
% # Apply a threshold at 0.75
% ./image_processor data/statue.png threshold-high data/statue-threshold-high.png
% # Apply a greyscale filter
% ./image_processor data/statue.png greyscale data/statue-greyscale.png
% # Apply a mean blur filter
% ./image_processor data/statue.png mean_blur data/statue-mean_blur.png
```

If your program correctly filters the images with the commands above, you are done with this checkpoint!

### Submitting your Checkpoint 3 (staring Tuesday, 10/5/2021)

Submit your work by uploading the following files to Gradescope for the Checkpoint2 assignment (which will be available starting Tuesday evening, October 5, 2021).  Your code will be automatically graded and your score recorded.  Upload the following:

 - Makefile
 - *.h
 - *.cc
 - Any other relevant files
 - *Note:* You do not need to submit PNG images or the stbi_image*.h libraries.

You are welcome to keep changing and submitting this checkpoint up to the deadline.  Gradescope will recompile and test your code.

THIS CHECKPOINT IS COMPLETE.

Congratulations!
