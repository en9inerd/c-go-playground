package fileutils

import (
	"bufio"
	"fmt"
	"os"
	"path/filepath"
)

type LineIterator struct {
	file    *os.File
	scanner *bufio.Scanner
}

// ReadInputFile reads the input file from a given path
func ReadInputFile(filename string) (string, error) {
	inputPath := filepath.Join(filename)
	data, err := os.ReadFile(inputPath)
	if err != nil {
		return "", fmt.Errorf("failed to read input file: %v", err)
	}
	return string(data), nil
}

// NewLineIterator creates a new LineIterator for a given file
func NewLineIterator(filename string) (*LineIterator, error) {
	file, err := os.Open(filename)
	if err != nil {
		return nil, fmt.Errorf("failed to open file: %v", err)
	}
	scanner := bufio.NewScanner(file)
	return &LineIterator{file, scanner}, nil
}

// Next returns the next line in the file
func (li *LineIterator) Next() (string, bool) {
	if !li.scanner.Scan() {
		return "", false
	}
	return li.scanner.Text(), true
}

// Close closes the file
func (li *LineIterator) Close() error {
	return li.file.Close()
}
