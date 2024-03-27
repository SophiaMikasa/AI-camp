import numpy as np


class LogisticRegression(object):
    def __init__(self, learning_rate=0.01, num_iterations=1000, regularization_param=0.1) -> None:
        self.learning_rate = learning_rate
        self.num_iterations = num_iterations
        self.regularization_param = regularization_param
        self.weights = None
        self.bias = None

    @staticmethod
    def sigmoid(z) -> float:
        return 1 / (1 + np.exp(-z))

    def compute_cost(self, X, y) -> float:
        m = X.shape[0]
        z = np.dot(X, self.weights) + self.bias
        h = self.sigmoid(z)
        regularization_term = (self.regularization_param / (2 * m)) * np.sum(np.square(self.weights))
        cost = (-1 / m) * np.sum(y * np.log(h) + (1 - y) * np.log(1 - h)) + regularization_term
        return cost

    def fit(self, X, y) -> None:
        # 未加正则表达式
        # self.weights = np.zeros(X.shape[1])
        # self.bias = 0
        #
        # for i in range(self.num_iterations):
        #     z = np.dot(X, self.weights) + self.bias
        #     predictions = self.sigmoid(z)
        #
        #     error = predictions - y
        #     gradient_weights = X.T.dot(error)/len(y)
        #     gradient_bias = np.sum(error) / len(y)
        #     self.weights -= self.learning_rate * gradient_weights
        #     self.bias -= self.learning_rate * gradient_bias
        # 加入正则表达式
        m, n = X.shape
        self.weights = np.zeros(n)
        self.bias = 0

        for _ in range(self.num_iterations):
            z = np.dot(X, self.weights) + self.bias
            h = self.sigmoid(z)
            error = h - y
            grad_weights = (1 / m) * np.dot(X.T, error) + (self.regularization_param / m) * self.weights
            grad_bias = (1 / m) * np.sum(error)
            self.weights -= self.learning_rate * grad_weights
            self.bias -= self.learning_rate * grad_bias

            # cost = self.compute_cost(X, y)
            # print(f'Epoch {_ + 1}/{self.num_iterations}, Cost: {cost}')

    def predict(self, X):
        z = np.dot(X, self.weights) + self.bias
        predictions = self.sigmoid(z)
        return np.round(predictions)

    def model(self, X, theta):
        return self.sigmoid(np.dot(X, theta.T))
