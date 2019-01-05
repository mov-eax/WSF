#!/bin/bash
SCRIPTPATH=$(dirname "$BASH_SOURCE")
echo "$SCRIPTPATH"

cd build

lcov --directory . --capture --output-file tests.coverage
bash <(curl -s https://codecov.io/bash) -t 00eef072-649c-40ef-aab6-e40310b6ad46
