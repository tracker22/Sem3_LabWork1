package main

import (
	"fmt"
	"os"
	"strings"
)

type FLNode struct {
	val  string
	next *FLNode
}

type FList struct {
	head *FLNode
	size int
}

func NewFList() *FList {
	return &FList{
		head: nil,
		size: 0,
	}
}

func searchKeyFL(ls *FList, key string) int {
	current := ls.head
	index := 0
	for current != nil && current.val != key {
		current = current.next
		index++
	}
	if current == nil {
		return -1
	}
	return index
}

func searchIndexFL(ls *FList, index int) *FLNode {
	if index >= ls.size || index < 0 {
		return nil
	}
	count := 0
	current := ls.head
	for count != index {
		current = current.next
		count++
	}
	return current
}

func insertFL(prev *FLNode, key string) {
	newNode := &FLNode{
		val:  key,
		next: prev.next,
	}
	prev.next = newNode
}

func pushFrontFL(ls *FList, key string) {
	newNode := &FLNode{
		val: key,
	}
	if ls.head != nil {
		newNode.next = ls.head
	}
	ls.head = newNode
	ls.size++
}

func pushBackFL(ls *FList, key string) {
	if ls.size == 0 {
		pushFrontFL(ls, key)
	} else {
		prev := searchIndexFL(ls, ls.size-1)
		insertFL(prev, key)
		ls.size++
	}
}

func insertAfterFL(ls *FList, index int, key string) {
	if index < 0 || index > ls.size-1 {
		return
	}
	if index == ls.size-1 {
		pushBackFL(ls, key)
	} else {
		prev := searchIndexFL(ls, index)
		insertFL(prev, key)
		ls.size++
	}
}

func insertBeforeFL(ls *FList, index int, key string) {
	if index < 0 || index > ls.size-1 {
		return
	}
	if index == 0 {
		pushFrontFL(ls, key)
	} else {
		prev := searchIndexFL(ls, index-1)
		insertFL(prev, key)
		ls.size++
	}
}

func popFrontFL(ls *FList) {
	if ls.size == 0 {
		return
	}
	temp := ls.head
	ls.head = ls.head.next
	_ = temp // Используем переменную
	ls.size--
}

func popBackFL(ls *FList) {
	if ls.size == 0 {
		return
	}
	if ls.size == 1 {
		popFrontFL(ls)
	} else {
		prev := searchIndexFL(ls, ls.size-2)
		temp := prev.next
		prev.next = nil
		_ = temp // Используем переменную
		ls.size--
	}
}

func removeIndexFL(ls *FList, index int) {
	if ls.size == 0 || index < 0 || index >= ls.size {
		return
	}

	if index == 0 {
		popFrontFL(ls)
	} else {
		prev := searchIndexFL(ls, index-1)
		temp := prev.next
		prev.next = temp.next
		_ = temp // Используем переменную
		ls.size--
	}
}

func removeBeforeFL(ls *FList, index int) {
	if index > 0 && index < ls.size {
		removeIndexFL(ls, index-1)
	}
}

func removeAfterFL(ls *FList, index int) {
	if index >= 0 && index < ls.size-1 {
		removeIndexFL(ls, index+1)
	}
}

func removeKeyFL(ls *FList, key string) {
	index := searchKeyFL(ls, key)
	if index != -1 {
		removeIndexFL(ls, index)
	}
}

func printFL(ls *FList) {
	current := ls.head
	for current != nil {
		fmt.Print(current.val, " ")
		current = current.next
	}
	fmt.Println()
}

func saveToFileFL(ls *FList, filename string) {
	file, err := os.Create(filename)
	if err != nil {
		fmt.Println("Error opening file for writing:", err)
		return
	}
	defer file.Close()

	current := ls.head
	for current != nil {
		_, err := file.WriteString(current.val + "\n")
		if err != nil {
			fmt.Println("Error writing to file:", err)
			return
		}
		current = current.next
	}
}

func loadFromFileFL(ls *FList, filename string) {
	content, err := os.ReadFile(filename)
	if err != nil {
		return
	}

	clearFL(ls)
	lines := strings.Split(string(content), "\n")
	for _, line := range lines {
		if line != "" {
			pushBackFL(ls, line)
		}
	}
}

func clearFL(ls *FList) {
	for ls.size > 0 {
		popFrontFL(ls)
	}
}
