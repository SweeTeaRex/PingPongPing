//                                                                                                                                                
//                                                                                                                                                
//  MMP""MM""YMM              `7MM"""Mq.                        `7MM"""Mq.                                                                        
//  P'   MM   `7                MM   `MM.                         MM   `MM.                                                                       
//       MM  .gP"Ya   ,6"Yb.    MM   ,M9  .gP"Ya `7M'   `MF'      MM   ,M9 `7Mb,od8 ,pW"Wq.   .P"Ybmmm `7Mb,od8 ,6"Yb.  `7MMpMMMb.pMMMb.  ,pP"Ybd 
//       MM ,M'   Yb 8)   MM    MMmmdM9  ,M'   Yb  `VA ,V'        MMmmdM9    MM' "'6W'   `Wb :MI  I8     MM' "'8)   MM    MM    MM    MM  8I   `" 
//       MM 8M""""""  ,pm9MM    MM  YM.  8M""""""    XMX          MM         MM    8M     M8  WmmmP"     MM     ,pm9MM    MM    MM    MM  `YMMMa. 
//       MM YM.    , 8M   MM    MM   `Mb.YM.    ,  ,V' VA.        MM         MM    YA.   ,A9 8M          MM    8M   MM    MM    MM    MM  L.   I8 
//     .JMML.`Mbmmd' `Moo9^Yo..JMML. .JMM.`Mbmmd'.AM.   .MA.    .JMML.     .JMML.   `Ybmd9'   YMMMMMb  .JMML.  `Moo9^Yo..JMML  JMML  JMML.M9mmmP' 
//                                                                                           6'     dP                                            
//                                                                                           Ybmmmd'                                              
//
//
// Created by: Trey Adams

#include <stdio.h>
#include <string.h>
#include <raylib.h>

typedef enum GameScreen {
    StartScreen = 0,
    PlayScreen
} GameScreen;


int main(void)
{
    InitWindow(1500, 1000, "Game");

    
    // screen size init
    const int screenWidth = GetScreenWidth();
    printf("screenWidth: %i", screenWidth);
    const int screenHeight = GetScreenHeight();
    printf("screenHeight: %i", screenHeight);
    

    GameScreen currentScreen = StartScreen;

    // ------StartScreen-------- 

    //programmers.png init
    Image programmers_image = LoadImage("programmers.png");
    Texture2D programmers_texture = LoadTextureFromImage(programmers_image);
    //free memory from Image)
    UnloadImage(programmers_image);
    // init button
    Rectangle startbutton = { (screenWidth/2), (screenHeight/2), 500, 100};

    // button bounds
    Rectangle startbtnbounds = { ((screenWidth/2)-startbutton.width/2), ((screenHeight/2) + 350), (float)startbutton.width, (float)startbutton.height};
    // init mouse
    Vector2 mousePoint = { 0.0f, 0.0f };

    // ----PlayScreen------

    // exit button
    Rectangle exit_button = {0, 0, 100, 100};
    Rectangle exit_button_bounds = {(screenWidth/2), 30, exit_button.width, exit_button.height};
    //exit.png init
    Image exit_image = LoadImage("exitdoor.png");
    ImageResize(&exit_image, 100, 100);
    Texture2D exit_texture = LoadTextureFromImage(exit_image);
    //free exit.png memory
    UnloadImage(exit_image);
    //init bouncing ball
    Vector2 ballPosition = { screenWidth/2.0f, screenHeight/2.0f };
    Vector2 ballSpeed = { 5.0f, 4.0f };
    int ballRadius = 20;
    // pause menu init
    bool pause = 0;
    // frame counter
    int framesCounter = 0;

    // init paddles
    Rectangle paddleLeft = { (screenWidth-(screenWidth/16)*15), (screenHeight/2), 25, 300};
    Rectangle paddleRight = { (screenWidth-(screenWidth/16)*1), (screenHeight/2), 25, 300};
    // paddle bounds
    Rectangle paddleLeft_bounds = {0, 0, paddleLeft.width, paddleLeft.height};
    Rectangle paddleRight_bounds = {0, 0, paddleRight.width, paddleRight.height };


    SetTargetFPS(60);
    
    while (!WindowShouldClose())
    {
        mousePoint = GetMousePosition();
        switch(currentScreen)
        {
            case StartScreen:
            {
                
                if(CheckCollisionPointRec(mousePoint, startbtnbounds) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    currentScreen = PlayScreen;
                }
                break;
            }
            case PlayScreen:
            {
                if(CheckCollisionPointRec(mousePoint, exit_button_bounds) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    currentScreen = StartScreen;
                }
                if (IsKeyPressed(KEY_SPACE)) pause = !pause;

                if (!pause)
                {
                    
                    

if ((ballPosition.x >= (GetScreenWidth() - ballRadius)) || (ballPosition.x <= ballRadius)) ballSpeed.x *= -1.0f;
                    if ((ballPosition.y >= (GetScreenHeight() - ballRadius)) || (ballPosition.y <= ballRadius)) ballSpeed.y *= -1.0f;
                break;
            }        
        }
        BeginDrawing();

        ClearBackground(WHITE);

        switch(currentScreen)
        {
            case StartScreen:
            {
                DrawText("Welcome! \nThis is my first C program that I have made on my own. \nHave fun!", 2, 2, 50, BLACK);
                // Used ChatGPT to help with centering button and image
                
                DrawRectangle((screenWidth/2)-(startbutton.width/2), ((screenHeight/2) + 350), startbutton.width, startbutton.height, BLACK);
                // measure text width
                int textWidth = MeasureText("START", 100);
                DrawText("START", (screenWidth/2)-(textWidth/2), ((screenHeight/2)+350)+(startbutton.height/2) - (100/2), 100, WHITE);
            
                // I used ChatGPT.com to figure out how to center the image 
                DrawTexture(programmers_texture, ((screenWidth - programmers_texture.width)/2), ((screenHeight - programmers_texture.height)/2), WHITE);

                // referenced button properties from user https://www.raylib.com/examples/textures/loader.html?name=textures_sprite_button
                break;
            }
            
            case PlayScreen:
            {
                //Draw Exit Sign
                DrawText("Click to Exit", (screenWidth/2), 0, 20, BLACK);
                DrawTexture(exit_texture, (screenWidth/2), 30, WHITE);

                //Draw ball
                DrawCircleV(ballPosition, (float)ballRadius, MAROON);

                // Draw Paddles
                DrawRectangle(paddleLeft.x, paddleLeft.y, paddleLeft.width, paddleLeft.height, BLACK);
                DrawRectangle(paddleRight.x, paddleRight.y, paddleRight.width, paddleRight.height, BLACK);



                break;



            }
        }

        EndDrawing();
    }

    CloseWindow();
    
    
    return 0;
}
