#include <gtest/gtest.h>
#include "matrix.h"
#include <stdexcept>

// ==========================================
// 1. НОРМАЛЬНЫЕ СЛУЧАИ
// ==========================================

// 1.1. Создание матрицы
TEST(MatrixTest, CreateMatrix_NormalCase) {
    Matrix A = create_matrix(3, 4);
    // Проверка размеров
    EXPECT_EQ(A.rows, 3);
    EXPECT_EQ(A.cols, 4);
    // Проверка выделения памяти
    EXPECT_NE(A.data, nullptr);
    // Проверка инициализации нулями
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
            EXPECT_DOUBLE_EQ(A.data[i][j], 0.0);
        }
    }
    // Освобождение памяти (исправлена утечка)
    free_matrix(A);
}

// 1.2. Сложение матриц
TEST(MatrixTest, Addition_NormalCase) {
    Matrix A = create_matrix(2, 2);
    Matrix B = create_matrix(2, 2);
    A.data[0][0] = 1; A.data[0][1] = 2;
    A.data[1][0] = 3; A.data[1][1] = 4;
    B.data[0][0] = 5; B.data[0][1] = 6;
    B.data[1][0] = 7; B.data[1][1] = 8;

    Matrix C = matrix_add(A, B);
    EXPECT_DOUBLE_EQ(C.data[0][0], 6.0);
    EXPECT_DOUBLE_EQ(C.data[0][1], 8.0);
    EXPECT_DOUBLE_EQ(C.data[1][0], 10.0);
    EXPECT_DOUBLE_EQ(C.data[1][1], 12.0);

    free_matrix(A);
    free_matrix(B);
    free_matrix(C);
}

// 1.3. Умножение матриц
TEST(MatrixTest, Multiplication_NormalCase) {
    Matrix A = create_matrix(2, 2);
    Matrix B = create_matrix(2, 2);
    A.data[0][0] = 1; A.data[0][1] = 2;
    A.data[1][0] = 3; A.data[1][1] = 4;
    B.data[0][0] = 5; B.data[0][1] = 6;
    B.data[1][0] = 7; B.data[1][1] = 8;

    Matrix C = matrix_multiply(A, B);
    EXPECT_DOUBLE_EQ(C.data[0][0], 19.0);
    EXPECT_DOUBLE_EQ(C.data[0][1], 22.0);
    EXPECT_DOUBLE_EQ(C.data[1][0], 43.0);
    EXPECT_DOUBLE_EQ(C.data[1][1], 50.0);

    free_matrix(A);
    free_matrix(B);
    free_matrix(C);
}

// 1.4. Копирование матрицы (индивидуальное задание №4)
TEST(MatrixTest, MatrixCopy_Independent) {
    Matrix original = create_matrix(2, 2);
    original.data[0][0] = 1.0; original.data[0][1] = 2.0;
    original.data[1][0] = 3.0; original.data[1][1] = 4.0;

    Matrix copy = matrix_copy(original);

    // Проверка размеров
    EXPECT_EQ(copy.rows, 2);
    EXPECT_EQ(copy.cols, 2);

    // Проверка глубокого копирования (разные адреса в куче)
    EXPECT_NE(copy.data, original.data);
    EXPECT_NE(copy.data[0], original.data[0]);

    // Проверка идентичности значений
    EXPECT_DOUBLE_EQ(copy.data[0][0], 1.0);
    EXPECT_DOUBLE_EQ(copy.data[1][1], 4.0);

    // Проверка независимости: изменение копии не меняет оригинал
    copy.data[0][0] = 99.0;
    EXPECT_DOUBLE_EQ(copy.data[0][0], 99.0);
    EXPECT_DOUBLE_EQ(original.data[0][0], 1.0);

    free_matrix(original);
    free_matrix(copy);
}

// 1.5. Освобождение памяти — нормальный случай
TEST(MatrixTest, FreeMatrix_NormalCase) {
    Matrix A = create_matrix(3, 3);
    EXPECT_NO_THROW(free_matrix(A));
}

// ==========================================
// 2. ГРАНИЧНЫЕ СЛУЧАИ
// ==========================================

// 2.1. Минимальный размер матрицы — 1×1
TEST(MatrixTest, CreateMatrix_MinimumSize) {
    Matrix A = create_matrix(1, 1);
    EXPECT_EQ(A.rows, 1);
    EXPECT_EQ(A.cols, 1);
    EXPECT_DOUBLE_EQ(A.data[0][0], 0.0);
    free_matrix(A);
}

// 2.2. Умножение вектор-строка × вектор-столбец приводит к 1×1
TEST(MatrixTest, Multiplication_RowTimesColumn_1x1) {
    Matrix A = create_matrix(1, 3);
    Matrix B = create_matrix(3, 1);
    A.data[0][0] = 1; A.data[0][1] = 2; A.data[0][2] = 3;
    B.data[0][0] = 4;
    B.data[1][0] = 5;
    B.data[2][0] = 6;

    Matrix C = matrix_multiply(A, B);
    EXPECT_EQ(C.rows, 1);
    EXPECT_EQ(C.cols, 1);
    EXPECT_DOUBLE_EQ(C.data[0][0], 32.0);

    free_matrix(A);
    free_matrix(B);
    free_matrix(C);
}

// ==========================================
// 3. НЕКОРРЕКТНЫЕ СЛУЧАИ
// ==========================================

// 3.1. Создание матрицы с нулевыми размерами
TEST(MatrixTest, CreateMatrix_ZeroRows) {
    EXPECT_THROW(create_matrix(0, 3), std::invalid_argument);
}

// 3.2. Создание матрицы с отрицательным размером
TEST(MatrixTest, CreateMatrix_NegativeCols) {
    EXPECT_THROW(create_matrix(3, -1), std::invalid_argument);
}

// 3.3. Сложение матриц разных размеров
TEST(MatrixTest, Addition_SizeMismatch) {
    Matrix A = create_matrix(2, 2);
    Matrix B = create_matrix(3, 3);
    EXPECT_THROW(matrix_add(A, B), std::invalid_argument);
    free_matrix(A);
    free_matrix(B);
}

// 3.4. Умножение матриц с несовместимыми размерами
TEST(MatrixTest, Multiplication_SizeMismatch) {
    Matrix A = create_matrix(2, 3);
    Matrix B = create_matrix(2, 2);
    EXPECT_THROW(matrix_multiply(A, B), std::invalid_argument);
    free_matrix(A);
    free_matrix(B);
}

// 3.5. Повторное освобождение пустой матрицы
TEST(MatrixTest, FreeMatrix_EmptyIsSafe) {
    Matrix empty{nullptr, 0, 0};
    EXPECT_NO_THROW(free_matrix(empty));
    EXPECT_NO_THROW(free_matrix(empty));
}