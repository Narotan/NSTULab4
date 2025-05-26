#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

// Метод Борда
string bordaWinner(const vector<string>& candidates, const vector<vector<string>>& votes) {
    map<string, int> scores;
    int n = candidates.size();

    for (const auto& vote : votes) {
        for (int i = 0; i < n; ++i) {
            scores[vote[i]] += n - 1 - i;
        }
    }

    // Поиск кандидата с максимальным числом баллов
    string winner;
    int maxScore = -1;
    for (const auto& [name, score] : scores) {
        if (score > maxScore) {
            maxScore = score;
            winner = name;
        }
    }

    return winner;
}

// Метод Кондорсе
string condorcetWinner(const vector<string>& candidates, const vector<vector<string>>& votes) {
    int n = candidates.size();
    map<string, map<string, int>> pairwise;

    // Подсчет попарных сравнений
    for (const auto& vote : votes) {
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                pairwise[vote[i]][vote[j]]++;
            }
        }
    }

    // Проверка кандидатов на победу по Кондорсе
    for (const auto& candA : candidates) {
        bool isWinner = true;
        for (const auto& candB : candidates) {
            if (candA == candB) continue;
            if (pairwise[candA][candB] <= pairwise[candB][candA]) {
                isWinner = false;
                break;
            }
        }
        if (isWinner) return candA;
    }

    return "Нет победителя по Кондорсе";
}

int main() {
    // Тест 1: Основной случай (разные голоса)
    vector<string> candidates1 = {"Петя", "Вася", "Оля"};
    vector<vector<string>> votes1 = {
        {"Вася", "Оля", "Петя"},
        {"Петя", "Вася", "Оля"},
        {"Оля", "Вася", "Петя"},
        {"Вася", "Петя", "Оля"}
    };
    cout << "Тест 1:\n";
    cout << "Победитель по методу Борда: " << bordaWinner(candidates1, votes1) << endl;
    cout << "Победитель по методу Кондорсе: " << condorcetWinner(candidates1, votes1) << endl << endl;

    // Тест 2: Все голосуют одинаково
    vector<string> candidates2 = {"А", "B", "C"};
    vector<vector<string>> votes2 = {
        {"A", "B", "C"},
        {"A", "B", "C"},
        {"A", "B", "C"}
    };
    cout << "Тест 2 (одинаковые предпочтения):\n";
    cout << "Победитель по методу Борда: " << bordaWinner(candidates2, votes2) << endl;
    cout << "Победитель по методу Кондорсе: " << condorcetWinner(candidates2, votes2) << endl << endl;

    // Тест 3: Парадокс Кондорсе (цикл)
    vector<string> candidates3 = {"A", "B", "C"};
    vector<vector<string>> votes3 = {
        {"A", "B", "C"},
        {"B", "C", "A"},
        {"C", "A", "B"}
    };
    cout << "Тест 3 (цикл Кондорсе):\n";
    cout << "Победитель по методу Борда: " << bordaWinner(candidates3, votes3) << endl;
    cout << "Победитель по методу Кондорсе: " << condorcetWinner(candidates3, votes3) << endl << endl;

    return 0;
}

