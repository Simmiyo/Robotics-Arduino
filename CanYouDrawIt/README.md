Game Name: Can You Draw It?

About:
Welcome to the game I created! As the name points out, its main purpose is to challenge you to replicate a variety of drawings, either offering you a helping hand or trying to trick you.
The physical device is composed of the following pieces:
- an LCD display which represents a channel of comunication between the player and the game itself, exposing details such as: the current level you are playing, the number of points gained until a particular moment.
Trough this display you may also consult the list of high scores, access the settings section and modify the player's name.
- 1088BS 8x8 matrix that we will call "the challenge screen" due to its role of displaying the drawing you are supposed to reproduce.
- 1088BS 8x8 matrix named suggestively "the drawing zone" since the player will use it as an empty space they are free to fill.
- two MAX7219 drivers controlling each of the matrixes.
- a joystick to handle the player's input.
- Arduino ("the brain").

Game Idea:
Level 1 and Level 2 are designed in order to train and prepare you for the adventures to come, being as basic as they can be.
Level 3 contains an easier version of the obstacles that will greet you in Level 4, while Level 5 is a much harder version of the first level.
After completing Level 6, the real challenge beggins!

How to play:
Use the joystick to move the blinking point around the drawing zone (up, down, left, right) and focus on replicating the model on the challenge screen. Depending on the phase of the game you're at, you might also need to use the push button of the joystick to fix a point on your draw.

-Level 1: All you have to do is to travel with the blinking dot along the drawing zone and mark the points, by pressing the switch, that correspond to the lighten up ones in the challenge screen.
There's no time pressure. After you completed the entire model, you shall pass to the next level.

-Level 2: No need for the push button this time. Your duty is to move the blinking dot exactly over the path exposed on the challenge screen, without overstepping the model.
No worries, the asked-for draw will be continuous.

-Level 3: In this one, the game will dictate you in which order to light up the leds on the drawing zone. 
So all you have to do is hurry to the indicated spot. However, be careful, there's a time limit.

-Level 4: This one reminds you of the previous level, isn't it? Those chaotic points that pop up on your drawing zone, tempting you to go straight to them and connect them to complete the picture.
Well, attention required! The game is trying to trick you now. One of the two powered up spots is not part of the model you are supposed to obtain, so you must constantly check out the original picture on the challenge screen.

-Level 5: First level again?! Unfortunatelly, not. There is a time limit now, hence you need to play fast. 
Moreover, after getting to a certain place by moving the joystick and pressing the button, your blinking dot will appear randomly somewhere in the drawing zone, in order tol confuse you.

-Level 6: It is snowing! Your blinking dot is falling from the skies (technically, covering all the rows in a column one by one). You can only use the joystick to change the column it's navigating on.
Also, pushing the switch at a time will cause either losing the round or adding a new fixed point in your drawing zone, depending on the position the dot is found the moment the button is pressed.
Hence, your main concern could be to avoid missing any part of the picture displayed in the challenge screen.

-Levels > 6: Starting with Level 6, your training ends. You are now prepared to fight for the highest score.
	(i) odd number level: Remember Level 4? Then you pretty much know what is to be done! Except, the game will struggle to trick and confuse you even more and more as the levels go by.
That means it may add more fake points together with the real one and will raise the time pressure.
	(ii) even number level: Yes, it is Level 6! But notice that the difficulty increases with the progress of the game.
The rows will automatically be change more and more often and you will feel like there's no time to fix the points.

You are allowed to repeat each level a number of times equal to the number of the level. 
If you keep losing and replaying a certain level, overpassing this number, the game will end and your score will be compared to the last highest score and eventually registered as the new one.   