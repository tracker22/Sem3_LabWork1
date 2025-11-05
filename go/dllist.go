package main

import (
	"fmt"
	"os"
	"strings"
)

type DLLNode struct {
	val  string
	next *DLLNode
	prev *DLLNode
}

type DLList struct {
	nil  *DLLNode
	size int
}

func NewDLList() *DLList {
	nilNode := &DLLNode{}
	nilNode.next = nilNode
	nilNode.prev = nilNode
	return &DLList{
		nil:  nilNode,
		size: 0,
	}
}

func isEmptyDL(ls *DLList) bool {
	return ls.nil.next == ls.nil
}

func findIndex(ls *DLList, key string) int {
	current := ls.nil.next
	index := 0
	for current != ls.nil && current.val != key {
		current = current.next
		index++
	}
	if current != ls.nil {
		return index
	}
	return -1
}

func searchKey(ls *DLList, key string) *DLLNode {
	current := ls.nil.next
	for current != ls.nil && current.val != key {
		current = current.next
	}
	if current != ls.nil {
		return current
	}
	return nil
}

func searchIndex(ls *DLList, index int) *DLLNode {
	if index >= ls.size || index < 0 {
		return nil
	}
	count := 0
	current := ls.nil.next
	for count != index {
		current = current.next
		count++
	}
	return current
}

func pushFront(ls *DLList, key string) {
	newNode := &DLLNode{
		val:  key,
		next: ls.nil.next,
		prev: ls.nil,
	}
	ls.nil.next.prev = newNode
	ls.nil.next = newNode
	ls.size++
}

func push_Back(ls *DLList, key string) {
	newNode := &DLLNode{
		val:  key,
		next: ls.nil,
		prev: ls.nil.prev,
	}
	ls.nil.prev.next = newNode
	ls.nil.prev = newNode
	ls.size++
}

func popBack(ls *DLList) {
	if isEmptyDL(ls) {
		return
	}
	temp := ls.nil.prev
	temp.prev.next = ls.nil
	ls.nil.prev = temp.prev
	_ = temp // Используем переменную
	ls.size--
}

func popFront(ls *DLList) {
	if isEmptyDL(ls) {
		return
	}
	temp := ls.nil.next
	temp.next.prev = ls.nil
	ls.nil.next = temp.next
	_ = temp // Используем переменную
	ls.size--
}

func insertAfter(ls *DLList, index int, key string) {
	if index < 0 || index > ls.size-1 {
		return
	}
	current := searchIndex(ls, index)
	newNode := &DLLNode{
		val:  key,
		next: current.next,
		prev: current,
	}
	current.next.prev = newNode
	current.next = newNode
	ls.size++
}

func insertBefore(ls *DLList, index int, key string) {
	if index < 0 || index > ls.size-1 {
		return
	}
	current := searchIndex(ls, index)
	newNode := &DLLNode{
		val:  key,
		next: current,
		prev: current.prev,
	}
	current.prev.next = newNode
	current.prev = newNode
	ls.size++
}

func removeNode(delNode *DLLNode) {
	if delNode == nil {
		return
	}
	delNode.prev.next = delNode.next
	delNode.next.prev = delNode.prev
}

func removeKey(ls *DLList, key string) {
	delNode := searchKey(ls, key)
	if delNode != nil {
		removeNode(delNode)
		ls.size--
	}
}

func removeAfter(ls *DLList, index int) {
	if index >= 0 && index < ls.size-1 {
		removeNode(searchIndex(ls, index+1))
		ls.size--
	}
}

func removeBefore(ls *DLList, index int) {
	if index > 0 && index < ls.size {
		removeNode(searchIndex(ls, index-1))
		ls.size--
	}
}

func printDL(ls *DLList) {
	current := ls.nil.next
	for current != ls.nil {
		fmt.Print(current.val, " ")
		current = current.next
	}
	fmt.Println()
}

func reversePrint(ls *DLList) {
	current := ls.nil.prev
	for current != ls.nil {
		fmt.Print(current.val, " ")
		current = current.prev
	}
	fmt.Println()
}

func saveToFileDL(ls *DLList, filename string) {
	file, err := os.Create(filename)
	if err != nil {
		fmt.Println("Error opening file for writing:", err)
		return
	}
	defer file.Close()

	current := ls.nil.next
	for current != ls.nil {
		_, err := file.WriteString(current.val + "\n")
		if err != nil {
			fmt.Println("Error writing to file:", err)
			return
		}
		current = current.next
	}
}

func loadFromFileDL(ls *DLList, filename string) {
	content, err := os.ReadFile(filename)
	if err != nil {
		fmt.Println("Error opening file for reading:", err)
		return
	}

	clearDL(ls)
	lines := strings.Split(string(content), "\n")
	for _, line := range lines {
		if line != "" {
			push_Back(ls, line)
		}
	}
}

func clearDL(ls *DLList) {
	for !isEmptyDL(ls) {
		popFront(ls)
	}
}
