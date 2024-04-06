from math import fabs
import numpy as np


class Interaction(object):
    def __init__(self, radius):
        self.radius = radius

    def interact(self, datas) -> list:
        new_datas = []
        # 该循环是计算每个智能体与它相邻的数的平均值
        for data in datas:
            nums = 0 # 首先对和它相差1的总值进行归零
            nums_value = 0.0 # 数量也进行归零
            for neighbor in datas:
                if neighbor == data: # 如果遍历到它本身就跳过
                    continue
                distance = fabs(data - neighbor)
                # 判断该智能体是否和这个智能体相差1，如果不是就跳过当前循环
                if distance < self.radius:
                    nums += 1
                    nums_value += neighbor
            if nums != 0: # 此时如过num不为0则说明还没完成形成聚类
                new_data = nums_value / nums
            # 此时如果形成聚类则返回原来的列表
            else:
                return datas
            new_datas.append(new_data)  # 更新一次交互后的数据
        return new_datas
