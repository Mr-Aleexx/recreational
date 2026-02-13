#include "raylib.h"
#include <stdio.h>
#include <time.h>
#include <math.h>

#define WIDTH  900
#define HEIGHT 600
#define DEG_TO_RAD (PI / 180.0)
#define LINE_THICNESS 5

const int CLOCK_RADIUS = HEIGHT * 0.45;
const Vector2 CLOCK_CENTER = {(float) WIDTH / 2, (float) HEIGHT / 2};

const int HOUR_HAND_LENGTH    = 0.5 * CLOCK_RADIUS;
const int MINUTE_HAND_LENGTH  = 0.6 * CLOCK_RADIUS;
const int SECONDS_HAND_LENGTH = 0.8 * CLOCK_RADIUS;


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


void draw_minute_markers(Vector2 center, float clock_radius) {
    float alpha = 0;

    for (int i = 0 ; i < 60 ; i++) {
        float x_in;
        float y_in;
        if (i % 5 == 0) {
            x_in = center.x +  clock_radius * 0.85 * cosf(alpha * DEG_TO_RAD);
            y_in = center.y +  clock_radius * 0.85 * sinf(alpha * DEG_TO_RAD);
        }
        else {
            x_in = center.x +  clock_radius * 0.9 * cosf(alpha * DEG_TO_RAD);
            y_in = center.y +  clock_radius * 0.9 * sinf(alpha * DEG_TO_RAD);
        }

        Vector2 in = {x_in, y_in};

        float x_out = center.x +  clock_radius * 0.98 * cosf(alpha * DEG_TO_RAD);
        float y_out = center.y +  clock_radius * 0.98 * sinf(alpha * DEG_TO_RAD);
        Vector2 out = {x_out, y_out};
        alpha += 360.0 / 60.0;
        DrawLineEx(in, out, LINE_THICNESS, createColor(0, 0, 0, 255));
    }


}

void draw_hour_hand(Vector2 center, int clock_radius, int hour) {

    float x_in, y_in;
    float x_out, y_out;

    x_in = center.x;
    y_in = center.y;
    Vector2 in = {x_in, y_in};

    x_out = center.x +  clock_radius * 0.98 * cosf(hour*60 * DEG_TO_RAD);
    y_out = center.y +  clock_radius * 0.98 * sinf(hour*60 * DEG_TO_RAD);
    Vector2 out = {x_out, y_out};

    DrawLineEx(in, out, LINE_THICNESS, createColor(0, 0, 0, 255));
}

void draw_minute_hand(Vector2 center, int clock_radius, int minute) {

    float x_in, y_in;
    float x_out, y_out;

    x_in = center.x;
    y_in = center.y;
    Vector2 in = {x_in, y_in};

    x_out = center.x +  clock_radius * 0.98 * cosf(minute*60 * DEG_TO_RAD);
    y_out = center.y +  clock_radius * 0.98 * sinf(minute*60 * DEG_TO_RAD);
    Vector2 out = {x_out, y_out};

    DrawLineEx(in, out, LINE_THICNESS, createColor(255, 0, 0, 255));
}

void draw_seconds_hand(Vector2 center, int clock_radius, int seconds) {

    float x_in, y_in;
    float x_out, y_out;

    x_in = center.x;
    y_in = center.y;
    Vector2 in = {x_in, y_in};

    x_out = center.x +  clock_radius * 0.98 * cosf(seconds*60 * DEG_TO_RAD);
    y_out = center.y +  clock_radius * 0.98 * sinf(seconds*60 * DEG_TO_RAD);
    Vector2 out = {x_out, y_out};

    DrawLineEx(in, out, LINE_THICNESS, createColor(255, 0, 0, 255));
}


int main(void)
{
    // Remove log messages, tracelog code 7 = none
    SetTraceLogLevel(7);

    Color background = createColor(0, 0, 0, 255);
    Color clock_color = createColor(255, 255 ,255 , 255);

    time_t current_time = time(NULL);
    char* current_time_str = ctime(&current_time);
    struct tm *tm_struct = localtime(&current_time);
    int hour = tm_struct->tm_hour;
    int minute = tm_struct->tm_min;
    int seconds = tm_struct->tm_sec;

    printf("Hour : %d\n minute : %d\n seconds : %d\n",hour, minute, seconds);

    InitWindow(WIDTH, HEIGHT, "RayLib Basic clock");

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(background);
            DrawCircle(CLOCK_CENTER.x , CLOCK_CENTER.y, CLOCK_RADIUS , clock_color);
            DrawText(TextFormat("Current time : %s\n ", current_time_str ), 10, 10, 20, LIGHTGRAY);
            draw_minute_markers(CLOCK_CENTER ,CLOCK_RADIUS);
            draw_hour_hand(CLOCK_CENTER, HOUR_HAND_LENGTH, hour);
            draw_minute_hand(CLOCK_CENTER, MINUTE_HAND_LENGTH, minute);
            draw_seconds_hand(CLOCK_CENTER, SECONDS_HAND_LENGTH, seconds);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
