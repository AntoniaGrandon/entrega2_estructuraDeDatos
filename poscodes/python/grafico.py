import matplotlib.pyplot as plt
import numpy as np

sizes_data = [500000, 1000000, 10000000]

radix_means = [786.15, 2420.14, 30545.00]
quick_means = [331.74, 648.57, 9818.94]
merge_means = [541.55, 864.32, 20726.60]

x_ticks_values = [10000, 100000, 500000, 1000000, 10000000]
x_ticks_labels = ['10K', '100K', '500K', '1M', '10M']

fig, ax = plt.subplots(figsize=(12, 8))

ax.plot(sizes_data, radix_means, marker='o', linestyle='-', label='RadixSort', color='blue')
ax.plot(sizes_data, quick_means, marker='s', linestyle='-', label='QuickSort', color='green')
ax.plot(sizes_data, merge_means, marker='^', linestyle='-', label='MergeSort', color='red')
ax.set_xscale('log')
ax.set_yscale('log')
ax.set_ylabel('Tiempo de Ejecución (ms)')
ax.set_xlabel('Tamaño del Dataset')
ax.set_title('Comparación de Rendimiento de Algoritmos (Escala Log-Log)')
ax.legend()
ax.grid(True, which="both", ls="--")
ax.set_xticks(x_ticks_values)
ax.set_xticklabels(x_ticks_labels)

plt.savefig('rendimiento_lineas_final.png')

print("¡Gráfico 'rendimiento_lineas_final.png' generado con éxito!")