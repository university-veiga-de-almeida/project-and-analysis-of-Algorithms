#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <limits>
#include <string>
#include <ctype.h>
#include <string.h>
#include <locale.h>

using namespace std;

// TIME COMPLEXITY: O(1)
typedef struct dataInput {
    unsigned int n = 0;
    unsigned int m = 0;

    char *a;
    char *b;
} DATAINPUT;

// TIME COMPLEXITY: O(1)
void cleanScreen() {
    system("CLS");
}

// TIME COMPLEXITY: BEST CASE THE O(n)
void intercalate(char v[], char aux[], int ini, int middle, int last) {
    int i = ini, j = last, k;

    for (k = ini; k <= middle; k++)
        aux[k] = v[k];

    for (k = middle+1; k <= last; k++)
        aux[last + middle + 1 - k] = v[k];

    for (k = ini; k <= last; k++)
        (aux[i] <= aux[j]) ? v[k] = aux[i++] : v[k] = aux[j--];
}

// TIME COMPLEXITY: BEST CASE THE O(n) --> intercalate, WORST CASE O(n log n)
void mergeSort(char v[], char aux[], int ini, int last) {
    if (ini < last) {
        int middle = (ini + last) / 2;
        mergeSort(v, aux, ini, middle);
        mergeSort(v, aux, middle+1, last);
        intercalate(v, aux, ini, middle, last);
    }
}

// TIME COMPLEXITY: WORST CASE O(n)
bool isChar(char v[], int TAM_MAX) {
    for(int i = 0; i < TAM_MAX; i++) {
        if(!isalpha(v[i])) {
            return false;
        }

        if(i == TAM_MAX - 1 && isalpha(v[i])) {
            return true;
        }
    }
}

// TIME COMPLEXITY: BEST CASE THE O(n), WORST CASE O(n log n) -> mergeSort
bool hasRepetition(char v[], int TAM_MAX) {
    mergeSort(v, new char[TAM_MAX], 0, TAM_MAX-1);

    for(int i = 0; i < TAM_MAX; i++) {
        if(v[i] == v[i+1]) {
            return true;
        }

        if(i == TAM_MAX-1) {
            return false;
        }
    }
}

// TIME COMPLEXITY: BEST CASE THE (1), WORST CASE O(n) -> RESURGENCE
void menuSizeInput(char type, string phrase, DATAINPUT *di) {
    int val;

    cout << "ENTER WITH THE QUANTITY OF ENTRY TO " << phrase << ": " << endl;
    cin >> val;

    // VERIFICA SE A ENTRADA ESTÁ DO TIPO CORRETO
    if(cin.fail() || val <= 0) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        cleanScreen();

        cout << "INVALID VALUE!" << endl;
        cout << "IMPORTANT: "
        << "\n 1) INPUT CAN NOT BE DIFFERENT FROM A NUMERICAL DIGIT!"
        << "\n 2) ENTRY CAN NOT BE LESS OR EQUAL TO ZERO!"
        << "\n 3) INPUT CAN NOT CONTAIN EQUAL CHARACTERS!\n\n" << endl;

        menuSizeInput(type, phrase, di);
    } else {
        cleanScreen();

        switch(type) {
            case 'A':
                di->n = val;
                break;
            case 'B':
                di->m = val;
                break;
        }
    }
}

// TIME COMPLEXITY: BEST CASE THE (1), WORST CASE O(n) -> RESURGENCE
void menuCharInput(char type, string phrase, DATAINPUT *di) {
    unsigned int TAM_MAX = 0;
    char *c;

    switch(type) {
        case 'A':
            TAM_MAX = di->n;
            c = new char[TAM_MAX];
            break;
        case 'B':
            TAM_MAX = di->m;
            c = new char[TAM_MAX];
            break;
    }

    (TAM_MAX > 1)
        ? cout << "DIGITE [" << TAM_MAX << "]" << " CHAR ONLY IN A LINE AND WITHOUT BLANK SPACES, TO " << phrase << ": " << endl
        : cout << "DIGITE [" << TAM_MAX << "]" << " CHAR ONLY IN A LINE AND WITHOUT BLANK SPACES, TO " << phrase << ": " << endl;

    cin >> c;

    if(strlen(c) < TAM_MAX || strlen(c) > TAM_MAX || !isChar(c, TAM_MAX) || hasRepetition(c, TAM_MAX)) {
        cleanScreen();

        cout << "INVALID VALUE!" << endl;
        cout << "IMPORTANT: "
        << "\n 1) INPUT CAN NOT BE DIFFERENT FROM AN ALPHANUMERIC SET!"
        << "\n 2) ENTRANCE CAN NOT CONTAIN BLANK SPACES!"
        << "\n 3) INPUT CAN NOT CONTAIN EQUAL CHARACTERS!"
        << "\n 4) INPUT CAN NOT BE LESS THAN [" << TAM_MAX << "]!\n\n" << endl;

        menuCharInput(type, phrase, di);
    } else {
        cleanScreen();

        switch(type) {
            case 'A':
                di->a = c;
                break;
            case 'B':
                di->b = c;
                break;
        }
    }
}

// TIME COMPLEXITY: O(m + n) = O(n)
void intersection(char a[], int n, char b[], int m, char c[], int *k) {
    int i = 0, j = 0;

    *k = 0;

    while(i < n && j < m) {
        if (a[i] < b[j]) {
            i++;
        } else if (b[j] < a[i]) {
            j++;
        } else { /* SE A == B */
            c[(*k)++] = b[j];
            i++;
        }
    }

    c[sizeof c + 1] = '\0';

    // CÓDIGO TEMPORÁRIO, SOMENTE PARA EXIBIR
    // NÃO CONSIDERA-LO NO TRABALHO!
    printf("VECTOR A: {%s} \n", a);
    printf("VECTOR B: {%s} \n", b);
    printf("VECTOR C: {%s} \n", c);
}

// TIME COMPLEXITY: BEST CASE THE O(n), WORST CASE O(n log n) -> mergeSort + intersection
int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "Portuguese");

    string phraseVetorA = "[VETOR A]", phraseVetorB = "[VETOR B]";
    DATAINPUT di;

    menuSizeInput('A', phraseVetorA, &di);
    menuSizeInput('B', phraseVetorB, &di);

    menuCharInput('A', phraseVetorA, &di);
    menuCharInput('B', phraseVetorB, &di);

    char vectorC[max(sizeof di.n, sizeof di.m)] = { 0 };
    int sizeK = sizeof vectorC;

    intersection(di.a, di.n, di.b, di.m, vectorC, &sizeK);
}
