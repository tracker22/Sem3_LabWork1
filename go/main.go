package main

import (
	"fmt"
	"os"
	"strconv"
	"strings"
)

func parseArguments(args []string) (string, string) {
	var filename, query string
	for i := 1; i < len(args); i++ {
		arg := args[i]
		if arg == "--file" && i+1 < len(args) {
			filename = args[i+1]
			i++
		} else if arg == "--query" && i+1 < len(args) {
			query = args[i+1]
			i++
		}
	}
	return filename, query
}

func parseQuery(query string) []string {
	cleanQuery := query
	if len(cleanQuery) > 0 && cleanQuery[0] == '\'' && cleanQuery[len(cleanQuery)-1] == '\'' {
		cleanQuery = cleanQuery[1 : len(cleanQuery)-1]
	}
	return strings.Fields(cleanQuery)
}

func fileExists(filename string) bool {
	_, err := os.Stat(filename)
	return err == nil
}

func handleArrayOperation(tokens []string, filename string) {
	staticArr := NewArray()

	if fileExists(filename) {
		loadFromFileArray(staticArr, filename)
	}

	if len(tokens) == 0 {
		fmt.Println("Error: Empty query")
		return
	}

	operation := tokens[0]

	switch operation {
	case "APUSH":
		if len(tokens) >= 2 {
			pushBack(staticArr, tokens[1])
			fmt.Printf("Added '%s' to array\n", tokens[1])
		}
	case "APUSH_INDEX":
		if len(tokens) >= 3 {
			index, err := strconv.Atoi(tokens[1])
			if err == nil {
				pushIndex(staticArr, index, tokens[2])
				fmt.Printf("Added '%s' at index %d in array\n", tokens[2], index)
			}
		}
	case "APOP_INDEX":
		if len(tokens) >= 2 {
			index, err := strconv.Atoi(tokens[1])
			if err == nil {
				popIndex(staticArr, index)
				fmt.Printf("Removed element at index %d from array\n", index)
			}
		}
	case "AGET":
		if len(tokens) >= 2 {
			index, err := strconv.Atoi(tokens[1])
			if err == nil {
				result := get(staticArr, index)
				fmt.Printf("Array[%d] = %s\n", index, result)
			}
		}
	case "APRINT":
		fmt.Print("Array contents: ")
		printArray(staticArr)
	case "AREPLACE":
		if len(tokens) >= 3 {
			index, err := strconv.Atoi(tokens[1])
			if err == nil {
				fmt.Printf("%s replaced with %s at index %d\n", staticArr.value[index], tokens[2], index)
				replace(staticArr, index, tokens[2])
			}
		}
	case "ALENGTH":
		fmt.Printf("Array length: %d\n", length(staticArr))
	default:
		fmt.Println("Error: Invalid array operation or missing parameters")
		return
	}

	saveToFileArray(staticArr, filename)
}

func handleDLLOperation(tokens []string, filename string) {
	staticDLL := NewDLList()

	if fileExists(filename) {
		loadFromFileDL(staticDLL, filename)
	}

	if len(tokens) == 0 {
		fmt.Println("Error: Empty query")
		return
	}

	operation := tokens[0]

	switch operation {
	case "DLLPUSH_FRONT":
		if len(tokens) >= 2 {
			pushFront(staticDLL, tokens[1])
			fmt.Printf("Added '%s' to front of doubly linked list\n", tokens[1])
		}
	case "DLLPUSH_BACK":
		if len(tokens) >= 2 {
			push_Back(staticDLL, tokens[1])
			fmt.Printf("Added '%s' to back of doubly linked list\n", tokens[1])
		}
	case "DLLSEARCH_KEY":
		if len(tokens) >= 2 {
			index := findIndex(staticDLL, tokens[1])
			if index != -1 {
				fmt.Printf("%s index %d\n", tokens[1], index)
			} else {
				fmt.Println("item not found")
			}
		}
	case "DLLINSERT_AFTER":
		if len(tokens) >= 3 {
			index, err := strconv.Atoi(tokens[1])
			if err == nil {
				insertAfter(staticDLL, index, tokens[2])
				fmt.Printf(">> %s after %d\n", tokens[2], index)
			}
		}
	case "DLLINSERT_BEFORE":
		if len(tokens) >= 3 {
			index, err := strconv.Atoi(tokens[1])
			if err == nil {
				insertBefore(staticDLL, index, tokens[2])
				fmt.Printf(">> %s before %d\n", tokens[2], index)
			}
		}
	case "DLLPOP_FRONT":
		popFront(staticDLL)
		fmt.Println("Removed front element from doubly linked list")
	case "DLLPOP_BACK":
		popBack(staticDLL)
		fmt.Println("Removed back element from doubly linked list")
	case "DLLREMOVE_AFTER":
		if len(tokens) >= 2 {
			index, err := strconv.Atoi(tokens[1])
			if err == nil && index >= 0 && index < staticDLL.size-1 {
				node := searchIndex(staticDLL, index+1)
				if node != nil {
					fmt.Printf("<< %s after %d\n", node.val, index)
					removeAfter(staticDLL, index)
				}
			} else {
				fmt.Printf("Error: Invalid index or no element after index %d\n", index)
			}
		}
	case "DLLREMOVE_BEFORE":
		if len(tokens) >= 2 {
			index, err := strconv.Atoi(tokens[1])
			if err == nil && index >= 0 && index < staticDLL.size {
				node := searchIndex(staticDLL, index-1)
				if node != nil {
					fmt.Printf("<< %s before %d\n", node.val, index)
					removeBefore(staticDLL, index)
				}
			} else {
				fmt.Printf("Error: Invalid index or no element after index %d\n", index)
			}
		}
	case "DLLREMOVE_KEY":
		if len(tokens) >= 2 {
			fmt.Printf("<< %s\n", tokens[1])
			removeKey(staticDLL, tokens[1])
		}
	case "DLLPRINT":
		fmt.Print("Doubly linked list contents: ")
		printDL(staticDLL)
	case "DLLRPRINT":
		fmt.Print("Doubly linked list reverse contents: ")
		reversePrint(staticDLL)
	case "DLLCLEAR":
		clearDL(staticDLL)
		fmt.Println("Doubly linked list cleared")
	default:
		fmt.Println("Error: Invalid doubly linked list operation or missing parameters")
		return
	}

	saveToFileDL(staticDLL, filename)
}

func handleFLOperation(tokens []string, filename string) {
	staticFL := NewFList()

	if fileExists(filename) {
		loadFromFileFL(staticFL, filename)
	}

	if len(tokens) == 0 {
		fmt.Println("Error: Empty query")
		return
	}

	operation := tokens[0]

	switch operation {
	case "FLPUSH_FRONT":
		if len(tokens) >= 2 {
			pushFrontFL(staticFL, tokens[1])
			fmt.Printf(">> %s\n", tokens[1])
		}
	case "FLPUSH_BACK":
		if len(tokens) >= 2 {
			pushBackFL(staticFL, tokens[1])
			fmt.Printf(">> %s\n", tokens[1])
		}
	case "FLINSERT_AFTER":
		if len(tokens) >= 3 {
			index, err := strconv.Atoi(tokens[1])
			if err == nil && index >= 0 && index < staticFL.size {
				insertAfterFL(staticFL, index, tokens[2])
				fmt.Printf(">> %s after %d\n", tokens[2], index)
			} else {
				fmt.Printf("Error: Invalid index %d\n", index)
			}
		}
	case "FLINSERT_BEFORE":
		if len(tokens) >= 3 {
			index, err := strconv.Atoi(tokens[1])
			if err == nil && index >= 0 && index < staticFL.size {
				insertBeforeFL(staticFL, index, tokens[2])
				fmt.Printf(">> %s before %d\n", tokens[2], index)
			} else {
				fmt.Printf("Error: Invalid index %d\n", index)
			}
		}
	case "FLPOP_FRONT":
		if staticFL.size > 0 {
			fmt.Printf("<< %s\n", staticFL.head.val)
			popFrontFL(staticFL)
		} else {
			fmt.Println("Forward list is empty")
		}
	case "FLPOP_BACK":
		if staticFL.size > 0 {
			node := searchIndexFL(staticFL, staticFL.size-1)
			if node != nil {
				fmt.Printf("<< %s\n", node.val)
				popBackFL(staticFL)
			}
		} else {
			fmt.Println("Forward list is empty")
		}
	case "FLREMOVE_AFTER":
		if len(tokens) >= 2 {
			index, err := strconv.Atoi(tokens[1])
			if err == nil && index >= 0 && index < staticFL.size-1 {
				node := searchIndexFL(staticFL, index+1)
				if node != nil {
					fmt.Printf("<< %s after %d\n", node.val, index)
					removeAfterFL(staticFL, index)
				}
			} else {
				fmt.Printf("Error: Invalid index or no element after index %d\n", index)
			}
		}
	case "FLREMOVE_BEFORE":
		if len(tokens) >= 2 {
			index, err := strconv.Atoi(tokens[1])
			if err == nil && index > 0 && index < staticFL.size {
				node := searchIndexFL(staticFL, index-1)
				if node != nil {
					fmt.Printf("<< %s before %d\n", node.val, index)
					removeBeforeFL(staticFL, index)
				}
			} else {
				fmt.Printf("Error: Invalid index or no element before index %d\n", index)
			}
		}
	case "FLSEARCH_KEY":
		if len(tokens) >= 2 {
			index := searchKeyFL(staticFL, tokens[1])
			if index != -1 {
				fmt.Printf("%s index %d\n", tokens[1], index)
			} else {
				fmt.Println("item not found")
			}
		}
	case "FLREMOVE_KEY":
		if len(tokens) >= 2 {
			fmt.Printf("<< %s\n", tokens[1])
			removeKeyFL(staticFL, tokens[1])
		}
	case "FLPRINT":
		if staticFL.size == 0 {
			fmt.Println("Forward list is empty")
		} else {
			fmt.Print("Forward list contents: ")
			printFL(staticFL)
		}
	case "FLCLEAR":
		clearFL(staticFL)
		fmt.Println("Forward list cleared")
	default:
		fmt.Println("Error: Invalid forward list operation or missing parameters")
		return
	}

	saveToFileFL(staticFL, filename)
}

func handleQueueOperation(tokens []string, filename string) {
	staticQueue := NewQueue()

	if fileExists(filename) {
		loadFromFileQueue(staticQueue, filename)
	}

	if len(tokens) == 0 {
		fmt.Println("Error: Empty query")
		return
	}

	operation := tokens[0]

	switch operation {
	case "QPUSH":
		if len(tokens) >= 2 {
			enqueue(staticQueue, tokens[1])
			fmt.Printf(">> %s\n", tokens[1])
		}
	case "QPOP":
		if !isEmptyQueue(staticQueue) {
			fmt.Printf("<< %s\n", staticQueue.head.val)
			dequeue(staticQueue)
		} else {
			fmt.Println("Queue is empty")
		}
	case "QPRINT":
		fmt.Printf("Queue contents: %s\n", printQueue(staticQueue))
	case "QCLEAR":
		clearQueue(staticQueue)
		fmt.Println("Queue cleared")
	default:
		fmt.Println("Error: Invalid queue operation or missing parameters")
		return
	}

	saveToFileQueue(staticQueue, filename)
}

func handleStackOperation(tokens []string, filename string) {
	staticStack := NewStack()

	loadFromFileStack(staticStack, filename)

	if len(tokens) == 0 {
		fmt.Println("Error: Empty query")
		return
	}

	operation := tokens[0]

	switch operation {
	case "SPUSH":
		if len(tokens) >= 2 {
			push(staticStack, tokens[1])
			fmt.Printf(">> %s\n", tokens[1])
		}
	case "SPOP":
		if !isEmptyStack(staticStack) {
			topValue := staticStack.top.val
			pop(staticStack)
			fmt.Printf("<< %s\n", topValue)
		} else {
			fmt.Println("Stack is empty")
		}
	case "SPRINT":
		if isEmptyStack(staticStack) {
			fmt.Println("Stack is empty")
		} else {
			fmt.Printf("Stack (top to bottom): %s\n", printStack(staticStack))
		}
	default:
		fmt.Println("Error: Invalid stack operation")
		return
	}

	saveToFileStack(staticStack, filename)
}

func main() {
	if len(os.Args) < 5 {
		fmt.Println("Usage:", os.Args[0], "--file <filename> --query '<operation> [value]'")
		fmt.Println("Available operations:")
		fmt.Println("Array: APUSH <value>, APUSH_INDEX <index> <value>, APOP_INDEX <index>, AGET <index>, APRINT, ALENGTH, ACLEAR")
		fmt.Println("Doubly Linked List: DLLPUSH_FRONT <value>, DLLPUSH_BACK <value>, DLLPOP_FRONT, DLLPOP_BACK, DLLPRINT, DLLRPRINT, DLLCLEAR")
		fmt.Println("Forward List: FLPUSH_FRONT <value>, FLPUSH_BACK <value>, FLPOP_FRONT, FLPOP_BACK, FLPRINT, FLCLEAR")
		fmt.Println("Queue: QPUSH <value>, QPOP, QPRINT, QCLEAR")
		fmt.Println("Stack: SPUSH <value>, SPOP, SPRINT, SCLEAR")
		os.Exit(1)
	}

	filename, query := parseArguments(os.Args)

	if filename == "" || query == "" {
		fmt.Println("Error: Both --file and --query arguments are required")
		os.Exit(1)
	}

	tokens := parseQuery(query)

	if len(tokens) == 0 {
		fmt.Println("Error: Empty query")
		os.Exit(1)
	}

	structureType := tokens[0]

	switch {
	case strings.HasPrefix(structureType, "A"):
		handleArrayOperation(tokens, filename)
	case strings.HasPrefix(structureType, "DLL"):
		handleDLLOperation(tokens, filename)
	case strings.HasPrefix(structureType, "FL"):
		handleFLOperation(tokens, filename)
	case strings.HasPrefix(structureType, "Q"):
		handleQueueOperation(tokens, filename)
	case strings.HasPrefix(structureType, "S"):
		handleStackOperation(tokens, filename)
	default:
		fmt.Printf("Error: Unknown structure type '%s'\n", structureType)
		os.Exit(1)
	}
}
