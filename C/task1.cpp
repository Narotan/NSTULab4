#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

float func(float x) {
    return cos(x + 0.5) - x - 2;
}

float dfunc(float x) {
    return -sin(x + 0.5) - 1;
}

float phi(float x) {
    return cos(x + 0.5) - 2;
}

void printHeader(const string& method) {
    cout << "\n\n" << method << ":\n";
    cout << setw(3) << "N" 
         << setw(15) << "xn" 
         << setw(15) << "xn+1" 
         << setw(15) << "xn+1 - xn" << endl;
}

// метод половинного деления 
float bisectionMethod(float epsilon, float leftBrd, float rightBrd, int counter) {
    float middle = (leftBrd + rightBrd)/2;

    cout << setw(3) << counter 
         << setw(15) << fixed << setprecision(4) << leftBrd 
         << setw(15) << fixed << setprecision(4) << rightBrd 
         << setw(15) << fixed << setprecision(4) << (rightBrd - leftBrd) 
         << endl;

    if (func(leftBrd) * func(middle) < 0) {
        rightBrd = middle;
    } else {
        leftBrd = middle;
    }

    if (fabs(rightBrd - leftBrd) <= epsilon) {
        return middle; 
    }

    return bisectionMethod(epsilon, leftBrd, rightBrd, counter+1);
}

// ньютона
float NewtonMethod(float epsilon, float x0) {
    float xCurr = x0;
    float xNext;
    int counter = 1;
    float diff;
    
    printHeader("Newton Method");
    
    do {
        xNext = xCurr - func(xCurr)/dfunc(xCurr);
        diff = fabs(xNext - xCurr);
        
        cout << setw(3) << counter 
             << setw(15) << fixed << setprecision(4) << xCurr 
             << setw(15) << fixed << setprecision(4) << xNext 
             << setw(15) << fixed << setprecision(4) << diff 
             << endl;
             
        xCurr = xNext;
        counter++;
        
    } while(diff > epsilon);
    
    return xCurr;
}

// метод простых итераций 
float SimpleIteration(float epsilon, float x0) {
    float xCurr = x0;
    float xNext;
    int counter = 1;
    
    printHeader("Simple Iteration");
    
    float diff;
    do {
        xNext = xCurr - func(xCurr)/dfunc(xCurr);
        diff = fabs(xNext - xCurr);
    
        cout << setw(3) << counter 
             << setw(15) << fixed << setprecision(4) << xCurr 
             << setw(15) << fixed << setprecision(4) << xNext 
             << setw(15) << fixed << setprecision(4) << diff
             << endl;
    
        xCurr = xNext;
        counter++;
        
    } while(diff > epsilon);
    
    
    return xNext;
}

int main() {
    float epsilon = pow(10, -4);
    
    // Метод половинного деления
    cout << "Bisection Method:\n";
    cout << setw(3) << "N" 
         << setw(15) << "an" 
         << setw(15) << "bn" 
         << setw(15) << "bn - an" << endl;
    
    float bisectRoot = bisectionMethod(epsilon, -2, -1, 1);
    cout << "\nBisection root: " << bisectRoot << endl;
    
    // Метод Ньютона
    float newtonRoot = NewtonMethod(epsilon, -1.5);
    cout << "\nNewton root: " << newtonRoot << endl;
    
    // Метод простых итераций
    float simpleRoot = SimpleIteration(epsilon, -1.5);
    cout << "\nSimple Iteration root: " << simpleRoot << endl;

    return 0;
}