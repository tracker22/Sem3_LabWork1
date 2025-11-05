package main

import (
	"fmt"
	"os"
	"strings"
)

type StackNode struct {
	val  string
	next *StackNode
}

type Stack struct {
	top *StackNode
}

func NewStack() *Stack {
	return &Stack{
		top: nil,
	}
}

func isEmptyStack(s *Stack) bool {
	return s.top == nil
}

func pop(s *Stack) {
	if isEmptyStack(s) {
		return
	}
	temp := s.top
	s.top = s.top.next
	_ = temp // Используем переменную, чтобы избежать ошибки
}

func push(s *Stack, key string) {
	newNode := &StackNode{
		val:  key,
		next: s.top,
	}
	s.top = newNode
}

func saveToFileStack(s *Stack, filename string) {
	file, err := os.Create(filename)
	if err != nil {
		fmt.Println("Error opening file for writing:", err)
		return
	}
	defer file.Close()

	// Создаем временный стек для реверса
	temp := NewStack()
	current := s.top

	for current != nil {
		newNode := &StackNode{
			val:  current.val,
			next: temp.top,
		}
		temp.top = newNode
		current = current.next
	}

	// Сохраняем временный стек (он уже в правильном порядке)
	current = temp.top
	for current != nil {
		_, err := file.WriteString(current.val + "\n")
		if err != nil {
			fmt.Println("Error writing to file:", err)
			return
		}
		current = current.next
	}

	// Очищаем временный стек (в Go это не обязательно, но для чистоты)
	for temp.top != nil {
		tempNode := temp.top
		temp.top = temp.top.next
		_ = tempNode // Используем переменную
	}
}

func loadFromFileStack(s *Stack, filename string) {
	content, err := os.ReadFile(filename)
	if err != nil {
		return
	}

	clearStack(s)
	lines := strings.Split(string(content), "\n")
	for _, line := range lines {
		if line != "" {
			push(s, line)
		}
	}
}

func clearStack(s *Stack) {
	for !isEmptyStack(s) {
		pop(s)
	}
}

func printStack(s *Stack) string {
	var result strings.Builder
	current := s.top
	for current != nil {
		result.WriteString(current.val)
		result.WriteString(" ")
		current = current.next
	}
	return result.String()
}
