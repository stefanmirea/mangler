# Interactive Executable Mangler

Binary analysis and reverse engineering of executables are part of the skill set required for security analysts, consultants and hackers. These skills not only allow in-depth understanding of proprietary platforms and software, but also a better understanding of the inner workings of an executable that may be built from code one has access to.

It is often the case in security analysis and reverse engineering that one needs to update the executable: update bytes in the text area, rewrite a global variable, fill information in string-like sections. These steps are required either to get an understanding of the inner workings, to inject hooks for later-on dynamic analysis or to harden the executable.

While executable viewers do exist (such as readelf, [MachO View][1], [IDA][2]), there is no easy way to mangle an executable file by rewriting certain portions in it.

We aim to build an interactive tool that allows the user to analyze sections, data and code inside an executable and provide the means to update parts of the executable as required for different scenarios. The user will use a GUI to state the sections and data that would need to be rewritten inside the executable.

For starters we will target Linux ELF x86 and x86\_64 executables, but we would extend it to ARM and to Mach-O executables on x86, x86\_64 and ARM.

[1]: http://sourceforge.net/projects/machoview/
[2]: https://www.hex-rays.com/products/ida/

Installation
=========
#1st method (Linux distro)

1.
	* a. Download the archive of the project and unzip it: https://github.com/stefanmirea/mangler.git
	
	* b. sudo apt-get install libgl1-mesa-dev libglu1-mesa-dev
	
	* c. Make sure you have objdump installed. If not sudo apt-get install binutils-dev.
	
	* d. Make sure you have g++ installed and that it is the lastest version. sudo apt-get install g++ in order to check.

2. Download the correct Qt installer for your architecture x86 or x64: https://download.qt.io/archive/qt/5.5/5.5.1/.
![What to download](http://i.imgur.com/hnrhyrA.png?1)

3. Install the package (chmod +x if it doesn't have execution rights).
./qt-opensource-linux-x86-5.5.1.run or  ./qt-opensource-linux-x64-5.5.1.run (depending on platform, 32 bit or 64 bit)

4. Set up path to Qt directory.
    * QT\_PATH="/path/to/qt/version/"
    * export QT\_PATH
    * example: QT\_PATH="/home/adrian/Qt5.5.1/5.5/"
    * cd $QT\_PATH and ls should show you a folder called "gcc"
    
5. Navigate to the mangler-master/ folder from step 1.

6. Create the Makefile using the following command:
    * for 32-bit installations: $QT\_PATH/gcc/bin/qmake mangler.pro
    * for 64-bit installations: $QT\_PATH/gcc\_64/bin/qmake mangler.pro
    * you have to be in the mangler-master/ folder! 
7. make (and of, course wait for a bit)

8. Make sure that the new-created 'mangler' file has run permissions (chmod +x mangler)

9. ./mangler

#2nd method (Linux distro)

1.
	* a. Download the archive of the project and unzip it: https://github.com/stefanmirea/mangler.git
	
	* b. sudo apt-get install libgl1-mesa-dev libglu1-mesa-dev
	
	* c. Make sure you have objdump installed. If not sudo apt-get install binutils-dev.
	
	* d. Make sure you have g++ installed and that it is the lastest version. sudo apt-get install g++ in order to check.

2. Download the correct Qt installer for your architecture x86 or x64: https://download.qt.io/archive/qt/5.5/5.5.1/.
![What to download](http://i.imgur.com/hnrhyrA.png?1)

3. Install the package (chmod +x if it doesn't have execution rights).
./qt-opensource-linux-x86-5.5.1.run or  ./qt-opensource-linux-x64-5.5.1.run (depending on platform, 32 bit or 64 bit)

4. Open QtCreator.
![QtCreator](http://i.imgur.com/5XNKcWo.png)

5. File > Open File or Project.
Then, from the folder obtained from step 1, select mangler.pro.
![Open Project](http://i.imgur.com/DOrdS4C.png)

6. Press "Configure Project".
![Configure Project](http://i.imgur.com/lmDsIgs.png)

7. Wait for QtCreator to scan / parse the source code files until the "Run" arrow is green.

8. Press the "Run" arrow button.
![Run](http://i.imgur.com/F0oEIax.png)

9. Wait for the program to build and run.

Usage
=========
1. File > Open. Select a 32 bit executable (you can find some in the mangler-master/examples/).
2. Explore the header, sections, segments contents in the left side.
3. Select a section and try to modify in the hexdump some data from it.
4. From the Section Contents, try to find the ".text" section and display its assembly representation.
5. Try to modify some of the instructions. Hint: `nop` will remove an instruction.
