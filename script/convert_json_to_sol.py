import os
import json

def convert_json_to_sol(json_dir):
    for filename in os.listdir(json_dir):
        if filename.endswith('.json'):
            json_path = os.path.join(json_dir, filename)
            sol_path = os.path.join(json_dir, filename.replace('.json', '.sol'))
            
            with open(json_path, 'r') as json_file:
                data = json.load(json_file)
                source_code = data.get('SourceCode', '')
                
                with open(sol_path, 'w') as sol_file:
                    sol_file.write(source_code)
                    
            print(f'Converted {filename} to {filename.replace(".json", ".sol")}')

# Replace 'your_json_directory' with the path to your directory containing the JSON files
convert_json_to_sol('your_json_directory/output')