/*
Компьютер «не знает» арифметики вещественных чисел.
Нужно научить его выполнять операции сложения, вычитания и умножения чисел с плавающей точкой,
используя только функции для работы с символами и строками и операции целочисленной арифметики.
Для этого нужно определить структурный тип данных DECIMAL для представления конечной десятичной дроби,
и написать функции, которые возвращают значения суммы, разности и произведения значений типа DECIMAL.

Выражение “компьютер «не знает» арифметики вещественных чисел” означает,
что запрещено использовать в программе типы float, double и их производные.
*/
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#define MAX_LINE 100

typedef struct
{
    int nf; // целые и дробная часть
    int r; // количество разрядов дробной части
} DECIMAL1;

int mypow(int x, int pow) // возведение в степень
                          // x - число, pow - степень
{
    int result = 1;

    for(int i = 0; i < pow; i++)
        result *= x;

    return result;
}

DECIMAL1 summarize(DECIMAL1 A, DECIMAL1 B) // сумма
{
    DECIMAL1 C;

    C.nf = A.nf * mypow(10, B.r) + B.nf * mypow(10, A.r);
    C.r = A.r + B.r;

    return C;
}

DECIMAL1 subtract(DECIMAL1 A, DECIMAL1 B) // разность
{
    DECIMAL1 C;

    C.nf = A.nf * mypow(10, B.r) - B.nf * mypow(10, A.r);
    C.r = A.r + B.r;

    return C;
}

DECIMAL1 multiply(DECIMAL1 A, DECIMAL1 B) // произведение
{
    DECIMAL1 C;

    C.nf = A.nf * B.nf;
    C.r = A.r + B.r;

    return C;
}

DECIMAL1 getdec(void) // выполняет ввод с консоли строки, изображающей конечную десятичную дробь,
                      // и преобразующую её в значение типа DECIMAL.
{
    DECIMAL1 X;

    int k = 0; // количество разрядов целой части

    char str[MAX_LINE];
    gets(str);

    for(int i = 0; i < strlen(str); i++)
    {
        if (str[i] != '.') // подсчет количества разрядов в целой части
            k++;
            else break;
    }

    X.r = strlen(str) - k - 1; // количество разрядов дробной части

    char *ptr;
    if ((ptr = strstr(str, ".")) != NULL) // значение целой и дробной части
    {
        *ptr = '\0';
        X.nf  = atoi(strcat(str, ptr + (strlen("."))));
    }

    return X;
}

void putdec(DECIMAL1 dec) // выполняет вывод на консоль строки, изображающей конечную десятичную дробь,
                          // представленную значением типа DECIMAL.
{
    int lenNF = 0; // длина целой и дробной части

    for (int i = dec.nf; i != 0; i /= 10)
        lenNF++;

    int lenN = lenNF - dec.r; // длина целой части

    printf("%d.", (int)((dec.nf / mypow(10, dec.r)))); // вывод целой части

    char *temp;
    itoa(dec.nf, temp, 10); // перевод числа dec.nf в строку temp

    int i = dec.r + lenN; // индекс последнего элемента строки

    while (temp[i] == '0') // пока нули не закончатся
        temp[i] = '\0'; // обрез строки

    char d[dec.r]; // строка десятичных цифр

    strcpy(d, temp + lenN); // удаление целой части, оставляем десятичную;

    printf("%s", d);
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    DECIMAL1 A, B, C;

    printf("Введите первое число: ");
    A = getdec();

    printf("\nВведите второе число: ");
    B = getdec();

    printf("\n\n\tРезультат:\n");

    /// cумма
    printf("\n\t");
    putdec(A);
    printf(" + ");
    putdec(B);
    printf(" = ");
    C = summarize(A, B);
    putdec(C);

    /// разность
    printf("\n\t");
    putdec(A);
    printf(" - ");
    putdec(B);
    printf(" = ");
    C = subtract(A, B);
    putdec(C);

    /// произведение
    printf("\n\t");
    putdec(A);
    printf(" * ");
    putdec(B);
    printf(" = ");
    C = multiply(A, B);
    putdec(C);

    getch();
    return 0;
}
