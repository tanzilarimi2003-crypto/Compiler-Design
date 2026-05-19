#include <iostream>
#include <fstream>
using namespace std;

bool isKeyword(string word) {
    string keywords[] = {"int", "float", "char", "if", "else", "while", "for", "return"};

    for(int i = 0; i < 8; i++) {
        if(word == keywords[i])
            return true;
    }
    return false;
}

bool isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=');
}


bool isConstant(string token) {
    if(token.empty()) return false;

    for(char ch : token) {
        if(ch < '0' || ch > '9') {
            return false;
        }
    }
    return true;
}

int main() {
    ifstream file("Myfile.txt");

    if(!file.is_open()) {
        cout << "Cannot open file!" << endl;
        return 1;
    }

    string line;

    while(getline(file, line)) {
        cout << "Line: " << line << endl;

        string token = "";

        for(int i = 0; i < line.length(); i++) {

            if(line[i] == ' ' || isOperator(line[i]) || line[i] == ';') {

                if(token != "") {
                    if(isKeyword(token))
                        cout << "Keyword: " << token << endl;
                    else if(isConstant(token))
                        cout << "Constant: " << token << endl;
                    else
                        cout << "Identifier: " << token << endl;

                    token = "";
                }

                if(isOperator(line[i])) {
                    cout << "Operator: " << line[i] << endl;
                }

                if(line[i] == ';') {
                    cout << "Separator: ;" << endl;
                }

            }
            else {
                token += line[i];
            }
        }

        if(token != "") {
            if(isKeyword(token))
                cout << "Keyword: " << token << endl;
            else if(isConstant(token))
                cout << "Constant: " << token << endl;
            else
                cout << "Identifier: " << token << endl;
        }

        cout << endl;
    }

    file.close();
    return 0;
}
