import matplotlib.pyplot as plt
import numpy as np
import pytest
from triangulate import triang_area, Polygon, triangulate


def test_triang_area():
    xs = [0, 1, 1]
    ys = [0, 0, 1]
    area = triang_area(xs, ys)
    assert area == pytest.approx(0.5)

    xs = [1, 2, 2]
    ys = [1, 1, 2]
    area = triang_area(xs, ys)
    assert area == pytest.approx(0.5)

    xs = [1, 2, 3]
    ys = [1, 2, 1]
    area = triang_area(xs, ys)
    assert area == pytest.approx(1.0)


def test_semi_polygon():
    xs = [0, 1, 1, 0]
    ys = [0, 0, 1, 1]

    polygon = Polygon(xs, ys)

    # pentagon
    theta = np.linspace(0, 2 * np.pi, 6)
    xs = list(np.cos(theta))
    ys = list(np.sin(theta))
    polygon = Polygon(xs, ys)
    fig, ax = plt.subplots(1, 1)
    polygon.plot(ax=ax, linestyle="--")

    triangs = triangulate(polygon)
    for triang in triangs:
        triang.plot(ax=ax, color="red")
    plt.show()
