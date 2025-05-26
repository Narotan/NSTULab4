package main

import (
	"fmt"
	"math"
	"math/rand"
	"time"
)

// заполнение массива случайными числами
func generateNum(arr *[]float64, length int) {
	source := rand.NewSource(time.Now().UnixNano())
	rng := rand.New(source)
	min, max := -250.0, 250.0

	for i := 0; i < length; i++ {
		*arr = append(*arr, min+rng.Float64()*(max-min))
	}
}

// сумма после минимального по модулю элемента
func sumAfterLeastElm(arr []float64) float64 {
	minElm := 260.0
	total := 0.0
	found := false

	for _, val := range arr {
		current := math.Abs(val)
		if current < minElm {
			minElm = current
			total = 0.0
			found = true
		} else if found {
			total += math.Abs(val)
		}
	}
	return total
}

// счетчик отрицательных чисел
func cntNegativeNum(arr []float64) int {
	negativeCnt := 0
	for _, val := range arr {
		if val < 0 {
			negativeCnt++
		}
	}
	return negativeCnt
}

// нахождение наибольшей убывающей последовательности
func findSequence(arr []float64, length int) []int {
	stPointer := 0
	endPointer := 0
	maxLength := -1
	result := make([]int, 3)

	for i := 0; i < length-1; i++ {
		if arr[i] > arr[i+1] {
			endPointer = i + 1
		} else {
			currentLength := endPointer - stPointer + 1
			if maxLength < currentLength {
				maxLength = currentLength
				result = []int{stPointer, endPointer, maxLength}
			}
			stPointer = i + 1
			endPointer = i + 1
		}
	}

	// Проверка последней последовательности
	currentLength := endPointer - stPointer + 1
	if maxLength < currentLength {
		result = []int{stPointer, endPointer, currentLength}
	}

	return result
}

// перевернутая последовательность из 3 задания
func reverseMaxSequence(arr []float64, length int) []float64 {
	sequence := findSequence(arr, length)
	newArr := make([]float64, 0)

	for i := sequence[1]; i >= sequence[0]; i-- {
		newArr = append(newArr, arr[i])
	}
	return newArr
}

func task1(arr []float64) {
	fmt.Println("Исходный массив:")
	for _, val := range arr {
		fmt.Println(val)
	}
	fmt.Println("––––––––––––––––––––––––––––––––––––")
}

func task2(arr []float64) {
	fmt.Println("Количество отрицательных элементов:", cntNegativeNum(arr))
	fmt.Println("Сумма после минимального по модулю:", sumAfterLeastElm(arr))
	fmt.Println("––––––––––––––––––––––––––––––––––––")
}

func task3(arr []float64, length int) {
	sequence := findSequence(arr, length)
	fmt.Println("Начало последовательности:", sequence[0])
	fmt.Println("Конец последовательности:", sequence[1])
	fmt.Println("Длина последовательности:", sequence[2])
	fmt.Println("Элементы последовательности:")
	for i := sequence[0]; i <= sequence[1]; i++ {
		fmt.Print(arr[i], " ")
	}
	fmt.Println("\n––––––––––––––––––––––––––––––––––––")
}

func task4(arr []float64, length int) {
	newArr := reverseMaxSequence(arr, length)
	fmt.Println("Перевернутая последовательность:")
	for _, val := range newArr {
		fmt.Println(val)
	}
	fmt.Println("––––––––––––––––––––––––––––––––––––")
}

func generateNumForTask5(arr *[]int, length int) {
	source := rand.NewSource(time.Now().UnixNano())
	rng := rand.New(source)
	min, max := 0, 20

	for i := 0; i < length; i++ {
		*arr = append(*arr, rng.Intn(max-min+1)+min)
	}
}

// сдвиг массивов
func shiftRight(arr1, arr2 []int) {
	if len(arr1) == 0 || len(arr2) == 0 {
		return
	}

	last1 := arr1[len(arr1)-1]
	last2 := arr2[len(arr2)-1]

	copy(arr1[1:], arr1[:len(arr1)-1])
	copy(arr2[1:], arr2[:len(arr2)-1])

	arr1[0] = last2
	arr2[0] = last1
}

func task5() {
	var arr1, arr2 []int
	generateNumForTask5(&arr1, 5)
	generateNumForTask5(&arr2, 3)

	fmt.Println("Массивы до перестановки:")
	fmt.Println("Первый:")
	for _, val := range arr1 {
		fmt.Print(val, " ")
	}
	fmt.Println("\nВторой:")
	for _, val := range arr2 {
		fmt.Print(val, " ")
	}
	fmt.Println()

	shiftRight(arr1, arr2)

	fmt.Println("Массивы после перестановки:")
	fmt.Println("Первый:")
	for _, val := range arr1 {
		fmt.Print(val, " ")
	}
	fmt.Println("\nВторой:")
	for _, val := range arr2 {
		fmt.Print(val, " ")
	}
	fmt.Println("\n––––––––––––––––––––––––––––––––––––")
}

func main() {
	const length = 20
	var arr []float64

	// Генерация массива
	generateNum(&arr, length)

	task1(arr)
	task2(arr)
	task3(arr, length)
	task4(arr, length)
	task5()
}
