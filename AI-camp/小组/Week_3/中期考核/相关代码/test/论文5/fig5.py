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
    if i > 550 :
        nums = [20]
    elif i> 400 and i < 550:
        nums = [8]
    elif i > 300 and i < 400:
        nums = [1]
    elif i>150 and i < 200:
        nums = [6]
    elif i >50 and i < 100:
        nums = [2]
    else:
        nums = [1]
    weights += nums

for time in range(9):
    new_list.append(custom_list)
    custom_list = model.interact(custom_list,weights=weights)

plt.plot(new_list,linewidth=0.3)
plt.xticks([0, 1, 2, 3, 4, 5])  # 设置 x 轴刻度
plt.yticks((0, 0.5, 1, 1.5, 2, 2.5, 3))  # 设置 y 轴刻度
plt.xlim(0, 5)
plt.ylim(0, 3)
plt.xlabel('t')
plt.ylabel('x')
# plt.savefig('fig5')
plt.show()