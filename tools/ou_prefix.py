#!/usr/bin/env python3

import re
import sys


types = [
        "int8_t",
        "int16_t",
        "int32_t",
        "int64_t",
        "uint8_t",
        "uint16_t",
        "uint32_t",
        "uint64_t",
        "size_t",
]

functions = [
]

for filename in sys.argv[1:]:
    with open(filename, "r") as f:
        contents = f.read()

    pattern = '([^_a-zA-Z0-9]|^)(%s)([^_a-zA-Z0-9]|$)' % "|".join(re.escape(x) for x in types + functions)
    contents = re.sub(pattern, r'\1ou_\2\3', contents)

    with open(filename, "w") as f:
        f.write(contents)
