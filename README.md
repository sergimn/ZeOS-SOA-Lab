# OS Implementation for SOA

This repo will consist on the implementation of ZeOS, a OS that is studied at 
the [SOA Subject in FIB](http://docencia.ac.upc.edu/FIB/grau/SOA/).

The main intention of this repo is to document all the steps needed to follow the [Lab Guide](http://docencia.ac.upc.edu/FIB/grau/SOA/documents/Zeos.pdf) 
([permalink](https://web.archive.org/web/20200216144547/http://docencia.ac.upc.edu/FIB/grau/SOA/documents/Zeos.pdf)) so other students (myself included)
do not struggle so much knowing which modifications serve what purpose.

### Development and QA
Altough the Makefile can compile the code, there would be a need to put the `zeos.bin` file generated inside a disk
so we can boot it. Since this is a very costly procedure, we can use one of the following commands to run our OS to
observe what we've done
```commandline
make emul       # Simple execution
make gdb        # GNU gdb attached execution
make emuldbg    # Bochs debugger attached execution
```
#### Dependencies
_Instructions here are extracted from the official Lab Guide_
* Install the following packages:
```commandline
sudo apt install build-essential bin86 libx11-dev libgtk2.0-dev libreadline-dev
```
* Install `bochs` version 2.6.7 two times with the following different flags:
```commandline
./configure --enable-gdb-stub --with-x --prefix=/opt/bochs_gdb # For GNU gdb debugger
./configure --enable-debug --enable-disasm --enable-x86-debugger --enable-readline --with-x --prefix=/opt/bochs # For Bochs debugger
```

#### Code quality
Since the base code (see c4a03ead876087a5837726ec4ea2b4363571eb0d ) was provided with a bad (or nonexistent) code style 
and I'm no master at identifying what characteristics this style has, I have decided that I will not use any code style
format utlity because the few that I tried, [Indent](https://www.gnu.org/software/indent/manual/) and 
[Astyle](http://astyle.sourceforge.net/astyle.html), just scrambled the code in a way that I didn't really like and I
feared assembly instructions could be then misinterpreted by the compiler.

I'm no master here so if you find a good solution to my code style problems please submit a merge request.

Nonetheless, I try to style my code close to what I was provided with.

#### Commit messages and merges
Because this repo is intended to keep track of the modifications needed to accomplish the tasks provided in the Lab Guide 
(see above), the commits and the commit messages should be explainatory enough so anyone coursing the subject gets what's
being done and for what purpose. Therefore, commits will try to show step by step what is needed to accomplish a bigger
task, and when that task is fulfilled, the feature branch will be merged in to the main (not master, see below) branch

#### Submitting work
This project tries to use [gitflow](https://nvie.com/posts/a-successful-git-branching-model/) and merge requests. However,
since this project will never (God, I hope so) be in a real production environment, the model will be slightly modified,
but the feature and develop branches philosophy stays the same. 

The main branch is deveop

#### Tagging
I will tag the last commit before any official delivery so everything it's easier to track
