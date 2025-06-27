import matplotlib.pyplot as plt
import re

def parse_test_results(file_path):
    passed_tests = 0
    failed_tests = 0
    
    with open(file_path, 'r') as file:
        for line in file:
            if match := re.search(r'\[  PASSED  \] (\d+) tests', line):
                passed_tests = int(match.group(1))
            elif match := re.search(r'\[  FAILED  \] (\d+) tests', line):
                failed_tests = int(match.group(1))
    
    return passed_tests, failed_tests

def main():
    file_path = 'test_results.txt'  # Update this to your actual file path
    passed, failed = parse_test_results(file_path)
    labels = ['Passed', 'Failed']
    values = [passed, failed]
    colors = ['green', 'red']
    
    plt.barh(labels, values, color=colors)
    plt.xlabel('Number of Tests')
    plt.title('Test Results')
    plt.show()

if __name__ == "__main__":
    main()
