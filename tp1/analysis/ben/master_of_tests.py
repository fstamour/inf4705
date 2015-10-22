#!/usr/bin/python3
import csv
import math
from pprint import pprint as p
import matplotlib.pyplot as plt
import sys
import numpy

def func_theoric(x):
    return x * math.log10(x)

def read_data(filename):
    with open(filename, "r") as f:
        points = {}
        reader = csv.reader(f, delimiter=",")
        for row in reader:
            serie = row[0].split("_")[2]
            serie = serie.split(".")[0]
            serie = int(int(serie)/10)
            size = row[1]
            time = float(row[2])
            if (serie, size) not in points.keys():
                points[(serie, size)] = time
            else:
                points[(serie, size)] += time

        for (serie, size), time in points.items():
            points[(serie, size)] /= 10

        return points


def test_rapport(data, filename):
    result = data

    array_0 = []
    array_1 = []
    array_2 = []
    for (serie, size), time in result.items():
        x = float(size)
        y = time / func_theoric(time)
        if serie == 0:
            array_0.append((x,y))
        elif serie == 1:
            array_1.append((x,y))
        else:
            array_2.append((x,y))

    array_0.sort(key=lambda x:x[0])
    plt.plot([x for (x,y) in array_0], [y for (x,y) in array_0])
    plt.savefig(filename + "0-9_rapport.png")
    plt.cla()
    plt.clf()
    plt.close()

    array_1.sort(key=lambda x:x[0])
    plt.plot([x for (x,y) in array_1], [y for (x,y) in array_1])
    plt.savefig(filename + "10-19_rapport.png")
    plt.cla()
    plt.clf()
    plt.close()

    array_2.sort(key=lambda x:x[0])
    plt.plot([x for (x,y) in array_2], [y for (x,y) in array_2])
    plt.savefig(filename + "20-29_rapport.png")
    plt.cla()
    plt.clf()
    plt.close()

def test_puissance(data, filename):
    result = data

    x_0 = []
    y_0 = []
    x_1 = []
    y_1 = []
    x_2 = []
    y_2 = []
    for (serie, size), time, in result.items():
        xi = math.log(float(size))
        yi = math.log(time)
        if serie == 0:
            x_0.append(xi)
            y_0.append(yi)
        elif serie == 1:
            x_1.append(xi)
            y_1.append(yi)
        else:
            x_2.append(xi)
            y_2.append(yi)
    x = numpy.array(x_0)
    y = numpy.array(y_0)
    A = numpy.vstack([x, numpy.ones(len(x))]).T
    m, c = numpy.linalg.lstsq(A,y)[0]
    plt.plot(x, y, "o", label="test de puissance", markersize=10)
    plt.plot(x, m*x + c, "r", label="y = " + str(m) + "x + " + str(c))
    plt.legend()
    plt.savefig(filename + "0-9_puissance.png")
    plt.cla()
    plt.clf()
    plt.close()

    x = numpy.array(x_1)
    y = numpy.array(y_1)
    A = numpy.vstack([x, numpy.ones(len(x))]).T
    m, c = numpy.linalg.lstsq(A,y)[0]
    plt.plot(x, y, "o", label="test de puissance", markersize=10)
    plt.plot(x, m*x + c, "r", label="y = " + str(m) + "x + " + str(c))
    plt.legend()
    plt.savefig(filename + "10-19_puissance.png")
    plt.cla()
    plt.clf()
    plt.close()

    x = numpy.array(x_2)
    y = numpy.array(y_2)
    A = numpy.vstack([x, numpy.ones(len(x))]).T
    m, c = numpy.linalg.lstsq(A,y)[0]
    plt.plot(x, y, "o", label="test de puissance", markersize=10)
    plt.plot(x, m*x + c, "r", label="y = " + str(m) + "x + " + str(c))
    plt.legend()
    plt.savefig(filename + "20-29_puissance.png")
    plt.cla()
    plt.clf()
    plt.close()

def test_constante(data, filename):
    result = data

    array_0 = []
    array_1 = []
    array_2 = []
    for (serie, size), time in result.items():
        x = func_theoric(float(size))
        if serie == 0:
            array_0.append((x, time))
        elif serie == 1:
            array_1.append((x, time))
        else:
            array_2.append((x, time))

    array_0.sort(key=lambda x:x[0])
    plt.plot([x for (x,y) in array_0], [y for (x,y) in array_0])
    plt.savefig(filename + "0-9_constante.png")
    plt.cla()
    plt.clf()
    plt.close()

    array_1.sort(key=lambda x:x[0])
    plt.plot([x for (x,y) in array_1], [y for (x,y) in array_1])
    plt.savefig(filename + "10-19_constante.png")
    plt.cla()
    plt.clf()
    plt.close()

    array_2.sort(key=lambda x:x[0])
    plt.plot([x for (x,y) in array_2], [y for (x,y) in array_2])
    plt.savefig(filename + "20-29_constante.png")
    plt.cla()
    plt.clf()
    plt.close()



if __name__ == "__main__":
    for filename in sys.argv[1:]:
        data = read_data(filename)
        test_rapport(data, filename)
        test_puissance(data, filename)
        test_constante(data, filename)

