import matplotlib.pyplot as plt
import one
import numpy as np

model = one.Interaction(1)
L = 10
n = 100 * L
number_of_elements = n
step = L/number_of_elements
start = 0.0
end = L
new_list = []
custom_list = [round(start + i * step, 2) for i in range(number_of_elements)]
# custom_list = np.random.uniform(0, 10, 1000)

for time in range(20):
    new_list.append(custom_list)
    custom_list = model.interact(custom_list)

plt.plot(new_list,linewidth=0.3)

plt.xticks([0, 5, 10, 15])  # 设置 x 轴刻度为 0 到 10，步长为 2
plt.yticks(range(0, 15, 1))  # 设置 y 轴刻度
plt.xlim(0, 15)
plt.ylim(0, 10)
plt.xlabel('t')
plt.ylabel('x')
# plt.savefig('fig1(b)')
plt.show()
