#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

void calculate_balance(int *cash) {
    std::ifstream atm("..\\ATM.bin");
    std::string temp;
    int count = 0;
    while (!atm.eof()) {
        atm >> *(cash + count);
        ++count;
    }
    atm.close();
}

void atm_filling() {
    int cash[6] = {0, 0, 0, 0, 0, 0}; //0 - 100; 1 - 200; 2 - 500; 3 - 1000; 4 - 2000; 5 - 5000
    calculate_balance(cash);
    int sum = 0;
    for(int i = 0; i < 6; ++i) {
        sum += cash[i];
    }
    std::ofstream atm("..\\ATM.bin");
    for (int i = sum; i < 1000; ++i) {
        ++cash[std::rand() % 6];
    }
    for (int i = 0; i < 6; ++i) {
        atm << cash[i] << std::endl;
    }
    atm.close();
}

void cashdraw() {
    std::cout << "Input the amount: ";
    int amount;
    int temp;
    std::cin >> amount;
    int cash[6] = {0, 0, 0, 0, 0, 0}; //0 - 100; 1 - 200; 2 - 500; 3 - 1000; 4 - 2000; 5 - 5000
    calculate_balance(cash);
    int nominal[6] = {100, 200, 500, 1000, 2000, 5000};
    for (int i = 5; i >= 0; --i) {
        temp = amount / nominal[i];
        if (temp > 0) {
            amount %= nominal[i];
            if (cash[i] - temp >= 0) {
                cash[i] -= temp;
            } else {
                temp -= cash[i];
                cash[i] = 0;
                amount += (temp * nominal[i]);
            }
        }
    }
    if (amount == 0) {
        std::cout << "Take your money.";
        std::ofstream atm("..\\ATM.bin");
        for (int i = 0; i < 6; ++i) {
            atm << cash[i] << std::endl;
        }
        atm.close();
    }
    else std::cout << "Not enough money in ATM.";
}

int main() {
    std::srand(std::time(nullptr));
    std::string action;
    std::cout << "Your action: ";
    std::cin >> action;
    if (action == "+") atm_filling();
    else if (action == "-") cashdraw();
    return 0;
}
