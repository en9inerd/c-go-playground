package main

import (
	"advent-of-code/fileutils"
	"fmt"
	"math"
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

// Your puzzle answer was 141.

// The first half of this puzzle is complete! It provides one gold star: *
// --- Part Two ---

// The next year, just to show off, Santa decides to take the route with the longest distance instead.

// He can still start and end at any two (different) locations he wants, and he still must visit each location exactly once.

// For example, given the distances above, the longest route would be 982 via (for example) Dublin -> London -> Belfast.

// What is the distance of the longest route?

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

	distances := make(map[string]map[string]int)
	for _, edge := range edges {
		if _, ok := distances[edge.From]; !ok {
			distances[edge.From] = make(map[string]int)
		}
		distances[edge.From][edge.To] = edge.Distance

		if _, ok := distances[edge.To]; !ok {
			distances[edge.To] = make(map[string]int)
		}
		distances[edge.To][edge.From] = edge.Distance
	}

	// Extract unique cities
	cities := make([]string, 0, len(distances))
	for city := range distances {
		cities = append(cities, city)
	}

	// Generate all permutations of the cities
	var allRoutes [][]string

	genPerms(cities, 0, &allRoutes)

	// shortestDistance := math.MaxInt
	// for _, route := range allRoutes {
	// 	routeDistance := calcRouteDistance(route, &distances)
	// 	if routeDistance < shortestDistance {
	// 		shortestDistance = routeDistance
	// 	}
	// }

	longestDistance := math.MinInt
	for _, route := range allRoutes {
		routeDistance := calcRouteDistance(route, &distances)
		if routeDistance > longestDistance {
			longestDistance = routeDistance
		}
	}

	// fmt.Printf("The shortest distance is %d\n", shortestDistance)
	fmt.Printf("The longest distance is %d\n", longestDistance)
}

// Helper to generate permutations
func genPerms(arr []string, start int, result *[][]string) {
	if start == len(arr)-1 {
		perm := make([]string, len(arr))
		copy(perm, arr)
		*result = append(*result, perm)
		return
	}

	for i := start; i < len(arr); i++ {
		arr[start], arr[i] = arr[i], arr[start]
		genPerms(arr, start+1, result)
		arr[start], arr[i] = arr[i], arr[start] // Backtrack
	}
}

// Helper to calculate total distance of route
func calcRouteDistance(route []string, distances *map[string]map[string]int) int {
	totalDistance := 0
	for i := 0; i < len(route)-1; i++ {
		totalDistance += (*distances)[route[i]][route[i+1]]
	}
	return totalDistance
}
