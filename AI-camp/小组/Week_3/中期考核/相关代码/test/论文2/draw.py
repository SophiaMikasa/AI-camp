import matplotlib.pyplot as plt

# 创建示例数据
x = range(0, 10)
y = [i**2 for i in x]

# 绘制图形
plt.plot(x, y)

# 设置 x 轴和 y 轴的范围
plt.xlim(0, 10)
plt.ylim(0, 100)

# 设置 x 轴和 y 轴的刻度标签
plt.xticks(range(0, 11, 2))  # 设置 x 轴刻度为 0 到 10，步长为 2
plt.yticks([0, 25, 50, 75, 100])  # 设置 y 轴刻度

# 设置刻度的位置、长度、方向等参数
plt.tick_params(axis='both', direction='in', length=5, width=1, colors='r')

# 显示图形
plt.show()