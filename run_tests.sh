#!/bin/bash

#fileName = $(ls test | grep '^impDone');
#echo $(fileName);
#for name in $a
#  execv ./target/compiler < name
#  python translated.py
#done

for x in test/*.test; do 
  ./target/compiler < $x 2> /dev/null
  echo "Running $x"
  echo ""
  python translated.py
  echo ""
done