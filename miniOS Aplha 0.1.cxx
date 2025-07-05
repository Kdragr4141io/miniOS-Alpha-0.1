#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <ctime>

void print_art(int index) {
    switch (index) {
        case 1:
            std::cout << R"(
    +--------+
    |  mini  |
    |  OS v1 |
    +--------+
            )" << "\n";
            break;
        case 2:
            std::cout << R"(
     __
    /  \
    |  |
    \__/
  Yazıcı: Çalıştı!
            )" << "\n";
            break;
        case 3:
            std::cout << R"(
  [*] ASCII Yazıcı
      █████
      █   █
      █   █
      █████
            )" << "\n";
            break;
        default:
            std::cout << "Bilinmeyen print numarası.\n";
    }
}

void play_game() {
    std::srand(std::time(0));
    int secret = std::rand() % 100 + 1;
    std::string input;
    int guess = 0;

    std::cout << "1 ile 100 arasında bir sayı tuttum. Tahmin et! (Çıkmak için 'exit' yaz)\n";

    while (true) {
        std::cout << "Tahminin: ";
        std::getline(std::cin, input);

        if (input == "exit" || input == "quit") {
            std::cout << "Oyundan çıkılıyor...\n";
            break;  // Oyun döngüsünden çık
        }

        std::istringstream iss(input);
        if (!(iss >> guess)) {
            std::cout << "Geçersiz giriş, sayı veya 'exit' yaz.\n";
            continue;
        }

        if (guess < secret) std::cout << "Daha büyük!\n";
        else if (guess > secret) std::cout << "Daha küçük!\n";
        else {
            std::cout << "Tebrikler! Bildin.\n";
            break;
        }
    }
}

int main() {
    std::string cmd;

    while (true) {
        std::cout << "miniOS> ";
        std::getline(std::cin, cmd);

        if (cmd == "exit") break;
        else if (cmd == "help") {
            std::cout << "Komutlar:\n";
            std::cout << "  help         - Yardım\n";
            std::cout << "  exit         - miniOS'tan çık\n";
            std::cout << "  calc x+y     - Basit hesaplama\n";
            std::cout << "  print <no>   - ASCII çıktı\n";
            std::cout << "  play         - Sayı tahmin oyunu oynar\n";
        }
        else if (cmd.substr(0, 4) == "calc") {
            std::string expr = cmd.substr(5);
            expr.erase(std::remove_if(expr.begin(), expr.end(), ::isspace), expr.end());
            size_t op_pos = expr.find_first_of("+-*/");
            if (op_pos == std::string::npos) {
                std::cout << "Hata: Geçerli bir işlem değil.\n";
                continue;
            }
            int a = std::stoi(expr.substr(0, op_pos));
            int b = std::stoi(expr.substr(op_pos + 1));
            char op = expr[op_pos];

            int result = 0;
            bool valid = true;
            switch(op) {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/': 
                    if (b != 0) result = a / b;
                    else { std::cout << "Hata: 0'a bölünemez.\n"; valid = false; }
                    break;
                default: std::cout << "Geçersiz işlem.\n"; valid = false;
            }

            if (valid) std::cout << "Sonuç: " << result << "\n";
        }
        else if (cmd.substr(0, 5) == "print") {
            std::istringstream iss(cmd.substr(6));
            int number;
            if (iss >> number) {
                print_art(number);
            } else {
                std::cout << "Kullanım: print <sayi>\n";
            }
        }
        else if (cmd == "play") {
            play_game();
        }
        else {
            std::cout << "Bilinmeyen komut: " << cmd << "\n";
        }
    }

    return 0;
}