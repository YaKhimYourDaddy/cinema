def renumber_showtimes(input_file, output_file):
    with open(input_file, 'r') as infile:
        lines = infile.readlines()
    
    updated_lines = []
    current_id = 1
    
    # First line is added as is without any changes
    updated_lines.append(lines[0])
    
    for line in lines[1:]:  # Start from the second line
        if line.strip():  # Check for non-empty lines
            parts = line.split('|')
            parts[0] = f"idShowtime{current_id:07}"  # Update idShowtime with padded number
            updated_lines.append('|'.join(parts))
            current_id += 1
    
    with open(output_file, 'w') as outfile:
        outfile.writelines(updated_lines)


# Usage
input_file = "Showtime.txt"
output_file = "Showtime.txt"
renumber_showtimes(input_file, output_file)
