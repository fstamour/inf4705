#!/usr/bin/python3
import csv
from pprint import pprint
import matplotlib.pyplot as plt
import math
import numpy


res_0 = {}
res_1 = {}
for size in ["1000", "5000", "10000", "50000", "100000", "500000"]:
    for serie in [0, 1, 2]:
        for threashold in ["1", "8"]:
            res_0[(size, serie, threashold)] = 0
            res_0[(size, serie, threashold)] = 0
            res_0[(size, serie, threashold)] = 0
            res_1[(size, serie, threashold)] = 0
            res_1[(size, serie, threashold)] = 0
            res_1[(size, serie, threashold)] = 0

print("reading csv")
with open("results.csv", "r") as f:
    reader = csv.reader(f, delimiter=',')
    next(reader)
    for row in reader:
        size = row[0]
        value = float(row[1])
        serie = int(int(row[2]) / 10)
        threashold = row[3]
        random = row[4]
        if random == "1":
            res_1[(size, serie, threashold)] += value
        else:
            res_0[(size, serie, threashold)] += value

for row in res_1.keys():
    res_1[row] /= 10

for row in res_0.keys():
    res_0[row] /= 10

print("done")

print("generating plots")
plots0 = {}
for key, value in res_0.items():
    if (key[1], key[2]) not in plots0.keys():
        plots0[(key[1], key[2])] = {"x":[], "y": []}
    plots0[(key[1], key[2])]["x"].append(math.log(float(key[0])))
    plots0[(key[1], key[2])]["y"].append(math.log(value))

for key, value in plots0.items():
    x = numpy.array(value["x"])
    y = numpy.array(value["y"])
    A = numpy.vstack([x, numpy.ones(len(x))]).T
    m, c = numpy.linalg.lstsq(A,y)[0]
    plt.plot(x, y, "o", label="original data", markersize=10)
    plt.plot(x, m*x + c, "r", label="Fitted line")
    plt.legend()
    filename = "plot_0_" + str(key[0]) + "_" + key[1] + ".png"
    print("saving file : " + filename)
    plt.savefig(filename)
    plt.clf()

plots1 = {}
for key, value in res_1.items():
    if (key[1], key[2]) not in plots1.keys():
        plots1[(key[1], key[2])] = {"x":[], "y": []}
    plots1[(key[1], key[2])]["x"].append(math.log(float(key[0])))
    plots1[(key[1], key[2])]["y"].append(math.log(value))

for key, value in plots1.items():
    x = numpy.array(value["x"])
    y = numpy.array(value["y"])
    A = numpy.vstack([x, numpy.ones(len(x))]).T
    m, c = numpy.linalg.lstsq(A,y)[0]
    plt.plot(x, y, "o", label="original data", markersize=10)
    plt.plot(x, m*x + c, "r", label="Fitted line")
    plt.legend()
    filename = "plot_1_" + str(key[0]) + "_" + key[1] + ".png"
    print("saving file: " + filename)
    plt.savefig(filename)
    plt.clf()

print("done")
