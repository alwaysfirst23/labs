#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

void file_to_vector(vector<string>& lines, string& filename) {
    string v;
    cout << "Enter the name of file: ";
    cin >> filename;
    ifstream file_to_read(filename);
    if (!file_to_read.is_open()) cout << "Error: file was not found" << endl;

    while (!file_to_read.eof()) {
        getline(file_to_read, v, '\n');
        lines.push_back(v); 
    }
    file_to_read.close(); 
}

void redactor(vector<string>& lines, string& filename, string& act) {
    int line;
    string text;

    cout << "What would you like to do with file? [view/edit/exit]:  ";
    cin >> act;
    if (act == "view") {
        cout << "Which line do you want to view?: ";
        while (!(cin >> line) || cin.peek() != '\n' || line < 1 || line > lines.size()) {
            cout << "Incorrect line, try again: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        cout << lines[line - 1] << endl; 
    }
    else if (act == "edit") {
        cout << "Which line do you want to edit?: ";
        while (!(cin >> line) || cin.peek() != '\n' || line < 1 || line > lines.size()) {
            cout << "Incorrect line, try again: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        cout << "Enter the text you want to put in the line: ";
        cin.ignore(10000, '\n');
        getline(cin, text);
        lines[line - 1] = text;
        ofstream file_to_write(filename);
        for (int i = 0; i < lines.size(); i++) {
            file_to_write << lines[i] << '\n';
        }
        file_to_write.close();
    }
}

int main() {
    string filename;
    vector<string> lines;
    string act;

    file_to_vector(lines, filename);
    do {
        redactor(lines, filename, act);
    } while ((act == "view") || (act == "edit"));
}
