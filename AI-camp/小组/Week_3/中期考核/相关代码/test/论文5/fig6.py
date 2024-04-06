import matplotlib.pyplot as plt
import two

L = 3
n = 200 * L
number_of_elements = n
step = L / number_of_elements
start = 0.0
end = L
custom_list = [round(start + i * step, 2) for i in range(number_of_elements)]
model = two.Interaction(1)

new_list = []
weights = []

for i in range(n):
    if i > 500:
        nums = [925]
    elif i < 200 and i > 100:
        nums = [300]
    elif i > 300 and i < 400:
        nums = [200]
    else:
        nums = [142]
    weights += nums

for time in range(31):
    new_list.append(custom_list)
    custom_list = model.interact(custom_list,weights=weights)

plt.plot(new_list,linewidth=0.3)
plt.xticks(range(0, 30, 5))  # 设置 x 轴刻度
plt.yticks((0, 0.5, 1, 1.5, 2, 2.5, 3))  # 设置 y 轴刻度
plt.xlim(0, 30)
plt.ylim(0, 3)
plt.xlabel('t')
plt.ylabel('x')
# plt.savefig('fig6')
plt.show()