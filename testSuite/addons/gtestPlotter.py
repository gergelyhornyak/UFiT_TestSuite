import matplotlib.pyplot as plt
import sys
import re

def main():

    inputFile = ""
    labels = ["PASSED","FAILED"]
    tests = [0,0]

    test_pattern = re.compile(r"\[\s*(OK|FAILED)\s*\] (\S+) \((\d+) ms\)")

    with open(sys.argv[1], "r") as f:
        inputFile = f.read()
    
    inputFile.split("Global test environment tear-down")[0]

    for match in test_pattern.findall(inputFile):
        print(match)
        status, test_name, time = match

        if status == "OK":
            tests[0] += 1  
        else:
            tests[1] += 1

    plt.figure(figsize=(5, 5))
    fig, ax = plt.subplots()
    ax.pie(tests, labels=labels, colors=['green', 'red'], autopct='%d%%', wedgeprops={"edgecolor": "black"})
    plt.title("Google Test Results")
    plt.savefig("gtest_results.png")
    return 0

if __name__ == "__main__":
    main()
