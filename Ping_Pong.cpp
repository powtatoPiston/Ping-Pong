#include "raylib.h"

    // Int variables
    int VarBallX = 100;
    int VarBallSpeedX = -3;
    int VarPlayerY = 80;
    int VarPlayerScore = 0;
    int VarBotScore = 0;
    int VarTextWidth = 0;
    int VarWinner = 0; // 0 is 'game still running', 1 is 'player wins', 2 is 'bot wins'

    // Float variables
    float VarBallY = 115;
    float VarBallSpeedY = 0;
    float VarBotY = 80;

// Reset shapes function
void ResetShapes()
{
    // Ball
    if(GetRandomValue(1, 2) == 1)
    {
        VarBallSpeedX = 3;
    }
    else
    {
        VarBallSpeedX = -3;
    }
    VarBallSpeedY = 0;
    VarBallX = 100;
    VarBallY = 115;

    // Paddles
    VarPlayerY = 80;
    VarBotY = 80;
}

int main()
{
         // Screen Setup
    InitWindow(320, 240, "Ping Pong");
    SetTargetFPS(60);

    while (!WindowShouldClose()) // Game loop
 {
BeginDrawing();
ClearBackground(BLACK);

    if(VarWinner != 0)
    {
        if(VarWinner == 1)
        {
            VarTextWidth = MeasureText("You Win", 30);
            DrawText("You Win", (320 - VarTextWidth) / 2, 135, 30, GREEN);
        }

        else
        {
            VarTextWidth = MeasureText("You Lose", 30);
            DrawText("You Lose", (320 - VarTextWidth) / 2, 135, 30, RED);
        }
        EndDrawing();

        if(IsKeyPressed(KEY_R))
        {
            ResetShapes();
            VarPlayerScore = 0;
            VarBotScore = 0;
            VarWinner = 0;
        }
    }

    else
    {
        // Moving the ball
VarBallX = VarBallX + VarBallSpeedX;
VarBallY = VarBallY + VarBallSpeedY;

//Bot movements
if((VarBotY + 30) < VarBallY)
{
    VarBotY = VarBotY + 1.75;
}

if((VarBotY + 30) > VarBallY)
{
    VarBotY = VarBotY - 1.75;
}

// Key inputs
if(IsKeyDown(KEY_W))
{
    VarPlayerY = VarPlayerY - 4;
}

if(IsKeyDown(KEY_S))
{
    VarPlayerY = VarPlayerY + 4;
}

// Define the shapes
Rectangle Ball = {VarBallX, VarBallY, 10, 10};
Rectangle Player = {20, VarPlayerY, 10, 60};
Rectangle Bot = {280, VarBotY, 10, 60};

// Ball bouncing
if(CheckCollisionRecs(Player, Ball) && VarBallSpeedX < 0)
{
    VarBallSpeedX = 0 - VarBallSpeedX;
    VarBallSpeedY = GetRandomValue(-35, 35) / 10.0f;
}

if(CheckCollisionRecs(Bot, Ball) && VarBallSpeedX > 0)
{
    VarBallSpeedX = 0 - VarBallSpeedX;
    VarBallSpeedY = GetRandomValue(-35, 35) / 10.0f;
}

if(VarBallY < 0)
{
    VarBallSpeedY = 0 - VarBallSpeedY;
}

if(VarBallY > 230)
{
    VarBallSpeedY = 0 - VarBallSpeedY;
}

// Paddle boundraries
if(VarPlayerY < 0)
{
    VarPlayerY = 1;
}

if(VarPlayerY > 180)
{
    VarPlayerY = 179;
}

if(VarBotY < 0)
{
    VarBotY = 1;
}

if(VarBotY > 180)
{
    VarBotY = 179;
}

// Points
if(VarBallX < -20)
{
    VarBotScore = VarBotScore + 1;
    ResetShapes();
    if(VarBotScore > 6)
    {
        VarWinner = 2;
    }
}

if(VarBallX > 340)
{
     VarPlayerScore = VarPlayerScore + 1;
    ResetShapes();
    if(VarPlayerScore > 6)
    {
        VarWinner = 1;
    }
}


// Set positions
Ball.x = VarBallX;
Ball.y = VarBallY;
Player.y = VarPlayerY;
Bot.y = VarBotY;

// Draw the screen shapes
DrawRectangleRec(Ball, WHITE);
DrawRectangleRec(Player, WHITE);
DrawRectangleRec(Bot, WHITE);

// Draw the screen scores
VarTextWidth = MeasureText(TextFormat("%i", VarPlayerScore), 25);
DrawText(TextFormat("%i", VarPlayerScore), 110 - (VarTextWidth / 2), 10, 25, WHITE);
VarTextWidth = MeasureText("|", 35);
DrawText("|", 160 - (VarTextWidth / 2), 5, 35, WHITE);
VarTextWidth = MeasureText(TextFormat("%i", VarBotScore), 25);
DrawText(TextFormat("%i", VarBotScore), 210 - (VarTextWidth / 2), 10, 25, WHITE);

EndDrawing();
 }
    }
    }