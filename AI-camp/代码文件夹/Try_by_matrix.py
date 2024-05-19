import numpy as np
import matplotlib.pyplot as plt

# a = np.array([[0, 0, 0], [0, 0, 0.3], [0, 1, 0]])
# k = np.array([[0, 0, 0], [0, 3, 0], [0, 0, 1]])
a = np.array([[0, 1, 1], [0.3, 0, 0.3], [1, 1, 0]])
k = np.array([[0, 0, 0], [0, 3, 0], [0, 0, 1]])
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
positions_list = [positions]
velocities_list = [velocities]
positions_l = [position_l]
velocities_l = [velocity_l]

times = 500
L = 10
interval = L / times
flag = 0
flag_position_x = 0
flag_position_y = 0
flag_velocity_x = 0
flag_velocity_y = 0
position_x_courage_time_One = 0
position_y_courage_time_One = 0
velocity_x_courage_time_One = 0
velocity_y_courage_time_One = 0
temp_times = 0

for time in range(1, times + 1):
    error_position = positions_list[time - 1] - positions_l[time - 1] - r
    error_velocity = velocities_list[time - 1] - velocities_l[time - 1]
    error_position[0] = np.array([0., 0.])
    error_velocity[0] = np.array([0., 0.])
    if ((np.abs(error_position[:, 0]) >= 0.001)).any() == False:
        if flag_position_x == 0:
            print(f"x方向的位置收敛时间为:{time * interval}")
            flag_position_x += 1
            position_x_courage_time_One = time * interval
            flag += 1
    if ((np.abs(error_position[:, 1]) >= 0.001)).any() == False:
        if flag_position_y == 0:
            print(f"y方向的位置收敛时间为:{time * interval}")
            flag_position_y += 1
            position_y_courage_time_One = time * interval
            flag += 1
    if ((np.abs(error_velocity[:, 0]) >= 0.001)).any() == False:
        if flag_velocity_x == 0:
            print(f"x方向的速度收敛时间为:{time * interval}")
            flag_velocity_x += 1
            velocity_x_courage_time_One = time * interval
            flag += 1
    if ((np.abs(error_velocity[:, 1]) >= 0.001)).any() == False:
        if flag_velocity_y == 0:
            print(f"y方向的速度收敛时间为:{time * interval}")
            flag_velocity_y += 1
            velocity_y_courage_time_One = time * interval
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

accelerations_list = np.concatenate([acceleration[np.newaxis, :] for acceleration in accelerations_list], axis=0)
positions_list = np.concatenate([position[np.newaxis, :] for position in positions_list], axis=0)
velocities_list = np.concatenate([velocities[np.newaxis, :] for velocities in velocities_list], axis=0)
#
# Y_velocity
temp_one = []
temp_two = []
temp_three = []
temp_four= []
for i in range(temp_times):
    temp_one.append(velocities_list[i][0][1])
    temp_two.append(velocities_list[i][1][1])
    temp_three.append(velocities_list[i][2][1])
    temp_four.append(velocity_l[1])
times_list = [i * interval for i in range(temp_times)]
plt.plot(times_list, temp_one, color='blue',lw=1,label='vehicle i')
plt.plot(times_list, temp_two, color='black',lw=1,label='vehicle i+1')
plt.plot(times_list, temp_three, color='red',lw=1,label='vehicle i+2')
plt.plot(times_list, temp_four,color='purple',lw=1,label='Leader')
plt.legend(loc='lower right')
plt.xlim(0, L)
plt.ylim(-L, L)
plt.xticks((0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10))
plt.yticks((-10, -8, -6, -4, -2, 0, 2, 4, 6, 8, 10))
plt.xlabel('Times(s)')
plt.ylabel('Y_Velocity(m/s)')
plt.show()
plt.savefig('fig5(b).png')

# X_velocity
temp_one = []
temp_two = []
temp_three = []
temp_four= []
for i in range(temp_times):
    temp_one.append(velocities_list[i][0][0])
    temp_two.append(velocities_list[i][1][0])
    temp_three.append(velocities_list[i][2][0])
    temp_four.append(velocity_l[0])
times_list = [i * interval for i in range(temp_times)]
plt.plot(times_list, temp_one, color='blue',lw=1,label='vehicle i')
plt.plot(times_list, temp_two, color='black',lw=1,label='vehicle i+1')
plt.plot(times_list, temp_three, color='red',lw=1,label='vehicle i+2')
plt.plot(times_list, temp_four,color='purple',lw=1,label='Leader')
plt.legend(loc='lower right')
plt.xlim(0, L)
plt.ylim(-L, L + 2)
plt.xticks((0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10))
plt.yticks((-10, -8, -6, -4, -2, 0, 2, 4, 6, 8, 10, 12))
plt.xlabel('Times(s)')
plt.ylabel('X_Velocity(m/s)')
plt.show()
plt.savefig('fig5(a).png')

# # position
# temp_position_xi = []
# temp_position_xi1 = []
# temp_position_xi2 = []
# temp_position_l_x = []
# temp_position_yi = []
# temp_position_yi1 = []
# temp_position_yi2 = []
# temp_position_l_y = []
# for i in range(temp_times):
#     temp_position_xi.append(positions_list[i][0][0])
#     temp_position_xi1.append(positions_list[i][1][0])
#     temp_position_xi2.append(positions_list[i][2][0])
#     temp_position_l_x.append(positions_l[i][0])
#     temp_position_yi.append(positions_list[i][0][1])
#     temp_position_yi1.append(positions_list[i][1][1])
#     temp_position_yi2.append(positions_list[i][2][1])
#     temp_position_l_y.append(positions_l[i][1])
# plt.plot(temp_position_xi, temp_position_yi, color='blue',lw=1,label='vehicle i')
# plt.plot(temp_position_xi1, temp_position_yi1, color='black',lw=1,label='vehicle i+1')
# plt.plot(temp_position_xi2, temp_position_yi2, color='red',lw=1,label='vehicle i+2')
# plt.plot(temp_position_l_x, temp_position_l_y,color='purple',lw=1,label='Leader')
# plt.legend(loc='lower right')
# plt.xlim(0, 60)
# plt.ylim(0, 80)
# plt.xticks((15, 30, 45, 60)) # 75, 90, 105, 120, 135, 150
# plt.yticks((0, 10, 20, 30, 40, 50, 60, 70, 80))
# plt.plot((positions_l[0][0],positions_list[0][2][0]),(positions_l[0][1],positions_list[0][2][1]),linestyle='--', color='brown')
# plt.plot((positions_l[0][0],positions_list[0][1][0]),(positions_l[0][1],positions_list[0][1][1]),linestyle='--', color='brown')
# plt.plot((positions_list[0][0][0],positions_list[0][2][0]),(positions_list[0][0][1],positions_list[0][2][1]),linestyle='--', color='brown')
# plt.plot((positions_list[0][0][0],positions_list[0][1][0]),(positions_list[0][0][1],positions_list[0][1][1]),linestyle='--', color='brown')
# plt.plot((positions_l[0][0],positions_list[50][2][0]),(positions_l[0][1],positions_list[50][2][1]),linestyle='--', color='brown')
# plt.plot((positions_l[0][0],positions_list[50][1][0]),(positions_l[0][1],positions_list[50][1][1]),linestyle='--', color='brown')
# plt.plot((positions_list[50][0][0],positions_list[50][2][0]),(positions_list[50][0][1],positions_list[50][2][1]),linestyle='--', color='brown')
# plt.plot((positions_list[50][0][0],positions_list[50][1][0]),(positions_list[50][0][1],positions_list[50][1][1]),linestyle='--', color='brown')
# plt.xlabel('X Position(m)')
# plt.ylabel('Y Position(m)')
# plt.show()
# plt.savefig('fig4.png')

# Longitudinal Gap
temp_one = []
temp_two = []
temp_three = []
temp_four= []
for i in range(temp_times):
    temp_one.append(positions_list[i][0][0]-positions_l[i][0])
    temp_two.append(positions_list[i][1][0]-positions_l[i][0])
    temp_three.append(positions_list[i][2][0]-positions_l[i][0])
    temp_four.append(positions_l[i][0]-positions_l[i][0])
times_list = [i * interval for i in range(temp_times)]
plt.plot(times_list, temp_one, color='blue',lw=1,label='vehicle i')
plt.plot(times_list, temp_two, color='black',lw=1,label='vehicle i+1')
plt.plot(times_list, temp_three, color='red',lw=1,label='vehicle i+2')
plt.plot(times_list, temp_four,color='purple',lw=1,label='Leader')
plt.legend(loc='lower right')
plt.xlim(0, 10)
plt.ylim(-20, 5)
plt.xticks((0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10))
plt.yticks((-20, -15, -10, -5, 0, 5))
plt.xlabel('Times(s)')
plt.ylabel('Longitudinal Gap(m)')
plt.show()
plt.savefig('fig6(a).png')

# Lateral  Gap(m)
temp_one = []
temp_two = []
temp_three = []
temp_four= []
for i in range(temp_times):
    temp_one.append(positions_list[i][0][1]-positions_l[i][1])
    temp_two.append(positions_list[i][1][1]-positions_l[i][1])
    temp_three.append(positions_list[i][2][1]-positions_l[i][1])
    temp_four.append(positions_l[i][1]-positions_l[i][1])
times_list = [i * interval for i in range(temp_times)]
plt.plot(times_list, temp_one, color='blue',lw=1,label='vehicle i')
plt.plot(times_list, temp_two, color='black',lw=1,label='vehicle i+1')
plt.plot(times_list, temp_three, color='red',lw=1,label='vehicle i+2')
plt.plot(times_list, temp_four,color='purple',lw=1,label='Leader')
plt.legend(loc='lower right')
plt.xlim(0, 10)
plt.ylim(-10, 20)
plt.xticks((0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10))
plt.yticks((-10, -5, 0, 5, 10, 15, 20))
plt.xlabel('Times(s)')
plt.ylabel('Lateral  Gap(m)')
plt.show()
plt.savefig('fig6(b).png')


a = np.array([[0, 0, 0], [0, 0, 0.3], [0, 1, 0]])
k = np.array([[0, 0, 0], [0, 3, 0], [0, 0, 1]])
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
positions_list = [positions]
velocities_list = [velocities]
positions_l = [position_l]
velocities_l = [velocity_l]

times = 500
L = 10
interval = L / times
flag = 0
flag_position_x = 0
flag_position_y = 0
flag_velocity_x = 0
flag_velocity_y = 0
position_x_courage_time_Two = 0
position_y_courage_time_Two = 0
velocity_x_courage_time_Two = 0
velocity_y_courage_time_Two = 0
temp_times = 0

for time in range(1, times + 1):
    error_position = positions_list[time - 1] - positions_l[time - 1] - r
    error_velocity = velocities_list[time - 1] - velocities_l[time - 1]
    error_position[0] = np.array([0., 0.])
    error_velocity[0] = np.array([0., 0.])
    if ((np.abs(error_position[:, 0]) >= 0.001)).any() == False:
        if flag_position_x == 0:
            print(f"x方向的位置收敛时间为:{time * interval}")
            flag_position_x += 1
            position_x_courage_time_Two = time * interval
            flag += 1
    if ((np.abs(error_position[:, 1]) >= 0.001)).any() == False:
        if flag_position_y == 0:
            print(f"y方向的位置收敛时间为:{time * interval}")
            flag_position_y += 1
            position_y_courage_time_Two = time * interval
            flag += 1
    if ((np.abs(error_velocity[:, 0]) >= 0.001)).any() == False:
        if flag_velocity_x == 0:
            print(f"x方向的速度收敛时间为:{time * interval}")
            flag_velocity_x += 1
            velocity_x_courage_time_Two = time * interval
            flag += 1
    if ((np.abs(error_velocity[:, 1]) >= 0.001)).any() == False:
        if flag_velocity_y == 0:
            print(f"y方向的速度收敛时间为:{time * interval}")
            flag_velocity_y += 1
            velocity_y_courage_time_Two = time * interval
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

# Y_velocity
temp_one = []
temp_two = []
temp_three = []
temp_four= []
for i in range(temp_times):
    temp_one.append(velocities_list[i][0][1])
    temp_two.append(velocities_list[i][1][1])
    temp_three.append(velocities_list[i][2][1])
    temp_four.append(velocity_l[1])
times_list = [i * interval for i in range(temp_times)]
plt.plot(times_list, temp_one, color='blue',lw=1,label='vehicle i')
plt.plot(times_list, temp_two, color='black',lw=1,label='vehicle i+1')
plt.plot(times_list, temp_three, color='red',lw=1,label='vehicle i+2')
plt.plot(times_list, temp_four,color='purple',lw=1,label='Leader')
plt.legend(loc='lower right')
plt.xlim(0, L)
plt.ylim(-L, L)
plt.xticks((0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10))
plt.yticks((-10, -8, -6, -4, -2, 0, 2, 4, 6, 8, 10))
plt.xlabel('Times(s)')
plt.ylabel('Y_Velocity(m/s)')
plt.show()
plt.savefig('fig9(b).png')

# X_velocity
temp_one = []
temp_two = []
temp_three = []
temp_four= []
for i in range(temp_times):
    temp_one.append(velocities_list[i][0][0])
    temp_two.append(velocities_list[i][1][0])
    temp_three.append(velocities_list[i][2][0])
    temp_four.append(velocity_l[0])
times_list = [i * interval for i in range(temp_times)]
plt.plot(times_list, temp_one, color='blue',lw=1,label='vehicle i')
plt.plot(times_list, temp_two, color='black',lw=1,label='vehicle i+1')
plt.plot(times_list, temp_three, color='red',lw=1,label='vehicle i+2')
plt.plot(times_list, temp_four,color='purple',lw=1,label='Leader')
plt.legend(loc='lower right')
plt.xlim(0, L)
plt.ylim(-L, L + 2)
plt.xticks((0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10))
plt.yticks((-10, -8, -6, -4, -2, 0, 2, 4, 6, 8, 10, 12))
plt.xlabel('Times(s)')
plt.ylabel('X_Velocity(m/s)')
plt.show()
plt.savefig('fig9(a).png')

# Longitudinal Gap
temp_one = []
temp_two = []
temp_three = []
temp_four= []
for i in range(temp_times):
    temp_one.append(positions_list[i][0][0]-positions_l[i][0])
    temp_two.append(positions_list[i][1][0]-positions_l[i][0])
    temp_three.append(positions_list[i][2][0]-positions_l[i][0])
    temp_four.append(positions_l[i][0]-positions_l[i][0])
times_list = [i * interval for i in range(temp_times)]
plt.plot(times_list, temp_one, color='blue',lw=1,label='vehicle i')
plt.plot(times_list, temp_two, color='black',lw=1,label='vehicle i+1')
plt.plot(times_list, temp_three, color='red',lw=1,label='vehicle i+2')
plt.plot(times_list, temp_four,color='purple',lw=1,label='Leader')
plt.legend(loc='lower right')
plt.xlim(0, 10)
plt.ylim(-20, 5)
plt.xticks((0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10))
plt.yticks((-20, -15, -10, -5, 0, 5))
plt.xlabel('Times(s)')
plt.ylabel('Longitudinal Gap(m)')
plt.show()
plt.savefig('fig8(a).png')

# Lateral  Gap(m)
temp_one = []
temp_two = []
temp_three = []
temp_four= []
for i in range(temp_times):
    temp_one.append(positions_list[i][0][1]-positions_l[i][1])
    temp_two.append(positions_list[i][1][1]-positions_l[i][1])
    temp_three.append(positions_list[i][2][1]-positions_l[i][1])
    temp_four.append(positions_l[i][1]-positions_l[i][1])
times_list = [i * interval for i in range(temp_times)]
plt.plot(times_list, temp_one, color='blue',lw=1,label='vehicle i')
plt.plot(times_list, temp_two, color='black',lw=1,label='vehicle i+1')
plt.plot(times_list, temp_three, color='red',lw=1,label='vehicle i+2')
plt.plot(times_list, temp_four,color='purple',lw=1,label='Leader')
plt.legend(loc='lower right')
plt.xlim(0, 10)
plt.ylim(-10, 20)
plt.xticks((0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10))
plt.yticks((-10, -5, 0, 5, 10, 15, 20))
plt.xlabel('Times(s)')
plt.ylabel('Lateral  Gap(m)')
plt.show()
plt.savefig('fig8(b).png')

print('\t\t\t\t\t\t\tCaseⅠ\tCaseⅡ')
print(f'\t\t\tLongitudinal gap{max(position_x_courage_time_One,velocity_x_courage_time_One)}s\t'
      f'{max(position_x_courage_time_Two,velocity_x_courage_time_Two)}s')
print('Convergence\tx-velocity')
print(f'Time\t\tLateral gap \t{max(position_y_courage_time_One,velocity_y_courage_time_One)}s\t'
      f'{max(position_y_courage_time_Two,velocity_y_courage_time_Two)}s')
print('\t\t\ty-velocity  ')
print('Oscillation Amplitude\t\tmedium\tmedium')
