# Interactive Executable Mangler

Binary analysis and reverse engineering of executables are part of the skill set required for security analysts, consultants and hackers. These skills not only allow in-depth understanding of proprietary platforms and software, but also a better understanding of the inner workings of an executable that may be built from code one has access to.

It is often the case in security analysis and reverse engineering that one needs to update the executable: update bytes in the text area, rewrite a global variable, fill information in string-like sections. These steps are required either to get an understanding of the inner workings, to inject hooks for later-on dynamic analysis or to harden the executable.

While executable viewers do exist (such as readelf, [MachO View][1], [IDA][2]), there is no easy way to mangle an executable file by rewriting certain portions in it.

We aim to build an interactive tool that allows the user to analyze sections, data and code inside an executable and provide the means to update parts of the executable as required for different scenarios. The user will use a GUI to state the sections and data that would need to be rewritten inside the executable.

For starters we will target Linux ELF x86 and x86\_64 executables, but we would extend it to ARM and to Mach-O executables on x86, x86\_64 and ARM.

Installation
=========

1.
	* a. Download the [archive][3] of the project and unzip it.
	
	* b. sudo apt-get install libgl1-mesa-dev libglu1-mesa-dev
	
	* c. Make sure you have objdump installed. If not sudo apt-get install binutils-dev.
	
	* d. Make sure you have g++ installed and that it is the lastest version. sudo apt-get install g++ in order to check.

2. Download the latest version of [segvcatch][4] and install it.  
`$ unzip segvcatch-0.9.1.zip`  
`$ cd segvcatch-0.9.1`  
`$ cmake .`  
`$ make`  
`$ sudo make install`  
Note: If the compiler complains about `syscall` declaration missing after issuing `make`, you need to `#include <unistd.h>` in `lib/x86_64-signal.h` and / or `lib/i386-signal.h`.

3. Download the correct [Qt installer][5] for your architecture x86 or x64.
![What to download](http://i.imgur.com/hnrhyrA.png?1)

4. Install the package (`chmod +x` if it doesn't have execution rights).  
`./qt-opensource-linux-x86-5.5.1.run`  
or  
`./qt-opensource-linux-x64-5.5.1.run` (depending on platform, 32 bit or 64 bit)

#1st method (Linux distro)

5. Set up path to Qt directory.
    * `QT_PATH="/path/to/qt/version/"`
    * `export QT_PATH`
    * example: `QT_PATH="/home/adrian/Qt5.5.1/5.5/"`
    * `cd $QT_PATH` and `ls` should show you a folder called `gcc` or `gcc_64`
    
6. Navigate to the `mangler-master/` folder from step 1.

7. Create the Makefile using the following command:
    * for 32-bit installations: `$QT_PATH/gcc/bin/qmake mangler.pro`
    * for 64-bit installations: `$QT_PATH/gcc_64/bin/qmake mangler.pro`
    * you have to be in the `mangler-master/` folder! 
8. `make` (and of, course wait for a bit)

9. Make sure that the new-created `mangler` file has run permissions (`chmod +x mangler`)

10. `./mangler`

#2nd method (Linux distro)

5. Open QtCreator.
![QtCreator](http://i.imgur.com/5XNKcWo.png)

6. File > Open File or Project.
Then, from the folder obtained from step 1, select mangler.pro.
![Open Project](http://i.imgur.com/DOrdS4C.png)

7. Press "Configure Project".
![Configure Project](http://i.imgur.com/lmDsIgs.png)

8. Wait for QtCreator to scan / parse the source code files until the "Run" arrow is green.

9. Press the "Run" arrow button.
![Run](http://i.imgur.com/F0oEIax.png)

10. Wait for the program to build and run.

Usage
=========
1. File > Open. Select a 32 bit executable (you can find some in the mangler-master/examples/).
2. Explore the header, sections, segments contents in the left side.
3. Select a section and try to modify in the hexdump some data from it. (center)
4. From the Section Contents, try to find the ".text" section and display its assembly representation. (right side)
5. Try to modify some of the instructions. Hint: `nop` will remove an instruction.

[1]: http://sourceforge.net/projects/machoview/
[2]: https://www.hex-rays.com/products/ida/
[3]: https://github.com/stefanmirea/mangler/archive/master.zip
[4]: https://code.google.com/archive/p/segvcatch/downloads
[5]: https://download.qt.io/archive/qt/5.5/5.5.1/