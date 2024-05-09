import matplotlib.pyplot as plt

# Data for Basic Version
basic_data = {
    16: {'CPU Time': 0.024, 'Memory Usage': 1245184},
    64: {'CPU Time': 0.195, 'Memory Usage': 1261568},
    128: {'CPU Time': 0.729, 'Memory Usage': 1294336},
    256: {'CPU Time': 2.786, 'Memory Usage': 1392640},
    384: {'CPU Time': 6.209, 'Memory Usage': 1687552},
    512: {'CPU Time': 11.151, 'Memory Usage': 2113536},
    768: {'CPU Time': 24.912, 'Memory Usage': 2637824},
    1024: {'CPU Time': 44.941, 'Memory Usage': 4079616},
    1280: {'CPU Time': 68.843, 'Memory Usage': 6127616},
    1536: {'CPU Time': 96.822, 'Memory Usage': 7618560},
    2048: {'CPU Time': 177.071, 'Memory Usage': 8093696},
    2560: {'CPU Time': 274.003, 'Memory Usage': 12582912},
    3072: {'CPU Time': 383.559, 'Memory Usage': 20594688},
    3584: {'CPU Time': 539.232, 'Memory Usage': 27312128},
    3968: {'CPU Time': 662.058, 'Memory Usage': 28409856}
}

# Data for Memory Efficient Version
memory_efficient_data = {
    16: {'CPU Time': 0.095, 'Memory Usage': 1376256},
    64: {'CPU Time': 0.582, 'Memory Usage': 1490944},
    128: {'CPU Time': 1.907, 'Memory Usage': 1490944},
    256: {'CPU Time': 6.582, 'Memory Usage': 1523712},
    384: {'CPU Time': 16.053, 'Memory Usage': 1769472},
    512: {'CPU Time': 28.482, 'Memory Usage': 1818624},
    768: {'CPU Time': 50.135, 'Memory Usage': 2048000},
    1024: {'CPU Time': 86.267, 'Memory Usage': 2244608},
    1280: {'CPU Time': 130.61, 'Memory Usage': 2293760},
    1536: {'CPU Time': 183.312, 'Memory Usage': 2506752},
    2048: {'CPU Time': 335.72, 'Memory Usage': 2555904},
    2560: {'CPU Time': 518.107, 'Memory Usage': 2588672},
    3072: {'CPU Time': 719.758, 'Memory Usage': 2670592},
    3584: {'CPU Time': 1011.669, 'Memory Usage': 2768896},
    3968: {'CPU Time': 1236.576, 'Memory Usage': 2834432}
}

# Extracting data for plotting
sizes = list(basic_data.keys())
basic_cpu_times = [basic_data[size]['CPU Time'] for size in sizes]
basic_memory_usages = [basic_data[size]['Memory Usage'] for size in sizes]

memory_efficient_cpu_times = [memory_efficient_data[size]['CPU Time'] for size in sizes]
memory_efficient_memory_usages = [memory_efficient_data[size]['Memory Usage'] for size in sizes]

# Plotting Memory Graph
plt.figure(figsize=(10, 6))
plt.plot(sizes, basic_memory_usages, label='Basic Version')
plt.plot(sizes, memory_efficient_memory_usages, label='Memory Efficient Version')
plt.xlabel('Problem Size (m+n)')
plt.ylabel('Memory Usage (KB)')
plt.title('Memory Usage Comparison')
plt.legend()
plt.grid(True)
plt.show()

# Plotting Time Graph
plt.figure(figsize=(10, 6))
plt.plot(sizes, basic_cpu_times, label='Basic Version')
plt.plot(sizes, memory_efficient_cpu_times, label='Memory Efficient Version')
plt.xlabel('Problem Size (m+n)')
plt.ylabel('CPU Time (ms)')
plt.title('CPU Time Comparison')
plt.legend()
plt.grid(True)
plt.show()
