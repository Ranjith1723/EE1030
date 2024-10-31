import numpy as np
import matplotlib.pyplot as plt
from sympy import symbols, Eq, solve

# Read coordinates from the .dat file
def read_coordinates(filename):
    # Assumes the file has coordinates in the form: x1 y1 x2 y2 a y3
    with open(filename, 'r') as file:
        data = file.read().split()
        x1, y1 = float(data[0]), float(data[1])
        x2, y2 = float(data[2]), float(data[3])
        x3_symbol, y3 = symbols('a'), float(data[5])
    return (x1, y1), (x2, y2), (x3_symbol, y3)

# Solve for 'a' to make points collinear
def find_a_for_collinearity(point_A, point_O, point_C):
    x1, y1 = point_A
    x2, y2 = point_O
    x3, y3 = point_C

    # Area formula for collinearity condition
    area_expr = x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)

    # Solve for 'a'
    solution_a = solve(Eq(area_expr, 0), x3)
    return solution_a[0]

# Generate line points between two points
def line_gen(A, B):
    line = np.zeros((2, 10))
    lam_1 = np.linspace(0, 1, 10)
    for i in range(10):
        temp = A + lam_1[i] * (B - A)
        line[:, i] = temp
    return line

# Main execution
filename = 'coordinates.dat'  # Replace with the actual path of your .dat file
point_A, point_O, point_C = read_coordinates(filename)

# Solve for 'a' to make the points collinear
a_value = find_a_for_collinearity(point_A, point_O, point_C)
print(f"The value of 'a' that makes the points collinear is: {a_value}")

# Substitute the value of 'a' back into point C
point_C = (float(a_value), point_C[1])

# Convert points to numpy arrays for plotting
A = np.array(point_A)
O = np.array(point_O)
C = np.array(point_C)

# Generate line segments for visualization
x_AO = line_gen(A, O)
x_OC = line_gen(O, C)

# Plot the line segments and points
plt.plot(x_AO[0, :], x_AO[1, :], 'b--', label='$AO$')
plt.plot(x_OC[0, :], x_OC[1, :], 'g--', label='$OC$')

# Plot the points A, O, and C
plt.scatter([A[0], O[0], C[0]], [A[1], O[1], C[1]], color='red')

# Label the points A, O, and C
labels = [f'A{tuple(A)}', f'O{tuple(O)}', f'C({a_value}, {C[1]})']
for i, txt in enumerate(labels):
    plt.annotate(txt, ([A[0], O[0], C[0]][i], [A[1], O[1], C[1]][i]), textcoords="offset points", xytext=(0, 10), ha='center')

# Display the plot
plt.axhline(0, color='grey', lw=0.5)
plt.axvline(0, color='grey', lw=0.5)
plt.legend(loc='best')
plt.grid(True)
plt.title("Collinearity of Points A, O, and C")
plt.xlabel("X-axis")
plt.ylabel("Y-axis")
plt.axis('equal')
plt.savefig('../figs/fig1.png')
plt.show()

