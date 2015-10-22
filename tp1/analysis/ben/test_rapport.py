#!/usr/bin/python3
import csv
import math
from pprint import pprint as p
import matplotlib.pyplot as plt
import sys

def func_theoric(x):
    return x * math.log10(x)

def test_rapport(filename):
    result = {}
    with open(filename, "r") as f:
        reader = csv.reader(f, delimiter=",")
        for row in reader:
            serie = row[0]
            serie = serie.split("_")
            serie = serie[2]
            serie = serie.split(".")[0]
            serie = int(int(serie)/ 10)
            size = row[1]
            time = row[2]
            if (serie, size) not in result.keys():
                result[(serie, size)] = float(time)
            else:
                result[(serie, size)] += float(time)

    for (serie, size), time in result.items():
        result[(serie, size)] /= 10

    array = []
    for (serie, size), time in result.items():
        x = float(size)
        y = float(time) / func_theoric(float(time))
        array.append((x,y))

    array.sort(key=lambda x:x[0])
    plt.plot([x for (x,y) in array], [y for (x,y) in array])
    plt.savefig(filename + "_rapport.png")
    plt.cla()
    plt.clf()
    plt.close()

if __name__ == "__main__":
    for filename in sys.argv[1:]:
        test_rapport(filename)

