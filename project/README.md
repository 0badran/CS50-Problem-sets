# 🏓 Pong Game
## My CS50 final project
### Video Demo:  https://youtu.be/4mnmx-lm-rY
### 💡 Description:
<p>It's a two-player game where two players compete to score the most goals against each other. To make the pace of the game a little more challenging, I sped up the ball when it hit the wall, up and down, by 5% of the current ball speed. I used a simple algorithm that reverses the ball's position to make the ball move in a vertical (y-axis) curve (negative and positive) when it hits the wall and a horizontal (x-axis) curve when it hits the paddles. 🧲 Quick cheat while playing. The closer the ball is to a 90-degree angle when it hits the wall, the less range it will have :)</p>

### 📚 About project & files structure
<p>This game has been made with Lua and LÖVE engine.</p>

<p>In this project we have those archives:</p>

* main.lua: Contains instructions for merging project file parts to create the visual part of the game;

* ball.lua: Creates a Ball object with properties and methods to control its movement, collision, and drawing;

* paddle.lua: Creates a new Paddle object with given x, y coordinates and side ('l' for left, 'r' for right);

* score.lua: Creates a new Score object;

* button.lua: Creates a new Button object with given x, y coordinates and text for button;

* conf.lua: Configures the game window properties;

* font: Inside this folder there is the font used;

* image: Used image for background game image & file;

* video: This folder has the video of the game menu;

* sound: Inside this folder we can found the background sound used in the game;

### 🎮 About the game
* <b>Paddles</b>
<p>The paddles are moved using the keyboard keys. The paddle on the left is shown in red and moves using "w key" (up) and "s key" (down), and the paddle on the right is shown in blue and moves using "up key" (up) and "down key" (down). The paddle moves at 300 pixels per second times the frame rate. Its position on the y-axis is always checked so that it does not exceed the window boundaries.</p>

* <b>Ball</b>
<p>The ball initially moves from the center of the window at 150 pixels per second times the frame rate, the speed is increased by 5% of the current ball speed 150 + (150 * 0.05 = 7.5) 157.5 + (5% of current speed) and so on, this calculation occurs as the ball hits the upper and lower walls, so after twenty collisions the ball speed is about 100 pixels faster than the paddles. Don't worry, it resets to its original position after a goal is scored.</p>
<p><b>🐞 Interesting bug</b></p>
When the ball hits the racket from below, the ball sticks to the racket (a continuous collision situation) and stops. I used AI to improve the algorithm (when the ball hits the racket, we move the ball slightly outside the racket to avoid the continuous collision that might cause the ball to stop).

### 🔉 Sound
The sounds has been made by: [Survivor](https://open.spotify.com/artist/26bcq2nyj5GB7uRr558iQg)<br />
You can download them in: [download](https://drive.usercontent.google.com/u/0/uc?id=0B4LOzioZvYiXYUk3OUJudDNRMW8&export=download)
### Hint
If you want to change the background sound, you can do so by placing the sound file in the sound folder and renaming it to `background-sound` If you don't want to, you can simply remove the folder<br/>
Note: that the file extension must be mb3

### ⚡ How to run
## Linux
#### PPA (Ubuntu)
1. Download and install: [Love 2d](https://love2d.org/)
```[bash]
sudo add-apt-repository ppa:bartbes/love-stable
sudo apt-get update
sudo apt-get install love
```
2. Run game
```[bash]
git clone https://github.com/0badran/cs50-final-project.git
love cs50-final-project
```
#### AppImage
1. Download AppImage: [Love 2d](https://love2d.org/)
2. Add execution permission to the file
```[bash]
chmod +x love.AppImage
```
3. Run game
```[bash]
git clone https://github.com/0badran/cs50-final-project.git
./love.AppImage cs50-final-project
```
NOTE: replace love.AppImage by the name of your file

## Windows
1. Download the exe file [Love 2d](https://love2d.org/) and install it
2. Get game
```[bash]
git clone https://github.com/0badran/cs50-final-project.git
```
3. Create a shortcut on your desktop (or other place)
4. Drag and drop the game folder (cs50-final-project) on Love 2d shortcut

## Mac
1. Download AppImage: [Love 2d](https://love2d.org/)
2. Check if love has permissions to execute
3. Get game
```[bash]
git clone https://github.com/0badran/cs50-final-project.git
```
4. Drag and drop the game folder (cs50-final-project) on Love 2d shortcut

### Screenshot from inside game
![game screenshot](/image/game-screenshot.gif)

### 🕹 Controls
W key: Move the left paddle up
S key: Move the left paddle down
Up key: Move the right paddle up
Down key: Move the right paddle down
<p>And..</p>

![this is cs50](/image/this_is_cs50.gif)
