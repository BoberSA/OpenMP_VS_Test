// omp_test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "math.h"

#define N 12500000


int _tmain(int argc, _TCHAR* argv[])
{
	double *a, *b, *c;
	
	a = new double[N];

	if (!a)
		return 0;

	b = new double[N];

	if (!b) {
		delete [] a;
		return 0;
	}

	c = new double[N];

	if (!c) {
		delete [] a;
		delete [] b;
		return 0;
	}

	int i, j;
	omp_set_dynamic(0);      // запретить менять число потоков с помощью переменной окружения
	omp_set_num_threads(4); // установить число потоков
	
	// инициализируем векторы
  
	for (i = 0; i < N; i++)
	{
		a[i] = i * 1.0;
		b[i] = i * 2.0;
	}
 
	std::cout << "-=:[ OpenMP test ]:=-" << std::endl;
	std::cout << "you can start Task Manager and see:" << std::endl;
	std::cout << "- 300MB memory consumption," << std::endl;
	std::cout << "- 4 threads for this process," << std::endl;
	std::cout << "- 100% processor loading." << std::endl << std::endl;
	std::cout << "doing some calculations..." << std::endl;
	// вычисляем что-то
	#pragma omp parallel shared(a, b, c) private(i)
	{
		#pragma omp for
		for (i = 0; i < N; i++)
			for (j = 0; j < 100; j++)
			c[i] = sqrt(sqrt(a[i]) + sqrt(b[i]));
	}
	std::cout << "calculations are done" << std::endl;
	std::cout << "press enter" << std::endl;

	std::cin.get();

	delete [] a;
	delete [] b;
	delete [] c;

	return 0;
}