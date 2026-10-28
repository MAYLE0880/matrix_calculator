/**
 * @file matrix.h
 * @brief Библиотека для работы с матрицами.
 * @author Студент
 * @version 0.1
 */

#ifndef MATRIX_H
#define MATRIX_H

#include <stdexcept>

/**
 * @brief Структура для представления матрицы.
 *
 * Хранит указатель на двумерный динамический массив данных и его размеры.
 * @warning Выделенную память необходимо освобождать с помощью free_matrix().
 */
typedef struct {
    double** data; ///< Указатель на двумерный массив данных.
    int rows;      ///< Количество строк в матрице.
    int cols;      ///< Количество столбцов в матрице.
} Matrix;

/**
 * @brief Создание новой матрицы с заданными размерами.
 *
 * @param rows Количество строк матрицы (> 0).
 * @param cols Количество столбцов матрицы (> 0).
 * @return Matrix Инициализированная нулями структура матрицы.
 *
 * @exception std::invalid_argument Если rows <= 0 или cols <= 0.
 * @exception std::bad_alloc Если не удалось выделить память.
 *
 * @note Время выполнения: O(rows * cols).
 * @see free_matrix()
 *
 * @code
 * Matrix A = create_matrix(3, 3);
 * @endcode
 */
Matrix create_matrix(int rows, int cols);

/**
 * @brief Освобождение памяти, занятой матрицей.
 *
 * Освобождает память каждой строки и массив указателей, предотвращая утечки памяти.
 *
 * @param m Матрица, память которой требуется освободить.
 * @note Функция безопасна при передаче пустой матрицы (nullptr).
 */
void free_matrix(Matrix m);

/**
 * @brief Сложение двух матриц одинакового размера.
 *
 * @param a Первая матрица.
 * @param b Вторая матрица.
 * @return Matrix Новая матрица, являющаяся суммой a и b.
 *
 * @exception std::invalid_argument Если размеры матриц a и b не совпадают.
 * @warning Результирующую матрицу необходимо освобождать через free_matrix().
 */
Matrix matrix_add(Matrix a, Matrix b);

/**
 * @brief Умножение двух матриц.
 *
 * @param a Матрица размером M x N.
 * @param b Матрица размером N x K.
 * @return Matrix Результат умножения размером M x K.
 *
 * @exception std::invalid_argument Если cols(a) != rows(b).
 * @note Сложность алгоритма: O(M * N * K).
 * @warning Результирующую матрицу необходимо освобождать через free_matrix().
 */
Matrix matrix_multiply(Matrix a, Matrix b);

/**
 * @brief Форматированный вывод матрицы в консоль.
 *
 * Выводит элементы с фиксированной точностью до 2 знаков после запятой.
 * Для больших матриц (> 10x8) автоматически формирует сокращенный вид.
 *
 * @param m Матрица для вывода.
 */
void print_matrix(Matrix m);

/**
 * @brief Создание матрицы из одномерного массива чисел.
 *
 * @param data Указатель на одномерный массив исходных данных.
 * @param rows Количество строк будущей матрицы.
 * @param cols Количество столбцов будущей матрицы.
 * @return Matrix Заполненная данными матрица.
 *
 * @exception std::invalid_argument Если data == nullptr или размеры неположительны.
 */
Matrix matrix_from_array(double* data, int rows, int cols);

/**
 * @brief Создание глубокой (независимой) копии матрицы.
 *
 * Выделяет новую память и копирует все значения. Изменение копии не влияет на оригинал.
 *
 * @param original Исходная матрица.
 * @return Matrix Независимая копия матрицы.
 *
 * @exception std::invalid_argument Если исходная матрица невалидна.
 * @warning Копию необходимо освободить через free_matrix().
 */
Matrix matrix_copy(Matrix original);

#endif // MATRIX_H