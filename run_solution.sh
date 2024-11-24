#!/bin/bash

# Run the golang solution for the given year and day.

if [ "$#" -ne 2 ]; then
  echo "Usage: $0 <year> <day>"
  exit 1
fi

YEAR=$1
DAY=$2

DAY_DIR="./src/advent_of_code/go/$YEAR/day$(printf "%02d" $DAY)"

if [ ! -d "$DAY_DIR" ]; then
  echo "Solution for year $YEAR, day $DAY not found."
  exit 1
fi

cd "$DAY_DIR" || exit
go run main.go
