#Parallel implementation of kNN using MPI#

<p>There are 3 versions of kNN implemented:<br/>
    1) Serial version with C++<br/>
    2) Version 1 with C++ and MPI<br/>
    3) Version 2 with C++ and MPI<br/>
</p>

<p>The training set: https://archive.ics.uci.edu/ml/datasets/Skin+Segmentation# <br/>
It has 245057 instances. The test set has 100 instances, random generated that haven't occurred in the training set.
</p>

<b>Version 1 with C++ and MPI</b>
<p>This version should be started with number of processors equal to the number of testing instances.
Each processor takes one of the testing instance, runs the algorithm and make a decision by itself.
Experiments show that this version is more efficient that the 2nd one.</p>

<b>Version 2 with C++ and MPI</b>
<p>In this version, each processor takes part in the solving the algorithm for each testing instance. 
The whole training set is split on (almost) equal parts (manually setting the boundaries) for each processor.
Then, each processor runs the algorithm for its part of the set, and returns the result to the master processor (default 0).
Master processor (default 0) does some more calculations to find the class for each test instance, and finally, prints out
the class value for each instance.
</p>

<p>To compile: mpicxx -o (*name of exec*) main.cpp -std=c++11<br/>
To run the exec: mpirun -np (*num of processors*) (*name of exec*)</p>


<b>Experiment with 100 test instances (serial / version 1 / version2):</b>
![screen_shot_1](http://image.prntscr.com/image/94da8a0f13dc47e686112c488908dfff.png)

<p>And that's it ! <br/> Hope you liked it :)</p>
