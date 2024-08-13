#!/bin/bash

# Ask for the path of the executable file
read -p "Enter the name of the source file: " source_file
read -p "Enter the desired executable file name: " executable_name

# Compile the source file
gcc -fopenacc -o "$executable_name" "$source_file" -lm

# Load HPCToolkit
source /home/apps/spack/share/spack/setup-env.sh
spack load hpctoolkit

# Run HPCToolkit commands
measurement_dir="hpctoolkit-$executable_name-measurements"
database_dir="hpctoolkit-$executable_name-database"

# # Step 2: set unlimited stack size
# ulimit -s unlimited



# Step 1: measure an execution of the executable
hpcrun -e REALTIME -t "./$executable_name"

# Step 2: set unlimited stack size
ulimit -s unlimited

# Step 3: measure an execution of the executable again
hpcrun -e REALTIME -t "./$executable_name"

# Step 4: compute program structure information
hpcstruct "$measurement_dir"

# Step 5: combine measurement data with program structure information
hpcprof "$measurement_dir"

# Step 6: view the kernel-level profile and trace data
hpcviewer "$database_dir"