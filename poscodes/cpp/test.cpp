#include "poscode.hpp"
#include "utils.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <numeric> // Para std::accumulate
#include <cmath>   // Para std::sqrt

// Estructura para definir cada set de datos
struct Dataset {
    std::string filename;
    size_t size;
};

// Función para calcular promedio y desviación estándar
void print_stats(const std::vector<double>& times) {
    if (times.empty()) {
        std::cout << "No data." << std::endl;
        return;
    }
    double sum = std::accumulate(times.begin(), times.end(), 0.0);
    double mean = sum / times.size();

    double sq_sum = 0.0;
    for(const double &t : times) {
        sq_sum += (t - mean) * (t - mean);
    }
    double stdev = std::sqrt(sq_sum / times.size());

    std::cout << "Avg: " << mean << " ms, Stdev: " << stdev << " ms" << std::endl;
}

// Plantilla para correr un experimento con cualquier función de ordenamiento
template<typename SortFunction>
void run_experiment(SortFunction sort_func, Poscode* original_data, size_t n, const std::string& name) {
    std::cout << "\n--- Probando " << name << " ---" << std::endl;
    std::vector<double> timings;

    for (int i = 0; i < 6; ++i) { // 1 corrida de calentamiento + 5 mediciones
        std::vector<Poscode> data_copy(original_data, original_data + n);

        auto start = std::chrono::high_resolution_clock::now();
        sort_func(data_copy.data(), n);
        auto end = std::chrono::high_resolution_clock::now();
        
        std::chrono::duration<double, std::milli> duration = end - start;
        
        if (i > 0) { // Descartamos la primera corrida (calentamiento)
            timings.push_back(duration.count());
        }
    }
    print_stats(timings);
}

int main(int nargs, char** vargs) {
    // Definimos los datasets que vamos a probar
    std::vector<Dataset> datasets = {
        {"/home/anto/universidad/estructuraDeDatosYAlgoritmos/tarea2/entrega2_estructuraDeDatos/poscodes/codes_500K.txt", 500000},
        {"/home/anto/universidad/estructuraDeDatosYAlgoritmos/tarea2/entrega2_estructuraDeDatos/poscodes/codes_1M.txt", 1000000},
        {"/home/anto/universidad/estructuraDeDatosYAlgoritmos/tarea2/entrega2_estructuraDeDatos/poscodes/codes_10M.txt", 10000000}
    };

    for (const auto& ds : datasets) {
        std::cout << "\n=================================================" << std::endl;
        std::cout << "CARGANDO DATASET: " << ds.filename << " (" << ds.size << " elementos)" << std::endl;
        std::cout << "=================================================" << std::endl;

        Poscode* original_data = readCodes(ds.filename, ds.size);
        if (!original_data) {
            std::cerr << "Error al cargar " << ds.filename << std::endl;
            continue; // Saltar al siguiente dataset si hay un error
        }

        // Corremos los 3 experimentos para este dataset
        run_experiment(radix_sort, original_data, ds.size, "RadixSort");
        run_experiment(quick_sort, original_data, ds.size, "QuickSort");
        run_experiment(merge_sort, original_data, ds.size, "MergeSort");

        deleteCodes(original_data); // Liberamos la memoria del dataset actual
    }

    return 0;
}