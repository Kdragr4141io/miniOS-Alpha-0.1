#include <iostream>
#include <string>
#include <sstream>
#include <thread>
#include <chrono>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

// Küçük harfe çevirme fonksiyonu
string toLower(const string& s) {
    string res = s;
    transform(res.begin(), res.end(), res.begin(),
        [](unsigned char c){ return tolower(c); });
    return res;
}

// Boot ekranı
void bootScreen() {
    cout << "BOOTING miniOS...\n";
    this_thread::sleep_for(chrono::seconds(5));
    cout << "\n";
}

// ASCII print modelleri
const vector<string> asciiModels = {
    "  /\\_/\\  \n ( o.o ) \n  > ^ <  ", // 1. model - kedi
    "  __\n /  \\\n|    |\n \\__/ ",    // 2. model - basit ev
    "  _\n /_\\\n( o )\n ||| ",         // 3. model - robot
    "  __\n /\\ \\\n \\_\\ \\\n  \\/_/ ",  // 4. model - ok
    "  /\\\n /  \\\n/____\\\n|    |"     // 5. model - piramit
};

// Memo için değişken
string memoNote = "";

// Sayı tahmin oyunu
void numberGuessingGame() {
    cout << "I have chosen a number between 1 and 100. Try to guess it!\n";
    int target = rand() % 100 + 1;
    int guess = 0;
    while (true) {
        cout << "Your guess: ";
        string line; getline(cin, line);
        try {
            guess = stoi(line);
        } catch (...) {
            cout << "Please enter a valid number.\n";
            continue;
        }
        if (guess > target) cout << "Lower\n";
        else if (guess < target) cout << "Higher\n";
        else {
            cout << "Congratulations! You guessed it!\n";
            break;
        }
    }
}

// miniBrowser fonksiyonu
void miniBrowser(bool& connected, vector<int>& downloadedModels) {
    cout << "Welcome to the Mini Browser 0.1\n";
    cout << "Refreshing the connection...\n";
    this_thread::sleep_for(chrono::seconds(7));

    string currentSite = "";
    bool inBrowser = true;

    while(inBrowser) {
        if (!connected) {
            cout << "Internet Access Denied. Please connect first.\n";
            break;
        }
        cout << "URL: ";
        string url; getline(cin, url);
        url = toLower(url);

        if (url == "exit") {
            inBrowser = false;
            cout << "Exiting browser...\n";
            break;
        }

        if (url == "refresh" && currentSite != "") {
            cout << "Refreshing the internet connection...\n";
            this_thread::sleep_for(chrono::seconds(2));
            url = currentSite; // refresh current site
        }

        if (url.substr(0,5) == "dial ") {
            cout << "You are already connected!\n";
            continue;
        }

        if (url == "bookmarks") {
            cout << "Bookmarks:\n";
            cout << "www.mininews.com\n";
            cout << "www.minios.com\n";
            cout << "www.devos.com\n";
            cout << "www.chatgpt.net\n";
            cout << "www.dialup.help\n";
            cout << "www.prints.com\n";
            cout << "www.jokes.net\n";
        }
        else if (url == "www.mininews.com") {
            currentSite = url;
            cout << "\n--- ALPHA 0.2 IS ANNOUNCED! ---\n\n";
        }
        else if (url == "www.prints.com") {
            currentSite = url;
            cout << "\nWelcome to Prints.com ASCII Art Gallery!\n";
            cout << "1. (Cat)\n2. (House)\n3. (Robot)\n4. (Arrow)\n5. (Pyramid)\n\n";
            cout << "Use 'download <number>' to download an ASCII model.\n";
            cout << "Use 'downloads' to list your downloaded models.\n";
            cout << "Use 'print <number>' to print a downloaded ASCII art.\n";
        }
        else if (url == "www.minios.com") {
            currentSite = url;
            cout << "\nWelcome to miniOS official site!\n";
            cout << "Here you can find updates, docs and downloads.\n";
        }
        else if (url == "www.devos.com") {
            currentSite = url;
            cout << "\nWelcome to DevOS - Developer's Paradise!\n";
            cout << "Tools and tips for coding enthusiasts.\n";
        }
        else if (url == "www.chatgpt.net") {
            currentSite = url;
            cout << "\nChatGPT Network - Your AI assistant online!\n";
            cout << "Ask your questions and get instant answers.\n";
        }
        else if (url == "www.dialup.help") {
            currentSite = url;
            cout << "\nDial-Up Help Center\n";
            cout << "Tips and troubleshooting for dial-up connections.\n";
        }
        else if (url == "www.jokes.net") {
            currentSite = url;
            cout << "\nWelcome to Jokes.net - lighten your day!\n";
            cout << "Why did the programmer quit his job? Because he didn't get arrays!\n";
        }
        else if (url.substr(0,9) == "download ") {
            if (currentSite != "www.prints.com") {
                cout << "You must be on www.prints.com to download.\n";
                continue;
            }
            string numStr = url.substr(9);
            int num = stoi(numStr);
            if (num >= 1 && num <= (int)asciiModels.size()) {
                cout << "Downloading...\n";
                this_thread::sleep_for(chrono::seconds(1));
                downloadedModels.push_back(num);
                cout << "Download successful!\n";
            } else {
                cout << "Invalid model number.\n";
            }
        }
        else if (url == "downloads") {
            if (downloadedModels.empty()) {
                cout << "No downloaded ASCII models.\n";
            } else {
                cout << "Downloaded models:\n";
                for (int d : downloadedModels) {
                    cout << d << ".\n";
                }
            }
        }
        else if (url.substr(0,6) == "print ") {
            if (downloadedModels.empty()) {
                cout << "No downloaded ASCII models to print.\n";
                continue;
            }
            string numStr = url.substr(6);
            int num = stoi(numStr);
            if (find(downloadedModels.begin(), downloadedModels.end(), num) == downloadedModels.end()) {
                cout << "Model not downloaded yet.\n";
            } else if (num >= 1 && num <= (int)asciiModels.size()) {
                cout << asciiModels[num-1] << "\n";
            } else {
                cout << "Invalid model number.\n";
            }
        }
        else {
            cout << "Unknown site.\n";
        }
    }
}

// Dial-up connection setup
void dialUpConnection(bool& connected) {
    cout << "Welcome to dial UP connection setup wizard\n";
    cout << "Select the Dial Up modem:\nTT INTERNET\n";

    while (true) {
        cout << "> ";
        string input; getline(cin, input);
        input = toLower(input);

        if (input == "tt internet") {
            string number;
            while(true) {
                cout << "Write the telephone number (e.g. DIAL 0530): ";
                getline(cin, number);
                string number_lower = toLower(number);
                if (number_lower.size() >= 5 && number_lower.substr(0,5) == "dial ") {
                    cout << "Dialing " << number.substr(5) << "...\n";
                    this_thread::sleep_for(chrono::seconds(10));
                    cout << "Connecting to the Dial UP internet...\n";
                    this_thread::sleep_for(chrono::seconds(10));
                    connected = true;
                    cout << "Connecting the internet successful!\n";
                    return;
                } else {
                    cout << "Please type number starting with 'DIAL ' (e.g. DIAL 0530)\n";
                }
            }
        } else {
            cout << "Please select a valid modem.\n";
        }
    }
}

int main() {
    srand(time(nullptr));
    bootScreen();

    bool connected = false;
    vector<int> downloadedModels;

    cout << "Type 'help' for commands.\n";

    while (true) {
        cout << "miniOS> ";
        string cmd;
        getline(cin, cmd);

        string cmdLower = toLower(cmd);

        if (cmdLower == "exit") break;

        else if (cmdLower == "help") {
            cout << "Commands:\n";
            cout << "help - Show this help\n";
            cout << "exit - Exit miniOS\n";
            cout << "calc <num1><op><num2> - Calculate basic math (+,-,*,/)\n";
            cout << "print <num> - Print ASCII model\n";
            cout << "memo - Open memo\n";
            cout << "play - Play number guessing game\n";
            cout << "connect - Setup dial-up internet\n";
            cout << "www - Open web browser\n";
            cout << "how connect internet - Show dial-up instructions\n";
            cout << "bookmarks - Show a list of bookmarks (only available in www)\n";
        }
        else if (cmdLower.substr(0,4) == "calc") {
            istringstream iss(cmd.substr(5));
            int a, b;
            char op;
            if (!(iss >> a >> op >> b)) {
                cout << "Invalid calculation format.\n";
                continue;
            }
            int result = 0;
            switch(op) {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/': result = (b != 0) ? a / b : 0; break;
                default: cout << "Invalid operation\n"; continue;
            }
            cout << "Result: " << result << "\n";
        }
        else if (cmdLower.substr(0,6) == "print ") {
            string numStr = cmd.substr(6);
            int num = stoi(numStr);
            if (num >= 1 && num <= (int)asciiModels.size()) {
                cout << asciiModels[num-1] << "\n";
            } else {
                cout << "Invalid model number.\n";
            }
        }
        else if (cmdLower == "memo") {
            cout << "Note 1:\n";
            if (memoNote.empty()) {
                cout << "(empty)\n";
            } else {
                cout << memoNote << "\n";
            }
            bool inMemo = true;
            while(inMemo) {
                cout << "memo: ";
                string line; getline(cin, line);
                if (toLower(line) == "exit") {
                    inMemo = false;
                } else {
                    memoNote = line;
                    cout << "Saved.\n";
                }
            }
        }
        else if (cmdLower == "play") {
            numberGuessingGame();
        }
        else if (cmdLower == "connect") {
            dialUpConnection(connected);
        }
        else if (cmdLower == "www") {
            miniBrowser(connected, downloadedModels);
        }
        else if (cmdLower == "how connect internet") {
            cout << "To connect to internet:\n";
            cout << "- Type 'connect' and follow the wizard\n";
            cout << "- Select 'TT INTERNET' modem\n";
            cout << "- Type telephone number like 'DIAL 0530'\n";
            cout << "- Wait for connection to succeed\n";
        }
        else {
            cout << "Unknown command\n";
        }
    }

    cout << "Goodbye from miniOS!\n";
    return 0;
}
