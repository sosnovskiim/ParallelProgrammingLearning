// Par_Domain_B.cpp

/* Лаб. 1, Задание 5
То же самое, что в задании 3, но со сравнением возможностей опции num_threads
в директиве #pragma omp parallel и вызова функции omp_set_num_threads.
*/

/* Лаб. 1, Задание 3 (ссылка)
Разработать программу, в которой при входе в параллельную область
каждый из потоков OpenMP должен распечатать сообщение.
*/

#include <locale.h>
#include <omp.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, ".ACP");

    // Запрещает динамическую установку нужного числа
    // потоков в следующих параллельных областях
    omp_set_dynamic(0);

    // Установка числа потоков OpenMP по умолчанию
    omp_set_num_threads(4);

    // Установка числа потоков OpenMP в данной параллельной области
    #pragma omp parallel num_threads(3)
    {
        printf("Параллельная область 1\n");
    }

    // Будет использоваться ранее заданное число потоков OpenMP по умолчанию
    #pragma omp parallel
    {
        printf("Параллельная область 2\n");
    }
}
