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



typedef enum GameScreen
{
    SplashScreen = 0,
    StartScreen,
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

    // init mouse
    Vector2 mousePoint = {0.0f, 0.0f};
    // mouse position
    

    // init audio device
    InitAudioDevice();
    GameScreen currentScreen = SplashScreen;

    // -------SplashScreen--------
    Image TREX_image = LoadImage("images/TREX.png");
    Texture2D TREX_texture = LoadTextureFromImage(TREX_image);
    UnloadImage(TREX_image);
    // init top and bottom text position
    int topText_yaxis = -50;
    int bottomText_yaxis = screenHeight+10;

    // ------StartScreen--------
    Color startscreen_color = {251, 72, 72, 255};

    
    // title image0
    Image pingPong_image = LoadImage("images/pingpongping.png");
    Texture2D pingpong_text = LoadTextureFromImage(pingPong_image);
    // free memory from Image)
    UnloadImage(pingPong_image);
    

    int fontSize = 100;
    int textWidth = MeasureText("Click to Start ", fontSize);

    // init button
    Rectangle startbutton = {((screenWidth / 2) - (textWidth / 2)-10), ((screenHeight / 2) + 350), textWidth+10, fontSize};

    // button bounds
    Rectangle startbtnbounds = {startbutton.x, startbutton.y, startbutton.width, startbutton.height};

    

    // ----PlayScreen------
    // init sound files
    Music startSound = LoadMusicStream("sounds/tokyo-cafe.wav");
    PlayMusicStream(startSound);
    Music playSound = LoadMusicStream("sounds/bop1.wav");
    PlayMusicStream(startSound);
    Sound ballbouncefx = LoadSound("sounds/whatever.wav");

    // adjust sound volume level
    SetSoundVolume(ballbouncefx, 0.4);
    // check for if sound is already playing
    

    // exit button
    Rectangle exit_button = {0, 0, 100, 100};
    Rectangle exit_button_bounds = {(screenWidth / 2), 30, exit_button.width, exit_button.height};

    // init bouncing ball
    Vector2 ballPosition = {screenWidth / 2.0f, screenHeight / 2.0f};
    Vector2 ballSpeed = {7.0f, 7.0f};
    int ballRadius = 50;

    // exit.png init
    Image exit_image = LoadImage("images/exitdoor.png");
    ImageResize(&exit_image, 50, 50);
    Texture2D exit_texture = LoadTextureFromImage(exit_image);
    UnloadImage(exit_image);

    // trollface.png init
    Image trollface = LoadImage("images/pingpongball.png");
    
    Image circleTrans = GenImageColor(trollface.width, trollface.height, BLANK);
    Vector2 imageCenter = {trollface.width / 2.0f, trollface.height / 2.0f};
    ImageDrawCircleV(&circleTrans, imageCenter, ballRadius, WHITE);
    ImageAlphaMask(&trollface, circleTrans);
    
    Texture2D troll_texture = LoadTextureFromImage(trollface);
    UnloadImage(circleTrans);
    // pause menu init
    bool pause = 0;
    // init state
    int state = 0;

    // frame counter
    int framesCounter = 0;
    // init alpha levels
    float imageTREX_alpha = 0.0f;
    float spaceText_alpha = 0.0f;
    float top_botText_alpha = 1.0f;

    // init paddles
    Rectangle paddleLeft = {(screenWidth - (screenWidth / 16) * 15), (screenHeight / 2), 25, 100};
    Rectangle paddleRight = {(screenWidth - (screenWidth / 16) * 1), (screenHeight / 2), 25, 100};

    

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // mouse point
        mousePoint = GetMousePosition();

        // update music stream
        
        
        // splashscreen

        if (currentScreen == SplashScreen && IsKeyDown(KEY_SPACE))
        {
            // Transition to PlayScreen
            currentScreen = StartScreen;
            // Reset flags for the new screen
            
        }
        // startscreem
        if (currentScreen == StartScreen && CheckCollisionPointRec(mousePoint, startbtnbounds) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            // Transition to PlayScreen
            currentScreen = PlayScreen;
            // Reset flags for the new screen
            
        }

        // playscreen
        if (currentScreen == PlayScreen && CheckCollisionPointRec(mousePoint, exit_button_bounds) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            // Transition to PlayScreen
            currentScreen = StartScreen;
            // Reset flags for the new screen
            
        }

        switch (currentScreen)
        {
        // case SplashScreen
        case SplashScreen:
        {
            if (!IsMusicStreamPlaying(startSound))
            {
                PlayMusicStream(startSound);
                
            }
            UpdateMusicStream(startSound);

            if (state == 0)
            {
                topText_yaxis += 0.6f;
                if(topText_yaxis == 3)
                {
                    topText_yaxis = 3;
                }
                bottomText_yaxis -= 0.6f;
                if(bottomText_yaxis <= (screenHeight-53))
                {
                    bottomText_yaxis = (screenHeight-53);
                    state = 1;
                }               
            }
            else if (state == 1)
            {
                
                imageTREX_alpha += 0.007f;                
                if(imageTREX_alpha >= 1.0f)
                {
                    imageTREX_alpha = 1.0f;
                    state = 2;
                }
                
            }
            else if (state == 2)
            {
                spaceText_alpha += 0.007f;
                if (spaceText_alpha >= 1.0f)
                {
                    spaceText_alpha = 1.0f;
                        
                }
            }
                       
            break;
        }
        // case StartScreen
        case StartScreen:
        {
            UpdateMusicStream(startSound);
            break;
        }
        // case PlayScreen
        case PlayScreen:
        {
            if (IsKeyPressed(KEY_SPACE))
                pause = !pause;

            if (!pause)
            {
                if (!IsMusicStreamPlaying(playSound))
                {
                    
                    PlayMusicStream(playSound);                   
                    
                }                
                UpdateMusicStream(playSound);
                // ball moving
                ballPosition.x += ballSpeed.x;
                ballPosition.y += ballSpeed.y;
                // Check walls collision for bouncing
                if ((ballPosition.x >= (GetScreenWidth() - ballRadius)) || (ballPosition.x <= ballRadius))
                    ballSpeed.x *= -1.0f;
                if ((ballPosition.y >= (GetScreenHeight() - ballRadius)) || (ballPosition.y <= ballRadius))
                    ballSpeed.y *= -1.0f;
                // check paddles for collision
                // ChatGPT used to adjust ball so sticking to paddle is avoided
                // Left paddle
                if (CheckCollisionCircleRec(ballPosition, ballRadius, paddleLeft))
                {
                    ballSpeed.x *= -1.0f;
                    ballSpeed.y *= 1.0f;
                    ballPosition.x = paddleLeft.x + paddleLeft.width + ballRadius;
                    PlaySound(ballbouncefx);
                }
                // Right paddle
                if (CheckCollisionCircleRec(ballPosition, ballRadius, paddleRight))
                {
                    ballSpeed.x *= -1.0f;
                    ballSpeed.y *= 1.0f;
                    ballPosition.x = paddleRight.x - ballRadius;
                    PlaySound(ballbouncefx);
                }
                // Left paddle controls init
                // Up key function
                if (IsKeyDown(KEY_W))
                {
                    if (paddleLeft.y >= 0)
                    {
                        paddleLeft.y -= 15.0f;
                    }
                }
                // Down key function
                if (IsKeyDown(KEY_S))
                {
                    if (paddleLeft.y + paddleLeft.height < screenHeight)
                    {
                        paddleLeft.y += 15.0f;
                    }
                }
                // right paddle moving
                if (ballPosition.y < (paddleRight.y + paddleRight.height / 2))
                {
                    paddleRight.y -= 5.5f;
                }
                else if (ballPosition.y > (paddleRight.y + paddleRight.height / 2))
                {
                    paddleRight.y += 5.5f;
                }
                // right paddle boundary
                if (paddleRight.y < 0)
                    paddleRight.y = 0;
                if ((paddleRight.y + paddleRight.height) > GetScreenHeight())
                {
                    paddleRight.y = GetScreenHeight() - paddleRight.height;
                    DrawTexture(troll_texture, ballPosition.x - (trollface.width / 2) - ballRadius, ballPosition.y - (trollface.height / 2), WHITE);
                }
            }

            if (CheckCollisionPointRec(mousePoint, exit_button_bounds) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {    
                currentScreen = StartScreen;
                               
            }
            
            else
                framesCounter++;
            break;
        }
        }
        BeginDrawing();

        ClearBackground(WHITE);

        switch (currentScreen)
        {
        case SplashScreen:
        {
            // Top Text render
            DrawText("TREX Programs presents.....", 5, topText_yaxis, 50, ColorAlpha(BLACK, top_botText_alpha));
            // TREX image render
            DrawTexture(TREX_texture, (screenWidth/2)-(TREX_texture.width/2), (screenHeight/2) - (TREX_texture.height/2), ColorAlpha(WHITE, imageTREX_alpha));
            // press space text render
            DrawText("Press SPACE to continue", 5, (screenHeight/2), 30, ColorAlpha(BLACK, spaceText_alpha));
            // bottom text render
            int productionLength = MeasureText(".....A TREX Programs production", 50);                
            DrawText(".....A TREX Programs production", screenWidth-(productionLength+5), bottomText_yaxis, 50, ColorAlpha(BLACK, top_botText_alpha));
            
            break;
        }
        case StartScreen:
        {
            // render background color
            ClearBackground(startscreen_color);
            // render Ping Pong Ping logo
            DrawTexture(pingpong_text, ((screenWidth/2)-(pingpong_text.width/2)), ((screenHeight/2)-(pingpong_text.height/2)), WHITE);
            // render start button            
            bool startbutton_collision = CheckCollisionPointRec(mousePoint, startbtnbounds);
            
            
            if(startbutton_collision)
            {
                DrawRectangle(startbtnbounds.x, startbtnbounds.y, startbtnbounds.width, startbtnbounds.height, BLACK);
            }
            else
            {
                DrawRectangle(startbtnbounds.x, startbtnbounds.y, startbtnbounds.width, startbtnbounds.height, startscreen_color);
            }
            // measure text width
            
            
            if(startbutton_collision)
            {
                DrawText("Click To Start", startbtnbounds.x+10, startbtnbounds.y, startbtnbounds.height, startscreen_color);
            }
            else
            {
                DrawText("Click To Start", startbtnbounds.x+10, startbtnbounds.y, startbtnbounds.height, BLACK);
            }
            // I used ChatGPT.com to figure out how to center the image
            
            // referenced button properties from user https://www.raylib.com/examples/textures/loader.html?name=textures_sprite_button
            break;
        }
        case PlayScreen:
        {
            // Draw Exit Sign
            DrawText("Click to Exit", (screenWidth / 2), 0, 20, BLACK);
            DrawTexture(exit_texture, (screenWidth / 2), 30, WHITE);
            // Draw ball
            DrawTexture(troll_texture, ballPosition.x - (troll_texture.width / 2), ballPosition.y - (troll_texture.height / 2), WHITE);
            Texture2D troll_texture = LoadTexture("images/Trollface.png");
            if (troll_texture.id == 0)
            {
                printf("Failed to load texture.\n");
            }
            // Draw Paddles
            DrawRectangle(paddleLeft.x, paddleLeft.y, paddleLeft.width, paddleLeft.height, BLACK);
            DrawRectangle(paddleRight.x, paddleRight.y, paddleRight.width, paddleRight.height, BLACK);
            // press space text
            int spaceLength = MeasureText("Press SPACE to pause", 20);
            DrawText("Press SPACE to pause", (screenWidth/2)-(spaceLength/2), screenHeight-30, 20, BLACK);
            
            break;
        }
    }
    EndDrawing();
    }
    UnloadSound(ballbouncefx);
    StopMusicStream(startSound);
    StopMusicStream(playSound);
    UnloadMusicStream(startSound);
    UnloadMusicStream(playSound);
    UnloadImage(trollface);
    UnloadTexture(troll_texture);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}

