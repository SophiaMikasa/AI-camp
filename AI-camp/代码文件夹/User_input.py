import numpy as np
import sys
import imageio
from PyQt5.QtWidgets import QApplication, QMainWindow, QLabel, QWidget, QPushButton
from PyQt5.QtCore import QTimer
from PyQt5.QtGui import QPainter, QColor, QPen
import tempfile
import functools
from PyQt5.QtCore import Qt


class TrailWidget(QWidget):
    def __init__(self, parent=None, nums=0):
        super().__init__(parent)
        self.trail = [[] for _ in range(nums)]  # 存储轨迹点的列表
        self.nums = nums
        self.color = ['pink', 'blue', 'black', 'red', 'green', 'grey', 'purple']

    def addTrailPoint(self, point, s_index):
        self.trail[s_index].append(point)
        if len(self.trail[s_index]) > 300:  # 限制轨迹点的数量
            self.trail[s_index].pop(0)  # 删除最旧的轨迹点

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

        # 设置画笔
        pen = QPen(Qt.black, 2, Qt.SolidLine)
        painter.setPen(pen)

        # 绘制 X 轴
        x_start = 100
        x_end = self.width() - 50
        y_x_axis = self.height() // 2 + 100
        painter.drawLine(x_start, y_x_axis, x_end, y_x_axis)

        # 绘制 Y 轴
        y_start = 50
        y_end = 700
        x_y_axis = 100
        painter.drawLine(x_y_axis, y_start, x_y_axis, y_end)

        # 添加 X 轴刻度和数标
        x_interval = 80  # 刻度间隔
        for x in range(x_start, x_end + 1, x_interval):
            painter.drawLine(x, y_x_axis - 5, x, y_x_axis + 5)
            painter.drawText(x - 5, y_x_axis + 20, str((x - x_start) * 15 // x_interval))

        # 添加 Y 轴刻度和数标
        y_interval = 60  # 刻度间隔
        for y in range(y_start, y_end + 1, y_interval):
            painter.drawLine(x_y_axis - 5, y, x_y_axis + 5, y)
            painter.drawText(x_y_axis - 30, y + 5, str((y_end - y) * 9 // y_interval))


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
        self.setGeometry(200, 200, 1000, 1000)
        self.trail_widget = [TrailWidget(self, nums=self.vehicle_nums) for _ in range(self.vehicle_nums)]
        self.timer = [QTimer(self) for _ in range(self.vehicle_nums)]
        self.label = [QLabel(self) for _ in range(self.vehicle_nums)]

        for e in range(vehicle_nums):
            self.trail_widget[e].setGeometry(0, 0, 1000, 1000)  # 设置轨迹控件与窗口大小相同
            self.label[e].setGeometry(50, 80, 10, 10)
            color_and_radius = f"background-color: {self.color[e]}; border-radius: 5px;"
            self.label[e].setStyleSheet(color_and_radius)
            self.timer[e].timeout.connect(functools.partial(self.move_dot, j=e))
            self.timer[e].start(30)  # 设置定时器间隔为50毫秒

        self.save_button = QPushButton("保存动图", self)
        self.save_button.setGeometry(20, 20, 100, 50)
        self.save_button.clicked.connect(self.save_animation)

        self.frame_count = 0
        self.animation_frames = []

    def move_dot(self, j):
        if self.index < len(self.coordinates):
            x = int(self.coordinates[self.index][j-1][0].round(1) * 10) + 50
            y = int(self.coordinates[self.index][j-1][1].round(1) * 10) - 180
            self.label[j-1].move(x, y)
            self.index += 1

            # 添加当前位置到轨迹
            center = self.label[j-1].geometry().center()
            self.trail_widget[j-1].addTrailPoint(center, s_index=j)

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


TIMES = 300
L = 10

n = int(input('你需要多少车辆?(要求大于等于2)\n'))
print(f'你有{n}辆车')
if n <= 1:
    print('输入错误\n')
    sys.exit()

print('请输入Leader的初始属性')
position_l_x = float(input('初始位置:\nx:'))
position_l_y = float(input('y:'))
position_l = np.array([position_l_x, position_l_y])
velocity_l_x = float(input('初始速度:\nx:'))
velocity_l_y = float(input('y:'))
velocity_l = np.array([velocity_l_x, velocity_l_y])
acceleration_l_x = float(input('初始加速度:\nx:'))
acceleration_l_y = float(input('y:'))
acceleration_l = np.array([acceleration_l_x, acceleration_l_y])

positions = []
velocities = []
k = np.zeros((n - 1, n - 1))
a = np.ones((n - 1, n - 1))
r = []

for i in range(n - 1):
    print(f'请输入第{i+1}辆小车的初始属性')
    position_x = float(input('初始位置:\nx:'))
    position_y = float(input('y:'))
    positions.append(np.array([position_x, position_y]))
    velocity_x = float(input('初始速度:\nx:'))
    velocity_y = float(input('y:'))
    velocities.append(np.array([velocity_x, velocity_y]))
    flag = input('需要和Leader连接吗?(需要则输入1,不需要则输入0)\n')
    while flag != '1' and flag != '0':
        print('输入错误,请重新输入')
        flag = input('需要和Leader连接吗?(需要则输入1,不需要则输入0)\n')
    if flag == '1':
        k[i - 1][i - 1] = 1
    a[i - 1][i - 1] = 0
    r_x = float(input('与Leader的距离(输入的值为正数,表示离Leader后方多少距离):\nx:'))
    r_y = float(input('y:'))
    r.append(np.array([-r_x, -r_y]))

positions = np.array(positions)
velocities = np.array(velocities)
r = np.array(r)
print('tips:所有的除Leader的小车都相互连接\n')

w = np.zeros((n - 1, n - 1))
for i in range(len(a)):
    for weight in a[i]:
        w[i, i] += weight
l = w - a
accelerations = [acceleration_l for _ in range(n - 1)]
accelerations = (accelerations - (l.dot(positions - r + velocities)) -
                 k.dot((positions - position_l) - r + (velocities - velocity_l)))
accelerations_list = [accelerations]
positions_list = [positions]
velocities_list = [velocities]
positions_l = [position_l]
velocities_l = [velocity_l]

interval = L / TIMES
for time in range(1, TIMES + 1):
    flag = 0
    error_position = positions_list[time - 1] - positions_l[time - 1] - r
    error_velocity = velocities_list[time - 1] - velocities_l[time - 1]
    if (np.abs(error_position) >= np.array([0.01, 0.01])).any() is False:
        flag += 1
    if (np.abs(error_velocity) >= np.array([0.01, 0.01])).any() is False:
        flag += 1
    if flag == 2:
        print(f"收敛时间为:{time * interval}")
        print(error_position)
        print(error_velocity)
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
    accelerations = [acceleration_l for _ in range(n - 1)]
    positions_list.append(new_position)
    velocities_list.append(new_velocity)
    positions_l.append(new_position_l)
    velocities_l.append(new_velocity_l)
    accelerations = (accelerations - (l.dot(new_position - r + new_velocity)) -
                    k.dot((new_position - positions_l[time]) - r + (new_velocity - velocities_l[time])))
    accelerations_list.append(accelerations)

accelerations_list = np.concatenate([acceleration[np.newaxis, :] for acceleration in accelerations_list], axis=0)
positions_list = np.concatenate([position[np.newaxis, :] for position in positions_list], axis=0)
velocities_list = np.concatenate([velocities[np.newaxis, :] for velocities in velocities_list], axis=0)

bias_positions = []
for i in range(len(positions_list)):
    bias_position = np.vstack((positions_l[i], positions_list[i]))
    bias_positions.append(bias_position)
bias_positions = np.concatenate([bias_position[np.newaxis, :] for bias_position in bias_positions], axis=0)
print(bias_positions)
index = 0
app = QApplication(sys.argv)
window = MainWindow(bias_positions, n)
window.show()
sys.exit(app.exec_())

# del TIMES, L, n, position_l_x, position_l_y, position_l, velocity_l_x, velocity_l_y
# del velocity_l, acceleration_l_x, acceleration_l_y, acceleration_l, positions, velocities
# del k, a, r, w, l, accelerations, accelerations_list, positions_list, velocities_list
# del positions_l, velocities_l, interval, temp_position_xi, temp_position_xi1
# del temp_position_xi2, temp_position_l_x, temp_position_yi, temp_position_yi1
# del temp_position_yi2, temp_position_l_y, nums, lines, content, Leader, floats, word
# del bias_positions, index, app, window
