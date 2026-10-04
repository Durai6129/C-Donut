#include <stdio.h>
#include <math.h>
#include <unistd.h>

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 40

const float theta_spacing = 0.02f; // initial 0.07f
const float phi_spacing = 0.01f;   // initial 0.02f

const float R1 = 0.5f;
const float R2 = 1.0f;
const float K2 = 10.0f;

const float K1 = SCREEN_WIDTH * K2 * 3.0f / (8.0f * (R1 + R2));

void render_frame(float A, float B){
    float cosA = cos(A), sinA = sin(A);
    float cosB = cos(B), sinB = sin(B);

    char output[SCREEN_WIDTH][SCREEN_HEIGHT];
    float zbuffer[SCREEN_WIDTH][SCREEN_HEIGHT];
    for(int y=0; y < SCREEN_HEIGHT; y++){
        for(int x = 0; x < SCREEN_WIDTH; x++){
            output[x][y] = ' ';
            zbuffer[x][y] = 0.0f;
        }
    }

    for(float theta = 0; theta <= 2 * M_PI; theta += theta_spacing){
        float costheta = cos(theta);
        float sintheta = sin(theta);

        for(float phi = 0; phi <= 2 * M_PI; phi += phi_spacing){
            float cosphi = cos(phi);
            float sinphi = sin(phi);

            float circlex = R2 + R1 * costheta;
            float circley = R1 * sintheta;

            // float x = circlex * cosphi;
            // float y = circley;
            // float z = K2 + -circlex * sinphi;  // multiply -1 if something goes wrong.

            float x = circlex * (cosB * cosphi + sinA * sinB * sinphi)
                - circley * cosA * sinB;
            float y = circlex * (sinB * cosphi - sinA * cosB * sinphi)
                + circley * cosA * cosB;
            float z = K2 + cosA * circlex * sinphi
                + circley * sinA;

            float ooz = 1/z; // "one over z"

            int xp = (int)(SCREEN_WIDTH / 2 + K1 * ooz * x);
            int yp = (int)(SCREEN_HEIGHT / 2 - K1 * ooz * y * 0.5); // minus because terminal's y axis points downward.

            float L = cosphi*costheta*sinB - cosA*costheta*sinphi -
            sinA*sintheta + cosB*(cosA*sintheta - costheta*sinA*sinphi);

            if (xp >= 0 && xp < SCREEN_WIDTH && yp >= 0 && yp < SCREEN_HEIGHT){
                if (L > 0){
                    if (ooz > zbuffer[xp][yp]){
                        zbuffer[xp][yp] = ooz;
                        int luminance_index = (int)(L*8);
                        output[xp][yp] = ".,-~:;=!*#$@"[luminance_index];
                    }
                }
            }
        }
    }

    printf("\x1b[H");
    for (int j = 0; j < SCREEN_HEIGHT; j++){
        for (int i = 0; i < SCREEN_WIDTH; i++){
            putchar(output[i][j]);
        }
        putchar('\n');
    }
}

int main(void)
{
    float A = 0;
    float B = 0;

    while (1) {
        render_frame(A, B);

        A += 0.04f; // initial 0.04f
        B += 0.02f; // initial 0.02f

        usleep(30000);
    }

    return 0;
}