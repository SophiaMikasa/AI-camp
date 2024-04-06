import matplotlib.pyplot as plt
import two

L = 4
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
    if i > 450:
        nums = [50]
    elif i < 350:
        nums = [50]
    else:
        nums = [47]
    # nums = [1]
    weights += nums

for time in range(15):
    new_list.append(custom_list)
    custom_list = model.interact(custom_list,weights=weights)

plt.plot(new_list,linewidth=0.3)
plt.xticks([0, 5, 10, 15])  # 设置 x 轴刻度
plt.yticks((0, 0.5, 1, 1.5, 2, 2.5, 3, 3.5, 4))  # 设置 y 轴刻度
plt.xlim(0, 15)
plt.ylim(0, 4)
plt.xlabel('t')
plt.ylabel('x')
plt.savefig('fig4(1)')
plt.show()