import matplotlib.pyplot as plt
import numpy as np

sizes_data = [500000, 1000000, 10000000]

radix_means = [928.401, 2107.36, 29852.7]
quick_means = [243.514, 518.198, 6581.54]
merge_means = [477.965, 1639.68, 14149.7]

x_ticks_values = [500000, 1000000, 10000000]
x_ticks_labels = ['500K', '1M', '10M']

fig, ax = plt.subplots(figsize=(12, 8))

ax.plot(sizes_data, radix_means, marker='o', linestyle='-', label='RadixSort', color='blue')
ax.plot(sizes_data, quick_means, marker='s', linestyle='-', label='QuickSort', color='green')
ax.plot(sizes_data, merge_means, marker='^', linestyle='-', label='MergeSort', color='red')
ax.set_xscale('log')
ax.set_yscale('log')
ax.set_ylabel('Tiempo de Ejecución (ms)')
ax.set_xlabel('Tamaño del Dataset')
ax.set_title('Comparación de Rendimiento de Algoritmos')
ax.legend()
ax.grid(True, which="both", ls="--")
ax.set_xticks(x_ticks_values)
ax.set_xticklabels(x_ticks_labels)

plt.savefig('rendimiento_lineas_final.png')

print("¡Gráfico 'rendimiento_lineas_final.png' generado con éxito!")