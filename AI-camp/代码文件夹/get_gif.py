import sys
import imageio
from PyQt5.QtWidgets import QApplication, QMainWindow, QLabel, QWidget, QPushButton
from PyQt5.QtCore import QTimer
from PyQt5.QtGui import QPainter, QColor, QPen
import tempfile
import functools
import numpy as np

class TrailWidget(QWidget):
    def __init__(self, parent=None, nums=0):
        super().__init__(parent)
        self.trail = [[] for _ in range(nums)]# 存储轨迹点的列表
        self.nums = nums
        self.color = ['pink', 'blue', 'black', 'red', 'green', 'grey', 'purple']

    def addTrailPoint(self, point, index):
        self.trail[index].append(point)
        if len(self.trail[index]) > 300:  # 限制轨迹点的数量
            self.trail[index].pop(0)  # 删除最旧的轨迹点

    def paintEvent(self, event=None):
        painter = QPainter(self)
        global index
        pen = QPen(QColor(self.color[index]))
        pen.setWidth(2)  # 设置线条宽度为3像素，可以根据需要调整
        painter.setPen(pen)
        index += 1
        index %= self.nums
        for e in range(len(self.trail[index]) - 1):
            painter.drawLine(self.trail[index][e], self.trail[index][e + 1])


class MainWindow(QMainWindow):
    def __init__(self, coordinates, vehicle_nums=0):
        super().__init__()
        Leaders_y = []
        for i in range(len(coordinates)):
            Leaders_y.append(coordinates[i][0][1])
        for i in range(len(coordinates)):
            for j in range(1, vehicle_nums):
                temp_y = coordinates[i][j][1]
                coordinates[i][j][1] += 2 * (Leaders_y[i] - temp_y)

        self.vehicle_nums = vehicle_nums
        self.coordinates = coordinates
        self.index = 0
        self.color = ['pink', 'blue', 'black', 'red', 'green', 'grey', 'purple']

        self.setWindowTitle("动图演示")
        self.setGeometry(200, 200, 1000, 400)
        self.trail_widget = [TrailWidget(self, nums=self.vehicle_nums) for _ in range(self.vehicle_nums)]
        self.timer = [QTimer(self) for _ in range(self.vehicle_nums)]
        self.label = [QLabel(self) for _ in range(self.vehicle_nums)]

        for e in range(vehicle_nums):
            self.trail_widget[e].setGeometry(0, 0, 1000, 400)  # 设置轨迹控件与窗口大小相同
            self.label[e].setGeometry(50, 80, 10, 10)
            color_and_radius = f"background-color: {self.color[e]}; border-radius: 5px;"
            self.label[e].setStyleSheet(color_and_radius)
            self.timer[e].timeout.connect(functools.partial(self.move_dot, j=e))
            self.timer[e].start(30)  # 设置定时器间隔为30毫秒

        self.save_button = QPushButton("保存动图", self)
        self.save_button.setGeometry(20, 20, 100, 50)
        self.save_button.clicked.connect(self.save_animation)

        self.frame_count = 0
        self.animation_frames = []

    def move_dot(self, j):
        if self.index < len(self.coordinates):
            x = int(self.coordinates[self.index][j-1][0].round(1) * 10) + 50
            y = int(self.coordinates[self.index][j-1][1].round(1) * 10) - 250
            self.label[j-1].move(x, y)
            self.index += 1

            # 添加当前位置到轨迹
            center = self.label[j-1].geometry().center()
            self.trail_widget[j-1].addTrailPoint(center, index=j)

            # 保存动图帧
            pixmap = self.grab()
            self.animation_frames.append(pixmap)

    def save_animation(self):
        try:
            if self.animation_frames:
                with tempfile.TemporaryDirectory() as temp_dir:
                    for e, frame in enumerate(self.animation_frames):
                        file_path = f"{temp_dir}/frame_{e}.png"
                        frame.save(file_path, "PNG")

                    image_paths = [f"{temp_dir}/frame_{e}.png" for e in range(len(self.animation_frames))]
                    images = [imageio.v2.imread(path) for path in image_paths]
                    imageio.mimsave("animation.gif", images, duration=0.03)

                print("动图已保存为 GIF。")
        except Exception as e:
            print("保存动图时出现异常:", e)


if __name__ == "__main__":
    while 1:
        print('你需要CaseⅠ的动图还是CaseⅡ的动图?')
        print('A.CaseI')
        print('B.CaseⅡ')
        print('C.退出')
        choice = input()
        if choice == 'A':
            a = np.array([[0, 2, 1], [0.3, 0, 0.3], [1, 1, 0]])
            k = np.array([[0, 0, 0], [0, 3, 0], [0, 0, 1]])
            break
        elif choice == 'B':
            a = np.array([[0, 0, 0], [0, 0, 1], [0, 1, 0]])
            k = np.array([[0, 0, 0], [0, 1, 0], [0, 0, 1]])
            break
        elif choice == 'C':
            n = input('退出成功，请按任意键继续')
            exit(0)
        else:
            print('输入错误')
    # a = np.array([[0, 0, 0], [0, 0, 1], [0, 1, 0]])
    # k = np.array([[0, 0, 0], [0, 1, 0], [0, 0, 1]])
    # a = np.array([[0, 1, 1], [1, 0, 1], [1, 1, 0]])
    # k = np.array([[0, 0, 0], [0, 1, 0], [0, 0, 1]])
    w = np.zeros((3, 3))
    for i in range(len(a)):
        for weight in a[i]:
            w[i, i] += weight
    l = w - a
    r = np.array([[-15., 0.], [-10., 0.], [-5., 0.]])
    acceleration_l = np.array([0., 0.])
    velocity_l = np.array([6., 0.])
    position_l = np.array([20., 50.])
    positions = np.array([[6., 60.], [10., 40.], [16., 70.]])
    velocities = np.array([[10., 5.], [8., 4.], [9., 3.]])
    acceleration = [acceleration_l for _ in range(3)]
    acceleration = (acceleration - (l.dot(positions - r + velocities)) -
                    k.dot((positions - position_l) - r + (velocities - velocity_l)))
    accelerations_list = [acceleration]
    position_l = np.array(position_l)
    positions = np.array(positions)
    positions_list = [positions]
    velocities_list = [velocities]
    positions_l = [position_l]
    velocities_l = [velocity_l]

    times = 400
    L = 10
    interval = L / times
    flag = 0
    flag_position_x = 0
    flag_position_y = 0
    flag_velocity_x = 0
    flag_velocity_y = 0
    temp_times = 0

    for time in range(1, times + 1):
        error_position = positions_list[time - 1] - positions_l[time - 1] - r
        error_velocity = velocities_list[time - 1] - velocities_l[time - 1]
        if ((np.abs(error_position[:, 0]) >= 0.001)).any() == False:
            if flag_position_x == 0:
                print(f"x方向的位置收敛时间为:{time * interval}")
                flag_position_x += 1
                flag += 1
        if ((np.abs(error_position[:, 1]) >= 0.001)).any() == False:
            if flag_position_y == 0:
                print(f"y方向的位置收敛时间为:{time * interval}")
                flag_position_y += 1
                flag += 1
        if ((np.abs(error_velocity[:, 0]) >= 0.001)).any() == False:
            if flag_velocity_x == 0:
                print(f"x方向的速度收敛时间为:{time * interval}")
                flag_velocity_x += 1
                flag += 1
        if ((np.abs(error_velocity[:, 1]) >= 0.001)).any() == False:
            if flag_velocity_y == 0:
                print(f"y方向的速度收敛时间为:{time * interval}")
                flag_velocity_y += 1
                flag += 1
        if flag == 4:
            temp_times = time
            break
        new_acceleration = accelerations_list[time - 1].copy()
        new_position = positions_list[time - 1].copy()
        new_velocity = velocities_list[time - 1].copy()
        velocity = new_velocity * interval
        acceleration = new_acceleration * interval
        new_position += velocity
        new_velocity += acceleration
        new_position_l = positions_l[time - 1].copy()
        new_position_l += velocity_l * interval
        new_velocity_l = velocities_l[time - 1].copy()
        new_velocity_l += acceleration_l * interval
        acceleration = [acceleration_l for _ in range(3)]
        positions_list.append(new_position)
        velocities_list.append(new_velocity)
        positions_l.append(new_position_l)
        velocities_l.append(new_velocity_l)
        acceleration = (acceleration - (l.dot(new_position - r + new_velocity)) -
                        k.dot((new_position - positions_l[time]) - r + (new_velocity - velocities_l[time])))
        accelerations_list.append(acceleration)

    if flag != 4:
        temp_times = times
    accelerations_list = np.concatenate([acceleration[np.newaxis, :] for acceleration in accelerations_list], axis=0)
    positions_list = np.concatenate([position[np.newaxis, :] for position in positions_list], axis=0)
    velocities_list = np.concatenate([velocities[np.newaxis, :] for velocities in velocities_list], axis=0)
    bias_positions = []
    for i in range(len(positions_list)):
        bias_position = np.vstack((positions_l[i], positions_list[i]))
        bias_positions.append(bias_position)
    bias_positions = np.concatenate([bias_position[np.newaxis, :] for bias_position in bias_positions], axis=0)
    index = 0
    app = QApplication(sys.argv)
    window = MainWindow(bias_positions, 4)
    window.show()
    sys.exit(app.exec_())

    # del a, k, w, l, r, acceleration_l, velocity_l, position_l, positions, velocities
    # del acceleration, accelerations_list, position_l, positions, positions_list
    # del velocities_list, positions_l, velocities_l, times, L, interval, flag
    # del flag_position_x, flag_position_y, flag_velocity_x, flag_velocity_y, temp_times
    # del bias_positions, index, app, window
