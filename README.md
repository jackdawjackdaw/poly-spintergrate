poly-spintertgrate {#mainpage}
=========
C.Coleman-Smith (cec24@phy.duke.edu) (code)
H.Haggard (all the hard bits)

Routines for integrating the classical spin dynamics of the pentahedron.

# Getting Started

## Requires:

* CMAKE (http://www.cmake.org/)
* A C Compiler

## Building & Installing

All of the src/*.mc files need to be preprocessed by Mathematica first. Make sure that you have the
appropriate symbols defined in your MM environment and then run splice on them. The helper function needed for
taking mathematica lists of spins and their components given as { J_{i,k}, ... } where i labels the spin and k
is the component is

    ToExportForm[thing_] :=  thing /.  {Subscript[J, i_, j_] -> Subscript[J, (i - 1)*3 + j]}   /. {Subscript[J, i_] -> J[[i]]}

Due to my inability to hold the evaluation of J[[i]] properly it's not possible to start the J arrays from
zero. Currently the C routines that pass J vectors around are all of length 13 and indexed from 1. 

Here is an example of splicing in the 54 equations of motion (in mathematica do)

    fileName = "/path/to/this/project/src/dynamics-eom-54.mc";
    Splice[fileName];
    
Now you can build the C code in the usual cmake way, from a terminal in the root directory of the project do

    mkdir build;
    cd build
    cmake ..
    make && make install

This will create all the project binaries and by default installs them into the project-root/bin folder. 

## Examples

Running `traj-54` with the input config `test-norm.txt` should produce stable and well behaved output for very
long times, although so far I've not tested it further than t=1000 with dt=0.01.

The input config `test-norm-bad.txt` seems to choke (probably due to a boundary crossing) at about t=5,
confirmed with dt = 0.01 and dt=0.0001.
