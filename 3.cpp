#include <tabulate/table.hpp>
#include <iostream>
#include <vector>
using namespace std;

void find_rect(vector<vector<int>> matrix, int row, int col) {
    int square = 0;
    int start_x = 1;
	int start_y = 1;
	int end_x = 1;
    int end_y = 1;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            int local_i = i;
            int local_j = j;
            int lenght = 0;
            int width = 1;
            int local_square = 0;

            while ((local_j < col) && (matrix[local_i][local_j] == 0)) {
                local_j++;
            }

            lenght = local_j - j;
            // Длина строки = local_j - j
            // Далее перебираем строки
            local_square = (lenght) * (width);
            if (local_square > square) square = local_square;
            while (lenght > 0) {
                // Рассматриваем следующую строку
                local_i++;
                width++;
                // Сдвигаем указатель обратно на позицию i
                local_j = j;
				// Пытаемся найти в нём строку из нулей длины length
				// Если не получается - отбрасываем local_j - j нулей
                for (local_j; ((local_j < col) && (local_j < j+lenght) && (local_i < row) && (matrix[local_i][local_j] == 0)); local_j++);
                if (local_j - j != lenght) {
					lenght -= lenght - (local_j - j); 
                }
                // Проверяем, не является ли текущая фигура наибольшей
                local_square = (lenght) * (width);
                if (local_square > square) {
                    square = local_square;
                    start_x = i + 1;
                    start_y = j + 1;
                    end_x = start_x + width - 1;
                    end_y = start_y + lenght - 1;
                }
            }
        }
    }
    cout << "Square: " << square << endl;
	cout << "Upper left corner: " << start_x << ", " << start_y << endl;
	cout << "Down right corner: " << end_x << ", " << end_y << endl;
}

int row_col_enter() {
    int number;
    while (!(cin >> number) || (cin.peek() != '\n') || (number < 2)) {
        cout << "Enter an integer >1: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    return number;
}

void matrix_enter(vector<vector<int>>& matrix, int row, int col) {
    cout << "Enter numbers (only 0 or 1)" << endl;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            int elem;
            while (!(cin >> elem) || cin.peek() != '\n' || (elem != 0 && elem != 1)) {
                cout << "Incorrect input, try again: ";
                cin.clear();
                cin.ignore(10000, '\n');
            }
            matrix[i][j] = elem;
        }
    }
}

void matrix_print(vector<vector<int>>& matrix, int row, int col) {
    cout << endl << "Entered matrix: " << endl;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    char cont = 'Y';
    do {
        cout << "Enter the number of rows: ";
        int row = row_col_enter();
        cout << "Enter the number of columns: ";
        int col = row_col_enter();
        vector<vector<int>> matrix(row, std::vector<int>(col, 0));

        matrix_enter(matrix, row, col);

        matrix_print(matrix, row, col);

        find_rect(matrix, row, col);

        cout << "[Y] for continue: ";
        cin >> cont;
    } while (cont == 'Y');
}
