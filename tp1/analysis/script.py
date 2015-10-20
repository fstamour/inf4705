#!/usr/bin/python3
import csv
from pprint import pprint
import matplotlib.pyplot as plt
import math
import numpy
from scipy import interpolate
from scipy.optimize import curve_fit, optimize


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

def f(x):
    return x*math.log(x, 10)

print("generating plots")
plots0 = {}
# prepare data in plots0
# plots0 = [ log(x), log(y), x, y/f(x), f(x), y]
for key, value in res_0.items():
    if (key[1], key[2]) not in plots0.keys():
        plots0[(key[1], key[2])] = {"x1":[], "y1": [], "x2": [], "y2": [], "x3": [], "y3": []}
    x = float(key[0])
    y = value
    plots0[(key[1], key[2])]["x1"].append(math.log(x))
    plots0[(key[1], key[2])]["y1"].append(math.log(y))
    plots0[(key[1], key[2])]["x2"].append(x)
    plots0[(key[1], key[2])]["y2"].append(float(y)/f(x))
    plots0[(key[1], key[2])]["x3"].append(float(f(x)))
    plots0[(key[1], key[2])]["y3"].append(y)

for key, value in plots0.items():
    #test du rapport
    x = numpy.array(value["x1"])
    y = numpy.array(value["y1"])
    A = numpy.vstack([x, numpy.ones(len(x))]).T
    m, c = numpy.linalg.lstsq(A,y)[0]
    plt.plot(x, y, "o", label="test de rapport", markersize=10)
    plt.plot(x, m*x + c, "r", label="Fitted line")
    plt.legend()
    filename = "plot_testrapport_0_" + str(key[0]) + "_" + key[1] + ".png"
    print("saving file : " + filename)
    plt.savefig(filename)
    plt.cla()
    plt.clf()
    plt.close()

    #test de puissance
    points = []
    for xi, yi in zip(value["x2"], value["y2"]):
        points.append([xi, yi])

    points.sort(key=lambda x:x[0])
    plt.plot([i[0] for i in points], [i[1] for i in points], marker='o', linestyle='-', label="test du puissance")
    plt.legend()
    filename = "plot_testpuissance_0_" + str(key[0]) + "_" + key[1] + ".png"
    print("saving file : " + filename)
    plt.savefig(filename)
    plt.cla()
    plt.clf()
    plt.close()

    #test des constantes
    points.clear()
    for xi, yi in zip(value["x3"], value["y3"]):
        points.append([xi, yi])

    points.sort(key=lambda x:x[0])
    plt.plot([i[0] for i in points], [i[1] for i in points], marker='o', linestyle='-', label="test de constantes")
    plt.legend()
    filename = "plot_testconstante_0_" + str(key[0]) + "_" + key[1] + ".png"
    print("saving file : " + filename)
    plt.savefig(filename)
    plt.cla()
    plt.clf()
    plt.close()

plots1 = {}
for key, value in res_1.items():
    if (key[1], key[2]) not in plots1.keys():
        plots1[(key[1], key[2])] = {"x1":[], "y1": [], "x2": [],"y2": [], "x3": [], "y3": []}
    x = float(key[0])
    y = value
    plots1[(key[1], key[2])]["x1"].append(math.log(x))
    plots1[(key[1], key[2])]["y1"].append(math.log(y))
    plots1[(key[1], key[2])]["x2"].append(x)
    plots1[(key[1], key[2])]["y2"].append(y/f(x))
    plots1[(key[1], key[2])]["x3"].append(float(f(x)))
    plots1[(key[1], key[2])]["y3"].append(y)

# test de rapport
for key, value in plots1.items():
    x = numpy.array(value["x1"])
    y = numpy.array(value["y1"])
    A = numpy.vstack([x, numpy.ones(len(x))]).T
    m, c = numpy.linalg.lstsq(A,y)[0]
    plt.plot(x, y, "o", label="original data", markersize=10)
    plt.plot(x, m*x + c, "r", label="Fitted line")
    plt.legend()
    filename = "plot_testrapport_1_" + str(key[0]) + "_" + key[1] + ".png"
    print("saving file: " + filename)
    plt.savefig(filename)
    plt.cla()
    plt.clf()
    plt.close()

    # test de puissance
    points = []
    for xi, yi in zip(value["x2"], value["y2"]):
        points.append([xi, yi])

    points.sort(key=lambda x:x[0])
    plt.plot([i[0] for i in points], [i[1] for i in points], marker='o', linestyle='-', label="test du puissance")
    plt.legend()
    filename = "plot_testpuissance_1_" + str(key[0]) + "_" + key[1] + ".png"
    print("saving file : " + filename)
    plt.savefig(filename)
    plt.clf()

    # test des constantes
    points.clear()
    for xi, yi in zip(value["x3"], value["y3"]):
        points.append([xi, yi])

    points.sort(key=lambda x:x[0])
    plt.plot([i[0] for i in points], [i[1] for i in points], marker='o', linestyle='-', label="test de constantes")
    plt.legend()
    filename = "plot_testconstante_1_" + str(key[0]) + "_" + key[1] + ".png"
    print("saving file : " + filename)
    plt.savefig(filename)
    plt.cla()
    plt.clf()
    plt.close()

print("done")
