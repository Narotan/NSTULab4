#include <iostream>
#include <vector>
#include <random>
#include <functional>  // для std::function
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

// делает последний выбор противника 
bool titForTat(int round, const vector<bool>& self, const vector<bool>& enemy) {
    if (round == 0) return true;
    return enemy[enemy.size()-1];
}

// проверяет сколько раз предал соперник если > половины то предает 
bool smartDiserve(int round, const vector<bool>& self, const vector<bool>& enemy) {
    if (self.size() == 0) {
        return true;
    } 
    int coopCount = count(enemy.begin(), enemy.end(), true);
    return coopCount >= enemy.size() / 2;
}

// сотродничает пока не предали
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

        // Подсчёт очков
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

        // Обновление истории
        hist1Self.push_back(move1);
        hist1Enemy.push_back(move2);
        hist2Self.push_back(move2);
        hist2Enemy.push_back(move1);
    }

    cout << "\nИгра: " << name1 << " vs " << name2 << "\n";
    cout << "Раундов: " << rounds << "\n";
    cout << name1 << " очков: " << score1 << "\n";
    cout << name2 << " очков: " << score2 << "\n";
    
    string winner;
    
    if (score1 > score2) {
        cout << "Победитель: " << name1 << endl;
        string winner = name1;
    } else if (score1 >= score2){
        cout << "Ничья" << endl;
        string winner = name1;
    } else {
        cout << "Победитель: " << name2 << endl;
        string winner = name2;
    }

    return winner;
}


int main() {
    playGame(grudger, alwaysRandom, "grudger", "always Random" );
    playGame(smartDiserve, titForTat, "smart diserve", "tit For Tat" );
    return 0;
}
