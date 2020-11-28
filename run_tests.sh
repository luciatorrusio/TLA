#!/bin/bash

for x in test/*.test; do 
  ./target/compiler < $x 2> /dev/null
  echo "Running $x"
  echo ""
  python3 out
  echo ""
done