package main

import (
	"fmt"
	"os"
	"strings"
)

type Array struct {
	size  int
	value []string
}

func NewArray() *Array {
	return &Array{
		size:  0,
		value: make([]string, 0),
	}
}

func pushIndex(arr *Array, index int, key string) {
	newV := make([]string, arr.size+1)

	i := 0
	for i != index {
		newV[i] = arr.value[i]
		i++
	}

	newV[i] = key

	for i < arr.size {
		newV[i+1] = arr.value[i]
		i++
	}

	arr.value = newV
	arr.size++
}

func pushBack(arr *Array, key string) {
	arr.value = append(arr.value, key)
	arr.size++
}

func popIndex(arr *Array, index int) {
	if index >= arr.size {
		return
	}

	newV := make([]string, 0, arr.size-1)
	newV = append(newV, arr.value[:index]...)
	newV = append(newV, arr.value[index+1:]...)

	arr.value = newV
	arr.size--
}

func replace(arr *Array, index int, key string) {
	if index < 0 || index >= arr.size {
		return
	}
	arr.value[index] = key
}

func printArray(arr *Array) {
	fmt.Println(strings.Join(arr.value, " "))
}

func get(arr *Array, index int) string {
	if index < 0 || index >= arr.size {
		return "Out of range"
	}
	return arr.value[index]
}

func length(arr *Array) int {
	return arr.size
}

func saveToFileArray(arr *Array, filename string) {
	file, err := os.Create(filename)
	if err != nil {
		fmt.Println("Error opening file for writing:", err)
		return
	}
	defer file.Close()

	for _, val := range arr.value {
		_, err := file.WriteString(val + "\n")
		if err != nil {
			fmt.Println("Error writing to file:", err)
			return
		}
	}
}

func loadFromFileArray(arr *Array, filename string) {
	content, err := os.ReadFile(filename)
	if err != nil {
		fmt.Println("Error opening file for reading:", err)
		return
	}

	clearArray(arr)
	lines := strings.Split(string(content), "\n")
	for _, line := range lines {
		if line != "" {
			pushBack(arr, line)
		}
	}
}

func clearArray(arr *Array) {
	arr.value = make([]string, 0)
	arr.size = 0
}
