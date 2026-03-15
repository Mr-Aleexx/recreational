#include <stdio.h>
#include <stdlib.h>

#include "raylib.h"

#define FPS 60

#define MAX_BALLS 300000
#define BALL_DEFAULT_RADIUS 10

#define WIDTH  1200.0f
#define HEIGHT 900.0f

#define TEXTURE_COUNT 10

bool use_gravity = true;
bool pause = 0;
bool rand_pos = true;
bool default_radius = true;

int ball_cur_number = 100;
int ball_increment  = MAX_BALLS / 20;

float bouncing_coefficient = 0.95f;
float gravity = 0.8f;

typedef struct {
    Vector2 position;
    Vector2 speed;
    int radius;
    Color color;
} Ball;


// initiate a ball with random pos, speed, color and radius if default radius is disabeled
// (disabeling default radius might cause lag)
void init_ball(Ball* b, Vector2* pos) {
    int radius;
    Vector2 speed = {GetRandomValue(-5,5), GetRandomValue(-5,5)};

    if (default_radius)
        radius = BALL_DEFAULT_RADIUS;
    else
        radius = GetRandomValue(5,20);

    Color color = {GetRandomValue(0,255), GetRandomValue(0,255), GetRandomValue(0,255), 255};

    b->position = *pos;
    b->speed    = speed;
    b->radius   = radius;
    b->color    = color;
}

void handle_ball_gravity(Ball* b) {
    b->position.x += b->speed.x;
    b->position.y += b->speed.y;
    if (use_gravity) b->speed.y += gravity;

    if (b->position.x >= (WIDTH - b->radius)) {
        b->position.x = WIDTH - b->radius + 1;
        b->speed.x *= -1.0f;
    } else if (b->position.x <= b->radius) {
        b->position.x = b->radius + 1;            
        b->speed.x *= -1.0f;
    }

    if (b->position.y >= (HEIGHT - b->radius)) {
        b->position.y = HEIGHT - b->radius + 1; 
        b->speed.y *= -bouncing_coefficient;
    } else if (b->position.y <= b->radius) {
        b->position.y = b->radius + 1; 
        b->speed.y *= -bouncing_coefficient;
    }

}

void print_ball_specs(Ball *b) {
    printf("Pos : %f:%f\nSpeed : %f:%f\nRadius : %d\n\n", 
            b->position.x, b->position.y,
            b->speed.x   , b->speed.y,
            b->radius);
}


Vector2 generate_rand_pos() {
    return (Vector2){GetRandomValue(0, GetScreenWidth()), GetRandomValue(10,GetScreenHeight())};
}

void draw_specs() {

    DrawText("PRESS SPACE to PAUSE BALL MOVEMENT", 10, 
            GetScreenHeight() - 30, 
            10, 
            LIGHTGRAY);

    if (use_gravity) DrawText("gravity: ON (Press G to disable) current gravity : ", 
            10, 
            GetScreenHeight() - 40, 
            10, 
            DARKGREEN);

    else DrawText("gravity: OFF (Press G to enable)", 
            10, 
            GetScreenHeight() - 40, 
            10, 
            RED);

    DrawText(TextFormat("Current gravity : %f", gravity), 
            10, 
            HEIGHT - 50, 
            10, 
            GREEN);


    DrawText(TextFormat("Bouncing coefficient : %.2f", bouncing_coefficient), 
            10,
            GetScreenHeight() - 60, 
            10, 
            DARKGREEN);


    DrawText(TextFormat("Number of balls: %d", ball_cur_number), 
            10,
            GetScreenHeight() - 80, 
            10, 
            DARKGREEN);
    DrawFPS(10, 10);
}

int main(void)
{

    SetTraceLogLevel(7);
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(WIDTH, HEIGHT, "Bouncing Balls");

    int texSize = BALL_DEFAULT_RADIUS * 2;

    RenderTexture ballTexture = LoadRenderTexture(texSize, texSize);
    BeginTextureMode(ballTexture);
        DrawCircle(BALL_DEFAULT_RADIUS, BALL_DEFAULT_RADIUS, (float)BALL_DEFAULT_RADIUS, WHITE);
        //DrawCircleLines(BALL_DEFAULT_RADIUS, BALL_DEFAULT_RADIUS, (float)BALL_DEFAULT_RADIUS, BLACK);
    EndTextureMode();


    Ball* balls = (Ball *)calloc(MAX_BALLS,sizeof(Ball));

    int framesCounter = 0;


    for (int i = 0; i < ball_cur_number; i++) {
        Vector2 pos = generate_rand_pos();
        init_ball(&balls[i], &pos);
    }


    SetTargetFPS(FPS); 

    while (!WindowShouldClose())    
    {
        if (!pause)
        {
            for(int i = 0 ; i < ball_cur_number ; i++) {
                handle_ball_gravity(&balls[i]);
            }
        }
        else framesCounter++;

        if (IsKeyPressed(KEY_G)) use_gravity = !use_gravity;
        if (IsKeyPressed(KEY_SPACE)) pause = !pause;
        
        if (IsKeyPressed(KEY_DOWN) && gravity > 0.1) gravity -= 0.05;
        if (IsKeyPressed(KEY_UP) ) gravity += 0.05;

        if (IsKeyPressed(KEY_LEFT)   && bouncing_coefficient > 0.1) bouncing_coefficient -= 0.05;
        if (IsKeyPressed(KEY_RIGHT)  && bouncing_coefficient < 1) bouncing_coefficient += 0.05;


        if (IsKeyPressed(KEY_Z))  {
            ball_cur_number-=ball_increment;
            if (ball_cur_number < 0) ball_cur_number = 0;
        }
        if (IsKeyPressed(KEY_X)) {

            int old = ball_cur_number;
            ball_cur_number += ball_increment;
            if (ball_cur_number > MAX_BALLS) ball_cur_number = MAX_BALLS;

            for (int i = old; i < ball_cur_number; i++) {
                Vector2 pos = generate_rand_pos();
                init_ball(&balls[i], &pos);
            }
        }

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && ball_cur_number < MAX_BALLS) {

            Vector2 ball_mouse_placement = {GetMouseX(), GetMouseY()};
            int old = ball_cur_number;
            ball_cur_number += 1;
            if (ball_cur_number > MAX_BALLS) ball_cur_number = MAX_BALLS;

            for (int i = old; i < ball_cur_number; i++) {
                init_ball(&balls[i], &ball_mouse_placement);
            }
        }

        BeginDrawing();

            ClearBackground(RAYWHITE);
            if (default_radius) {
                for (int i = 0 ; i < ball_cur_number ; i++) {
                    DrawTexture(ballTexture.texture,
                                (int)(balls[i].position.x - ballTexture.texture.width / 2.0f),
                                (int)(balls[i].position.y - ballTexture.texture.height / 2.0f),
                                balls[i].color);
                }
            }
            else {
                for(int i = 0 ; i < ball_cur_number ; i++) {
                    DrawCircleV(balls[i].position, balls[i].radius, balls[i].color);
                }
            }

        draw_specs();

        if (pause && ((framesCounter/30)%2)) DrawText("PAUSED", (WIDTH  / 2) - 20, (HEIGHT / 2) - 20, 30, GRAY);


        EndDrawing();
    }

    free(balls);
    UnloadRenderTexture(ballTexture);
    CloseWindow();

    return 0;
}

