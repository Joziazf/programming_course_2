import matplotlib.pyplot as plt
import numpy as np


pts = [
    (-2, -4),
    (2, 3),
    (-4, 1)
]

xs = [p[0] for p in pts] + [pts[0][0]]
ys = [p[1] for p in pts] + [pts[0][1]]

plt.plot(xs, ys, 'b-')
plt.fill(xs, ys, alpha=0.2, color='blue')

labels = ['P1', 'P2', 'P3']
for i, (px, py) in enumerate(pts):
    plt.plot(px, py, 'bo', markersize=6)
    plt.annotate(
        f'{labels[i]} ({px:.3f}, {py:.3f})',
        (px, py),
        textcoords='offset points',
        xytext=(8, 8)
    )

x_min, x_max = min(xs) - 5, max(xs) + 5
x = np.linspace(x_min, x_max, 400)
plt.xlim(x_min, x_max)

if abs(4) > 1e-9:
    plt.plot(
        x, (-2 - -7 * x) / 4,
        '--', alpha=0.5, label='-7x + 4y = -2'
    )
else:
    plt.axvline(x=0.285714, linestyle='--', alpha=0.5)

if abs(2) > 1e-9:
    plt.plot(
        x, (-18 - 5 * x) / 2,
        '--', alpha=0.5, label='5x + 2y = -18'
    )
else:
    plt.axvline(x=-3.6, linestyle='--', alpha=0.5)

if abs(-6) > 1e-9:
    plt.plot(
        x, (-14 - 2 * x) / -6,
        '--', alpha=0.5, label='2x + -6y = -14'
    )
else:
    plt.axvline(x=-7, linestyle='--', alpha=0.5)

plt.axhline(0, color='black', linewidth=0.5)
plt.axvline(0, color='black', linewidth=0.5)
plt.grid(True, alpha=0.3)
plt.legend()
plt.title('Triangle  |  Area = 17.000')
plt.tight_layout()
plt.show()
