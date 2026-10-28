#include "matrix.h"
#include <iostream>

int main() {
    // Создание матриц
    Matrix A = create_matrix(2, 2);
    Matrix B = create_matrix(2, 2);

    // Заполнение данными
    A.data[0][0] = 1; A.data[0][1] = 2;
    A.data[1][0] = 3; A.data[1][1] = 4;

    B.data[0][0] = 5; B.data[0][1] = 6;
    B.data[1][0] = 7; B.data[1][1] = 8;

    // Базовые операции
    Matrix sum = matrix_add(A, B);
    Matrix product = matrix_multiply(A, B);
    Matrix copy = matrix_copy(A);

    // Вывод результатов
    std::cout << "Matrix A:" << std::endl;
    print_matrix(A);

    std::cout << "Matrix B:" << std::endl;
    print_matrix(B);

    std::cout << "Sum A + B:" << std::endl;
    print_matrix(sum);

    std::cout << "Product A * B:" << std::endl;
    print_matrix(product);

    std::cout << "Copy of A:" << std::endl;
    print_matrix(copy);

    // Освобождение памяти
    free_matrix(A);
    free_matrix(B);
    free_matrix(sum);
    free_matrix(product);
    free_matrix(copy);

    return 0;
}