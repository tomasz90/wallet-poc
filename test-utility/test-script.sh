#!/bin/bash

current_path=$(pwd)

mv "$current_path/src/main.cpp" "$current_path/test-utility/main.cpp"

pio test -e test --project-dir "$current_path" -v

mv "$current_path/test-utility/main.cpp" "$current_path/src/main.cpp"
