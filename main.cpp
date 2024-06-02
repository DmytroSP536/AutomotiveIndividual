#include <iostream>      // Підключення бібліотеки для роботи зі стандартним введенням/виведенням
#include <fstream>       // Підключення бібліотеки для роботи з файлами
#include <vector>        // Підключення бібліотеки для використання векторів
#include <string>        // Підключення бібліотеки для роботи з рядками
#include <sstream>       // Підключення бібліотеки для роботи з потоками рядків
#include <iomanip>       // Підключення бібліотеки для маніпуляцій з форматуванням введення/виведення
#include <cstring>       // Підключення бібліотеки для роботи з функціями C-string

const int RECORD_SIZE = 100; // Фіксована довжина запису (у символах)
const int INDEX_SIZE = 4; // Довжина поля індексу (у символах)
const int DATA_SIZE = RECORD_SIZE - INDEX_SIZE - 1; // Довжина поля даних (у символах), зменшена на 1 для пробілу

// Структура для представлення запису
struct Record {
    int index; // Індекс запису
    char data[DATA_SIZE + 1]; // Дані запису (+1 для нульового термінатора)

    // Конструктор для створення запису з даними
    Record(int idx, const std::string& str) : index(idx) {
        memset(data, 0, sizeof(data)); // Ініціалізація поля даних нулями
        strncpy(data, str.c_str(), std::min(sizeof(data) - 1, str.size())); // Копіювання даних у поле data
    }

    // Конструктор для створення порожнього запису
    Record() : index(0) {
        memset(data, 0, sizeof(data)); // Ініціалізація поля даних нулями
    }
};

// Функція для запису масиву записів у файл
void writeRecordsToFile(const std::string& filename, const std::vector<Record>& records, int N) {
    std::ofstream file(filename); // Відкриття файлу в текстовому режимі

    if (!file) { // Перевірка, чи файл успішно відкрився
        std::cerr << "Не вдалося відкрити файл для запису.\n"; // Виведення повідомлення про помилку
        return; // Вихід з функції у випадку помилки
    }

    // Ініціалізація масиву порожніми записами
    std::vector<Record> fullRecords(N);

    // Заповнення масиву даними, якщо індекс в межах дозволеного
    for (const auto& record : records) {
        if (record.index >= 0 && record.index < N) {
            fullRecords[record.index] = record; // Додавання запису у відповідну позицію
        }
    }

    // Запис усіх записів у файл
    for (const auto& rec : fullRecords) {
        std::ostringstream oss;
        oss << std::setw(INDEX_SIZE) << std::setfill('0') << rec.index << " "; // Форматування індексу з нулями
        oss << std::setw(DATA_SIZE) << std::setfill(' ') << rec.data << "\n"; // Форматування даних з пробілами
        file << oss.str(); // Запис рядка у файл
    }

    file.close(); // Закриття файлу
}

int main() {
    int N; // Кількість записів
    std::cout << "Введіть кількість записів: "; // Виведення повідомлення для користувача
    std::cin >> N; // Зчитування кількості записів

    // Створення масиву записів (приклад)
    std::vector<Record> records = {
        Record(0, "Дані запису 1"),
        Record(2, "Дані запису 3"),
        Record(5, "Дані запису 6")
    };

    std::string filename = "records.txt"; // Ім'я файлу

    // Запис масиву записів у файл
    writeRecordsToFile(filename, records, N);

    std::cout << "Записи успішно записані у файл " << filename << ".\n"; // Повідомлення про успішний запис

    return 0; // Повернення нульового значення для позначення успішного завершення програми
}
