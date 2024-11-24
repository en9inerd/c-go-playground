package main

import (
	"advent-of-code/fileutils"
	"fmt"
)

// --- Day 9: All in a Single Night ---

// Every year, Santa manages to deliver all of his presents in a single night.

// This year, however, he has some new locations to visit; his elves have provided him the distances between every pair of locations. He can start and end at any two (different) locations he wants, but he must visit each location exactly once. What is the shortest distance he can travel to achieve this?

// For example, given the following distances:

// London to Dublin = 464
// London to Belfast = 518
// Dublin to Belfast = 141

// The possible routes are therefore:

// Dublin -> London -> Belfast = 982
// London -> Dublin -> Belfast = 605
// London -> Belfast -> Dublin = 659
// Dublin -> Belfast -> London = 659
// Belfast -> Dublin -> London = 605
// Belfast -> London -> Dublin = 982

// The shortest of these is London -> Dublin -> Belfast = 605, and so the answer is 605 in this example.

// What is the distance of the shortest route?

type Edge struct {
	From     string
	To       string
	Distance int
}

func main() {
	it, err := fileutils.NewLineIterator("2015/day9/input.txt")
	if err != nil {
		fmt.Println(err)
		return
	}
	defer func() {
		if err := it.Close(); err != nil {
			fmt.Println(err)
		}
	}()

	edges := make([]Edge, 0, 50)
	for {
		line, ok := it.Next()
		if !ok {
			break
		}

		edge := Edge{}
		fmt.Sscanf(line, "%s to %s = %d", &edge.From, &edge.To, &edge.Distance)

		edges = append(edges, edge)
	}

	cities := make(map[string]bool)
	for _, edge := range edges {
		cities[edge.From] = false
		cities[edge.To] = false
	}

}
