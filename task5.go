package main

import (
	"fmt"
	"math/rand"
	"time"
)

// Генерация количества раундов
func generateNum() int {
	rand.Seed(time.Now().UnixNano())
	return rand.Intn(101) + 100 // 100-200
}

// Алгоритмы

func alwaysRandom(round int, self, enemy []bool) bool {
	return rand.Intn(2) == 0
}

func titForTat(round int, self, enemy []bool) bool {
	if round == 0 {
		return true
	}
	if len(enemy) == 0 {
		return true
	}
	return enemy[len(enemy)-1]
}

func smartDiserve(round int, self, enemy []bool) bool {
	if len(self) == 0 {
		return true
	}
	coopCount := 0
	for _, v := range enemy {
		if v {
			coopCount++
		}
	}
	return coopCount >= len(enemy)/2
}

func grudger(round int, self, enemy []bool) bool {
	for _, v := range enemy {
		if !v {
			return false
		}
	}
	return true
}

// Функция игры между двумя алгоритмами
func playGame(
	alg1 func(int, []bool, []bool) bool,
	alg2 func(int, []bool, []bool) bool,
	name1 string,
	name2 string,
) string {
	rounds := generateNum()
	score1, score2 := 0, 0

	hist1Self := make([]bool, 0)
	hist1Enemy := make([]bool, 0)
	hist2Self := make([]bool, 0)
	hist2Enemy := make([]bool, 0)

	for i := 0; i < rounds; i++ {
		move1 := alg1(i, hist1Self, hist1Enemy)
		move2 := alg2(i, hist2Self, hist2Enemy)

		// Подсчёт очков
		switch {
		case move1 && move2:
			score1 += 24
			score2 += 24
		case move1 && !move2:
			score2 += 20
		case !move1 && move2:
			score1 += 20
		default:
			score1 += 4
			score2 += 4
		}

		// Обновление истории
		hist1Self = append(hist1Self, move1)
		hist1Enemy = append(hist1Enemy, move2)
		hist2Self = append(hist2Self, move2)
		hist2Enemy = append(hist2Enemy, move1)
	}

	fmt.Printf("\nИгра: %s vs %s\n", name1, name2)
	fmt.Printf("Раундов: %d\n", rounds)
	fmt.Printf("%s очков: %d\n", name1, score1)
	fmt.Printf("%s очков: %d\n", name2, score2)

	var winner string
	switch {
	case score1 > score2:
		fmt.Printf("Победитель: %s\n", name1)
		winner = name1
	case score1 == score2:
		fmt.Println("Ничья")
		winner = "Ничья"
	default:
		fmt.Printf("Победитель: %s\n", name2)
		winner = name2
	}

	return winner
}

func main() {
	rand.Seed(time.Now().UnixNano())
	playGame(grudger, alwaysRandom, "grudger", "always Random")
	playGame(smartDiserve, titForTat, "smart diserve", "tit For Tat")
}
