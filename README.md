# PIC
PIC uses the Particle In Cell method to simulate kinetic plasmas. Part of my project for PHYS3051

## Running the code
### Download
To download the code, clone this repository to your desired location. No external dependancies are required.

### Compiling
To compile, cd into PIC/exec, and edit the 4th line of make.sh to `make [platform]` where `[platform]` corresponds to the operating system you're using, and is one of the following:
  `"aix" "bsd" "c89" "freebsd" "generic" "linux" "macosx" "mingw" "posix" "solaris"`
  
 Note that this has only been tested on Ubuntu, if this doesn't work on your platform please let me know.
 
 ### Executing
 
To execute the code run `./PIC.ex test.lua`. This will run the test simulation. This file can be editted to suit your needs.
