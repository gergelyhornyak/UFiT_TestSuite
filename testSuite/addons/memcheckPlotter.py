import matplotlib.pyplot as plt
import sys
import re

def main():
    if len(sys.argv) == 3:
        print(f"memcheck plotter reading {sys.argv[1]} and exporting as {sys.argv[2]}\n")

    leak_pattern = re.compile(r"(definitely lost|indirectly lost|possibly lost|still reachable|suppressed): (\d+) bytes")
    leak_counts = {"definitely lost": 0, "indirectly lost": 0, "possibly lost": 0, "still reachable": 0, "suppressed": 0}
    
    with open(sys.argv[1], "r") as f:
        for line in f:
            match = leak_pattern.search(line)
            if match:
                leak_type, bytes_lost = match.groups()
                leak_counts[leak_type] += int(bytes_lost)

    plt.figure(figsize=(10, 5))
    plt.bar(leak_counts.keys(), leak_counts.values(), color=['red', 'orange', 'yellow', 'blue', 'cyan'])
    #plt.xticks(rotation=20, ha='right')
    plt.xlabel("Leak Severity")
    plt.ylabel("Bytes Lost")
    plt.title("Memory Leaks Detected by Valgrind Memcheck")
    plt.grid()
    plt.savefig(sys.argv[2])
    return 0

if __name__ == "__main__":
    main()
