#include <iostream>
#include <cmath>
#include <iomanip>
#include <limits>

using namespace std;

// Чи дійсне число
bool isValidReal(double x) {
    return isfinite(x);
}

// Чи натуральне n > 0
bool isValidN(int n) {
    return n > 0;
}

// eps у межах (10^-20 ... 10^-5)
bool isValidEps(double eps) {
    return eps >= 1e-20 && eps <= 1e-5;
}

// g у межах (10^2 ... 10^5)
bool isValidG(double g) {
    return g >= 1e2 && g <= 1e5;
}

//  ЗАВДАННЯ 1

void task1() {
    cout << "\n Завдання 1 \n";

    int n;
    cout << "Введiть кiлькiсть точок n = ";
    cin >> n;

    if (!isValidN(n)) {
        cout << "Помилка! n має бути натуральним.\n";
        return;
    }

    double a, r;
    cout << "Введіть сторону трикутника a = ";
    cin >> a;
    cout << "Введіть радіус кола r = ";
    cin >> r;

    int countYellow = 0;

    cout << "Введіть точки (x y):\n";
    for (int i = 0; i < n; i++) {
        double x, y;
        cin >> x >> y;

        // Умова для жовтої області
        bool inTriangle = (x >= 0 && y >= 0 && x + y <= a);
        bool inCircle   = ((x - r) * (x - r) + y * y <= r * r);

        if (inTriangle && !inCircle)
            countYellow++;
    }

    cout << "Кiлькiсть точок у жовтiй областi: " << countYellow << "\n";
}

// ЗАВДАННЯ 2
// Формула:
//  S = -( Σ(k=0..n) [ (-1)^k * ( -π/2 + √x )^(1+2k ) / (1+2k)! ] )
//  F = S^(x/3)
// Вивести кожен 4-й елемент при непарному n.


void task2() {
    cout << "\n Завдання 2 \n";

    double x;
    int n;

    do {
        cout << "Введiть x: ";
        cin >> x;
        if (!isValidReal(x)) cout << "Помилка! Введiть дiйсне число.\n";
    } while (!isValidReal(x));

    do {
        cout << "Введiть n: ";
        cin >> n;
        if (!isValidN(n)) cout << "Помилка! n має бути натуральним.\n";
    } while (!isValidN(n));

    double A = -M_PI/2 + sqrt(x);

    double S = 0;

    for (int k = 0; k <= n; k++) {
        double term = pow(-1, k) * pow(A, 1 + 2*k) / tgamma(2*k + 2);  // (1+2k)! = Γ(2k+2)
        S -= term;

        if (n % 2 == 1 && (k + 1) % 4 == 0)
            cout << "Кожен 4-й елемент [" << (k+1)/4 << "] = " << term << "\n";
    }

    double F = pow(S, x / 3.0);

    cout << "Результат = " << F << "\n";
}

//  ЗАВДАННЯ 3

// Ряд: u_n = (n! * n) / (2n)!
// Умова зупинки: |u_n| < eps або |u_n| > g


void task3() {
    cout << "\n Завдання 3 \n";

    double eps, g;
    int M;

    do {
        cout << "eps (10^-20 ... 10^-5): ";
        cin >> eps;
        if (!isValidEps(eps)) cout << "Помилка! eps поза межами.\n";
    } while (!isValidEps(eps));

    do {
        cout << "g (10^2 ... 10^5): ";
        cin >> g;
        if (!isValidG(g)) cout << "Помилка! g поза межами.\n";
    } while (!isValidG(g));

    cout << "Крок виводу M = ";
    cin >> M;

    double S = 0;
    int n = 1;

    cout << fixed << setprecision(15);

    while (true) {
        double un = (tgamma(n+1) * n) / tgamma(2*n + 1); // (n!*n)/(2n)!

        S += un;

        if (n % M == 0)
            cout << "n=" << setw(5) << n << "   S=" << S << "   u_n=" << un << "\n";

        if (fabs(un) < eps) {
            cout << "\nРяд збiгається.\n";
            break;
        }

        if (fabs(un) > g) {
            cout << "\nРяд розбiгається!\n";
            break;
        }

        n++;
    }

    cout << "\nКiнцева сума: " << S << "\n";
}

//  МЕНЮ


void menu() {
    int choice;

    do {
        cout << "\n================ МЕНЮ ================\n";
        cout << "1 — Завдання 1\n";
        cout << "2 — Завдання 2\n";
        cout << "3 — Завдання 3\n";
        cout << "0 — Вихiд\n";
        cout << "======================================\n";
        cout << "Ваш вибiр: ";

        cin >> choice;

        switch (choice) {
            case 1: task1(); break;
            case 2: task2(); break;
            case 3: task3(); break;
            case 0: cout << "Вихiд...\n"; break;
            default: cout << "Невiрний пункт меню!\n";
        }

    } while (choice != 0);
}

//      MAIN

int main() {
    menu();
    return 0;
}
