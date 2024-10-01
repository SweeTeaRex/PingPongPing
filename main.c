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
    
    // screen size init
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    InitWindow(screenWidth, screenHeight, "Game");

    GameScreen currentScreen = StartScreen;
    //programmers.png init
    Image programmers_image = LoadImage("programmers.png");
    Texture2D programmers_texture = LoadTextureFromImage(programmers_image);
    //free memory from Image)
    UnloadImage(programmers_image);
    // init button
    Rectangle startbutton = { (screenWidth/2), (screenHeight/2), 500, 100};
    // button bounds
    Rectangle startbtnbounds = { 0, 0, (float)startbutton.width, (float)startbutton.height};
    // init mouse
    Vector2 mousePoint = { 0.0f, 0.0f };
    
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
                
                DrawRectangle((screenWidth/2), ((screenHeight/2)/2), startbutton.width, startbutton.height, BLACK);
                DrawText("START",(screenWidth/2), ((screenHeight/2)/2), 100, WHITE);
            
                // I used ChatGPT.com to figure out how to center the image 
                DrawTexture(programmers_texture, ((screenWidth - programmers_texture.width)/2), ((screenHeight - programmers_texture.height)/2), WHITE);

                // referenced button properties from user https://www.raylib.com/examples/textures/loader.html?name=textures_sprite_button
                break;
            }
            
            case PlayScreen:
            {
                DrawText("Play Screen", 0, 0, 20, BLACK);
                break;
            }
        }

        EndDrawing();
    }

    CloseWindow();
    
    
    return 0;
}
