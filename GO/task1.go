package main

import (
	"fmt"
	"math"
)

// Функция f(x)
func f(x float64) float64 {
	return math.Cos(x+0.5) - x - 2
}

// Производная f'(x)
func df(x float64) float64 {
	return -math.Sin(x+0.5) - 1
}

// Функция φ(x) для метода простых итераций
func phi(x float64) float64 {
	return math.Cos(x+0.5) - 2
}

// Вывод заголовка таблицы
func printHeader(method string) {
	fmt.Printf("\n\n%s:\n", method)
	fmt.Printf("%-3s%-15s%-15s%-15s\n", "N", "xn", "xn+1", "xn+1 - xn")
}

// Метод половинного деления (бисекции)
func bisectionMethod(epsilon, left, right float64, counter int) float64 {
	middle := (left + right) / 2

	fmt.Printf("%-3d%-15.4f%-15.4f%-15.4f\n",
		counter, left, right, right-left)

	if f(left)*f(middle) < 0 {
		right = middle
	} else {
		left = middle
	}

	if math.Abs(right-left) <= epsilon {
		return middle
	}

	return bisectionMethod(epsilon, left, right, counter+1)
}

// Метод Ньютона
func newtonMethod(epsilon, x0 float64) float64 {
	xCurr := x0
	var xNext float64
	counter := 1

	printHeader("Newton Method")

	for {
		xNext = xCurr - f(xCurr)/df(xCurr)
		fmt.Printf("%-3d%-15.4f%-15.4f%-15.4f\n",
			counter, xCurr, xNext, math.Abs(xNext-xCurr))

		if math.Abs(xNext-xCurr) <= epsilon {
			break
		}

		xCurr = xNext
		counter++
	}

	return xNext
}

// Метод простых итераций
func simpleIteration(epsilon, x0 float64) float64 {
	xCurr := x0
	var xNext float64
	counter := 1

	printHeader("Simple Iteration")

	for {
		xNext = phi(xCurr)
		fmt.Printf("%-3d%-15.4f%-15.4f%-15.4f\n",
			counter, xCurr, xNext, math.Abs(xNext-xCurr))

		if math.Abs(xNext-xCurr) <= epsilon {
			break
		}

		xCurr = xNext
		counter++
	}

	return xNext
}

func main() {
	epsilon := 1e-4

	// Метод половинного деления
	fmt.Println("Bisection Method:")
	fmt.Printf("%-3s%-15s%-15s%-15s\n", "N", "an", "bn", "bn - an")
	bisectRoot := bisectionMethod(epsilon, -2, -1, 1)
	fmt.Printf("\nBisection root: %.4f\n", bisectRoot)

	// Метод Ньютона
	newtonRoot := newtonMethod(epsilon, -1.5)
	fmt.Printf("\nNewton root: %.4f\n", newtonRoot)

	// Метод простых итераций
	simpleRoot := simpleIteration(epsilon, -1.5)
	fmt.Printf("\nSimple Iteration root: %.4f\n", simpleRoot)
}
