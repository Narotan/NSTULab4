// variant 5
// Линейный конгруэнтный генератор

#include <iostream>

using namespace std;

int main() {
    int x,a,b,c,stX;
    cout << "Xo : ";
    cin >> stX;
    cout << endl;
    cout << "A : ";
    cin >> a;
    cout << endl;
    cout << "B : ";
    cin >> b;
    cout << endl;
    cout << "C : ";
    cin >> c;
    cout << endl;

    int count = 0;
    int index = 1;
    int curr = stX;
    x = stX;
    for (int i = 0; i<10; i++) {
        cout << curr << " ";
        curr = (a * x + b) % c;
        if(curr != stX) {
            index++;
        }
        x = curr;
     
    }  
    
    cout << endl;
    cout << "индекс элемента с которого начинается повторение: " << index << endl;
    return 0;
}