#include <iostream>
#include <vector>
#include <random>
#include <functional>
#include <map>
#include <algorithm>

using namespace std;

// Генерация количества раундов
int generateNum() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(100, 200);
    return distrib(gen);
}

// Алгоритмы
bool alwaysRandom(int round, const vector<bool>& self, const vector<bool>& enemy) {
    return rand() % 2 == 0;
}

bool titForTat(int round, const vector<bool>& self, const vector<bool>& enemy) {
    if (round == 0) return true;
    return enemy.back();
}

bool smartDiserve(int round, const vector<bool>& self, const vector<bool>& enemy) {
    if (enemy.empty()) return true;
    int coopCount = count(enemy.begin(), enemy.end(), true);
    return coopCount >= enemy.size() / 2;
}

bool grudger(int round, const vector<bool>& self, const vector<bool>& enemy) {
    return find(enemy.begin(), enemy.end(), false) == enemy.end();
}

// Функция игры между двумя алгоритмами
string playGame(
    function<bool(int, const vector<bool>&, const vector<bool>&)> alg1,
    function<bool(int, const vector<bool>&, const vector<bool>&)> alg2,
    const string& name1,
    const string& name2
) {
    int rounds = generateNum();
    int score1 = 0, score2 = 0;

    vector<bool> hist1Self, hist1Enemy;
    vector<bool> hist2Self, hist2Enemy;

    for (int i = 0; i < rounds; ++i) {
        bool move1 = alg1(i, hist1Self, hist1Enemy);
        bool move2 = alg2(i, hist2Self, hist2Enemy);

        if (move1 && move2) {
            score1 += 24;
            score2 += 24;
        } else if (move1 && !move2) {
            score1 += 0;
            score2 += 20;
        } else if (!move1 && move2) {
            score1 += 20;
            score2 += 0;
        } else {
            score1 += 4;
            score2 += 4;
        }

        hist1Self.push_back(move1);
        hist1Enemy.push_back(move2);
        hist2Self.push_back(move2);
        hist2Enemy.push_back(move1);
    }

    cout << "\nИгра: " << name1 << " vs " << name2 << "\n";
    cout << "Раундов: " << rounds << "\n";
    cout << name1 << " очков: " << score1 << "\n";
    cout << name2 << " очков: " << score2 << "\n";

    if (score1 > score2) {
        cout << "Победитель: " << name1 << "\n";
        return name1;
    } else if (score2 > score1) {
        cout << "Победитель: " << name2 << "\n";
        return name2;
    } else {
        cout << "Ничья\n";
        return "draw";
    }
}

// Игра между игроком и ИИ
void playWithUser(function<bool(int, const vector<bool>&, const vector<bool>&)> ai, const string& aiName) {
    int rounds = 10;
    int userScore = 0, aiScore = 0;
    vector<bool> userHistory, aiHistory;

    cout << "\n=== Матч против алгоритма: " << aiName << " ===\n";

    for (int i = 0; i < rounds; ++i) {
        bool aiMove = ai(i, aiHistory, userHistory);
        int userMoveInt;
        cout << "\nРаунд " << i + 1 << ": Сотрудничать (1) или Предать (0)? ";
        while (!(cin >> userMoveInt) || (userMoveInt != 0 && userMoveInt != 1)) {
            cout << "Неверный ввод" << endl;
            cin.clear();
            cout << "Введите 1 (сотрудничать) или 0 (предать): ";
        }
        bool userMove = (userMoveInt == 1);

        // Подсчёт очков
        if (userMove && aiMove) {
            userScore += 24;
            aiScore += 24;
        } else if (userMove && !aiMove) {
            userScore += 0;
            aiScore += 20;
        } else if (!userMove && aiMove) {
            userScore += 20;
            aiScore += 0;
        } else {
            userScore += 4;
            aiScore += 4;
        }

        // Обновление истории
        userHistory.push_back(userMove);
        aiHistory.push_back(aiMove);

        cout << "Вы выбрали: " << (userMove ? "Сотрудничать" : "Предать") << ", "
             << aiName << " выбрал: " << (aiMove ? "Сотрудничать" : "Предать") << "\n";
    }

    // Итоги
    cout << "\n=== Итоги матча ===\n";
    cout << "Вы: " << userScore << " очков\n";
    cout << aiName << ": " << aiScore << " очков\n";
    if (userScore > aiScore)
        cout << "Вы победили!\n";
    else if (aiScore > userScore)
        cout << "Победил " << aiName << "\n";
    else
        cout << "Ничья\n";
}

// Турнир из двух раундов
int main() {
    // Названия и функции алгоритмов
    vector<pair<string, function<bool(int, const vector<bool>&, const vector<bool>&)>>> strategies = {
        {"grudger", grudger},
        {"alwaysRandom", alwaysRandom},
        {"smartDiserve", smartDiserve},
        {"titForTat", titForTat}
    };

    map<string, int> wins;

    // Раунд 1: каждый с каждым
    cout << "\n=== Раунд 1: групповой этап ===\n";
    for (size_t i = 0; i < strategies.size(); ++i) {
        for (size_t j = i + 1; j < strategies.size(); ++j) {
            string winner = playGame(strategies[i].second, strategies[j].second, strategies[i].first, strategies[j].first);
            if (winner != "draw") {
                wins[winner]++;
            }
        }
    }

    // Вывод количества побед
    cout << "\n=== Итоги 1-го раунда ===\n";
    for (const auto& [name, win_count] : wins) {
        cout << name << ": " << win_count << " побед\n";
    }

    // Поиск 2 лучших стратегий
    vector<pair<string, int>> sorted_winners(wins.begin(), wins.end());
    sort(sorted_winners.begin(), sorted_winners.end(), [](auto& a, auto& b) {
        return a.second > b.second;
    });

    if (sorted_winners.size() < 2) {
        cout << "Недостаточно данных для финала\n";
        return 0;
    }

    string finalist1 = sorted_winners[0].first;
    string finalist2 = sorted_winners[1].first;

    auto find_func = [&](const string& name) {
        for (auto& s : strategies) {
            if (s.first == name) {
                return s.second;
            }
            
        }
    };

    cout << "\n=== Финал: " << finalist1 << " vs " << finalist2 << " ===\n";
    playGame(find_func(finalist1), find_func(finalist2), finalist1, finalist2);

    cout << "\n=== Матч с пользователем против победителя турнира ===\n";
    playWithUser(find_func(finalist1), finalist1);

    return 0;
}
