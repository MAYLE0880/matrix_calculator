#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <algorithm>

typedef struct {
    double** data; // Указатель на двумерный массив данных
    int rows;      // Количество строк в матрице
    int cols;      // Количество столбцов в матрице
} Matrix;

// Создание матрицы с выделением памяти
Matrix create_matrix(int rows, int cols) {
    if (rows <= 0 || cols <= 0) {
        throw std::invalid_argument("Matrix dimensions must be positive");
    }

    Matrix mat;
    mat.rows = rows;
    mat.cols = cols;
    mat.data = new double*[rows];

    for (int i = 0; i < rows; i++) {
        mat.data[i] = new double[cols](); // () сразу инициализирует нулями
    }

    return mat;
}

// Освобождение памяти
void free_matrix(Matrix m) {
    if (m.data == nullptr) {
        return;
    }

    for (int i = 0; i < m.rows; i++) {
        if (m.data[i] != nullptr) {
            delete[] m.data[i];
            m.data[i] = nullptr;
        }
    }

    delete[] m.data;
    m.data = nullptr;
    m.rows = 0;
    m.cols = 0;
}

// Сложение матриц
Matrix matrix_add(Matrix a, Matrix b) {
    if (a.rows != b.rows || a.cols != b.cols) {
        throw std::invalid_argument("Matrices must have the same dimensions for addition");
    }

    Matrix c = create_matrix(a.rows, a.cols);
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            c.data[i][j] = a.data[i][j] + b.data[i][j];
        }
    }
    return c;
}

// Умножение матриц
Matrix matrix_multiply(Matrix a, Matrix b) {
    if (a.cols != b.rows) {
        throw std::invalid_argument("Matrix A cols must equal Matrix B rows for multiplication");
    }

    Matrix c = create_matrix(a.rows, b.cols);
    for (int i = 0; i < a.rows; i++) {
        for (int k = 0; k < b.cols; k++) {
            for (int j = 0; j < a.cols; j++) {
                c.data[i][k] += a.data[i][j] * b.data[j][k];
            }
        }
    }
    return c;
}

// Инициализация из одномерного массива
Matrix matrix_from_array(double* data, int rows, int cols) {
    if (data == nullptr) {
        throw std::invalid_argument("Input array cannot be nullptr");
    }
    if (rows <= 0 || cols <= 0) {
        throw std::invalid_argument("Matrix dimensions must be positive");
    }

    Matrix m = create_matrix(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            m.data[i][j] = data[i * cols + j];
        }
    }
    return m;
}

// Вывод матрицы в консоль
void print_matrix(Matrix m) {
    if (m.data == nullptr || m.rows <= 0 || m.cols <= 0) {
        std::cout << "[Empty matrix]" << std::endl;
        return;
    }

    std::cout << std::fixed << std::setprecision(2);

    const int MAX_ROWS_TO_SHOW = 10;
    const int MAX_COLS_TO_SHOW = 8;
    bool show_summary = (m.rows > MAX_ROWS_TO_SHOW || m.cols > MAX_COLS_TO_SHOW);
    int rows_to_show = show_summary ? MAX_ROWS_TO_SHOW : m.rows;
    int cols_to_show = show_summary ? MAX_COLS_TO_SHOW : m.cols;

    for (int i = 0; i < rows_to_show; i++) {
        if (show_summary && i == MAX_ROWS_TO_SHOW / 2 && m.rows > MAX_ROWS_TO_SHOW) {
            std::cout << "[...";
            for (int j = 0; j < cols_to_show - 2; j++) {
                std::cout << "      ";
            }
            std::cout << "...]" << std::endl;
            continue;
        }

        std::cout << "[";
        for (int j = 0; j < cols_to_show; j++) {
            if (show_summary && j == MAX_COLS_TO_SHOW / 2 && m.cols > MAX_COLS_TO_SHOW) {
                std::cout << " ... ";
                continue;
            }
            std::cout << std::setw(6) << m.data[i][j];

            if (j < cols_to_show - 1) {
                std::cout << " ";
            }
        }
        std::cout << "]";

        if (show_summary && m.cols > MAX_COLS_TO_SHOW) {
            std::cout << " ...";
        }
        std::cout << std::endl;
    }

    if (show_summary && m.rows > MAX_ROWS_TO_SHOW) {
        std::cout << "[...";
        for (int j = 0; j < std::min(cols_to_show, m.cols); j++) {
            std::cout << " ... ";
        }
        std::cout << "...]" << std::endl;
    }

    if (show_summary) {
        std::cout << "Matrix " << m.rows << "x" << m.cols
                  << " (showing first " << rows_to_show << "x" << cols_to_show << ")"
                  << std::endl;
    }
}

Matrix matrix_copy(Matrix original) {
    if (original.data == nullptr || original.rows <= 0 || original.cols <= 0) {
        throw std::invalid_argument("Cannot copy an uninitialized or invalid matrix");
    }

    Matrix copy = create_matrix(original.rows, original.cols);

    for (int i = 0; i < original.rows; i++) {
        for (int j = 0; j < original.cols; j++) {
            copy.data[i][j] = original.data[i][j];
        }
    }

    return copy;
}