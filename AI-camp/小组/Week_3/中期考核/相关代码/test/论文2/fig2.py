import matplotlib.pyplot as plt
import one
from math import sqrt
import numpy as np


coordinates = [[]for _ in range(10)]
coordinates[0] = [0, 0.5]
coordinates[1] = [0, 1]
coordinates[2] = [-1.2, 1]
coordinates[3] = [1.2, 1]
coordinates[4] = [-0.5, 1.5]
coordinates[5] = [0.5, 1.5]
coordinates[6] = [-0.7, 2]
coordinates[7] = [0.5, 2]
coordinates[8] = [0, 2.2]
coordinates[9] = [0, 3]
coordinates = np.array(coordinates)
gamas = [1/len(coordinates), 2/len(coordinates), 2/len(coordinates)+0.02]

for gama in gamas:
    model = one.Interaction(1, gama=gama)
    f_list = []
    temp = coordinates
    for i in range(12):
        print(f"Γ={gama}")
        print(coordinates)
        sum_x = sum(coord[0] for coord in coordinates)
        sum_y = sum(coord[1] for coord in coordinates)

        # 计算平均值得到中心坐标
        center_x = sum_x / len(coordinates)
        center_y = sum_y / len(coordinates)
        c = np.array((center_x, center_y))
        print(c)
        fx = 0.0
        for coord in coordinates:
            fx += sqrt((coord[0] - c[0])**2 + (coord[1] - c[1])**2)
        coordinates = model.interact(coordinates)
        f_list.append(fx)
    coordinates = temp
    t = [i+1 for i in range(len(f_list)-1)]
    plt.plot(t, f_list[1:], label=f'Γ={gama}')

plt.xticks(range(0, 12, 1))  # 设置 x 轴刻度为 0 到 10，步长为 2
plt.yticks([1, 2, 3, 4, 5, 6, 7, 8, 9])  # 设置 y 轴刻度
plt.xlim(1, 11)
plt.ylim(0, 9)
plt.xlabel('t/s')
plt.ylabel('f(x)')
plt.legend(loc='upper right')
plt.savefig('fig2')
plt.show()
