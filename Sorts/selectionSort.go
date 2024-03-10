package main

import "fmt"

func selectionSort(array []int) []int {
	var index int
	var temp int
	for i := 0; i < len(array)-1; i++ {
		index = i
		for j := i + 1; j < len(array); j++ {
			if array[j] < array[index] {
				index = j
			}
		}
		temp = array[i]
		array[i] = array[index]
		array[index] = temp
	}
	return array
}
func main() {
	array := []int{4, 7, 1, 15, 2, 1, 5}
	fmt.Println(selectionSort(array))
}
