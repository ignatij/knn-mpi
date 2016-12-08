#Parallel implementation of kNN using MPI#

<p>There are 3 versions of kNN implemented:
    *Serial version with C++
    *Version 1 with C++ and MPI
    *Version 2 with C++ and MPI
</p>

###Version 1 with C++ and MPI###
<p>This version should be started with number of processors equal to the number of testing instances.
Each processor takes one of the testing instance, runs the algorithm and make a decision by itself.
Experiments show that this version is more efficient that the 2nd one.</p>

###Version 2 with C++ and MPI###
<p>In this version, each processor takes part in the solving the algorithm for each testing instance. 
The whole training set is split on (almost) equal parts (manually setting the boundaries) for each processor.
Then, each processor runs the algorithm for its part of the set, and returns the result to the master processor (default 0).
Master processor (default 0) does some more calculations to find the class for each test instance, and finally, prints out
the class value for each instance.
</p>

To compile: mpicxx -o (*name of exec*) main.cpp -std=c++11
To run the exec: mpirun -np (*num of processors*) (*name of exec*)


###Experiment with 100 test instances (serial / version 1 / version2):###
![screen_shot_1](http://prnt.sc/dgzcq1)

