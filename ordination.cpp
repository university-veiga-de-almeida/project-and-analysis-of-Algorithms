#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <chrono>
#include <unistd.h>
#include <iostream>

using namespace std;

int *v, *v1, *v2, *v3, *v4, *v5, *v6, *v7;

// MY CODE
void radixSort(int vector[], int sz) {
    int i;
    int *b;
    int bigger = vector[0];
    int exp = 1;

    b = (int *)calloc(sz, sizeof(int));

    for (i = 0; i < sz; i++) {
        if (vector[i] > bigger)
    	    bigger = vector[i];
    }

    while (bigger/exp > 0) {
        int bucket[10] = { 0 };
    	for (i = 0; i < sz; i++)
    	    bucket[(vector[i] / exp) % 10]++;
    	for (i = 1; i < 10; i++)
    	    bucket[i] += bucket[i - 1];
    	for (i = sz - 1; i >= 0; i--)
    	    b[--bucket[(vector[i] / exp) % 10]] = vector[i];
    	for (i = 0; i < sz; i++)
    	    vector[i] = b[i];
    	exp *= 10;
    }

    free(b);
}

//-------------------------------------------------------------------------------------
void bubbleSort(int v[], int n)
{
    bool changed;
    int k = n;

    do {
      changed = false;
      k--;
      for (int i = 0; i < k; i++)
        if (v[i+1] < v[i]) {
          int aux = v[i+1];
          v[i+1] = v[i];
          v[i] = aux;
          changed = true;
        }
    } while (changed);
}

//-------------------------------------------------------------------------------------
void insertionSort(int v[], int n)
{
    int i, j, key;
    for (j = 1; j < n; j++) {
        key = v[j];
        i = j - 1;
        while (i >= 0 && v[i] > key) {
            v[i+1] = v[i];
            i--;
        }
        v[i+1] = key;
    }
}

//-------------------------------------------------------------------------------------
void selectionSort(int v[], int n)
{
  int i, j, min;

  for(i = 0; i < n-1; i++) {
    min = i;
    for (j = i + 1; j < n; j++)
      if (v[j] < v[min])
        min = j;

    if (min != i) {
      int temp = v[min];
      v[min] = v[i];
      v[i] = temp;
    }
  }
}

//-------------------------------------------------------------------------------------
void shellSort(int v[], int n)
{
    int i , j , value;
    int h = 1;
    while(h < n) {
        h = 3*h+1;
    }
    while (h > 1) {
        h /= 3;
        for(i = h; i < n; i++) {
            value = v[i];
            j = i - h;
            while (j >= 0 && value < v[j]) {
                v [j + h] = v[j];
                j -= h;
            }
            v [j + h] = value;
        }
    }
}

//-------------------------------------------------------------------------------------
void quickSort1(int v[], int ini, int end)
{
    int i = ini;
    int j = end;
    int pivot = v[(ini+ end)/2];  // Pivot is the central element

    do
    {
        while (v[i] < pivot && i < end)
            i++;
        while (pivot < v[j] && j > ini)
            j--;
        if (i <= j)
        {
            int aux = v[i];
            v[i] = v[j];
            v[j] = aux;
            i++;
            j--;
        }
    } while (i <= j);

    if (ini < j)
        quickSort1(v,ini,j);
    if (i < end)
        quickSort1(v,i,end);
}

void quickSort(int v[], int sz)
{
    quickSort1(v, 0, sz-1);
}

//-------------------------------------------------------------------------------------
void intercalate(int v[], int aux[], int ini, int mid, int end)
{
    int i = ini, j = end, k;

    for (k = ini; k <= mid; k++)
        aux[k] = v[k];

    for (k = mid+1; k <= end; k++)
        aux[end + mid + 1 - k] = v[k];

    for (k = ini; k <= end; k++)
        if (aux[i] <= aux[j])
            v[k] = aux[i++];
        else
            v[k] = aux[j--];
}

void mergeSort1(int v[], int aux[], int ini, int end)
{
    if (ini < end) {
        int mid = (ini + end) / 2;
        mergeSort1(v, aux, ini, mid);
        mergeSort1(v, aux, mid+1, end);
        intercalate(v, aux, ini, mid, end);
    }
}

void mergeSort(int v[], int n)
{
    int *aux = (int *) malloc(n * sizeof(int));

    mergeSort1(v, aux, 0, n-1);

    free(aux);
}

//-------------------------------------------------------------------------------------
void generate(int v[], int sz)
{
    srand((unsigned int)time(NULL));

    for (int i = 0; i < sz; i++)
        v[i] = rand() % INT_MAX;
}

//-------------------------------------------------------------------------------------
void copy(int origin[], int destiny[], int n)
{
    for (int i = 0; i < n; i++)
        destiny[i] = origin[i];
}

//-------------------------------------------------------------------------------------
bool check(int v[], int n)
{
    for (int i = 0; i < n-1; i++)
        if (v[i] > v[i+1])
            return false;

    return true;
}

//-------------------------------------------------------------------------------------
void invert(int v[], int n)
{
    for (int i = 0, j = n-1; i < n/2; i++,j--)
        v[i] = v[j];
}

//-------------------------------------------------------------------------------------
int main(void)
{
    chrono::steady_clock::time_point start, end;
    long double cpu_time;
    int sz, iter;
    char  methods[100];
    long double time[] = { 0, 0, 0, 0, 0, 0, 0 };

    sz = 0;
    printf("How many numbers do you want?? ");
    scanf("%d", &sz);
    getchar();

    if (sz <= 0)
        return 0;

    printf("SELECT THE METHOD:\n 1-RADIX SORT [MY CODE] \n 2-Bubble sort\n 3-Selection sort\n 4-Insertion sort\n 5-Shell sort\n 6-Quicksort\n 7-Mergesort\n methods: ");
    gets( methods);

    printf("How many executions do you want? (1, 2, 3, ...)? ");
    scanf("%d", &iter);
    getchar();

    if (iter <= 0)
        return 0;

    v  = (int *) malloc(sz * sizeof(int));
    v1 = (int *) malloc(sz * sizeof(int));
    v2 = (int *) malloc(sz * sizeof(int));
    v3 = (int *) malloc(sz * sizeof(int));
    v4 = (int *) malloc(sz * sizeof(int));
    v5 = (int *) malloc(sz * sizeof(int));
    v6 = (int *) malloc(sz * sizeof(int));
    v7 = (int *) malloc(sz * sizeof(int));

    for (int i = 1; i <= iter; i++) {
        printf("------------------------------------------------\nExecucao %d:\n------------------------------------------------\n", i);

        printf("Gerando %d elementos...\n", sz);
        generate(v, sz);
        copy(v, v1, sz);
        copy(v, v2, sz);
        copy(v, v3, sz);
        copy(v, v4, sz);
        copy(v, v5, sz);
        copy(v, v6, sz);
        copy(v, v7, sz);

        // RadixSort
        if (strchr( methods, '1') != NULL) {
            printf("RADIX SORT [MY CODE]...\n");

            start = chrono::steady_clock::now();

            radixSort(v7, sz);

            end = chrono::steady_clock::now();

            cpu_time = chrono::duration_cast<chrono::nanoseconds>(end - start).count() / (long double) 1000000.0;

            printf("%s. time: %lf ms (%lf s)\n", check(v1, sz) ? "OK":"ERRO", cpu_time, cpu_time/1000);

            time[0] += cpu_time;
        }

        // bubble
        if (strchr( methods, '2') != NULL) {
            printf("Bubble sort...\n");

            start = chrono::steady_clock::now();

            bubbleSort(v1, sz);

            end = chrono::steady_clock::now();

            cpu_time = chrono::duration_cast<chrono::nanoseconds>(end - start).count() / (long double) 1000000.0;

            printf("%s. time: %lf ms (%lf s)\n", check(v1, sz) ? "OK":"ERRO", cpu_time, cpu_time/1000);

            time[0] += cpu_time;
        }

        // selection
        if (strchr( methods, '3') != NULL) {
            printf("Selection sort...\n");
            start = chrono::steady_clock::now();

            selectionSort(v3, sz);

            end = chrono::steady_clock::now();

            cpu_time = chrono::duration_cast<chrono::nanoseconds>(end - start).count() / (long double) 1000000.0;

            printf("%s. time: %lf ms (%lf s)\n", check(v3, sz) ? "OK":"ERRO", cpu_time, cpu_time/1000);

            time[1] += cpu_time;
        }

        // insertion
        if (strchr( methods, '4') != NULL) {
            printf("Insertion sort...\n");

            start = chrono::steady_clock::now();

            insertionSort(v2, sz);

            end = chrono::steady_clock::now();

            cpu_time = chrono::duration_cast<chrono::nanoseconds>(end - start).count() / (long double) 1000000.0;

            printf("%s. time: %lf ms (%lf s)\n", check(v2, sz) ? "OK":"ERRO", cpu_time, cpu_time/1000);

            time[2] += cpu_time;
        }


        // shell
        if (strchr( methods, '5') != NULL) {
            printf("Shell sort...\n");

            start = chrono::steady_clock::now();

            shellSort(v4, sz);

            end = chrono::steady_clock::now();

            cpu_time = chrono::duration_cast<chrono::nanoseconds>(end - start).count() / (long double) 1000000.0;

            printf("%s. time: %lf ms (%lf s)\n", check(v4, sz) ? "OK":"ERRO", cpu_time, cpu_time/1000);

            time[3] += cpu_time;
        }

        // quick
        if (strchr( methods, '6') != NULL) {
            printf("Quick sort...\n");

            start = chrono::steady_clock::now();

            quickSort(v5, sz);

            end = chrono::steady_clock::now();

            cpu_time = chrono::duration_cast<chrono::nanoseconds>(end - start).count() / (long double) 1000000.0;

            printf("%s. time: %lf ms (%lf s)\n", check(v5, sz) ? "OK":"ERRO", cpu_time, cpu_time/1000);

            time[4] += cpu_time;
        }

        // merge
        if (strchr( methods, '7') != NULL) {
            printf("Merge sort...\n");

            start = chrono::steady_clock::now();

            mergeSort(v6, sz);

            end = chrono::steady_clock::now();

            cpu_time = chrono::duration_cast<chrono::nanoseconds>(end - start).count() / (long double) 1000000.0;

            printf("%s. time: %lf ms (%lf s)\n", check(v6, sz) ? "OK":"ERRO", cpu_time, cpu_time/1000);

            time[5] += cpu_time;
        }
    }

    if (iter > 1) {
        printf("-------------------------------------------\ntimes medios:\n");
        if (strchr( methods, '1') != NULL)
            printf("RADIX SORT [MY CODE]:    %lf ms (%lf s)\n", time[0]/iter, time[0]/(iter*1000));
        if (strchr( methods, '2') != NULL)
            printf("Bubble sort:    %lf ms (%lf s)\n", time[1]/iter, time[1]/(iter*1000));
        if (strchr( methods, '3') != NULL)
            printf("selection sort: %lf ms (%lf s)\n", time[2]/iter, time[2]/(iter*1000));
        if (strchr( methods, '4') != NULL)
            printf("Insertion sort: %lf ms (%lf s)\n", time[3]/iter, time[3]/(iter*1000));
        if (strchr( methods, '5') != NULL)
            printf("Shell sort:     %lf ms (%lf s)\n", time[4]/iter, time[4]/(iter*1000));
        if (strchr( methods, '6') != NULL)
            printf("Quick sort:     %lf ms (%lf s)\n", time[5]/iter, time[5]/(iter*1000));
        if (strchr( methods, '7') != NULL)
            printf("Merge sort:     %lf ms (%lf s)\n", time[6]/iter, time[6]/(iter*1000));
    }

    free(v);
    free(v1);
    free(v2);
    free(v3);
    free(v4);
    free(v5);
    free(v6);
    free(v7);
}
