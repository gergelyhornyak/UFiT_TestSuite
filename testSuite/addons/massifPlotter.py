import matplotlib.pyplot as plt
import sys

def main():
    if len(sys.argv) == 3:
        print(f"massif plotter reading {sys.argv[1]} and exporting as {sys.argv[2]}\n")
        
    timestamps = []
    memory_usage = []

    with open(sys.argv[1], "r") as f:
        for line in f:
            if line.startswith("time="):
                timestamps.append(int(line.split("=")[1].strip()))
            elif line.startswith("mem_heap_B="):
                memory_usage.append(int(line.split("=")[1].strip()))

    plt.figure(figsize=(10, 5))
    plt.plot(timestamps, memory_usage)
    plt.xlabel("Time (ticks)")
    plt.ylabel("Heap Memory (bytes)")
    plt.title("Heap Memory Usage Over Time")
    plt.grid()
    plt.savefig(sys.argv[2])
    return 0

if __name__ == "__main__":
    main()
