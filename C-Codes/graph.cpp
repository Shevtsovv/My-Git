#include "raylib.h"

const int screen_width = 800, screen_hight = 800;
const int hwm = 400;
const float dx = 0.1;
const int x_max = 20, x_min = -20;

void Draw_Axes(int* m){
    Vector2 x_ = {0, screen_hight / 2};
    Vector2 x1_ = {screen_width, screen_hight / 2};
    Vector2 y_ = {screen_width / 2, 0};
    Vector2 y1_ = {screen_width / 2, screen_hight};
    DrawLineEx(x_, x1_, 2, GRAY);
    DrawLineEx(y_, y1_, 2, GRAY);

    for(int x = screen_width / 2; x < screen_width; x += (1*(*m))){
        DrawLine(x, screen_hight / 2 - hwm, x, screen_hight / 2 + hwm, DARKGRAY);
    }
    for(int x = screen_width / 2; x > 0; x -= (1*(*m))){
        DrawLine(x, screen_hight / 2 - hwm, x, screen_hight / 2 + hwm, DARKGRAY);
    }
    for(int y = screen_hight / 2; y < screen_hight; y += (1*(*m))){
        DrawLine(screen_width / 2 - hwm, y, screen_width / 2 + hwm, y, DARKGRAY);
    }
    for(int y = screen_hight / 2; y > 0; y -= (1*(*m))){
        DrawLine(screen_width / 2 - hwm, y, screen_width / 2 + hwm, y, DARKGRAY);
    }
}

void Draw_Function(int* m){
    for (float i = x_min; i < x_max; i += dx){
        DrawCircle(i*(*m) + screen_width / 2, -(i * i * (*m)) + screen_hight / 2, 3, GREEN);
    }
}
int main() {
    int mult = 400, dm = 10;
    
    InitWindow(screen_width, screen_hight, "Raylib Graph Example");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(BLACK);
        Draw_Axes(&mult);
        Draw_Function(&mult);

        if (GetMouseWheelMove() > 0){
            mult += dm;
            if (mult >= 350){mult = 350;}
        }
        if (GetMouseWheelMove() < 0) 
        {
            mult -= dm;
            if (mult <= 20) {mult = 20;}
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
