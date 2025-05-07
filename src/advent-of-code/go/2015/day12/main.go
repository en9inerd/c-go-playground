package main

import (
	"advent-of-code/fileutils"
	"encoding/json"
	"fmt"
	"log"
)

func main() {
	jsonText, err := fileutils.ReadInputFile("input.txt")
	if err != nil {
		log.Fatalln("Error reading file:", err)
	}

	sum := 0
	var parsed any

	err = json.Unmarshal([]byte(jsonText), &parsed)
	if err != nil {
		log.Fatalln("Error parsing JSON:", err)
	}

	sum = sumJSON(parsed, false)
	fmt.Println("Sum of all numbers (part 1):", sum)

	sum = sumJSON(parsed, true)
	fmt.Println("Sum of all numbers ignoring red (part 2):", sum)
}

func sumJSON(data any, ignoreRed bool) int {
	switch val := data.(type) {
	case float64:
		return int(val)
	case int:
		return val
	case []any:
		sum := 0
		for _, item := range val {
			sum += sumJSON(item, ignoreRed)
		}
		return sum
	case map[string]any:
		sum := 0
		for _, v := range val {
			if ignoreRed {
				if s, ok := v.(string); ok && s == "red" {
					return 0
				}
			}
			sum += sumJSON(v, ignoreRed)
		}
		return sum
	default:
		return 0
	}
}
