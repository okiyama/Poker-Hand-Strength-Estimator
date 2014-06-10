# Runs parallelized sorting network code.
# Author: Julian Jocque
#   
#   Request 2 processors 
#PBS -l procs=2
#
#   Request 3 and 1/2 hours of wall time
#PBS -l walltime=0:40:00
#
#   Request that regular output and terminal output go to the same file
#PBS -j oe
#
# Goto PBS working directory
cd $PBS_O_WORKDIR
#
echo "Job started on `hostname` at `date`"
mpirun ./pokerBasic 
echo "Job Ended at `date`"