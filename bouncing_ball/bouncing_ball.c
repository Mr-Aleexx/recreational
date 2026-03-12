#include <stdio.h>
#include <stdlib.h>

#include "raylib.h"

#define FPS 60

#define MAX_BALL 3000
#define BALL_DEFAULT_RADIUS 20

#define WIDTH  1200.0f
#define HEIGHT 900.0f

bool use_gravity = true;
bool pause = 0;
bool rand_pos = true;
bool default_ball_radius = true;

float bouncing_coefficient = 0.95f;
float gravity = 0.8f;

typedef struct {
    Vector2 ball_position;
    Vector2 ball_speed;
    int ball_radius;
    Color ball_color;
} Ball;

void init_ball(Ball* b, Vector2 pos, Vector2 speed, int radius, Color color ) {
    b->ball_position = pos;
    b->ball_speed    = speed;
    b->ball_radius   = radius;
    b->ball_color    = color;
}

void handle_ball_gravity(Ball* b) {
    b->ball_position.x += b->ball_speed.x;
    b->ball_position.y += b->ball_speed.y;
    if (use_gravity) b->ball_speed.y += gravity;

    if (b->ball_position.x >= (WIDTH - b->ball_radius)) {
        b->ball_position.x = WIDTH - b->ball_radius;   
        b->ball_speed.x *= -1.0f;
    } else if (b->ball_position.x <= b->ball_radius) {
        b->ball_position.x = b->ball_radius;            
        b->ball_speed.x *= -1.0f;
    }

    if (b->ball_position.y >= (HEIGHT - b->ball_radius)) {
        b->ball_position.y = HEIGHT - b->ball_radius; 
        b->ball_speed.y *= -bouncing_coefficient;
    } else if (b->ball_position.y <= b->ball_radius) {
        b->ball_position.y = b->ball_radius; 
        b->ball_speed.y *= -bouncing_coefficient;
    }

}

void print_ball_specs(Ball *b) {
    printf("Pos : %f:%f\nSpeed : %f:%f\nRadius : %d\n\n", 
            b->ball_position.x, b->ball_position.y,
            b->ball_speed.x   , b->ball_speed.y,
            b->ball_radius);
}


void DrawSpecs(int framesCounter) {

            DrawText("PRESS SPACE to PAUSE BALL MOVEMENT", 10, GetScreenHeight() - 30, 10, LIGHTGRAY);

            if (use_gravity) DrawText("gravity: ON (Press G to disable) current gravity : ", 10, GetScreenHeight() - 40, 10, DARKGREEN);

            else DrawText("gravity: OFF (Press G to enable)", 10, GetScreenHeight() - 40, 10, RED);

            DrawText(TextFormat("Current gravity : %f", gravity), 10, HEIGHT - 50, 10, GREEN);


            DrawText(TextFormat("Bouncing coefficient : %.2f", bouncing_coefficient), 10, GetScreenHeight() - 60, 10, DARKGREEN);
            if (pause && ((framesCounter/30)%2)) DrawText("PAUSED", (WIDTH  / 2) - 20, (HEIGHT / 2) - 20, 30, GRAY);

            DrawFPS(10, 10);
}

int main(void)
{

    SetTraceLogLevel(7);
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(WIDTH, HEIGHT, "raylib [shapes] example - bouncing ball");


    int texSize = BALL_DEFAULT_RADIUS * 2;
    RenderTexture ballTexture = LoadRenderTexture(texSize, texSize);
    BeginTextureMode(ballTexture);
        DrawCircle(BALL_DEFAULT_RADIUS, BALL_DEFAULT_RADIUS, (float)BALL_DEFAULT_RADIUS, WHITE);
        DrawCircleLines(BALL_DEFAULT_RADIUS, BALL_DEFAULT_RADIUS, (float)BALL_DEFAULT_RADIUS, BLACK);
    EndTextureMode();


    Ball* balls = malloc(MAX_BALL*sizeof(Ball));

    int framesCounter = 0;

    for(int i = 0 ; i < MAX_BALL ; i++) {
    
        Vector2 pos;
        int radius;

        if (rand_pos) 
            pos = (Vector2){GetRandomValue(20, WIDTH  - 20), GetRandomValue(20, HEIGHT - 20)};
        else
            pos = (Vector2){WIDTH/2, HEIGHT/2};

        Vector2 speed = {GetRandomValue(-5, 5), GetRandomValue(-5, 5) };

        if (default_ball_radius)
            radius = BALL_DEFAULT_RADIUS;
        else
            radius    = GetRandomValue(5, 20);

        Color color   = { GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(0, 255), 255 };

        init_ball(&balls[i],pos, speed, radius,color);

    }


    SetTargetFPS(FPS); 

    while (!WindowShouldClose())    
    {
        if (IsKeyPressed(KEY_G)) use_gravity = !use_gravity;
        if (IsKeyPressed(KEY_SPACE)) pause = !pause;
        
        if (IsKeyPressed(KEY_DOWN) && gravity > 0.1) gravity -= 0.05;
        if (IsKeyPressed(KEY_UP) ) gravity += 0.05;

        if (IsKeyPressed(KEY_LEFT)   && bouncing_coefficient > 0.1) bouncing_coefficient -= 0.05;
        if (IsKeyPressed(KEY_RIGHT)  && bouncing_coefficient < 1) bouncing_coefficient += 0.05;

        if (!pause)
        {
            for(int i = 0 ; i < MAX_BALL ; i++) {
                handle_ball_gravity(&balls[i]);
            }
        }
        else framesCounter++;

        BeginDrawing();

            ClearBackground(RAYWHITE);
            if (default_ball_radius) {
                for (int i = 0 ; i < MAX_BALL ; i++) {
                    DrawTexture(ballTexture.texture,
                                (int)(balls[i].ball_position.x - ballTexture.texture.width / 2.0f),
                                (int)(balls[i].ball_position.y - ballTexture.texture.height / 2.0f),
                                balls[i].ball_color);
                }
            }
            else {
                for(int i = 0 ; i < MAX_BALL ; i++) {
                    DrawCircleV(balls[i].ball_position, balls[i].ball_radius, balls[i].ball_color);
                }
            }

        DrawSpecs(framesCounter);
        EndDrawing();
    }

    free(balls);

    CloseWindow();

    return 0;
}

