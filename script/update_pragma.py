import os
import re

def replace_pragma_in_file(file_path):
    with open(file_path, 'r') as file:
        file_contents = file.read()
    
    new_contents, num_replacements = re.subn(r'pragma solidity (?:= )?0\.8\.\d+;', r'pragma solidity ^0.8.0;', file_contents)
    
    if num_replacements > 0:
        with open(file_path, 'w') as file:
            file.write(new_contents)
        print(f"Updated pragma in: {file_path}")
    else:
        print(f"No changes made in: {file_path}")

def replace_pragma_in_directory(directory_path):
    for root, _, files in os.walk(directory_path):
        for file_name in files:
            if file_name.endswith('.sol'):
                file_path = os.path.join(root, file_name)
                replace_pragma_in_file(file_path)

# The direction should be set to the path where you have the .sol file. 
# it is in ./output by default
directory_path = './output'
replace_pragma_in_directory(directory_path)
