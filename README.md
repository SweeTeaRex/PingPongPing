# PING PONG PING
## VIDEO DEMO. https://youtu.be/Jvm9DGZ9_R8?si=C6-b13nA_WjMFNt_
### Description: Ping Pong Ping is a recreation of the game Pong, created with C, and assisted with the library RayLib.

Ping Pong Ping is a recreation of the game Pong, that was popular in the late 60's. I utilized the library called "RayLib" that acts
as a game engine to render the game world. I originally wanted to make a BlackJack game with JavaScript, but after some thinking, i realized 
using C with RayLib would be more to my level.

The main file for Ping Pong Ping is written in 3 levels.

The first level is the first initlization of the varibales needed thruought the code. THe second level is the "back ground" code that dictates how the variables are affected.
The third layer is the actual rendering of the visual windows and textures that go into the game world. Ping Pong Ping is only a 2D game, with multiple variables that changes as the program is running.

To create the textures used in the game, i first had to load the image into the code. Then i had to convert the image, to a texture, utilizing a function that does this.
I then draw the texture in the game world for the texture to show.

For the sound files, i created my own custom wav files utilzing the program Audacity. I recorded my voice, and looped the sound files in order to create a sound track. 

The ball textures and splash screen TREX images were created with the application GIMP.

The splash screen and start screen sound tracks are open source freeware sound files that i downloaded from the internet. 

To create the game, i first initlize all the images to textures, and varibles that will go into things like paddle movement and ball position, 
Then i have to write the background code. Basically, if the ball touches the side walls, it add +1 to Team Score. If the user presses the R key, the game returns the ball back to
the initlization position. This is achieved by creating a ifGameisOver = true or false variable. If the varible turn true at any point, the code is written to redraw the ball position.
If the user presses the spacebar, the FPS stops. The balls movment is dictated by the Frames Per Second. As each frame is rendered, the ball moves the alloted pixels it is programed to. The 
same applies to the paddles. The automated paddles are codded to match the balls y axis. The balls radius +/- dictates how far from the border the ball's collision reconginzed. On the splash screen, the text's
rendering alpha is adjusted from 0 to 1.0 to create the fade in effect. The text's position is adjusted on the y axis to create the "drop in' effect. 