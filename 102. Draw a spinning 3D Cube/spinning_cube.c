#include <stdio.h>
#include <math.h>
#include <string.h>
#include <unistd.h>

#define WIDTH 200
#define HEIGHT 60
#define CUBE_WIDTH 25
#define DISTANCE_FROM_CAM 80
#define INCREMENT_SPEED 0.6f
#define SIZE_FACTOR 40

float YZ, ZX, XY;

float z_buffer[WIDTH*HEIGHT];
char buffer[WIDTH*HEIGHT];
int background_ASCII_code = ' ';

float x, y, z;
float ooz;
int xp, yp;
int idx;

float calculate_x(int i, int j, int k) {
  return j * sin(YZ) * sin(ZX) * cos(XY) - k * cos(YZ) * sin(ZX) * cos(XY) +
         j * cos(YZ) * sin(XY) + k * sin(YZ) * sin(XY) + i * cos(ZX) * cos(XY); 
}

float calculate_y(int i, int j, int k) {
  return j * cos(YZ) * cos(XY) + k * sin(YZ) * cos(XY) -
         j * sin(YZ) * sin(ZX) * sin(XY) + k * cos(YZ) * sin(ZX) * sin(XY) -
         i * cos(ZX) * sin(XY);
}

float calculate_z(int i, int j, int k) {
  return k * cos(YZ) * cos(ZX) - j * sin(YZ) * cos(ZX) + i * sin(ZX);
}

void calculate_for_surface(float cube_x, float cube_y, float cube_z, int ch) {
  x = calculate_x(cube_x, cube_y, cube_z);
  y = calculate_y(cube_x, cube_y, cube_z);
  z = calculate_z(cube_x, cube_y, cube_z) + DISTANCE_FROM_CAM;
  
  ooz = 1/z;

  xp = (int)(WIDTH/1.5 - 2 * CUBE_WIDTH + SIZE_FACTOR * ooz * x * 2);
  yp = (int)(HEIGHT/2 + SIZE_FACTOR * ooz * y);

  idx = xp + yp *WIDTH;
  if (idx > 0 && idx < WIDTH*HEIGHT ) {
    if (ooz > z_buffer[idx]) {
      z_buffer[idx] = ooz;
      buffer[idx] = ch;
    }
  } 
}

int main(void) {
  while(1) {
    memset(buffer, background_ASCII_code,WIDTH*HEIGHT );
    memset(z_buffer, 0, WIDTH* HEIGHT * 4);
    for(float cube_x = -CUBE_WIDTH; cube_x < CUBE_WIDTH; cube_x += INCREMENT_SPEED) {
      for(float cube_y = -CUBE_WIDTH; cube_y < CUBE_WIDTH; cube_y += INCREMENT_SPEED) {
        calculate_for_surface(cube_x, cube_y, -CUBE_WIDTH, '#'); 
        calculate_for_surface(CUBE_WIDTH, cube_y, cube_x, '$');
        calculate_for_surface(-CUBE_WIDTH, cube_y, -cube_x, '.');
        calculate_for_surface(-cube_x, cube_y, CUBE_WIDTH, '~');
        calculate_for_surface(cube_x, -CUBE_WIDTH, -cube_y, ';');
        calculate_for_surface(cube_x, CUBE_WIDTH, cube_y, '-');
      }
    }
    for(int k = 0; k < WIDTH*HEIGHT ; k++) {
      putchar(k % WIDTH? buffer[k] : 10);
    }
    YZ += 0.003;
    ZX += 0.003;
    // XY += 0.003;
  }
  return 0;
}
