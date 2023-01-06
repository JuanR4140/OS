# 16-bit to 32-bit Operating System
## How to run
- Type `make` in this directory. This will compile the operating system into an `os-image.bin`, which can be used by the Bochs emulator to emulate the operating system.
- After compiling, run Bochs in this directory by either
- - Pressing Run (if on Replit)
  - typing `bochs -f bochsrc.txt -q` in the shell in this directory
  - typing `make run` in the shell in this directory, which will automatically compile the OS and run bochs.
- Finally, bochs will read the `bochsrc.txt` file present in this directory and use its contents to load in the file automatically.
  If for whatever reason it doesn't, you will see a `Bochs Configuration: Main Menu` screen in the terminal.
  From here, type `2` for `Read options from...` and type `[Enter]` or `bochsrc.txt` (Bochs will recognize both as `bochsrc.txt`), then
  type `[Enter] ` or `6` for `Begin simulation` (Bochs will recognize both as `6`).<br>
  There we go! Bochs has loaded in our operating system! Now, all that is left to do is run it!
- In the event you get a Bochs `PANIC` message, don't.. panic.. (haha) and just type `cont` to `continue`
- In the event you get dropped into a Bochs debug shell, and aren't debugging this operating system, type `c` to finally run Bochs and
  see the operating system in action!
## Clean Up
Once finished, run `make clean` to clean the directories of any files that aren't source code.
## How it Works
This operating system boots in 16-bit Real Mode, uses BIOS interrupts to read the operating system from disk, loading it
into memory address 0x1000 before loading in the GDT to the CPU, switching to 32-bit Protected Mode before, finally,
jumping to the kernel where we set the ISR's and IRQ's to currently handle timer and keyboard events.
## What It Does
This operating system can't do much yet, but some things it *can* do are as follows:
- print messages to screen
- read keyboard
- respond to user input
- very crude memory implementations
## Planning On Next
I intend to improve the way `malloc` works. I also intend to implement a simple file system
in which the operating system can access. From there, we can make a very basic operating system that
can write, read, execute, and load files that can serve as an old 1980's personal computer.