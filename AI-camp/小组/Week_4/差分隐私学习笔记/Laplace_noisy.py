import numpy as np


def laplace_mechanism(query_result, sensitivity, epsilon):
    # 计算拉普拉斯噪声
    scale = sensitivity / epsilon
    noise = np.random.laplace(loc=0, scale=scale)

    # 添加噪声到查询结果
    noisy_result = query_result + noise

    return noisy_result