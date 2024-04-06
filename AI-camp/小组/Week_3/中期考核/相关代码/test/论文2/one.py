from math import sqrt
import numpy as np


class Interaction(object):
    def __init__(self, radius, gama):
        self.radius = radius
        self.gama = gama

    def interact(self, datas) -> np.ndarray:
        new_datas = np.array((0.0, 0.0))
        for data in datas:
            nums_value = np.array((0.0, 0.0))
            for neighbor in datas:
                if np.array_equal(neighbor, data):  # 如果遍历到它本身就跳过
                    continue
                distance = sqrt((data[0] - neighbor[0])**2 + (data[1] - neighbor[1])**2)
                # 判断该智能体是否和这个智能体相差1，如果不是就跳过当前循环
                if distance <= self.radius:
                    nums_value += (neighbor.astype(float) - data.astype(float))
            new_data = nums_value * self.gama
            new_datas = np.vstack((new_datas, data + new_data))
            # new_datas = np.concatenate((new_datas, new_data + data), axis=0) # 更新一次交互后的数据
        new_datas = new_datas[1:, :]
        return new_datas
