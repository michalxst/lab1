#include "sort_algorithms.h"
#include <chrono>
#include <fstream>
#include <iostream>
#include <math.h>

#define DataType int 


template<typename T>
using SortFncPoint = void (*)(T*, T*, int, int, int);


template<typename T>
void print_table(T *tab, int n)
{
    for (int i = 0; i < n; i++) std::cout << tab[i] << " ";
}


template<typename T>
T *create_table(int n)
{
	return new T[n];
}


template<typename T>
void kill_table(T *table)
{
	delete[] table;
}


//wypelnia tabele uzywajac random numerow
//1-100000
template<typename T>
void fill_random(T *tab, int n)
{
	for (int i = 0; i < n; i++) tab[i] = rand() % 100000 + 1;
}


//sortuje dany procent tabeli
template<typename T>
void sort_percent(T *tab, int n, double percent)
{
    if (percent == 100) //sortuje w odwrotnej kolejnosci
    {
        std::sort(tab, tab + n, std::greater<T>());
        return;
    }
	std::sort(tab, tab + (int)((n*percent) / 100));
}


template<typename T>
void check_if_sorted(T *tab, int n)
{
    for (int i = 0; i < n - 1 ; i++)
    {
        if(tab[i] > tab[i + 1])
        {
            std::cout << "Tabela nie zostala posortowana!\nNastepuje wylaczenie programu";
            std::cin.get();
            exit(1);
        }
    }
}


void check_if_open (std::ofstream &file)
{
    if (!file.is_open())
     {
        std::cout << "Plik nie zostal otwarty\nNastepuje wylaczenie programu";
        std::cin.get();
        exit(1);
     }
}


//wykonac sortowanie tabeli w podany sposob
//czas sortowania podany w ms
template<typename T>
double sort_it(SortFncPoint<DataType> fp, int n, T *tab, T *tmp)
{
    auto t_start = std::chrono::high_resolution_clock::now(); //wlacz zegar
    fp(tab, tmp, 0, n-1, log(n) * 2);
    auto t_end = std::chrono::high_resolution_clock::now(); //wylacz zegar

    return std::chrono::duration<double, std::milli>(t_end - t_start).count(); 
}


// sortuje tabele w okreslonych warunkach
//zapisuje wynik (czas sortowania) w pliku Results.txt
// funkcja w terminalu pokazuje status sortowania
int main()
{
    std::ofstream file("Results.txt");
    check_if_open(file);

    srand(time(NULL));

	int loops = 1; //liczba tabel posortowanych w kazdej konfiguracji
	int ntab[5] = {10000, 50000, 100000, 500000, 1000000}; //rozmiary tablic
	double percenttab[8] = {0, 25, 50, 75, 95, 99, 99.7, 100}; //procent posortowanych elementow, 100 oznacza tablice posortowana od tylu

	SortFncPoint<DataType> mpoint= &mergeWrap, qpoint = &quickWrap, ipoint = &introWrap; //wskazniki na funkcje sort
    SortFncPoint<DataType> ptable[3] = {qpoint, mpoint, ipoint};

	double counter = 0;
	int iter = 0;
	std::string sorts[3] = {"QUCIK_SORT", "MERGE_SORT", "INTRO_SORT"};

    for(SortFncPoint<DataType> fp : ptable) //dla kazdej funkcji sortujacej
    {
        std::cout << sorts[iter++] << std::endl;
        for (double percent : percenttab) //dla kazdego wczesniej posrtowanego procenta
        {
            for (int n : ntab) // dla kazdej wielkosci tabeli
            {
                DataType *tab = create_table<DataType>(n);
                DataType *tmp = create_table<DataType>(n);

                for (int i = 0; i < loops; i++) //posortuj okreslona liczbe tabel
                {
                    fill_random<DataType>(tab, n);
                    sort_percent<DataType>(tab, n, percent);
                    counter += sort_it<DataType>(fp, n, tab, tmp);
                    check_if_sorted<DataType>(tab, n);

                    std::cout << i << "%" << "\r";
                }
                kill_table<DataType>(tab);
                kill_table<DataType>(tmp);

                std::cout << n << " tablica posortowana!" << std::endl;

                file << counter / loops << " "; //zapisuje czas na posortowanie
                counter = 0;
            }
            std::cout << percent << " % posortowane.!" << std::endl;
        }
        file << "\n";
    }
    std::cout << "END OF SORTING!";
	std::cin.get();
	file.close();

	return 0;
}