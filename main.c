/*
��������� ��� ����� ���������� ������������ �����.
����� ������� ��� ��������� �������� ��������, ��������� � ��������� ����� � ��������� ������,
��������� ������ ������� ��� ������ � ��������� � �������� � �������� ������������� ����������.
��� ����� ����� ���������� ����������� ��� ������ DECIMAL ��� ������������� �������� ���������� �����,
� �������� �������, ������� ���������� �������� �����, �������� � ������������ �������� ���� DECIMAL.

��������� ���������� ��� ����� ���������� ������������ ����� ��������,
��� ��������� ������������ � ��������� ���� float, double � �� �����������.
*/
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#define MAX_LINE 100

typedef struct
{
    int nf; // ����� � ������� �����
    int r; // ���������� �������� ������� �����
} DECIMAL1;

int mypow(int x, int pow) // ���������� � �������
                          // x - �����, pow - �������
{
    int result = 1;

    for(int i = 0; i < pow; i++)
        result *= x;

    return result;
}

DECIMAL1 summarize(DECIMAL1 A, DECIMAL1 B) // �����
{
    DECIMAL1 C;

    C.nf = A.nf * mypow(10, B.r) + B.nf * mypow(10, A.r);
    C.r = A.r + B.r;

    return C;
}

DECIMAL1 subtract(DECIMAL1 A, DECIMAL1 B) // ��������
{
    DECIMAL1 C;

    C.nf = A.nf * mypow(10, B.r) - B.nf * mypow(10, A.r);
    C.r = A.r + B.r;

    return C;
}

DECIMAL1 multiply(DECIMAL1 A, DECIMAL1 B) // ������������
{
    DECIMAL1 C;

    C.nf = A.nf * B.nf;
    C.r = A.r + B.r;

    return C;
}

DECIMAL1 getdec(void) // ��������� ���� � ������� ������, ������������ �������� ���������� �����,
                      // � ������������� � � �������� ���� DECIMAL.
{
    DECIMAL1 X;

    int k = 0; // ���������� �������� ����� �����

    char str[MAX_LINE];
    gets(str);

    for(int i = 0; i < strlen(str); i++)
    {
        if (str[i] != '.') // ������� ���������� �������� � ����� �����
            k++;
            else break;
    }

    X.r = strlen(str) - k - 1; // ���������� �������� ������� �����

    char *ptr;
    if ((ptr = strstr(str, ".")) != NULL) // �������� ����� � ������� �����
    {
        *ptr = '\0';
        X.nf  = atoi(strcat(str, ptr + (strlen("."))));
    }

    return X;
}

void putdec(DECIMAL1 dec) // ��������� ����� �� ������� ������, ������������ �������� ���������� �����,
                          // �������������� ��������� ���� DECIMAL.
{
    int lenNF = 0; // ����� ����� � ������� �����

    for (int i = dec.nf; i != 0; i /= 10)
        lenNF++;

    int lenN = lenNF - dec.r; // ����� ����� �����

    printf("%d.", (int)((dec.nf / mypow(10, dec.r)))); // ����� ����� �����

    char *temp;
    itoa(dec.nf, temp, 10); // ������� ����� dec.nf � ������ temp

    int i = dec.r + lenN; // ������ ���������� �������� ������

    while (temp[i] == '0') // ���� ���� �� ����������
        temp[i] = '\0'; // ����� ������

    char d[dec.r]; // ������ ���������� ����

    strcpy(d, temp + lenN); // �������� ����� �����, ��������� ����������;

    printf("%s", d);
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    DECIMAL1 A, B, C;

    printf("������� ������ �����: ");
    A = getdec();

    printf("\n������� ������ �����: ");
    B = getdec();

    printf("\n\n\t���������:\n");

    /// c����
    printf("\n\t");
    putdec(A);
    printf(" + ");
    putdec(B);
    printf(" = ");
    C = summarize(A, B);
    putdec(C);

    /// ��������
    printf("\n\t");
    putdec(A);
    printf(" - ");
    putdec(B);
    printf(" = ");
    C = subtract(A, B);
    putdec(C);

    /// ������������
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
