#include "utils.hpp"
#include "linkedList.hpp"
#include "poscode.hpp"
#include "node.hpp"

#include <iostream>
#include <fstream>
#include <vector>


// --- Agrega estas funciones a utils.cpp ---

// Función auxiliar para intercambiar dos elementos
void swap(Poscode& a, Poscode& b) {
    Poscode temp = a;
    a = b;
    b = temp;
}

// Función de partición
int partition(Poscode *A, int low, int high) {
    Poscode pivot = A[high]; // Tomamos el último elemento como pivote
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        // Comparamos los códigos postales como strings
        if (A[j].getData() < pivot.getData()) {
            i++;
            swap(A[i], A[j]);
        }
    }
    swap(A[i + 1], A[high]);
    return (i + 1);
}

// Función recursiva de QuickSort
void quick_sort_recursive(Poscode *A, int low, int high) {
    if (low < high) {
        int pi = partition(A, low, high);
        quick_sort_recursive(A, low, pi - 1);
        quick_sort_recursive(A, pi + 1, high);
    }
}

// Esta es la función principal que debes rellenar
void quick_sort(Poscode *A, size_t n) {
    if (n > 0) {
        quick_sort_recursive(A, 0, n - 1);
    }
}


// --- Agrega estas funciones a utils.cpp ---

// Función para combinar (merge) dos sub-arreglos ordenados
void merge(Poscode *A, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Crear arreglos temporales
    std::vector<Poscode> L(n1), R(n2);

    // Copiar datos a los arreglos temporales L[] y R[]
    for (int i = 0; i < n1; i++)
        L[i] = A[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = A[mid + 1 + j];

    // Combinar los arreglos temporales de vuelta en A[left..right]
    int i = 0; // Índice inicial del primer sub-arreglo
    int j = 0; // Índice inicial del segundo sub-arreglo
    int k = left; // Índice inicial del sub-arreglo combinado

    while (i < n1 && j < n2) {
        if (L[i].getData() <= R[j].getData()) {
            A[k] = L[i];
            i++;
        } else {
            A[k] = R[j];
            j++;
        }
        k++;
    }

    // Copiar los elementos restantes de L[], si hay alguno
    while (i < n1) {
        A[k] = L[i];
        i++;
        k++;
    }

    // Copiar los elementos restantes de R[], si hay alguno
    while (j < n2) {
        A[k] = R[j];
        j++;
        k++;
    }
}

// Función recursiva de MergeSort
void merge_sort_recursive(Poscode *A, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort_recursive(A, left, mid);
        merge_sort_recursive(A, mid + 1, right);
        merge(A, left, mid, right);
    }
}

// Esta es la función principal que debes rellenar
void merge_sort(Poscode *A, size_t n) {
    if (n > 1) {
        merge_sort_recursive(A, 0, n - 1);
    }
}


//para ordenar los codigos vamos de derecha a izquierda
void radix_sort(Poscode *A, size_t n){
    // 1. Ordenar la segunda letra
    counting_sort(A, n, 5);

    // 2. Ordenar la primera letra
    counting_sort(A, n, 4);

    // 3. Ordenar los 4 dígitos, de derecha a izquierda
    counting_sort(A, n, 3);
    counting_sort(A, n, 2);
    counting_sort(A, n, 1);
    counting_sort(A, n, 0);

}

Poscode *readCodes(const std::string &strfile, size_t n){
    // Replace "example.txt" with the actual path to your text file.
    Poscode *codes = new Poscode[n];

    std::ifstream inputFile(strfile);    
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the file!" << std::endl;        
        return nullptr;
    }
    // 3. Read the file content line by line.
    std::string line;
    for(size_t i = 0; i < n; i++){
        std::getline(inputFile, line); 
        codes[i] = Poscode(line);
    }
    
    inputFile.close();
    return codes;
}

void deleteCodes(Poscode *codes){
    if (codes != nullptr) {
        delete[] codes;
    }    
}

void counting_sort(Poscode *A, size_t n, int p){
    int M;
    if (p >= 4) {
        M = 26;
    }
    else {
        M = 10;
    }

    LinkedList node[M];

    for(int i = 0; i < n; i++){
        char valor = A[i].getValue(p);
        int M_index;
        if (p >= 4) {
            M_index = valor - 'A';
        }
        else {
            M_index = valor - '0';
        }
        if(M_index >= 0 && M_index < M){
            node[M_index].add_last(i);
        }
    }

    std::vector<Poscode> array(n);;
    size_t posicion = 0;
    for(int i = 0; i < M; i++){
        Node* node_ = node[i].get_head();
        while (node_ != nullptr){
            size_t index = node_ -> getData();
            array[posicion] = A[index];
            posicion ++;
            node_ = node_ -> getNext();
        }
    }

    for(int i = 0; i < n; i++){
        A[i] = array[i];
    }

}