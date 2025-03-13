from eplot.Graph import GraphMaker
from eplot.Graph import LineType
from eplot.Graph import XY_PlotEntry, XY2_PlotEntry, Switches
from eplot.Legend import Position

import math

B = 3650
Ro = 100e3

R1 = 1000e3
R2 = 10e3

T = 100

mlt = 0.1
x = [i * mlt for i in range(1, int(T / mlt))]

g = GraphMaker("100k_B4250_0-120")
for r in [100, 200, 300, 510, 750, 1e3, 2e3, 3e3, 5.1e3, 7.5e3, 10e3, 20e3, 30e3, 51e3, 75e3]:
    R2 = r
    vo = []
    for i in x:
        h = Ro * math.pow(math.e, B * (1.0 / (i + 273) - 1.0 / (25 + 273)))
        vo.append(((R1 * R2 + R2 * h) * 5.0 / (R1 * h + R1 * R2 + h)))
    g.AddEntry(XY_PlotEntry(x, vo, f"$V_o$ ($R_1={'{: .1e}'.format(R1)}$, $R_2={'{: .1e}'.format(R2)}$, $B=4250$)", line=LineType.Solid))

g.Plot(("Temp [C]", "$Vo$ [V]"), legposition=Position.OutsideLower)
