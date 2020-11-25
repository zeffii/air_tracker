import os
import pathlib

def print_shifted(data, offset=0):
    num_rows = len(data)
    for i in range(num_rows):
        print(data[(i+offset)%num_rows])

p = pathlib.Path(__file__).parent.absolute()
p = os.path.dirname(p)
new_append_path = ["res", "pattern_data_1.air"]

pattern_path = os.path.join(p, *new_append_path)

pattern_data = []
with open(pattern_path) as f:
    content = f.readlines()
    pattern_data = [x.strip() for x in content[1:]]

print_shifted(pattern_data, 16)
