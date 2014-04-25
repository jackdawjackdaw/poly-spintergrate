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

## TimeStep Testing

The `test-dt.sh` script can be used to run the code with a variety of time steps, results for the
`test-norm.txt` input can be found in `dt-test`. Things seem to converge for dt < 1e-4

## comparison to other code

For the equifacial J=1 case, the input configurations (in the km variables)
    0.3 0.4 0.90 0.91
    0.39 0.49 0.72 0.52
are somewhat canonical, we can convert these into test configurations for the Jspin mode using the testtri.out program from the old project
    
    0.300000 0.400000 0.900000 0.910000 0.5950000000000000 -0.1268420441422706 0.9605031835769006 -0.9217923692713692 0.2432560099607408
    0.390000 0.490000 0.720000 0.520000 0.7408000000000000 -0.6424454075882373 0.7424881777579435 -0.9194442230709421 -0.3159278343080713

this output lists `q1, q2, p1, p2, n2z, n3y, n3z, n4y, n4z`, the jlists are then

    0  0  -1  0  0.803726  0.595  0.247679  -0.126842  0.960503  0.30187  -0.921792  0.243256
    0  0  -1  0  0.671726  0.7408  0.189671  -0.642445  0.742488  0.234119  -0.919444  -0.315928

the first of these is written to `test-norms-equi-1.dat`. A quick sanity check is to use the function
`hamPiecewise` in the MM notebook to obtain the volume and compare this against the output of `hamscan.out` in
the original project codebase. The reported volumes do indeed agree. 
    
    
