#!/bin/bash


# Find all .c files in the current directory and its subdirectories excluding libft/src
c_files=$(find . -type f -name "*.c" ! -path "./libft/src/*")

# Initialize variables for sum and unique files
sum_functions=0
sum_lines=0
unique_files=0
prev_folder=""

# Print the header of the table
echo -e "\n\e[1;34mFunctions\tLines\tFilename\t\t\tFolder\e[0m"

# Loop through each .c file
for file in $c_files; do
    # Extract filename (only the filename without the path)
    filename=$(basename "$file")

    # Extract folder name
    folder=$(dirname "$file" | sed 's|^\./||')

    # Count lines in the file
    lines=$(wc -l < "$file")

    # Count functions in the file
    functions=$(grep "^{" "$file" | wc -l)

    # Update sum variables
    sum_functions=$((sum_functions + functions))
    sum_lines=$((sum_lines + lines))

    # Track unique files
    ((unique_files++))

    # Check if folder has changed
    if [ "$folder" != "$prev_folder" ]; then
        # Add an empty line
        echo
        prev_folder="$folder"
    fi

    # Set color based on the condition
    if [ "$functions" -gt 5 ]; then
        color_code="\e[31m"  # Red color
    else
        color_code="\e[0m"   # Reset color
    fi

    # Print the table row with color
    printf "${color_code}  %s\t\t%s\t%-25s\t%s\e[0m\n" "$functions" "$lines" "$filename" "$folder"
done

# Print the summary line in orange and bold
echo -e "\n\e[1;33m  $sum_functions\t\t$sum_lines\t$unique_files different files\e[0m"
