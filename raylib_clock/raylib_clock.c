#include "raylib.h"
#include <stdio.h>
#include <time.h>
#include <math.h>

#define WIDTH  900
#define HEIGHT 600

#define DEG_TO_RAD (180.0 / PI)

int clamp(int v) {
    if (v < 0) return 0;
    if (v > 255) return 255;
    return v;
}

struct Color createColor(int r, int g, int b, int a) {
    return (struct Color){
        clamp(r),
        clamp(g),
        clamp(b),
        clamp(a)
    };
}


void draw_minute_markers(int center_x, float clock_radius) {
    float alpha = 0;

    for (int i = 0 ; i < 60 ; i++) {
        float x = center_x + clock_radius * cosf(alpha * DEG_TO_RAD);
        float y = center_x + clock_radius * sinf(alpha * DEG_TO_RAD);

        alpha += 360.0 / 60.0;
        DrawRectangle(x, y , 2, 2, createColor(255, 0, 0, 255));
    }


}

int main(void)
{
    // Remove log messages, tracelog code 7 = none
    SetTraceLogLevel(7);

    Color background = createColor(255, 255, 255, 255);
    Color clock_color = createColor(0, 0 ,0 , 255);

    time_t current_time = time(NULL);
    char* current_time_str = ctime(&current_time);

    int clock_radius = HEIGHT * 0.45;

    InitWindow(WIDTH, HEIGHT, "RayLib Basic clock");

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(background);
            DrawCircle(WIDTH/2, HEIGHT/2, clock_radius , clock_color);
            DrawText(TextFormat("Current time : %s\n ", current_time_str ), 10, 10, 20, LIGHTGRAY);
            draw_minute_markers(HEIGHT  / 2 ,clock_radius );
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
