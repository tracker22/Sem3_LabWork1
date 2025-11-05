package main

import (
	"fmt"
	"os"
	"strings"
)

type Node struct {
	val  string
	next *Node
	prev *Node
}

type Queue struct {
	head *Node
	tail *Node
}

func NewQueue() *Queue {
	return &Queue{
		head: nil,
		tail: nil,
	}
}

func isEmptyQueue(q *Queue) bool {
	return q.head == nil
}

func enqueue(q *Queue, key string) {
	newNode := &Node{
		val: key,
	}
	if isEmptyQueue(q) {
		q.head = newNode
		q.tail = newNode
	} else {
		newNode.prev = q.tail
		q.tail.next = newNode
		q.tail = newNode
	}
}

func dequeue(q *Queue) {
	if isEmptyQueue(q) {
		return
	}
	if q.tail == q.head {
		q.head = nil
		q.tail = nil
	} else {
		temp := q.head
		q.head = q.head.next
		q.head.prev = nil
		_ = temp // Используем переменную
	}
}

func saveToFileQueue(q *Queue, filename string) {
	file, err := os.Create(filename)
	if err != nil {
		fmt.Println("Error opening file for writing:", err)
		return
	}
	defer file.Close()

	current := q.head
	for current != nil {
		_, err := file.WriteString(current.val + "\n")
		if err != nil {
			fmt.Println("Error writing to file:", err)
			return
		}
		current = current.next
	}
}

func loadFromFileQueue(q *Queue, filename string) {
	content, err := os.ReadFile(filename)
	if err != nil {
		fmt.Println("Error opening file for reading:", err)
		return
	}

	clearQueue(q)
	lines := strings.Split(string(content), "\n")
	for _, line := range lines {
		if line != "" {
			enqueue(q, line)
		}
	}
}

func clearQueue(q *Queue) {
	for !isEmptyQueue(q) {
		dequeue(q)
	}
}

func printQueue(q *Queue) string {
	var result strings.Builder
	current := q.head
	for current != nil {
		result.WriteString(current.val)
		result.WriteString(" ")
		current = current.next
	}
	return result.String()
}
