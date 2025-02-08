package main

import (
	"fmt"
	"strconv"
	"strings"
)

func main() {
	var input string
	var num int

	fmt.Println("Provide sequence of digits: ")
	fmt.Scan(&input)

	fmt.Println("How many times to apply lookAndSay: ")
	fmt.Scanf("%d", &num)

	for i := 0; i < num; i++ {
		input = lookAndSay(input)
	}

	fmt.Println(len(input))
}

func lookAndSay(digits string) string {
	var builder strings.Builder
	count := 1
	for i := 0; i < len(digits); i++ {
		if i < len(digits)-1 && digits[i] == digits[i+1] {
			count++
		} else {
			builder.WriteString(strconv.Itoa(count) + string(digits[i]))
			count = 1
		}
	}

	return builder.String()
}
