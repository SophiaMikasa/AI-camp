import matplotlib.pyplot as plt
import numpy as np
import one

new_list = []
# custom_list = [round(start + i * step, 2) for i in range(number_of_elements)]
model = one.Interaction(1)
L = 25
x = [3,L]
y1 = [2.5,L/2]
y2 = [-2.5,-L/2]

# 绘制两条虚线
plt.plot(x, y1, linestyle='--', label='Line 1',color='gray')
plt.plot(x, y2, linestyle='--', label='Line 2',color='gray')
L_range = L*10+1

for l in range(3,L_range):
    interacte_times = 50
    number_of_elements = 100 + 7 * l
    l=l*0.1
    step = l / number_of_elements
    start = 0.0
    end = l
    custom_list = [round(start + i * step, 2) for i in range(number_of_elements)]
    for time in range(interacte_times):
        custom_list = model.interact(custom_list)
    matrix = np.array(custom_list)
    new_matrix = matrix - l/2
    matrix_L = np.full(number_of_elements, l)
    plt.scatter(matrix_L, new_matrix,s=0.5,c='blue')

plt.xlabel('L')
plt.ylabel('x-L/2')
# plt.savefig('fig2(18)')
plt.show()