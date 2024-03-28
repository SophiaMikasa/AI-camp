import numpy as np
import random


class KMeans:
    def __init__(self, n_clusters, max_iter=300):
        self.n_clusters = n_clusters
        self.max_iter = max_iter
        self.centroids = []

    def fit(self, X):
        self.centroids = self._initialize_centroids(X)
        for _ in range(self.max_iter):
            labels = self._assign_points(X, self.centroids)
            new_centroids = self._update_centroids(X, labels)
            if np.allclose(self.centroids, new_centroids):
                break
            self.centroids = new_centroids

    def _initialize_centroids(self, X):
        indices = np.random.choice(X.shape[0], self.n_clusters, replace=False)
        return X[indices]
    @staticmethod
    def _assign_points(X, centroids):
        distances = np.sqrt(((X - centroids[:, np.newaxis])**2).sum(axis=2))
        return np.argmin(distances, axis=0)

    def _update_centroids(self, X, labels):
        new_centroids = np.zeros_like(self.centroids)
        for i in range(self.n_clusters):
            new_centroids[i] = np.mean(X[labels == i], axis=0)
        return new_centroids

    def predict(self, X):
        distances = np.sqrt(((X - self.centroids[:, np.newaxis]) ** 2).sum(axis=2))
        labels = np.argmin(distances, axis=0)
        return labels
