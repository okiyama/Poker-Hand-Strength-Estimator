Poker-Hand-Strength-Estimator
=============================

A parallelized poker hand simulator to determine the strength of a poker hand that uses monte carlo estimation and OpenMPI

The basic idea is to run millions of poker hands per minute in parallel, determining which hand wins when choosing
random hands to play against a given chosen hand. To do this, I wrote a poker hand simulator in C and then parallelized
the operation using OpenMPI.

I tested out using Derived data types to pass the data around as well, but found little success.

The serial version should work just fine on your computer, and it may even parallelize if you have multiple cores.

You must have mpicc installed, on Ubuntu you can get this with 
    sudo apt-get install libopenmpi-dev
    
After that, you can just make with "make basic" then run with mpirun pokerBasic.
To run this properly in parallel, take a look at the various .sh files included. They will show you a bit about how
to do this with Torque on a multi-node super computer.

This code was tested on the Union College cluster and it works on up to 64 nodes.
