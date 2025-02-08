package main

import (
	"fmt"
	"strings"
)

const (
	alphMin = 97
	alphMax = 122
)

func main() {
	var input, result string

	fmt.Print("Puzzle input: ")
	fmt.Scan(&input)

	for password := range passwordInc(input) {
		result = password
	}

	fmt.Println("Next password: ", result)

	for password := range passwordInc(result) {
		result = password
	}

	fmt.Println("Next password: ", result)
}

func passwordInc(input string) <-chan string {
	c := make(chan string)

	go func() {
		defer close(c)
		bytes := []byte(input)

		incrementPassword(bytes)

		for {
			if validate(bytes) {
				c <- string(bytes)
				break
			}

			incrementPassword(bytes)
		}
	}()

	return c
}

func incrementPassword(bytes []byte) {
	carry := true
	for i := len(bytes) - 1; i >= 0 && carry; i-- {
		if bytes[i] < alphMax {
			bytes[i]++
			carry = false

			if bytes[i] == 'i' || bytes[i] == 'o' || bytes[i] == 'l' {
				bytes[i]++
			}
		} else {
			bytes[i] = alphMin
		}
	}
}

func validate(str []byte) bool {
	if checkDisallowedLetter(str) &&
		checkThreeLetters(str) && checkTwoPairsOfLetters(str) {
		return true
	} else {
		return false
	}
}

func checkThreeLetters(str []byte) bool {
	for i, ch := range str {
		if len(str)-1-i >= 3 && str[i+1] == ch+1 && str[i+2] == ch+2 {
			return true
		}
	}
	return false
}

func checkDisallowedLetter(str []byte) bool {
	if strings.Contains(string(str), "i") || strings.Contains(string(str), "o") ||
		strings.Contains(string(str), "l") {
		return false
	}
	return true
}

func checkTwoPairsOfLetters(str []byte) bool {
	pairsMap := make(map[string]struct{})
	pairs := 0
	for i := 0; i < len(str)-1; i++ {
		if str[i] == str[i+1] {
			pair := string(str[i : i+2])

			if _, exists := pairsMap[pair]; !exists {
				pairsMap[pair] = struct{}{}
				pairs++
			}

			i++
		}
	}
	return pairs >= 2
}
