#!/bin/bash

for x in test/*.test; do 
  ./target/compiler < $x
  echo "Running $x"
  echo ""
  python3 out
  echo ""
done