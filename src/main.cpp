#include <iostream>
#include <fstream>
using namespace std;
#include <stdlib.h>
#include <math.h>

#define CATCH_CONFIG_RUNNER
#include </home/gamekoff/ns/src/catch.hpp>

/** \file main.cpp
 * Основной файл программы.
 */

/**
Таблица истинности для четырех переменных (массив x)
\param[in] x массив сигналов
\return значение заданной булевой функции
\f$
    f({\bf x})=x_0 \wedge x_1 \vee x_2 \vee x_3
\f$
*/
int getTableTrue(int *x)
{
    if (!x) return -1;
    for (int i=0; i<4; i++)
        if (x[i] != 0 && x[i] != 1) 
            return -1;
	return x[0] & x[1] | x[2] | x[3];
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
TEST_CASE( "getTableTrue", "[getTableTrue]" ) {
    REQUIRE( getTableTrue(0) == -1 );
    
    int *x = new int[4];
    x[0]=0; x[1]=0; x[2]=0; x[3]=0; REQUIRE( getTableTrue(x) == 0 );
    x[0]=0; x[1]=0; x[2]=0; x[3]=1; REQUIRE( getTableTrue(x) == 1 );
    x[0]=0; x[1]=0; x[2]=1; x[3]=0; REQUIRE( getTableTrue(x) == 1 );
    x[0]=0; x[1]=0; x[2]=1; x[3]=1; REQUIRE( getTableTrue(x) == 1 );
    x[0]=0; x[1]=1; x[2]=0; x[3]=0; REQUIRE( getTableTrue(x) == 0 );
    x[0]=0; x[1]=1; x[2]=0; x[3]=1; REQUIRE( getTableTrue(x) == 1 );
    x[0]=0; x[1]=1; x[2]=1; x[3]=0; REQUIRE( getTableTrue(x) == 1 );
    x[0]=0; x[1]=1; x[2]=1; x[3]=1; REQUIRE( getTableTrue(x) == 1 );
    x[0]=1; x[1]=0; x[2]=0; x[3]=0; REQUIRE( getTableTrue(x) == 0 );
    x[0]=1; x[1]=0; x[2]=0; x[3]=1; REQUIRE( getTableTrue(x) == 1 );
    x[0]=1; x[1]=0; x[2]=1; x[3]=0; REQUIRE( getTableTrue(x) == 1 );
    x[0]=1; x[1]=0; x[2]=1; x[3]=1; REQUIRE( getTableTrue(x) == 1 );
    x[0]=1; x[1]=1; x[2]=0; x[3]=0; REQUIRE( getTableTrue(x) == 1 );
    x[0]=1; x[1]=1; x[2]=0; x[3]=1; REQUIRE( getTableTrue(x) == 1 );
    x[0]=1; x[1]=1; x[2]=1; x[3]=0; REQUIRE( getTableTrue(x) == 1 );
    x[0]=1; x[1]=1; x[2]=1; x[3]=1; REQUIRE( getTableTrue(x) == 1 );
    
    x[0]=0; x[1]=0; x[2]=0; x[3]=2; REQUIRE( getTableTrue(x) == -1 );
    x[0]=0; x[1]=0; x[2]=2; x[3]=0; REQUIRE( getTableTrue(x) == -1 );
    x[0]=0; x[1]=2; x[2]=0; x[3]=0; REQUIRE( getTableTrue(x) == -1 );
    x[0]=2; x[1]=0; x[2]=0; x[3]=0; REQUIRE( getTableTrue(x) == -1 );
}
#endif

/**
Вычисление net
\param[in] x массив сигналов
\param[in] w массив весов
\return значение суммы
\f$
    {\rm net}({\bf x},{\bf w})=w_4 + \sum_{i=0}^3{x_iw_i}
\f$
*/
double getNet(int *x, double *w)
{
    if (!x || !w) return -1;
    for (int i=0; i<4; i++) if (x[i] != 0 && x[i] != 1) return -1;
    for (int i=0; i<5; i++) if (w[i] < -1 || w[i] > 1) return -1;
	double sum = w[4];   // w0
	for (int i = 0; i < 4; i++) sum += x[i] * w[i]; 
	return sum;
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
TEST_CASE( "getNet", "[getNet]" ) {
    REQUIRE( getNet(0, new double[5]) == -1 );
    REQUIRE( getNet(new int[4], 0) == -1 );
    
    int *x = new int[4];
    x[0]=0; x[1]=0; x[2]=0; x[3]=2; REQUIRE( getNet(x, new double[5]) == -1 );
    x[0]=0; x[1]=0; x[2]=2; x[3]=0; REQUIRE( getNet(x, new double[5]) == -1 );
    x[0]=0; x[1]=2; x[2]=0; x[3]=0; REQUIRE( getNet(x, new double[5]) == -1 );
    x[0]=2; x[1]=0; x[2]=0; x[3]=0; REQUIRE( getNet(x, new double[5]) == -1 );
    
    double *w = new double[5];
    w[0]=0.0; w[1]=0.0; w[2]=0.0; w[3]=0.0; w[4]=2.0; REQUIRE( getNet(new int[4], w) == -1 );
    w[0]=0.0; w[1]=0.0; w[2]=0.0; w[3]=2.0; w[4]=0.0; REQUIRE( getNet(new int[4], w) == -1 );
    w[0]=0.0; w[1]=0.0; w[2]=2.0; w[3]=0.0; w[4]=0.0; REQUIRE( getNet(new int[4], w) == -1 );
    w[0]=0.0; w[1]=2.0; w[2]=0.0; w[3]=0.0; w[4]=0.0; REQUIRE( getNet(new int[4], w) == -1 );
    w[0]=2.0; w[1]=0.0; w[2]=0.0; w[3]=0.0; w[4]=0.0; REQUIRE( getNet(new int[4], w) == -1 );
    
    x[0]=0; x[1]=0; x[2]=0; x[3]=0; w[0]=1.0; w[1]=1.0; w[2]=1.0; w[3]=1.0; w[4]=0.5; REQUIRE( getNet(x, w) == 0.5 );
    x[0]=1; x[1]=1; x[2]=1; x[3]=1; w[0]=1.0; w[1]=1.0; w[2]=1.0; w[3]=1.0; w[4]=0.5; REQUIRE( getNet(x, w) == 4.5 );
}
#endif

/**
Пороговая функция
\param[in] x массив сигналов
\param[in] w массив весов
\return значение пороговой функции
\f$
    f({\rm net})=\left\{
    \begin{array}{l}
    1,\ {\rm net}\geq 0, \\
    0,\ {\rm net} < 0
    \end{array}
    \right.
\f$
*/
int getFunPorog(int *x, double *w)
{
    if (!x || !w) return -1;
    for (int i=0; i<4; i++) if (x[i] != 0 && x[i] != 1) return -1;
    for (int i=0; i<5; i++) if (w[i] < -1 || w[i] > 1) return -1;
	double net = getNet(x, w);
	if (net >= 0) return 1;
	else return 0;
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
TEST_CASE( "getFunPorog", "[getFunPorog]" ) {
    REQUIRE( getFunPorog(0, new double[5]) == -1 );
    REQUIRE( getFunPorog(new int[4], 0) == -1 );
    
    int *x = new int[4];
    x[0]=0; x[1]=0; x[2]=0; x[3]=2; REQUIRE( getFunPorog(x, new double[5]) == -1 );
    x[0]=0; x[1]=0; x[2]=2; x[3]=0; REQUIRE( getFunPorog(x, new double[5]) == -1 );
    x[0]=0; x[1]=2; x[2]=0; x[3]=0; REQUIRE( getFunPorog(x, new double[5]) == -1 );
    x[0]=2; x[1]=0; x[2]=0; x[3]=0; REQUIRE( getFunPorog(x, new double[5]) == -1 );
    
    double *w = new double[5];
    w[0]=0.0; w[1]=0.0; w[2]=0.0; w[3]=0.0; w[4]=2.0; REQUIRE( getFunPorog(new int[4], w) == -1 );
    w[0]=0.0; w[1]=0.0; w[2]=0.0; w[3]=2.0; w[4]=0.0; REQUIRE( getFunPorog(new int[4], w) == -1 );
    w[0]=0.0; w[1]=0.0; w[2]=2.0; w[3]=0.0; w[4]=0.0; REQUIRE( getFunPorog(new int[4], w) == -1 );
    w[0]=0.0; w[1]=2.0; w[2]=0.0; w[3]=0.0; w[4]=0.0; REQUIRE( getFunPorog(new int[4], w) == -1 );
    w[0]=2.0; w[1]=0.0; w[2]=0.0; w[3]=0.0; w[4]=0.0; REQUIRE( getFunPorog(new int[4], w) == -1 );
    
    x[0]=0; x[1]=0; x[2]=0; x[3]=0; w[0]=1.0; w[1]=1.0; w[2]=1.0; w[3]=1.0; w[4]=-0.5; REQUIRE( getFunPorog(x, w) == 0 );
    x[0]=1; x[1]=1; x[2]=1; x[3]=1; w[0]=1.0; w[1]=1.0; w[2]=1.0; w[3]=1.0; w[4]=-0.5; REQUIRE( getFunPorog(x, w) == 1 );
}
#endif

/**
Вычисление рациональной сигмоидальной функции
\param[in] x массив сигналов
\param[in] w массив весов
\return значение рациональной сигмоидальной функции
\f$
    f({\rm net})=\frac{1}{2}\left(
    \frac {\rm net}{1+|{\rm net}|} + 1
    \right)
\f$
*/
double getRezSig(int *x, double *w)
{
    if (!x || !w) return -1;
    for (int i=0; i<4; i++) if (x[i] != 0 && x[i] != 1) return -1;
    for (int i=0; i<5; i++) if (w[i] < -1 || w[i] > 1) return -1;
	double net = getNet(x, w);
	return (net / (1 + fabs(net)) + 1) / 2;
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
TEST_CASE( "getRezSig", "[getRezSig]" ) {
    REQUIRE( getRezSig(0, new double[5]) == -1 );
    REQUIRE( getRezSig(new int[4], 0) == -1 );
    
    int *x = new int[4];
    x[0]=0; x[1]=0; x[2]=0; x[3]=2; REQUIRE( getRezSig(x, new double[5]) == -1 );
    x[0]=0; x[1]=0; x[2]=2; x[3]=0; REQUIRE( getRezSig(x, new double[5]) == -1 );
    x[0]=0; x[1]=2; x[2]=0; x[3]=0; REQUIRE( getRezSig(x, new double[5]) == -1 );
    x[0]=2; x[1]=0; x[2]=0; x[3]=0; REQUIRE( getRezSig(x, new double[5]) == -1 );
    
    double *w = new double[5];
    w[0]=0.0; w[1]=0.0; w[2]=0.0; w[3]=0.0; w[4]=2.0; REQUIRE( getRezSig(new int[4], w) == -1 );
    w[0]=0.0; w[1]=0.0; w[2]=0.0; w[3]=2.0; w[4]=0.0; REQUIRE( getRezSig(new int[4], w) == -1 );
    w[0]=0.0; w[1]=0.0; w[2]=2.0; w[3]=0.0; w[4]=0.0; REQUIRE( getRezSig(new int[4], w) == -1 );
    w[0]=0.0; w[1]=2.0; w[2]=0.0; w[3]=0.0; w[4]=0.0; REQUIRE( getRezSig(new int[4], w) == -1 );
    w[0]=2.0; w[1]=0.0; w[2]=0.0; w[3]=0.0; w[4]=0.0; REQUIRE( getRezSig(new int[4], w) == -1 );
    
    x[0]=0; x[1]=0; x[2]=0; x[3]=0; w[0]=1.0; w[1]=1.0; w[2]=1.0; w[3]=1.0; w[4]=-1.0; REQUIRE( getRezSig(x, w) == 0.25 );
    x[0]=1; x[1]=1; x[2]=1; x[3]=1; w[0]=0.25; w[1]=0.25; w[2]=0.25; w[3]=0.25; w[4]=0.0; REQUIRE( getRezSig(x, w) == 0.75 );
}
#endif

/**
Принятие решения по сигмоидальной функции
\param[in] x массив сигналов
\param[in] w массив весов
\return 1 или 0, если решение принято или не принято, соответственно
*/
int getFunSigmaPorog(int *x, double *w)
{
    if (!x || !w) return -1;
    for (int i=0; i<4; i++) if (x[i] != 0 && x[i] != 1) return -1;
    for (int i=0; i<5; i++) if (w[i] < -1 || w[i] > 1) return -1;
	double rez = getRezSig(x, w);
	if (rez >= 0.5) return 1;
	else return 0;
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
TEST_CASE( "getFunSigmaPorog", "[getFunSigmaPorog]" ) {
    REQUIRE( getFunSigmaPorog(0, new double[5]) == -1 );
    REQUIRE( getFunSigmaPorog(new int[4], 0) == -1 );
    
    int *x = new int[4];
    x[0]=0; x[1]=0; x[2]=0; x[3]=2; REQUIRE( getFunSigmaPorog(x, new double[5]) == -1 );
    x[0]=0; x[1]=0; x[2]=2; x[3]=0; REQUIRE( getFunSigmaPorog(x, new double[5]) == -1 );
    x[0]=0; x[1]=2; x[2]=0; x[3]=0; REQUIRE( getFunSigmaPorog(x, new double[5]) == -1 );
    x[0]=2; x[1]=0; x[2]=0; x[3]=0; REQUIRE( getFunSigmaPorog(x, new double[5]) == -1 );
    
    double *w = new double[5];
    w[0]=0.0; w[1]=0.0; w[2]=0.0; w[3]=0.0; w[4]=2.0; REQUIRE( getFunSigmaPorog(new int[4], w) == -1 );
    w[0]=0.0; w[1]=0.0; w[2]=0.0; w[3]=2.0; w[4]=0.0; REQUIRE( getFunSigmaPorog(new int[4], w) == -1 );
    w[0]=0.0; w[1]=0.0; w[2]=2.0; w[3]=0.0; w[4]=0.0; REQUIRE( getFunSigmaPorog(new int[4], w) == -1 );
    w[0]=0.0; w[1]=2.0; w[2]=0.0; w[3]=0.0; w[4]=0.0; REQUIRE( getFunSigmaPorog(new int[4], w) == -1 );
    w[0]=2.0; w[1]=0.0; w[2]=0.0; w[3]=0.0; w[4]=0.0; REQUIRE( getFunSigmaPorog(new int[4], w) == -1 );
    
    x[0]=0; x[1]=0; x[2]=0; x[3]=0; w[0]=1.0; w[1]=1.0; w[2]=1.0; w[3]=1.0; w[4]=-1.0; REQUIRE( getFunSigmaPorog(x, w) == 0 );
    x[0]=1; x[1]=1; x[2]=1; x[3]=1; w[0]=0.25; w[1]=0.25; w[2]=0.25; w[3]=0.25; w[4]=0.0; REQUIRE( getFunSigmaPorog(x, w) == 1 );
}
#endif

/**
Точка входа в программу
\return результат работы программы
*/
int main()
{
	int x[4]; 
	ofstream  fout("Rezult.txt");
	
	double nu = 0.3; // Норма обучения
	for (int I = 0; I < 2; I++) // Цикл по 2-м функциям активации
	{
		switch (I)
		{
		case 0: cout << "FA porogovaya" << endl;   
			fout << "FA porogovaya" << endl;
			break;
		case 1: cout << "FA sigmoidalnaya" << endl;
			fout << "FA sigmoidalnaya" << endl;
		}
		double w[5] = { 0, 0, 0, 0, 0 }; // Начальные веса  w[4] используется вместо нулевого индекса
		int err;  // Ошибка
		int k = 0; // Номер эпохи обучения
		int NumErr; // Число ошибок в эпохе
		int y; // Выход
		do  // Цикл по эпохам обучения
		{

			int i; // Индекс для перехода к другому образцу
			for (i = 0; i < 4; i++) x[i] = 0; // Начальный образец (решение)
			NumErr = 0; // Число ошибок в эпохе
			cout << "k=" << k << endl << "W=" << w[4] << ", ";
			fout << "k=" << k << endl << "W=" << w[4] << ", ";
			for (i = 0; i < 4; i++) {
				cout << w[i] << ", "; // Начальный образец (решение)
				fout << w[i] << ", ";
			}
			
			do  // Цикл просмотра всех значений входных переменных (цикл просмотра образцов обучающей выборки)
			{
				cout << endl << "{" << x[0] << ", " << x[1] << ", " << x[2] << ", " << x[3] << "} -> Y=" << getTableTrue(x);
				fout << endl << "{" << x[0] << ", " << x[1] << ", " << x[2] << ", " << x[3] << "} -> Y=" << getTableTrue(x);
				switch (I)
				{
				case 0: y = getFunPorog(x, w); break; // Используем пороговую функции
				case 1: y = getFunSigmaPorog(x, w); // Используем сигмоидальной функции
				
				}
				cout << endl << "Ocenka Y=";
				cout << y << ", ";
				fout << endl << "Ocenka Y=";
				fout << y << ", ";
				err = getTableTrue(x) - y; // Ошибка
				if (err != 0) { // Есть ошибка
					++NumErr; // Считаем число ошибок в эпохе
					// Коррекция весов
					switch (I)
					{
					case 0: // Пороговая функция
							for (i = 0; i < 4; i++) w[i] += nu*err*x[i];
							w[4] = w[4] += nu*err; // Корректировка w0
							break;
					case 1: // рациональная сигмоидальная функция
						double net = getNet(x, w);
						double proiz; // Значение производной
						if (net >= 0) proiz = 1. / (2 * (1 + net)*(1 + net));
						else proiz = 1. / (2 * (1 - net)*(1 - net));
						// Корректировка весов
						for (i = 0; i < 4; i++)
							for (i = 0; i < 4; i++) w[i] += nu*err*x[i] * proiz;
						w[4] += nu*err*proiz; // Корректировка w0
					}
				}
				// Переход к след решению (образцу) по аналогии с двичными числами
				for (i = 3; i >= 0; --i) if (x[i] == 0) {
					x[i] = 1; break; // Первый с конца разряд равный 0 увеличиваем на 1

				}
				else x[i] = 0; // Последние разряды равные 1 обращаем в 0

			} while (i >= 0); // Если break сработал, то получено новое решение, иначе все решения закончились
			k++; // Номер эпохи увеличиваем на 1
			cout << endl << "Error=" << NumErr << endl;
			fout << endl << "Error=" << NumErr << endl;

		} while (NumErr > 0); // Цикл по эпохам завершается когда число ошибок 0
	}
	fout.close();
	system("pause");
    
    int result = Catch::Session().run();
    return ( result < 0xff ? result : 0xff );
}
