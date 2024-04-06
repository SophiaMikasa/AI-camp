import matplotlib.pyplot as plt
import one

model = one.Interaction(1)
new_list = []
L = 0.1
n = 10
number_of_elements = n
step = L/number_of_elements
start = 0.0
end = L
custom_list = [round(start + i * step, 2) for i in range(number_of_elements)]
# custom_list = np.random.uniform(0, 10, 1000)

for time in range(4):
    new_list.append(custom_list)
    custom_list = model.interact(custom_list)

plt.plot(new_list,linewidth=0.3)

plt.xlabel('t')
plt.ylabel('x')
# plt.savefig('special_fig')
plt.show()