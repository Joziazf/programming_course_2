import matplotlib.pyplot as plt
import numpy as np


x_c, y_c = 4.33333, -0.333333
x = np.linspace(x_c - 10, x_c + 10, 400)

plt.xlim(x_c - 10, x_c + 10)
plt.ylim(y_c - 10, y_c + 10)

if abs(4) > 1e-9:
    plt.plot(x, (3 - 1 * x) / 4, 'b-', label='1x + 4y = 3')
else:
    plt.axvline(x=3, color='b', label='x = 3')

if abs(5) > 1e-9:
    plt.plot(x, (7 - 2 * x) / 5, 'r-', label='2x + 5y = 7')
else:
    plt.axvline(x=3.5, color='r', label='x = 3.5')

plt.plot(x_c, y_c, 'go', markersize=8, label=f'({x_c:.3f}, {y_c:.3f})')
plt.annotate(
    f'({x_c:.3f}, {y_c:.3f})',
    (x_c, y_c),
    textcoords='offset points',
    xytext=(8, 8)
)

plt.axhline(0, color='black', linewidth=0.5)
plt.axvline(0, color='black', linewidth=0.5)
plt.grid(True, alpha=0.3)
plt.legend()
plt.title('First task')
plt.tight_layout()
plt.show()
