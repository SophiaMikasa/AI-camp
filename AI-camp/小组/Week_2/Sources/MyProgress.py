import numpy as np
from math import sqrt


class MyRegression(object):
    def __init__(self, method, learning_rate=0.01, max_iter=1000, tol=1e-4, alpha=0.01):
        self.theta = None
        # self.learning_rate = learning_rate  # 初始学习率
        self.max_iter = max_iter  # 最大迭代次数
        self.tol = tol  # 容忍误差
        self.alpha = alpha
        # self.history_learning_rate = []  # 记录学习率历史
        self.method = method
        self.cost_history = []

    def fit(self, x, y):
        x_b = np.concatenate((np.ones((x.shape[0], 1)), x), axis=1)

        if self.method == 'ols':
            self.theta = np.linalg.inv(x_b.T.dot(x_b)).dot(x_b.T).dot(y)
        elif self.method == 'gd':
            theta = np.random.randn(x_b.shape[1])
            for epoch in range(self.max_iter):
                y_pred = np.dot(x_b, theta)
                error = y_pred - y
                loss = np.mean((error ** 2) / 2)
                self.cost_history.append(loss)
                gradient = 2 * np.dot(x_b.T, error) / len(x_b)
                theta -= self.alpha * gradient
                if len(self.cost_history) > 1 and abs(self.cost_history[-1] - self.cost_history[-2]) < self.tol:
                    break
            self.theta = theta

    # def olspredict(self, x_test):
    #     x_test_b = np.c_[np.ones((len(x_test), 1)), x_test]
    #     return x_test_b.dot(self.theta)

    def predict(self, x_test):
        x_test_b = np.c_[np.ones((len(x_test), 1)), x_test]
        return x_test_b.dot(self.theta)

    @staticmethod
    def mean_squared_error(y_test, y_predict) -> float:
        return np.sum((y_predict - y_test) ** 2) / len(y_test)

    def mean_absolute_error(self, y_test, y_pred) -> float:
        return sqrt(self.mean_squared_error(y_test, y_pred))

    @staticmethod
    def var(y_test) -> float:
        return sum((y_test.mean() - y_test) ** 2) / len(y_test)

    @staticmethod
    def r2_score(y_test, y_pred) -> float:
        mean_y_true = np.mean(y_test)
        total_sum_of_squares = np.sum((y_test - mean_y_true) ** 2)
        # 残差
        residual_sum_of_squares = np.sum((y_test - y_pred) ** 2)
        r2_score = 1 - (residual_sum_of_squares / total_sum_of_squares)

        return r2_score
        # return 1 - self.mean_squared_error(y_test, y_pred) / self.var(y_test)

    def score(self, x_test, y_test) -> float:
        y_pred = self.predict(x_test)
        return self.r2_score(y_test, y_pred)

    # def gdscore(self, x_test, y_test) -> float:
    #     y_pred = self.gdpredict(x_test)
    #     return self.r2_score(y_test, y_pred)


# X_train, X_test, y_train, y_test = train_test_split(family, target, test_size=0.2)
# # 训练集中样本的个数
# n_train = X_train.shape[0]
# # 训练集中样本特征值的个数
# n_features = X_train.shape[1]
#
# w = np.random.randn(n_features)
# b = 1.1# 偏移项
# lr = 0.001# 学习度
# epochs = 3000# 训练次数
#
# def model(x):
#     y_hat = w.dot(x)+b
#     return y_hat
#
# reg = 0.5
#
# for epoch in range(epochs):
#     sum_w = 0.0
#     sum_b = 0.0
#     for i in range(n_train):
#         xi = X_train[i]
#         yi = y_train[i]
#         yi_hat = model(xi)
#         sum_w += (yi_hat - yi) * xi
#         sum_b += (yi_hat - yi)
#     grad_w = (2.0 / n_train) * sum_w + (2.0 + reg * w)
#     grad_b = (2.0 / n_train) * sum_b
#     w = w - lr * grad_w
#     b = b - lr * grad_b
#
# def loss_function(X,y):
#     total_loss = 0
#     n_sample = len(X)
#     for i in range(n_sample):
#         xi = X[i]
#         yi = y[i]
#         yi_hat = model(xi)
#         total_loss += (yi_hat - yi) ** 2
#     avg_loss = (1/n_sample) * total_loss
#     return avg_loss
#
# train_loss = loss_function(X_train, y_train)
# test_loss = loss_function(X_test, y_test)

# https://scikit-learn.org/stable/modules/generated/sklearn.linear_model.LinearRegression.html#sklearn.linear_model.LinearRegression

# 梯度下降算法优化(加入正则表达式)
# self.theta = np.zeros(x.shape[1])  # 初始化参数为零向量
#
# for epoch in range(1, self.max_iter + 1):
#     y_pred = np.dot(x, self.theta)
#     # 后面一项正则化防止过拟合
#     loss = np.mean((y_pred - y) ** 2) / 2 + self.alpha * np.sum(self.theta ** 2) / 2
#     self.cost_history.append(loss)
#     gradient = np.dot(x.T, (y_pred - y)) / len(y) + self.alpha * self.theta
#     self.learning_rate = self.learning_rate / epoch
#     self.history_learning_rate.append(self.learning_rate)
#     self.theta -= self.learning_rate * gradient
#     if len(self.cost_history) > 1 and abs(self.cost_history[-1] - self.cost_history[-2]) < self.tol:
#         break
