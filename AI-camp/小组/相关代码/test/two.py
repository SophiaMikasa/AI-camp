from math import fabs


class Interaction(object):
    def __init__(self, radius):
        self.radius = radius

    def interact(self, datas, weights) -> list:
        new_datas = []
        for data_index, data in enumerate(datas):
            total_weighted_value = 0.0
            total_weight = 0.0
            for neighbor_index, neighbor in enumerate(datas):
                if neighbor_index == data_index:
                    continue
                distance = fabs(data - neighbor)
                if distance < self.radius:
                    total_weighted_value += neighbor * weights[neighbor_index]  # 使用邻居的值乘以权重
                    total_weight += weights[neighbor_index]  # 累加权重
            if total_weight != 0:
                new_data = total_weighted_value / total_weight
            else:
                return datas
            new_datas.append(new_data)
        return new_datas
