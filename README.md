# PIC
PIC uses the Particle In Cell method to simulate kinetic plasmas. Part of my project for PHYS3051

## Running the code
### Download
To download the code, clone this repository to your desired location. No external dependancies are required.

### Compiling
First, make sure lua is compiled. To compile lua, cd into `inc/lua-5.3.5` and run `make PLATFORM` where `PLATFORM` is one of `aix` `bsd` `c89` `freebsd` `generic` `linux` `macosx` `mingw` `posix` `solaris`. If you are running windows, copy the pre-compiled binaries into `inc/lua/5.3.5/src` (I think, I haven't tried it).

To compile PIC, run `make` in the home directory of the project. `make clean` will remove object files, and `make cleaner` will remove the target executable.
 
 ### Executing
 
To execute the code run `../bin/PIC test.lua` from inside `PIC/exec`. This will run the test simulation. This file can be editted to suit your needs. For convience, `run.sh` will remove any output files, then start a new simulation using `test.lua`.
