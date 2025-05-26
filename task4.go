package main

import (
	"fmt"
)

func bordaWinner(candidates []string, votes [][]string) string {
	scores := make(map[string]int)
	n := len(candidates)

	for _, vote := range votes {
		for i := 0; i < n; i++ {
			scores[vote[i]] += n - 1 - i
		}
	}

	// Поиск кандидата с максимальным числом баллов
	winner := ""
	maxScore := -1
	for name, score := range scores {
		if score > maxScore {
			maxScore = score
			winner = name
		}
	}

	return winner
}

func condorcetWinner(candidates []string, votes [][]string) string {
	n := len(candidates)
	pairwise := make(map[string]map[string]int)

	// Инициализация карты сравнений
	for _, cand := range candidates {
		pairwise[cand] = make(map[string]int)
	}

	// Подсчет попарных сравнений
	for _, vote := range votes {
		for i := 0; i < n; i++ {
			for j := i + 1; j < n; j++ {
				pairwise[vote[i]][vote[j]]++
			}
		}
	}

	// Проверка кандидатов на победу по Кондорсе
	for _, candA := range candidates {
		isWinner := true
		for _, candB := range candidates {
			if candA == candB {
				continue
			}
			if pairwise[candA][candB] <= pairwise[candB][candA] {
				isWinner = false
				break
			}
		}
		if isWinner {
			return candA
		}
	}

	return "Нет победителя по Кондорсе"
}

func main() {
	// Тест 1: Разные голоса
	candidates1 := []string{"Петя", "Вася", "Оля"}
	votes1 := [][]string{
		{"Вася", "Оля", "Петя"},
		{"Петя", "Вася", "Оля"},
		{"Оля", "Вася", "Петя"},
		{"Вася", "Петя", "Оля"},
	}
	fmt.Println("Тест 1:")
	fmt.Println("Победитель по методу Борда:", bordaWinner(candidates1, votes1))
	fmt.Println("Победитель по методу Кондорсе:", condorcetWinner(candidates1, votes1))
	fmt.Println()

	// Тест 2: Все голосуют одинаково
	candidates2 := []string{"A", "B", "C"}
	votes2 := [][]string{
		{"A", "B", "C"},
		{"A", "B", "C"},
		{"A", "B", "C"},
	}
	fmt.Println("Тест 2 (одинаковые предпочтения):")
	fmt.Println("Победитель по методу Борда:", bordaWinner(candidates2, votes2))
	fmt.Println("Победитель по методу Кондорсе:", condorcetWinner(candidates2, votes2))
	fmt.Println()

	// Тест 3: Парадокс Кондорсе (цикл)
	candidates3 := []string{"A", "B", "C"}
	votes3 := [][]string{
		{"A", "B", "C"},
		{"B", "C", "A"},
		{"C", "A", "B"},
	}
	fmt.Println("Тест 3 (цикл Кондорсе):")
	fmt.Println("Победитель по методу Борда:", bordaWinner(candidates3, votes3))
	fmt.Println("Победитель по методу Кондорсе:", condorcetWinner(candidates3, votes3))
	fmt.Println()
}
