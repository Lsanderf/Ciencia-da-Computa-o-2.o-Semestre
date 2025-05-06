import random
import time
import matplotlib.pyplot as plt

# Classe para contar métricas
class Metrics:
    def __init__(self):
        self.comparisons = 0
        self.movements = 0

# Algoritmos de ordenação
def selection_sort(arr, metrics):
    n = len(arr)
    for i in range(n):
        min_idx = i
        for j in range(i+1, n):
            metrics.comparisons += 1
            if arr[j] < arr[min_idx]:
                min_idx = j
        if i != min_idx:
            arr[i], arr[min_idx] = arr[min_idx], arr[i]
            metrics.movements += 1

def insertion_sort(arr, metrics):
    for i in range(1, len(arr)):
        key = arr[i]
        j = i - 1
        while j >= 0 and arr[j] > key:
            metrics.comparisons += 1
            arr[j + 1] = arr[j]
            metrics.movements += 1
            j -= 1
        metrics.comparisons += 1
        arr[j + 1] = key
        metrics.movements += 1

def bubble_sort(arr, metrics):
    n = len(arr)
    for i in range(n):
        for j in range(0, n - i - 1):
            metrics.comparisons += 1
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]
                metrics.movements += 1

def quicksort(arr, metrics):
    def _quicksort(arr, low, high):
        if low < high:
            pi = partition(arr, low, high)
            _quicksort(arr, low, pi - 1)
            _quicksort(arr, pi + 1, high)

    def partition(arr, low, high):
        pivot = arr[high]
        i = low - 1
        for j in range(low, high):
            metrics.comparisons += 1
            if arr[j] < pivot:
                i += 1
                arr[i], arr[j] = arr[j], arr[i]
                metrics.movements += 1
        arr[i + 1], arr[high] = arr[high], arr[i + 1]
        metrics.movements += 1
        return i + 1

    _quicksort(arr, 0, len(arr) - 1)

# Tamanhos dos vetores e resultados
sizes = [100, 1000, 10000]
results = {"Selection": [], "Insertion": [], "Bubble": [], "Quicksort": []}

# Função para medir desempenho
def benchmark_sort(algorithm, name):
    for size in sizes:
        arr = [random.randint(0, size) for _ in range(size)]
        metrics = Metrics()
        arr_copy = arr.copy()
        start = time.time()
        algorithm(arr_copy, metrics)
        end = time.time()
        results[name].append({
            "size": size,
            "time": (end - start) * 1000,
            "comparisons": metrics.comparisons,
            "movements": metrics.movements
        })

# Executa benchmarks
benchmark_sort(selection_sort, "Selection")
benchmark_sort(insertion_sort, "Insertion")
benchmark_sort(bubble_sort, "Bubble") 
benchmark_sort(quicksort, "Quicksort")

# Função para plotar gráficos
def plot_metric(metric):
    for name in results:
        plt.plot(sizes, [entry[metric] for entry in results[name]], label=name)
    plt.xlabel("Tamanho do vetor")
    plt.ylabel(metric.capitalize())
    plt.title(f"{metric.capitalize()} vs Tamanho do vetor")
    plt.legend()
    plt.grid(True)
    plt.xscale("log")
    plt.yscale("log")
    plt.show()

# Gerar gráficos de tempo, comparações e movimentações
plot_metric("time")
plot_metric("comparisons")
plot_metric("movements")
