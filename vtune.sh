#!/bin/bash

# Get the list of available advisor modules
vtune_module=$(module avail | grep vtune)

available_modules = $(module )

#list of the modules 
echo "available modules : "
module avail | grep vtune

# Ask the user for the VTune module name
echo "Enter the name of the VTune module: "
read vtune_module

# Load the VTune module
module load $vtune_module

# Ask the user for the absolute path to the project directory
echo "Enter the absolute path to the project directory: "
read project_dir

# Check if the project directory exists
if [! -d "$project_dir" ]; then
  echo "Error: Project directory does not exist."
  exit 1
fi

# Ask the user for the absolute path to the executable file
echo "Enter the absolute path to the executable file: "
read executable_file

# Check if the executable file exists
if [! -f "$executable_file" ]; then
  echo "Error: Executable file does not exist."
  exit 1
fi

# Create the VTune command
vtune_cmd="vtune --collect=hotspot --result-dir=$project_dir/report./$executable_file"

# Run the VTune command
echo "Running VTune command: $vtune_cmd"
eval $vtune_cmd

# Open the generated report using vtune-gui
echo "Opening report in vtune-gui..."
vtune-gui $project_dir/report