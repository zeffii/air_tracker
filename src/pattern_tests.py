import os
import pathlib

def print_shifted(data, offset=0):
    for l in data:
        print(l)

p = pathlib.Path(__file__).parent.absolute()
p = os.path.dirname(p)
new_append_path = ["res", "pattern_data_1.air"]

pattern_path = os.path.join(p, *new_append_path)

pattern_data = []
with open(pattern_path) as f:
    content = f.readlines()
    pattern_data = [x.strip() for x in content[1:]]

print_shifted(pattern_data, 0)
