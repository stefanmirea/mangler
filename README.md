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

#Easy way (Linux 32 bit and 64 bit)

0. TODO: Download the release of the project and unzip it.

1. Download the correct Qt installer for your architecture x86 or x64: https://download.qt.io/archive/qt/5.5/5.5.1/.
![What to download](http://i.imgur.com/hnrhyrA.png?1)

2. Install the package.
./qt-opensource-linux-x86-5.5.1.run or  ./qt-opensource-linux-x64-5.5.1.run

3. Open QtCreator.
![QtCreator](http://i.imgur.com/5XNKcWo.png)

4. File > Open File or Project.
Then, from the folder obtained from step 0, select mangler.pro.

![Open Project](http://i.imgur.com/DOrdS4C.png)

5. Press "Configure Project".

![Configure Project](http://i.imgur.com/lmDsIgs.png)

6. Wait for QtCreator to scan / parse the source code files until the "Run" arrow is green.

7. Press the "Run" arrow button.

![Run](http://i.imgur.com/F0oEIax.png)

8. Wait for the program to build and run.

