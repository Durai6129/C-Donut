import math
import time

SCREEN_WIDTH = 80
SCREEN_HEIGHT = 40

theta_spacing = 0.04
phi_spacing = 0.01

R1 = 0.5
R2 = 1.0
K2 = 10.0

K1 = SCREEN_WIDTH * K2 * 3.0 / (8.0 * (R1 + R2))

def render_frame(A, B):
    cosA = math.cos(A); sinA = math.sin(A)
    cosB = math.cos(B); sinB = math.sin(B)

    output = [[' '] * SCREEN_HEIGHT for _ in range(SCREEN_WIDTH)]
    zbuffer = [[0.0] * SCREEN_HEIGHT for _ in range(SCREEN_WIDTH)]

    # for theta in range(0, 2 * math.pi, theta_spacing):
    theta = 0
    while theta < 2 * math.pi:
        costheta = math.cos(theta)
        sintheta = math.sin(theta)

        # for phi in range(0, 2 * math.pi, phi_spacing):
        phi = 0
        while phi < 2 * math.pi:
            cosphi = math.cos(phi)
            sinphi = math.sin(phi)

            circlex = R2 + R1 * costheta
            circley = R1 * sintheta

            x = circlex * (cosB * cosphi + sinA * sinB * sinphi) - circley * cosA * sinB
            y = circlex * (sinB * cosphi - sinA * cosB * sinphi) + circley * cosA * cosB
            z = K2 + cosA * circlex * sinphi + circley * sinA

            ooz = 1/z

            xp = int(SCREEN_WIDTH / 2 + K1 * ooz * x)
            yp = int(SCREEN_HEIGHT / 2 - K1 * ooz * y * 0.5)

            L = (cosphi * costheta * sinB) - (cosA * costheta * sinphi) - (sinA * sintheta) + cosB * (cosA * sintheta - costheta * sinA * sinphi)

            if xp >= 0 and xp < SCREEN_WIDTH and yp >= 0 and yp < SCREEN_HEIGHT:
                if L > 0:
                    if ooz > zbuffer[xp][yp]:
                        zbuffer[xp][yp] = ooz
                        luminance_index = min(int(L * 8), 10)
                        output[xp][yp] = ".,-~:;=*#$@"[luminance_index]

            phi += phi_spacing

        theta += theta_spacing

    print("\x1b[H", end='')
    for j in range(SCREEN_HEIGHT):
        for i in range(SCREEN_WIDTH):
            print(output[i][j], end='')
        print()


def main():
    A = 0
    B = 0

    while True:
        render_frame(A, B)
        time.sleep(0.01)

        A += 0.04
        B += 0.02

if __name__ == "__main__":
    main()