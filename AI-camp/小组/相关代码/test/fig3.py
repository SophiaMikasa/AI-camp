import matplotlib.pyplot as plt
import one

number_of_elements = 5000
step = 20/5000
start = 0.0
end = 20

model = one.Interaction(1)
new_list = []
custom_list = [round(start + i * step, 2) for i in range(number_of_elements)]
# custom_list = np.random.uniform(0, 10, 1000)

for time in range(21):
    new_list.append(custom_list)
    custom_list = model.interact(custom_list)

plt.plot(new_list,linewidth=0.3)
plt.xlabel('t')
plt.ylabel('x')
# plt.savefig('fig3')
plt.show()