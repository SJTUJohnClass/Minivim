# Assignment 2: MiniVim

> Project 2 of John Class 2023.
> Due: **November 21st**. 
> Please do not hesitate to contact us if you have any questions about this document.
> You can get a Chinese version of this document by throwing it into [deepl.com](https://www.deepl.com/translator).
> Thanks to *Zhou Jiahao* and *Yang Zhenyu*, TAs of John Class 2022 who created this project.

## <a id = "1">Contents</a>

- [Assignment 2: MiniVim](#assignment-2-minivim)
  - [Contents](#contents)
  - [ Introduction ](#-introduction-)
  - [ Our Purposes ](#-our-purposes-)
  - [ Assignment ](#-assignment-)
    - [ Basic ](#-basic-)
      - [ Base TUI ](#-base-tui-)
      - [ Multiple modes ](#-multiple-modes-)
      - [ Command line arguments ](#-command-line-arguments-)
      - [ Commands ](#-commands-)
      - [ Shortcut Keys ](#-shortcut-keys-)
    - [ Extension ](#-extension-)
      - [ Word Completion ](#-word-completion-)
      - [ Search and Substitution ](#-search-and-substitution-)
      - [ Line Number and Jump ](#-line-number-and-jump-)
      - [ Line Wrapping ](#-line-wrapping-)
      - [ Command History ](#-command-history-)
      - [ Path and relative path ](#-path-and-relative-path-)
    - [ Conventions ](#-conventions-)
  - [ Environment ](#-environment-)
    - [ WSL Install ](#-wsl-install-)
      - [ Install WSL ](#-install-wsl-)
      - [ Install Building Tools ](#-install-building-tools-)
    - [ Change APT Source(If needed) ](#-change-apt-sourceif-needed-)
    - [ Editor files in WSL ](#-editor-files-in-wsl-)
      - [ Use Clion to Code in WSL ](#-use-clion-to-code-in-wsl-)
      - [ Use VSCode to code in WSL ](#-use-vscode-to-code-in-wsl-)
    - [ Ncurses Install ](#-ncurses-install-)
    - [ CMake Install ](#-cmake-install-)
  - [ Guideline ](#-guideline-)
    - [ Keyboard ](#-keyboard-)
    - [ Ncurses ](#-ncurses-)
      - [ Window ](#-window-)
      - [ Cursor ](#-cursor-)
      - [ Some Setup Function ](#-some-setup-function-)
      - [ Simple Demo ](#-simple-demo-)
      - [ More Inforamations ](#-more-inforamations-)
    - [ Command Line Arguments ](#-command-line-arguments--1)
      - [ Manually Parsing ](#-manually-parsing-)
      - [ GNU `getopt` Function(Optional) ](#-gnu-getopt-functionoptional-)
      - [ Using Third-party Library(Optional) ](#-using-third-party-libraryoptional-)
    - [ Project Layout ](#-project-layout-)
      - [ Example ](#-example-)
      - [ Build Above Project Using CMake ](#-build-above-project-using-cmake-)
      - [Using CMake to compile ncurses\_demo.cpp](#using-cmake-to-compile-ncurses_democpp)
    - [ Introduction to Extension: Word Completion(Optional) ](#-introduction-to-extension-word-completionoptional-)
      - [ Usage ](#-usage-)
  - [ Grade ](#-grade-)
  - [ Suggestions ](#-suggestions-)

## <a id = "2"> Introduction </a>

Vim is a highly configurable text editor built to make, create, and change any kind of text very efficiently. It is included as "vi" with most UNIX systems and with Apple OS X.

![vim](https://notes.sjtu.edu.cn/uploads/upload_a201d56cb84c36a2634c341aaa2fcfed.png)

By simply typing ```vim <file_path>```, you can then open a file with vim. You can view text file in `Normal Mode`, insert characters in `Insert Mode`, and input command in `Command Mode`. We will explain those modes in assignment details.

You can take a brief lesson on vim on this [website](https://www.openvim.com/). This may take you twenty minutes or more, but covers some of the basic operations of vim, and you can also run vim in your own environment to actually try it out. Vimtutor is another helper to learn vim if you want. You can use it by simply typing `vimtutor` in your WSL.

Our assignment requirements are not as complex but will allow you to implement a text editor that has basic functionality (with some specified extensions) and can actually be used, **starting from scratch**.

That means we won't give you **any existing files**, you need to complete the whole job starting from your own new directory. The **guidelines** needed to complete the project are at the back of this document, and you can always find a TA to answer questions.

## <a id = "3"> Our Purposes </a>

We use this project to help you

- Learn how to use STL libraries
- Learn about project layout
- Use abstraction to code clearly and simply
- Enhance your simulation capabilities
- Standardize your coding style
- Be familiar with the command line
- Use CMake to compile your project
- Understand the compilation of multiple `.cpp`, `.h`, and other files(Optional)


## <a id = "4"> Assignment </a>

### <a id = "4.1"> Basic </a>

#### <a id = "4.1.1"> Base TUI </a>

Your TUI(Terminal User Interface) should look like this.

* File Window displays the opened file, and you can edit a file in this window.
* Information Window displays some file-related information. Here's the minimum information you should display: `Mode`, `Filename`, `Cursor line and column`.
* Command Window displays the commands the user input. **Note that you should print a `:` at the beginning of the command window when entering the command mode.**

<center>
      <img src="https://github.com/JohnClass2023/Minivim-2023/blob/main/pngs/windows.png" 
   alt="Window Layout"
   width="300" height="200"/>
</center>





#### <a id = "4.1.2"> Multiple modes </a>

 * Normal mode:
   In normal mode, we can move the cursor and browse the opened file by $\uparrow \downarrow \leftarrow \rightarrow$.
 * Insert mode:
   In insert mode, we can edit files by moving cursor. Edit files like appending, modifying, and deleting (just like vim).
 * Command mode:
   In command mode, we can type in and execute some commands.

 Mode-switching graph is shown below:

 <center>
 <img src="https://github.com/JohnClass2023/Minivim-2023/blob/main/pngs/mode_transference.png" 
  alt="Mode Switch"
  width="300" height="200"/>
 </center>




#### <a id = "4.1.3"> Command line arguments </a>

 User can open your minivim in terminal by command

```
 minivim [options] <filename>
```

 This command will open a file specified by `<filename>` in your minivim. The file is under the directory of your minivim executable file. If the file doesn't exist, create it.
 You should support several optional arguments in command line:

 * `-t`: open file in truncation mode. You should truncate the file from the beginning.
 * `-R`: open a file in **read-only** mode.
 * `-W break/scroll`: wrap the lines by line breaks / scrolling (extension)

 To start your MiniVim by `minivim` rather than `PATH/TO/MiniVim`, you may need to add your executable file to `/bin` or export your executable file to `$PATH`. See more details in [Export to PATH](https://stackoverflow.com/questions/56981754/how-to-make-a-programme-executable-anywhere-in-the-shell).


#### <a id = "4.1.4"> Commands </a>

 You should support several base commands:

 * `:w`: Save the file.
 * `:q`: Quit. Warn user if the file is changed but unsaved.
 * `:q!`: Force quit (i.e. Do not save the file and force quit.).
 * `:wq`: Save then quit.

#### <a id = "4.1.5"> Shortcut Keys </a>

You should support several shortcut keys in **Normal Mode**:

* `dd`: delete the entire line that the cursor is currently on.
  - If the next line exists, move the cursor to the first non-blank character of the next line.
* `0`: Move the cursor to the beginning of the line.
* `$`: Move the cursor to the end of the line.
* `w`: Move forward one word (delimited by a white space or a new line). 
  - If the cursor is at a blank character or the end of a word, move the cursor to the beginning of the next word.
  - If the cursor is at the end of a line, move the cursor to the beginning of the next line if it exists..
* `b`: Move backward one word (delimited by a white space or a new line). 
  - If the cursor is at a blank character or the beginning of a word, move to the end of the previous word.
  - If the cursor is at the beginning of a line, move to the end of the previous line if it exists.

### <a id = "4.2"> Extension </a>

#### <a id = "4.2.1"> Word Completion </a>

MiniVim gives some options for auto-completion when user has entered the prefix. You may need an extra window to display the alternative words and let user select words.

To complete the current word, the user should first press `Tab`. If there is more than one option, the user should then enter numbers (to choose the word), press $\leftarrow \rightarrow$ / $\uparrow \downarrow$ / $+ -$ (to switch between the pages, just like your `shu ru fa` I really do not know what it is in English TAT), or press `Esc` to quit. Otherwise, if there is only one option, your program should complete the words directly after 'Tab' is pressed.

If the user wants to type `Tab`, they should press `Tab` twice if this extension is implemented.

You can get the English word library named `words_alpha.txt` in this repo.

#### <a id = "4.2.2"> Search and Substitution </a>

Minivim supports searching for a word in the full file and substituting it with another word. User may use command `:sub "stone" "gold"` to substitute stone with gold.

  
#### <a id = "4.2.3"> Line Number and Jump </a>

MiniVim supports displaying line numbers at the beginning of a line and jumping to a specific line by command `:jmp LineNumber`. You may display the specific line on the top.

#### <a id = "4.2.4"> Line Wrapping </a>

In Vim, if one line has too many characters making it exceed the window, vim will split it into several lines with them sharing the same line number. We don't make any demands of this, you can implement it as you like. But you should notice that, if you split it then you need to care about where your cursor will be if you press $\uparrow$ and $\downarrow$. On the other hand, if you're not willing to split it, then you have to scroll your windows left or right if the cursor exceeds the windows. You can choose any way you want and implement it, and you can complete this extension by implementing both, switched by using '-W break'(default) or '-W scroll' in program arguments.

#### <a id = "4.2.5"> Command History </a>

MiniVim supports browse commands previously entered in **Command Mode** by $\uparrow \downarrow$.

#### <a id = "4.2.6"> Path and relative path </a>

Remember we call `minivim [options] <filename>` to use minivim and the file we open is under the directory of your minivim executable. Now you are asked to support using path and relative path to open the file.

### <a id = "4.3"> Conventions </a>

These are some conventions you need to follow. You are asked to implement these features compulsively. **Violation of these conventions may dock your score of the basic part. Please read and follow them meticulously**

* If the number of file lines exceeds the maximum number of lines in the file window, you should display only part of the file and scroll the file when the cursor reaches the bottom of the window. 
* Similar to vim, in normal mode, your cursor should NOT exceed the end of a line and the end of the file; whereas in insert mode, your cursor should BE ABLE TO reach the end of a line and the end of the file. Therefore, if you switch from insert mode to normal mode, your cursor should go back a column. 
* About the length of `tab`: a better way to handle `\t` is to deem `\t` as a fixed number of spaces, like 4 or 2. Also, you can simulate its behavior in Vim, but sometimes it's too complex and confusing. We highly **recommend**(just recommend) you to see it as 4 spaces. 
* About `:q!` command: If the file you are editing does not exist and was created by MiniVim, then this operation will also undo the creation.
* When in vim you press $\downarrow$ first and $\uparrow$ second, the cursor will be at its former position instead of the length of this line and the following line. You need to implement this in your minivim. For example, if we have three lines with lengths of $10, 5, 12$ respectively and your cursor is at the $8$ th char of the first line. When pressing $\downarrow$, the cursor will move to the end of the second line because it doesn't have enough characters. Then you press $\downarrow$ again, your program must ensure that now the cursor is at the $8$ th character of the third line. After that, you Press $\uparrow$ two times, and the cursor must return to the $8$ th char in the first line. In short, when pressing $\uparrow$ or $\downarrow$, minivim needs to remember the current column of the cursor. If the new line doesn't have enough characters, then the cursor will be at the end of the line. Press $\uparrow$ or $\downarrow$ again, if this new line has enough columns, the cursor must be at the column that minivim remembers.
* $\rightarrow$ and $\leftarrow$ are not allowed to jump to the next/previous line when at the end/beginning of a line.
* In break-line mode, $\downarrow$ and $\uparrow$ should jump to the next/previous line in the original text regardless of whether the current line is split into several to display or not.
* Try to align the behavior of your MiniVim with the real Vim as much as possible.

Also, if you are not sure about other features that you need to implement, please contact us directly. We will give definite answers to your questions.


## <a id = "5"> Environment </a>

### <a id = "5.1"> WSL Install </a>

#### <a id = "5.1.1"> Install WSL </a>

> **Students who have installed WSL in tutorial class 1 can skip this phase.**

We are sorry to announce that due to some technical limitations, this project is to be done in *Linux*. You may have heard of Linux: It's an operating system just like Windows and MacOS. Of course, it would be impractical to require all of you guys to install a new system directly on your desktop, rather we recommend doing this through WSL. I'd like to say beforehand that all the steps below are simply suggestions, and you are free to achieve the same goal using anything you prefer.

WSL stands for *Windows Subsystem for Linux*. For now just view it as a virtual machine run in Windows, though in fact there are some subtle (and important) differences between them. To install WSL (or most of other tools you need in the future), the best way is to go directly to the official website and read the [guide](https://learn.microsoft.com/en-us/windows/wsl/install). In short, the easy way:

1. Open your Windows terminal like cmd and Powershell.
2. Type in `wsl --install -d Ubuntu-20.04`. (Or any linux-es you want with any versions)
3. Waiting for Ubuntu-20.04 to ask you to type in your new username and password.
4. After all these have done, reboot your terminal and type in `wsl`. If everything goes smoothly, terminal prompt will change to Linux style.

there is a hard, but more customizable way to install, but let's omit it for now. The tutorial is available on the website above. Now WSL2 and Ubuntu (One of the various Linux-es) should have been successfully installed.

An aside: you can install *Windows terminal* to gain a more pleasing experience when using Powershell and Ubuntu.

If everything goes smoothly, you are now in a working Linux system. It's very likely you have no idea how to use it; however, to this end, not much is needed. If you're interested, find a good book and read a few chapters. Here I'll just explain something basic.

#### <a id = "5.1.2"> Install Building Tools </a>

> **Students who have installed g++ in their WSL can skip this phase.**

In Linux, you interact with system mainly by using commands in a shell. Firstly, as you have done in Windows via VSCode or CLion, a compiler for C++ is essential. Type `sudo apt update` and hit enter. You are required to enter your password (created by yourself a few minutes ago). Then a lot of texts rolled down the screen: that's what it should be like. Then type `sudo apt install build-essential` to install the most basic components for developing programs. During the process, enter "y" every time the system asks.

A little bit of explanation: `sudo` means you run the following command as a root user: you have permission to do this. This is why you are asked to provide the password. `apt` is a software, or program, designed for managing your software. The `update` you feed it means you want it to update its *sources* (see later). The `install` you feed it means you want it to install the following software package `build-essential` for you. build-essential contains a bunch of software packages including gcc, g++, make, and so on.

```bash
# get build-essential
sudo apt update
sudo apt install build-essential
```

### <a id = "5.2"> Change APT Source(If needed) </a>

By the way, as we all know, in China and some other places the internet is sometimes strange. From my own experience `apt` worked quite well by default, but there do exist circumstances it just can't download something. There are many ways to solve this: you can use a proxy, but to be honest, I managed to do that in my home but failed here in SJTU. Another approach is to change the *sources*.

Briefly, there is a list of URLs as "sources" for `apt` to fetch something like a list. The list contains the names of software available, their descriptions, where to download it, what other software it depends on, and many other things. We can replace the default "sources" with new ones which, made a little change: the download URLs it provides work well in China. Then how to do this? This needs a little bit more work, and good guidance can be found [here](https://mirrors.sjtug.sjtu.edu.cn/docs/ubuntu).

### <a id = "5.3"> Editor files in WSL </a>

#### <a id = "5.3.1"> Use Clion to Code in WSL </a>

> These contents are edited by TAs of John Class 2022, but I prefer VSCode, haha.
> I keep this just because someone may want to use CLion as their IDE.

But, how to write code? No no, we don't use `vim` because there is some way to access WSL using CLion, and it provides more than merely manipulating files. To this end install CMake (see below) in advance. As always, read [this](https://www.jetbrains.com/help/clion/how-to-use-wsl-development-environment-in-product.html) is a good idea. In short,

1. create a new project. The project should be located in the file system of Ubuntu. A good place is somewhere in `/home/your-user-name/`.
2. in `CMakeList.txt`, change `cmake_minimum_required` to 3.16
3. go to Settings / Build, Execution, Deployment / Toolchains
4. click "+" and choose WSL
5. Everything is automated. wait then click OK
6. go to Settings / Build, Execution, Deployment / CMake
7. change the toolchain to "WSL" (the one you just created)
8. click OK. if everything goes fine the debug window below shouldn't report any errors.

IDEs used for this assignment are not limited, you can still use whatever you're already familiar with. 

#### <a id = "5.3.2"> Use VSCode to code in WSL </a>

One thing we need to know is that WSL shares the file system with the Windows system, which means we can create the project in any directory you want in Windows but compile the project in WSL. That is really useful for me.

You need to

1. create a new project directory. The project does not need to be located in the file system of Ubuntu. You can put it anywhere you want but do remember the path of it.
2. create `CMakeList.txt` and do as we have said in [Use Clion to code in WSL](#Use-VSCode-to-code-in-WSL).
3. open your VSCode, and click `File / Open Folder` to open your project file.
4. click the button which looks like two A4 overlapping each other. Left of your screen will show files and sub-directories in your project. You can click any of it and edit it.
5. open your VSCode terminal, and type in `wsl` to use WSL. When you are in your WSL, type `make`. If everything about your project is done, there will be a `minivim` executable(I don't know how to call an executable in Linux, maybe its name is not executable) in your `bin` sub-directory.

### <a id = "5.4"> Ncurses Install </a>

Use this command to install ncurses in WSL2.

```
sudo apt install libncurses5-dev libncursesw5-dev
```

### <a id = "5.5"> CMake Install </a>

Use this command to install & verify cmake in WSL2.

```
sudo apt install cmake
cmake --version
```

## <a id = "6"> Guideline </a>

### <a id = "6.1"> Keyboard </a>

MiniVim is a keyboard-only editor, so all operations will be done with keys. To achieve this, we need to know how to represent keys from the keyboard first.
As we all know, it's easy to get the character 'a' in the alphabet by typing `'a'`. However, there are many chars on the keyboard (such as `Esc`, `Backspace`) that are not in the alphabet. What is used to represent them in the computer?
[ASCII](https://www.asciitable.com/) stands for American Standard Code for Information Interchange. Computers can only understand numbers, so an ASCII code is the numerical representation of a character such as `a` or `Esc` or an action of some sort. For example, the number `97` represents char `a` and `27` represents `Esc`. You can find the corresponding characters in the ASCII table.

### <a id = "6.2"> Ncurses </a>

Ncurses (new curses) is a programming library providing an application programming interface (API) that allows the programmer to write text-based user interfaces (TUI) in a terminal-independent manner. It is a toolkit for developing "GUI-like" application software that runs under a terminal emulator. 

To use ncurses library, you should include header file by `#include <ncurses.h>` and link ncurses library by `g++ -o xxx xxx.cpp -lncurses` when compiling.

> To use ncurses library in CMake project, you can refer to the example in **CMake subsection** of this document.

#### <a id = "6.2.1"> Window </a>

A **window** is a square area in your terminal. In this project, the whole terminal is simply divided into 3 windows.

<center class="half">
<img src="https://github.com/JohnClass2023/Minivim-2023/blob/main/pngs/windows.png" 
   alt="Window Layout"
   width="300" height="200"/><img 
   src="https://github.com/JohnClass2023/Minivim-2023/blob/main/pngs/effect.png" 
   alt="Demo Layout" 
   width="300" height="200"
   />
</center>








File window displays the opened file, and user can edit the file in this window. Information window displays some file information such as *filename*, *edit mode*, and so on. Command window displays the command input by user in command mode.

At the very beginning, you need to call `initscr()` to create the initial window. A customized window can be created by calling 

```
WINDOW *win = newwin(lines, cols, startx, starty);
```

By the way, the coordinates of windows are shown below: 

<center>
<img src="https://github.com/JohnClass2023/Minivim-2023/blob/main/pngs/axles.png" 
   alt="Window Layout"
   width="300" height="200"/>
</center>







We can get the begin position by `getbegyx(win, y, x)` and the max position by `getmaxyx(win, y, x)`.

Next, we want to input and output something in the window. `wprintw` and `getch` can help us. We can print "Hello world in 2022" to the windows we just created by 

```
wprintw(win, "Hello world in %d", 2022);
wrefresh(win);
```

And we can clear the window by `wclear(win)`.

Note that after we have printed some characters, we usually have to refresh the window by calling `wrefresh`.

To distinguish the different windows more clearly, you can call `wbkgd` to set the front-end and back-end colors of the window. Here is a code snippet:

```
int color_pair_num = 0;
start_color();
// init color pair
init_pair(COLOR_PAIR(color_pair_num), COLOR_WHITE, COLOR_CYAN);
// set window color
wbkgd(win, color_pair_num);
```

In the end, **remember to call `endwin()` to destroy all windows before the program exits**.

#### <a id = "6.2.2"> Cursor </a>

The **cursor** is an indicator that shows you where you are editing. We can move the cursor to $(line, col)$ in the window by calling 

```
wmove(win, line, col);
```

If you want to move to $(line, col)$ and print 'Hello, world!', just call `mvwprintw(win, line, col, "Hello, world!");` to finish these actions in one line.
If you want to insert the characters before the cursor, you may need `winsch(win, char);`. There is also a combination of move and insert `mvwinsch(win, y, x, char);`.
If you want to delete the characters under the cursor, `wdelch` and `mvwdelch` may help.
To delete and insert a line, use `wdeleteln` and `winsertln`.
In fact, there are lots of functions you can use to **reduce the workload**, you can check the documentation of [ncurses](https://pubs.opengroup.org/onlinepubs/7908799/xcurses/) or just google it.

#### <a id = "6.2.3"> Some Setup Function </a>

* `raw()`: Normally the terminal driver buffers the characters a user types until a new line or carriage return is encountered. However, most programs require that the characters be available as soon as the user types them. The above function is used to disable line buffering.
* `echo()` and `noecho()`: These functions control the echoing of characters typed by the user to the terminal. `noecho()` switches off echoing.
* `keypad(win, bool)`:  It enables the reading of function keys like F1, F2, arrow keys etc. Almost every interactive program enables this, as arrow keys are a major part of any User Interface.

#### <a id = "6.2.4"> Simple Demo </a>

You can find a **ncurses demo** named `ncurses_demo.cpp` in this repo.

#### <a id = "6.2.5"> More Inforamations </a>

Get more information in [Ncurses Tutorial](http://www.ibiblio.org/pub/Linux/docs/HOWTO/other-formats/pdf/NCURSES-Programming-HOWTO.pdf) and [Ncurses API](https://pubs.opengroup.org/onlinepubs/7908799/xcurses/).

### <a id = "6.3"> Command Line Arguments </a>

MiniVim is a command-line program that accepts arguments passed from the command line by the user at startup. At its simplest, the ```hello.txt``` in ```vim hello.txt``` is a command line argument.

In C/C++, command line arguments are passed into the program via two arguments to the ```main``` function:

```C++
int main(int argc, char *argv[]) {
  ...
}
```

```argc``` indicates the number of arguments; ```argv``` is an array of strings of length ```argc```, which stores all the arguments passed in.

for example, using ``./bin/minivim --test -cmdline arguments`` to run the minivim program, its `main` function will receive the following arguments:

```python
argc = 4
argv = ["./bin/minivim", "--test", "-cmdline", "arguments"]
```

#### <a id = "6.3.1"> Manually Parsing </a>

Once you understand the basics, you can accept **simple** command-line arguments yourself (like, in this project, using `argv[1]` as filename). But if the accepted parameters start to get complicated, parsing them yourself becomes cumbersome and error-prone.

#### <a id = "6.3.2"> GNU `getopt` Function(Optional) </a>

C/C++ introduces the `getopt` function in the header `<unistd.h>` to help programmers with the relatively tedious task of parsing. This is a convenient option if you don't want to parse manually and have to add some arguments in a simple format.

Here are some tutorials and examples on `getopt`: 

+ https://cloud.tencent.com/developer/article/1176216
+ https://en.wikipedia.org/wiki/Getopt

#### <a id = "6.3.3"> Using Third-party Library(Optional) </a>

It is more convenient and encouraged to use any other **third-party library** to complete more complicated command-line argument parsing, but this requires that you have the ability to import external libraries into your project, which you can try if you have more spare time.

Popular Modern C++ Argument Parsers:

+ https://github.com/adishavit/argh (C++11 required)
+ https://github.com/muellan/clipp (C++11 required)
+ https://github.com/p-ranav/argparse (C++17 required)

You can choose the most suitable implementation yourself, as long as the required functionality is completed. :)

### <a id = "6.4"> Project Layout </a>

For a code project that is not a single file, you will of course need to consider how to plan the directory layout: A sensible and elegant project layout can greatly enhance your programming experience.

Although the volume of this assignment is still relatively small, we still recommend a sound structure to get you familiar with how to organize a CMake project from scratch.

> We take `CMake` as an example build-system, but you can use whatever you like: `Makefile`, `XMake`...

#### <a id = "6.4.1"> Example </a>

```
project/
├── .gitignore
├── README.md
├── CMakeLists.txt
├── bin/
│   └── <compiled executable files>
├── build/
│   └── <cmake generated build files>
├── include/
│   └── *.h
├── lib/
│   └── <precompiled lib files>
└── src/
  └── *.cpp
...
```

Above is a simple C++ project layout, let's break it down:

+ `.gitignore`: Ignore non-project files like `.idea/`, `bin/`, `build/`, and so on.
+ `README.md`: Self-introduction of your project.
+ `CMakeLists.txt`: Tell CMake how to build your project & compile executable file.
+ `bin/`: Save your compiled executable file (e.g., `minivim`).
+ `build/`: Hold the compile scripts and half-compile files generated by CMake.
+ `include/`: Header files of your own project or imported third-party project.
+ `lib/`: Lib files (precompiled code) from imported third-party projects.
+ `src/`: Your own `*.cpp` source code.

Not all parts of it are necessary, e.g. the `lib` directory is not needed if no third-party libraries are introduced; you can also add directories yourself, like `scripts`, `docs`, `tests` ...

See [this website](https://www.linkedin.com/pulse/what-general-c-project-structure-like-herbert-elwood-gilliland-iii) or google for more introduction.

#### <a id = "6.4.4"> Build Above Project Using CMake </a>

For complex projects, it is annoying and unnecessary to execute `g++ ...` commands manually every time you compile. CMake can generate compilation scripts based on the `CMakeLists.txt` and conveniently invoke them.

For simple projects with ncurses libraries, a `CMakeLists.txt` example is as follows：

```CMake
# specify the minimum version of CMake that is supported
cmake_minimum_required(VERSION 3.10)

# include a project name
project(cmake-example)

# set C++ Version & executable output path
set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# make your compiler aware of header directory
include_directories(${PROJECT_SOURCE_DIR}/include)

# find & include ncurses library
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

# create a variable that includes needed source files
set(MY_SOURCES
  ${PROJECT_SOURCE_DIR}/src/hello.cpp
  ${PROJECT_SOURCE_DIR}/src/world.cpp
  ${PROJECT_SOURCE_DIR}/src/main.cpp
)

# specify an executable, 
# build from the specified source files
add_executable(example-bin ${MY_SOURCES})

# link ncurses library with your executable
target_link_libraries(example-bin ${CURSES_LIBRARY})
```

**This is just a simple demo. You may need to make some changes to adapt to your project.**

To configure & compile this project, simply:

```bash
# configure project in specified cmake directory: build/
cmake -B build
# compile target in build directory
cmake --build build --target example-bin
```

For more examples & usage, see [ttroy50/cmake-examples](https://github.com/ttroy50/cmake-examples), ranging from a basic hello-world project to complicated features, with detailed explanations. [on-demand, Recommended]

#### <a id = "6.4.5">Using CMake to compile ncurses_demo.cpp</a>

We upload a project directory in the git repo, which includes a "CMakeLists.txt" and a "ncurses_demo.cpp" in the "src" sub-directory.

To compile the `ncurses_demo.cpp`, we suggest you open the `project` directory in WSL, and type in the following commands

```
cmake -B build
cmake --build build --target minivim
```

If all things go well, there will be a "minivim" executable in the `bin` sub-directory. Try to call it by `./bin/minivim`, and you will see a TUI.

> In fact, the way we ask you to open "minivim" file is to call `minivim` instead of `./bin/minivim`. To implement this, you need to add it to `$PATH`. Tutorials are in [here](#4.1.3)

### <a id = "6.5"> Introduction to Extension: Word Completion(Optional) </a>

In order to efficiently predict target words based on their prefixes, we need to use a trie-tree. The algorithm for trie-tree is not the focus of our assignment, so you can put the implementation of the tire-tree in this link (any other implementation is acceptable) into your project:

https://github.com/kephir4eg/trie

> Since `auto_ptr` used in this repo was deprecated in C++17, you can change it to `unique_ptr` if your Cpp standard is 17 or later. 

#### <a id = "6.5.1"> Usage </a>

To install this library, simply copy `trie/src/trie.h` to your `{project}/include/`

To create & initialize & fill the trie_set:

```c++
#include <trie.h>
#include <iostream>

using Lexicon = trie::trie_map<char, trie::SetCounter>;

int main() {
  Lexicon lexicon;

  lexicon.insert("where");
  lexicon.insert("have");
  lexicon.insert("you");
  lexicon.insert("been");

  std::cout << lexicon.contains("where") << " ";
  std::cout << lexicon.contains("have") << " ";
  std::cout << lexicon.contains("you") << " ";
  std::cout << lexicon.contains("been") << " ";
  std::cout << std::endl;
}
```

To iterate words with a specified prefix:

```c++
#include <trie.h>
#include <iostream>
#include <vector>

using Lexicon  = trie::trie_map<char, trie::SetCounter>;
using WordList = std::vector<std::string>;

int main() {
  Lexicon lexicon;
  WordList words = { "what", "wakes", "you", "and", "when", "why" };

  for (const auto &word : words) {
      lexicon.insert(word);
  }

  for (auto it = lexicon.find_prefix("wh"); it != lexicon.end(); ++it)
      std::cout << it.key() << ' ';
  std::cout << std::endl;
}
```

The output is `what when why`, as expected. With this library, you can predict words by their prefixes easily.


## <a id = "7"> Grade </a>

+ Basic: total 60
  + Base terminal user interface: 10
  + Multiple modes & Text Edit: 25
  + In-editor Commands: 5
  + Command line arguments: 5
  + File persistence: 10
  + Shortcut Key: 5
+ Extensions: up to 20
  + Word Completion: 10
  + Search and Substitution: 5
  + Another way of line wrapping: 10
  + Line Number and Jump: 5
  + Command History: 5
  + Path and relative path: 5
+ Coding Conventions & Project Layout: 10
+ Q & A: 10

## <a id = "8"> Suggestions </a>

To help you with your project, we have some suggestions for you.

1. When come across some problems, try to handle them yourself at first. Google or Baidu are all good methods to solve your problems. After that, if you are not satisfied with the answer, you can ask for TAs for free.
2. Try to install all the environments that the project needs. Affirm that they are working well and then begin your project.
3. At the beginning of your project, try to research the demo cpp file, and figure out how it works. Also, you can change some arguments in the file to make the TUI to be displayed as you like.
4. Before coding, try to think about how to break up your project into several independent parts, like *file processing* model, *window processing* model, *cursor processing* model, *contents processing* model, and something else. You can do it in your will. We don't acquire it, but it's a good habit when you're coding and it will make the whole thing easier.
5. An important thing is that you'd better consider how to store your file in the program, how to insert a char, and how to append a line.
6. After all the above has been done, try to test the effect after you change or add something to your program. **This project is not standardized. That means your grade depends on your ultimate performance, which means the performance of your program is really important.**
7. You can communicate with your classmates. **Plagiarism is forbidden in John Class. We welcome idea exchanges, but any form of cheat will be taken seriously. If you're not sure about your behavior, please talk with us in case of misunderstandings.**
