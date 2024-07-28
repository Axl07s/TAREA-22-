// Autor: Axel Molineros
// Fecha: 2024-07-25
// 1) Utilice el programa que mide el tiempo de ejecución de los algoritmos de ordenación.
// a) Agregue el algoritmo de ordenación secuencial.
// b) Ahora midamos listas grandes:

#include <iostream>
#include <cstdlib>
#include <time.h>
#include <windows.h>
#include <vector>

using namespace std;

// Llena los vectores con números aleatorios
void VectorNumAleatorios(vector<int>& v, int total) {
    int lim_inf = 1;
    int lim_sup = 1000;
    v.clear(); // Limpiar el vector antes de llenarlo
    for(int k = 0; k < total; k++) {
        int numero = lim_inf + rand() % ((lim_sup + 1) - lim_inf);
        v.push_back(numero);
    }
}

// Intercambia dos números (corregido usando referencias)
void Intercambiar(int& num1, int& num2) {
    int aux = num1;
    num1 = num2;
    num2 = aux;
}

// Ordena el arreglo usando el algoritmo de burbuja mejorado
void burbujaMejorado(vector<int>& arreglo) {
    int tamano = arreglo.size();
    int comparaciones = tamano;
    bool termino = false;
    for (int i = 0; i < (tamano-1); i++) {
        if (termino)
            break;
        termino = true;
        for (int j = 0; j < comparaciones-1; j++) {
            if (arreglo[j] > arreglo[j+1]) {
                Intercambiar(arreglo[j], arreglo[j+1]);
                termino = false;
            }
        }
        comparaciones--;
    }
}

// Ordena el arreglo usando el algoritmo de ordenamiento Shell
void ordenShell(vector<int>& a) {
    int n = a.size();
    int ints, i, aux;
    bool band;

    ints = n;
    while(ints > 1) {
        ints = ints / 2;
        band = true;
        while(band == true) {
            band = false;
            i = 0;
            while((i + ints) < n) {
                if(a[i] > a[i + ints]) {
                    aux = a[i];
                    a[i] = a[i + ints];
                    a[i + ints] = aux;
                    band = true;
                }
                i++;
            }
        }
    }
}

// Ordena el arreglo usando el algoritmo de ordenamiento Shell optimizado
void ordenShellOptimizado(vector<int>& a) {
    int n = a.size();
    int ints, i, aux;
    bool band;

    ints = n;
    while(ints > 1) {
        ints = (ints * 10) / 13; // Factor de reducción óptimo según la literatura
        if (ints < 1)
            ints = 1;
        
        band = true;
        while(band == true) {
            band = false;
            i = 0;
            while((i + ints) < n) {
                if(a[i] > a[i + ints]) {
                    aux = a[i];
                    a[i] = a[i + ints];
                    a[i + ints] = aux;
                    band = true;
                }
                i++;
            }
        }
    }
}

void OrdenamientoQuicksort(vector<int>& a, int primerValor, int ultimoValor) {
    int central, i, j, pivote;
    central = (primerValor + ultimoValor) / 2; //Posicion central del arreglo
    pivote = a[central]; //Capturar el valor medio del arreglo
    i = primerValor;
    j = ultimoValor;
    do {
        //Separando en dos partes el arreglo
        while(a[i] < pivote) i++; //Separando los valores menores al pivote
        while(a[j] > pivote) j--; //Separando los valores mayores al pivote
        if(i <= j) {
            int temporal;
            //Intercambio de valores
            temporal = a[i];
            a[i] = a[j];
            a[j] = temporal;
            i++;
            j--;
        }
    } while(i <= j);

    if (primerValor < j)
        OrdenamientoQuicksort(a, primerValor, j);

    if (i < ultimoValor)
        OrdenamientoQuicksort(a, i, ultimoValor);
}

// Ordena el arreglo usando el algoritmo de ordenación secuencial
void ordenSecuencial(vector<int>& a) {
    int n = a.size();
    for (int i = 1; i < n; i++) {
        int key = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}

// Función para calcular diferencia de tiempos usando QueryPerformanceCounter
double performancecounter_diff(LARGE_INTEGER *a, LARGE_INTEGER *b) {
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    return (double)(a->QuadPart - b->QuadPart) / (double)freq.QuadPart;
}

int main() {
    srand(time(NULL));
    
    // Tamaños de listas pequeñas
    vector<int> tamanos_pequenos = {10, 20, 30, 40, 50};
    
    // Tamaños de listas grandes
    vector<int> tamanos_grandes = {5000, 15000, 30000, 45000, 60000};
    
    LARGE_INTEGER t_ini, t_fin;
    double seg_secuencial, seg_burbuja, seg_shell, seg_shellopt, seg_quicksort;

    cout << "Medición de tiempos para listas pequeñas" << endl;
    
    // Medición de tiempos para listas pequeñas
    for (int tamano : tamanos_pequenos) {
        vector<int> vectorSecuencial, vectorBurbuja, vectorShell, vectorShell_Opt, vectorQuickSort;
        VectorNumAleatorios(vectorSecuencial, tamano);
        vectorBurbuja = vectorShell = vectorShell_Opt = vectorQuickSort = vectorSecuencial;
        
        // Algoritmo de ordenación secuencial
        QueryPerformanceCounter(&t_ini);
        ordenSecuencial(vectorSecuencial);
        QueryPerformanceCounter(&t_fin);
        seg_secuencial = performancecounter_diff(&t_fin, &t_ini);
        cout << "Secuencial, " << tamano << " elementos: " << seg_secuencial * 1000.0 << " ms" << endl;

        // Algoritmo de burbuja mejorado
        QueryPerformanceCounter(&t_ini);
        burbujaMejorado(vectorBurbuja);
        QueryPerformanceCounter(&t_fin);
        seg_burbuja = performancecounter_diff(&t_fin, &t_ini);
        cout << "Burbuja Mejorado, " << tamano << " elementos: " << seg_burbuja * 1000.0 << " ms" << endl;
        
        // Algoritmo de ordenamiento Shell
        QueryPerformanceCounter(&t_ini);
        ordenShell(vectorShell);
        QueryPerformanceCounter(&t_fin);
        seg_shell = performancecounter_diff(&t_fin, &t_ini);
        cout << "Shell, " << tamano << " elementos: " << seg_shell * 1000.0 << " ms" << endl;
        
        // Algoritmo de ordenamiento Shell optimizado
        QueryPerformanceCounter(&t_ini);
        ordenShellOptimizado(vectorShell_Opt);
        QueryPerformanceCounter(&t_fin);
        seg_shellopt = performancecounter_diff(&t_fin, &t_ini);
        cout << "Shell Optimizado, " << tamano << " elementos: " << seg_shellopt * 1000.0 << " ms" << endl;
        
        // Algoritmo de ordenamiento QuickSort
        QueryPerformanceCounter(&t_ini);
        OrdenamientoQuicksort(vectorQuickSort, 0, vectorQuickSort.size() - 1);
        QueryPerformanceCounter(&t_fin);
        seg_quicksort = performancecounter_diff(&t_fin, &t_ini);
        cout << "QuickSort, " << tamano << " elementos: " << seg_quicksort * 1000.0 << " ms" << endl;
    }
    
    cout << "\nMedición de tiempos para listas grandes" << endl;
    
    // Medición de tiempos para listas grandes
    for (int tamano : tamanos_grandes) {
        vector<int> vectorSecuencial, vectorBurbuja, vectorShell, vectorShell_Opt, vectorQuickSort;
        VectorNumAleatorios(vectorSecuencial, tamano);
        vectorBurbuja = vectorShell = vectorShell_Opt = vectorQuickSort = vectorSecuencial;
        
        // Algoritmo de ordenación secuencial
        QueryPerformanceCounter(&t_ini);
        ordenSecuencial(vectorSecuencial);
        QueryPerformanceCounter(&t_fin);
        seg_secuencial = performancecounter_diff(&t_fin, &t_ini);
        cout << "Secuencial, " << tamano << " elementos: " << seg_secuencial * 1000.0 << " ms" << endl;

        // Algoritmo de burbuja mejorado
        QueryPerformanceCounter(&t_ini);
        burbujaMejorado(vectorBurbuja);
        QueryPerformanceCounter(&t_fin);
        seg_burbuja = performancecounter_diff(&t_fin, &t_ini);
        cout << "Burbuja Mejorado, " << tamano << " elementos: " << seg_burbuja * 1000.0 << " ms" << endl;
        
        // Algoritmo de ordenamiento Shell
        QueryPerformanceCounter(&t_ini);
        ordenShell(vectorShell);
        QueryPerformanceCounter(&t_fin);
        seg_shell = performancecounter_diff(&t_fin, &t_ini);
        cout << "Shell, " << tamano << " elementos: " << seg_shell * 1000.0 << " ms" << endl;
        
        // Algoritmo de ordenamiento Shell optimizado
        QueryPerformanceCounter(&t_ini);
        ordenShellOptimizado(vectorShell_Opt);
        QueryPerformanceCounter(&t_fin);
        seg_shellopt = performancecounter_diff(&t_fin, &t_ini);
        cout << "Shell Optimizado, " << tamano << " elementos: " << seg_shellopt * 1000.0 << " ms" << endl;
        
        // Algoritmo de ordenamiento QuickSort
        QueryPerformanceCounter(&t_ini);
        OrdenamientoQuicksort(vectorQuickSort, 0, vectorQuickSort.size() - 1);
        QueryPerformanceCounter(&t_fin);
        seg_quicksort = performancecounter_diff(&t_fin, &t_ini);
        cout << "QuickSort, " << tamano << " elementos: " << seg_quicksort * 1000.0 << " ms" << endl;
    }
    
    return 0;
}
