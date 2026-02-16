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

const float HOUR_HAND_LENGTH    = 0.35 * CLOCK_RADIUS;
const float MINUTE_HAND_LENGTH  = 0.6  * CLOCK_RADIUS;
const float SECONDS_HAND_LENGTH = 0.8  * CLOCK_RADIUS;

// Angle progressions since it's used everywhere
const float HOUR_AP   = 360.0/12.0;
const float MINSEC_AP = 360.0/60.0;

int clamp(int v) {
    if (v < 0) return 0;
    if (v > 255) return 255;
    return v;
}

struct Color create_color(int r, int g, int b, int a) {
    return (struct Color){
        clamp(r),
        clamp(g),
        clamp(b),
        clamp(a)
    };
}


void draw_minute_markers() {
    float alpha = 0;

    for (int i = 0 ; i < 60 ; i++) {
        float x_in;
        float y_in;
        float percentage_mult = (i % 5 == 0) ? 0.85 : 0.9;
        float line_thiccness  = (i % 5 != 0) ? 2    : LINE_THICNESS;

        x_in = CLOCK_CENTER.x + CLOCK_RADIUS * percentage_mult * cosf(alpha * DEG_TO_RAD);
        y_in = CLOCK_CENTER.y +  CLOCK_RADIUS * percentage_mult * sinf(alpha * DEG_TO_RAD);

        Vector2 in = {x_in, y_in};

        float x_out = CLOCK_CENTER.x + CLOCK_RADIUS * 0.98 * cosf(alpha * DEG_TO_RAD);
        float y_out = CLOCK_CENTER.y + CLOCK_RADIUS * 0.98 * sinf(alpha * DEG_TO_RAD);
        Vector2 out = {x_out, y_out};
        alpha += MINSEC_AP;
        DrawLineEx(in, out, line_thiccness, create_color(0, 0, 0, 255));
    }
}


void draw_hour_numbers() {

    int   position_correction = 3;
    float alpha = -90.0 + HOUR_AP;
    float x, y;

    for (int i = 0 ; i < 12 ; i++) {
        x = CLOCK_CENTER.x + CLOCK_RADIUS * 0.75 * cos(alpha * DEG_TO_RAD);
        y = CLOCK_CENTER.y + CLOCK_RADIUS * 0.75 * sin(alpha * DEG_TO_RAD);

        alpha += HOUR_AP;
        int text_size = MeasureText(TextFormat("%d", (i+1)), 30) / 2; 
        DrawText(TextFormat("%d", (i+1) ), x - text_size, y - text_size - position_correction, 30, create_color(0, 0, 0, 255));
    }
}

void draw_hour_hand(struct tm *tm) {

    float minutes_progression = ((float)tm->tm_min) / 60.0;
    float alpha = (((float) (tm->tm_hour % 12)) * HOUR_AP) - 90.0;
    alpha += HOUR_AP*minutes_progression;

    float x_out, y_out;
    x_out = CLOCK_CENTER.x + HOUR_HAND_LENGTH * cosf(alpha * DEG_TO_RAD);
    y_out = CLOCK_CENTER.y + HOUR_HAND_LENGTH * sinf(alpha * DEG_TO_RAD);
    Vector2 out = {x_out, y_out};

    DrawLineEx(CLOCK_CENTER, out, LINE_THICNESS, create_color(0, 0, 0, 255));
}

void draw_minute_hand(struct tm *tm) {

    float seconds_progression =  ((float)(tm->tm_sec)) / 60.0;

    float alpha = (((float) (tm->tm_min) * MINSEC_AP) - 90.0);
    alpha += MINSEC_AP*seconds_progression;

    float x_out, y_out;
    x_out = CLOCK_CENTER.x + MINUTE_HAND_LENGTH * cosf(alpha * DEG_TO_RAD);
    y_out = CLOCK_CENTER.y + MINUTE_HAND_LENGTH * sinf(alpha * DEG_TO_RAD);
    Vector2 out = {x_out, y_out};

    DrawLineEx(CLOCK_CENTER, out, LINE_THICNESS, create_color(0, 0, 0, 255));
}

void draw_seconds_hand(struct tm *tm) {

    float alpha = (((float) (tm->tm_sec)) * (360.0 / 60.0)) - 90.0;
    float x_out, y_out;

    x_out = CLOCK_CENTER.x + SECONDS_HAND_LENGTH * cosf(alpha * DEG_TO_RAD);
    y_out = CLOCK_CENTER.y + SECONDS_HAND_LENGTH * sinf(alpha * DEG_TO_RAD);
    Vector2 out = {x_out, y_out};

    DrawLineEx(CLOCK_CENTER, out, 2, create_color(255, 0, 0, 255));
}

void debug_time(struct tm *tm) {
    int hour    = tm->tm_hour;
    int minute  = tm->tm_min;
    int seconds = tm->tm_sec;
    printf("Hour : %d\nminute : %d\nseconds : %d\n",hour, minute, seconds);
}

int main(void)
{
    // Remove log messages, tracelog code 7 = none
    SetTraceLogLevel(7);
    // Anti aliazing
    SetConfigFlags(FLAG_MSAA_4X_HINT);

    Color background  = create_color(0, 0, 0, 255);
    Color clock_color = create_color(255, 255 ,255 , 255);

    time_t current_time = time(NULL);
    char* current_time_str = ctime(&current_time);
    struct tm *tm_struct = localtime(&current_time);

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

            draw_minute_markers();

            draw_hour_hand(tm_struct);
            draw_minute_hand(tm_struct);
            draw_seconds_hand(tm_struct);

            draw_hour_numbers();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
