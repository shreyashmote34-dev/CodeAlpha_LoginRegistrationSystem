
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
using namespace std;

// Check whether username already exists
bool usernameExists(string username) {
    ifstream file("users.txt");

    string storedUsername, storedPassword;

    while (file >> storedUsername >> storedPassword) {
        if (storedUsername == username) {
            return true;
        }
    }

    return false;
}

// Registration Function
void registerUser() {

    string username, password;

    cout << "\n===== USER REGISTRATION =====\n";

    cout << "Enter Username: ";
    getline(cin, username);

    cout << "Enter Password: ";
    getline(cin, password);

    // Input validation
    if (username.empty() || password.empty()) {
        cout << "Error: Fields cannot be empty!\n";
        return;
    }

    // Prevent spaces in credentials
    if (username.find(' ') != string::npos ||
        password.find(' ') != string::npos) {
        cout << "Error: Spaces are not allowed!\n";
        return;
    }

    // Password validation
    if (password.length() < 6) {
        cout << "Error: Password must be at least 6 characters!\n";
        return;
    }

    // Duplicate username check
    if (usernameExists(username)) {
        cout << "Error: Username already exists!\n";
        return;
    }

    // Save credentials in file
    ofstream file("users.txt", ios::app);

    if (!file) {
        cout << "Error: Unable to open file!\n";
        return;
    }

    file << username << " " << password << endl;
    file.close();

    cout << "\nRegistration Successful!\n";
}

// Login Function
void loginUser() {

    string username, password;

    cout << "\n===== USER LOGIN =====\n";

    cout << "Enter Username: ";
    getline(cin, username);

    cout << "Enter Password: ";
    getline(cin, password);

    ifstream file("users.txt");

    if (!file) {
        cout << "Error: No registered users found!\n";
        return;
    }

    string storedUsername, storedPassword;

    bool loginSuccess = false;

    // Verify username and password
    while (file >> storedUsername >> storedPassword) {

        if (storedUsername == username &&
            storedPassword == password) {

            loginSuccess = true;
            break;
        }
    }

    file.close();

    if (loginSuccess) {
        cout << "\nLogin Successful! Welcome "
             << username << "!\n";
    }
    else {
        cout << "\nInvalid Username or Password!\n";
    }
}

// Main Function
int main() {

    int choice;

    do {

        cout << "\n===== LOGIN AND REGISTRATION SYSTEM =====\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";

        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input!\n";
            break;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {

            case 1:
                registerUser();
                break;

            case 2:
                loginUser();
                break;

            case 3:
                cout << "Thank you! Exiting...\n";
                break;

            default:
                cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 3);

    return 0;
}
