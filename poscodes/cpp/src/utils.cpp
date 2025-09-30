#include "utils.hpp"
#include "linkedList.hpp"
#include "poscode.hpp"
#include "node.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>  

//a <=> b
void swap(Poscode& a, Poscode& b) {
    Poscode temp = a;
    a = b;
    b = temp;
}

//dividir aleatoriamente
int split_qs(Poscode *A, int i, int j) {
    int p = i + rand() % (j - i + 1);

    while (i < j) {
        while (i < p && A[i].getData() <= A[p].getData()) {
            i++;
        }

        while (j > p && A[j].getData() >= A[p].getData()) {
            j--;
        }

        swap(A[i], A[j]);

        if (i == p) {
            p = j;
        } else if (j == p) {
            p = i;
        }
    }
    return p;
}

//función del quick_sort como el libro
void quick_sort_recursivo(Poscode *A, int i, int j) {
    if (i < j) {
        int k = split_qs(A, i, j);
        quick_sort_recursivo(A, i, k - 1);
        quick_sort_recursivo(A, k + 1, j);
    }
}

//quick_sort para n datos 
void quick_sort(Poscode *A, size_t n) {
    if (n > 1) {
        quick_sort_recursivo(A, 0, n - 1);
    }
}

//ordena el subarreglo
void merge(Poscode *A, int i, int j, int k) {
    std::vector<Poscode> A_aux(j - i + 1);
    int q = 0;
    int p1 = i;
    int p2 = k + 1;

    while (p1 <= k && p2 <= j) {
        if (A[p1].getData() <= A[p2].getData()) {
            A_aux[q] = A[p1];
            p1++;
        } else {
            A_aux[q] = A[p2];
            p2++;
        }
        q++;
    }

    while (p1 <= k) {
        A_aux[q] = A[p1];
        p1++;
        q++;
    }

    while (p2 <= j) {
        A_aux[q] = A[p2];
        p2++;
        q++;
    }

    for (size_t idx = 0; idx < A_aux.size(); ++idx) {
        A[i + idx] = A_aux[idx];
    }
}

//función del merges_sort como el libro
void merge_sort_recursivo(Poscode *A, int i, int j) {
    if (i < j) {
        int k = i + (j - i) / 2;
        merge_sort_recursivo(A, i, k);
        merge_sort_recursivo(A, k + 1, j);
        merge(A, i, j, k);
    }
}

//merge_sort para n datos
void merge_sort(Poscode *A, size_t n) {
    if (n > 1) {
        merge_sort_recursivo(A, 0, n - 1);
    }
}

//se ordena de derecha a izquierda el código
void radix_sort(Poscode *A, size_t n){
    counting_sort(A, n, 5);
    counting_sort(A, n, 4);
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
    //ver si es la columna es un número o letra
    int M;
    if (p >= 4) {
        M = 26;
    }
    else {
        M = 10;
    }

    //node: arreglo de listas enlazadas de tamaño M
    LinkedList node[M];

    //Recorremos todo el arreglo A
    for(int i = 0; i < n; i++){
        //para cada elemento de A vemos la columna p
        char valor = A[i].getValue(p);
        //convertir las letras en numeros
        int M_index;
        if (p >= 4) {
            M_index = valor - 'A';
        }
        else {
            M_index = valor - '0';
        }
        //guardamos el indice del elemento de A
        if(M_index >= 0 && M_index < M){
            node[M_index].add_last(i);
        }
    }

    //creamos un arreglo array
    std::vector<Poscode> array(n);;
    size_t posicion = 0;
    //recorremos todo el arreglo de node 
    for(int i = 0; i < M; i++){
        //recorremos los indices que contiene cada lista del arreglo node
        Node* node_ = node[i].get_head();
        while (node_ != nullptr){
            //obtenemos el indice original del elemento
            size_t index = node_ -> getData();
            //guarda en array el elemento en A en la posición index
            array[posicion] = A[index];
            posicion ++;
            node_ = node_ -> getNext();
        }
    }

    //copiamos lo que hay en array en A
    for(int i = 0; i < n; i++){
        A[i] = array[i];
    }

}