#include "raylib.h"
#include <stdio.h>
#include <time.h>
#include <math.h>

#define WIDTH  900
#define HEIGHT 600
#define DEG_TO_RAD (M_PI / 180.0)
#define LINE_THICNESS 5

const int CLOCK_RADIUS = HEIGHT * 0.45;
const Vector2 CLOCK_CENTER = {(float) WIDTH / 2, (float) HEIGHT / 2};

const float HOUR_HAND_LENGTH    = 0.5 * CLOCK_RADIUS;
const float MINUTE_HAND_LENGTH  = 0.6 * CLOCK_RADIUS;
const float SECONDS_HAND_LENGTH = 0.8 * CLOCK_RADIUS;


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
        float percentage_mult = (i % 5 == 0) ? 0.85 : 0.9;

        x_in = center.x +  clock_radius * percentage_mult * cosf(alpha * DEG_TO_RAD);
        y_in = center.y +  clock_radius * percentage_mult * sinf(alpha * DEG_TO_RAD);

        Vector2 in = {x_in, y_in};

        float x_out = center.x +  clock_radius * 0.98 * cosf(alpha * DEG_TO_RAD);
        float y_out = center.y +  clock_radius * 0.98 * sinf(alpha * DEG_TO_RAD);
        Vector2 out = {x_out, y_out};
        alpha += 360.0 / 60.0;
        DrawLineEx(in, out, LINE_THICNESS, createColor(0, 0, 0, 255));
    }


}

void draw_hour_hand(struct tm *tm) {
    float alpha = ((float) (tm->tm_hour % 12)) * 30;

    float x_out, y_out;
    x_out = CLOCK_CENTER.x + HOUR_HAND_LENGTH * cosf(alpha * DEG_TO_RAD);
    y_out = CLOCK_CENTER.y + HOUR_HAND_LENGTH * sinf(alpha * DEG_TO_RAD);
    Vector2 out = {x_out, y_out};

    DrawLineEx(CLOCK_CENTER, out, LINE_THICNESS, createColor(0, 0, 0, 255));
}

void draw_minute_hand(struct tm *tm) {

    float alpha = ((float) (tm->tm_min) * 6);

    float x_out, y_out;
    x_out = CLOCK_CENTER.x + HOUR_HAND_LENGTH * cosf(alpha * DEG_TO_RAD);
    y_out = CLOCK_CENTER.y + HOUR_HAND_LENGTH * sinf(alpha * DEG_TO_RAD);
    Vector2 out = {x_out, y_out};

    DrawLineEx(CLOCK_CENTER, out, LINE_THICNESS, createColor(0, 0, 255, 255));
}

void draw_seconds_hand(struct tm *tm) {

    float alpha = ((float) (tm->tm_sec)) * 6;
    float x_out, y_out;

    x_out = CLOCK_CENTER.x + HOUR_HAND_LENGTH * cosf(alpha * DEG_TO_RAD);
    y_out = CLOCK_CENTER.y + HOUR_HAND_LENGTH * sinf(alpha * DEG_TO_RAD);
    Vector2 out = {x_out, y_out};

    printf("alpha : %f\n",alpha);
    DrawLineEx(CLOCK_CENTER, out, LINE_THICNESS, createColor(255, 0, 0, 255));}


int main(void)
{
    // Remove log messages, tracelog code 7 = none
    SetTraceLogLevel(7);


    Color background = createColor(0, 0, 0, 255);
    Color clock_color = createColor(255, 255 ,255 , 255);

    time_t current_time = time(NULL);
    char* current_time_str = ctime(&current_time);
    struct tm *tm_struct = localtime(&current_time);
    size_t size_tm = sizeof(*tm_struct);
    printf("size of tm : %zu\n", size_tm);
    int hour = tm_struct->tm_hour;
    int minute = tm_struct->tm_min;
    int seconds = tm_struct->tm_sec;

    printf("Hour : %d\nminute : %d\nseconds : %d\n",hour, minute, seconds);

    InitWindow(WIDTH, HEIGHT, "RayLib Basic clock");

    while (!WindowShouldClose())
    {
        current_time = time(NULL);
        current_time_str = ctime(&current_time);
        tm_struct = localtime(&current_time); 
        BeginDrawing();
            ClearBackground(background);
            DrawCircle(CLOCK_CENTER.x , CLOCK_CENTER.y, CLOCK_RADIUS , clock_color);
            DrawText(TextFormat("Current time : %s\n ", current_time_str ), 10, 10, 20, LIGHTGRAY);
            draw_minute_markers(CLOCK_CENTER ,CLOCK_RADIUS);
            draw_hour_hand(tm_struct);
            draw_minute_hand(tm_struct);
            draw_seconds_hand(tm_struct);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
