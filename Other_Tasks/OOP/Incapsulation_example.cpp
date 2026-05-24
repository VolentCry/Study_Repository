#include <iostream>

class BankAccount {
// PRIVATE: Скрытая часть (как внутренности кофемашины или сейф)
private:
    double balance; // Баланс счета спрятан от прямого доступа

// PUBLIC: Доступная часть (как кнопки на панели управления)
public:
    // Конструктор: задаем начальный баланс при создании счета
    BankAccount(double initial_balance) {
        if (initial_balance >= 0) {
            balance = initial_balance;
        } else {
            balance = 0;
        }
    }

    // Метод для пополнения счета
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            std::cout << "Счет пополнен на " << amount << ". Новый баланс: " << balance << "\n";
        } else {
            std::cout << "Ошибка: Сумма пополнения должна быть больше нуля!\n";
        }
    }

    // Метод для снятия денег
    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            std::cout << "Снято " << amount << ". Остаток: " << balance << "\n";
        } else {
            std::cout << "Ошибка: Недостаточно средств или неверная сумма!\n";
        }
    }

    // Метод, чтобы просто узнать баланс (геттер)
    double getBalance() {
        return balance;
    }
};

int main() {
    // Создаем счет с 1000 рублей
    BankAccount myAccount(1000);

    // myAccount.balance = 1000000; // ОШИБКА! Компилятор не разрешит это сделать, так как balance находится в private.

    // Мы можем управлять счетом только через "кнопки" (public методы):
    myAccount.deposit(500);   // Положили 500
    myAccount.withdraw(200);  // Сняли 200
    myAccount.withdraw(5000); // Попытка снять больше, чем есть (выдаст ошибку)

    std::cout << "Итоговый баланс: " << myAccount.getBalance() << "\n";

    return 0;
}