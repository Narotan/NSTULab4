#include <iostream>
#include <vector>
#include <random>
#include <cmath>

using namespace std;

// заполнение массива случайными числами
void generateNum(vector<float>& arr, int length) {
    minstd_rand0 gen;
    uniform_real_distribution<> distrib(-250.0, 250.0);
    
    for (int i = 0; i < length; ++i) {
        arr.push_back(distrib(gen));
    }
}

// сумма после минимального по модулю элемента 
float SumAftLeastElm(vector<float>& arr) {
    float minElm = 260.0;
    float total = 0.0;

    for (const auto& i : arr) {
        if (fabs(i) < minElm) {
            minElm = fabs(i);
            total = 0.0;
        } else {
            total += fabs(i);
        }
    }
    return total;
}

// счетчик отриацательных чисел
int cntNegativeNum(vector<float>& arr) {
    int negativeCnt = 0;
    for(const auto& i : arr) {
        if (i < 0) negativeCnt++;
    }
    return negativeCnt;
}

// нахождение наибольшей убывающей последовательности 
vector<int> fndSequence(vector<float>& arr, int length) {
    int stPointer = 0;
    int endPointer = 0;
    int mxlength = -1;
    vector<int> result;
    
    for (int i = 0; i < (length - 1); i++) {
        if (arr[i] > arr[i+1]) {
            endPointer += 1;
        } else {
            if (mxlength < (endPointer - stPointer)) {
                mxlength = (endPointer - stPointer);
                result = {stPointer, endPointer, mxlength+1};
            }
            endPointer += 1;
            stPointer = endPointer;
        }
    }
    return result;
}

// перевернутая последовательонсть из 3 задания 
vector<float> reverseMxSequense(vector<float>& arr, int length) {
    vector<int> sequense = fndSequence(arr, length); 
    vector<float> newArr;
    for(int i = sequense[1]; i >= sequense[0]; i--) {
        newArr.push_back(arr[i]);
    }
    return newArr;
}

void task1(vector<float>& arr) {
    cout << "Исходный массив:" << endl;
    for(const auto& i : arr) {
        cout << i << endl;
    }
    cout << "––––––––––––––––––––––––––––––––––––" << endl;
}

void task2(vector<float>& arr) {
    cout << "Количество отрицательных элементов: " << cntNegativeNum(arr) << endl;
    cout << "Сумма после минимального по модулю: " << SumAftLeastElm(arr) << endl;
    cout << "––––––––––––––––––––––––––––––––––––" << endl;
}

void task3(vector<float>& arr, int length) {
    vector<int> sequense = fndSequence(arr, length);  
    cout << "Начало последовательности: " << sequense[0] << endl;
    cout << "Конец последовательности: " << sequense[1] << endl;
    cout << "Длина последовательности: " << sequense[2] << endl;
    cout << "Элементы последовательности: " << endl;
    for(int i = sequense[0]; i <= sequense[1]; i++) {
        cout << arr[i] << " " << endl;
    }
    cout << "––––––––––––––––––––––––––––––––––––" << endl;
}

void task4(vector<float>& arr, int length) {
    vector<float> newArr = reverseMxSequense(arr, length);
    cout << "Перевернутая последовательность: " << endl;
    for (const auto& i : newArr) {
        cout << i << endl;
    }
    cout << "––––––––––––––––––––––––––––––––––––" << endl;
}

void generateNumForTask5(vector<int>& arr, int length) {
    minstd_rand0 gen;
    uniform_int_distribution<> distrib(0, 20);
    
    for (int i = 0; i < length; ++i) {
        arr.push_back(distrib(gen));
    }
}

// сдвиг массивов ы
void shiftRight(vector<int>& arr1, vector<int>& arr2) {
    int last1 = arr1.back();
    int last2 = arr2.back();
    
    for (int i = (arr1.size() - 1); i >= 0; i--) {
        arr1[i] = arr1[i- 1];
    }

    for (int i = (arr2.size() - 1); i >= 0; i--) {
        arr2[i] = arr2[i- 1];
    }

    arr1[0] = last2;
    arr2[0] = last1;

}

// задание 5
void task5() {
    vector<int >arr1, arr2;
    generateNumForTask5(arr1, 5);
    generateNumForTask5(arr2, 3);

    cout << "массивы до перестановки " << endl;
    cout << "первый: " << endl;
    for (const auto& i : arr1) {
        cout << i << " ";
    }
    cout << endl;
    cout << "второй: " << endl;
    for (const auto& i : arr2) {
        cout << i << " ";
    }
    cout << endl;

    cout << "массивы после перестановки " << endl;
    shiftRight(arr1, arr2);
    cout << "первый: " << endl;
    for (const auto& i : arr1) {
        cout << i << " ";
    }
    cout << endl;
    cout << "второй: " << endl;
    for (const auto& i : arr2) {
        cout << i << " ";
    }
    cout << endl;

}


int main() {
    vector<float> arr;
    const int length = 20;
    
    // Генерация массива
    generateNum(arr, length);
    
    task1(arr);    
    task2(arr);  
    task3(arr, length); 
    task4(arr, length);
    task5();
    return 0;
}