// Script by Vital

var VK_R = 82;
var game_speed = 1.0;

while (true) {
  wait(0);

  if (op(0x0256, 0) && isKeyPressed(VK_R)) {
    // Wait for button release (ON)
    while (isKeyPressed(VK_R)) {
      wait(0);
    }

    setGameSpeed(1.0);
    playSound(13);

    // Decrease the game speed
    while (game_speed > 0.26) {
      wait(0);
      setGameSpeed(game_speed * 0.9);
    }

    // Maintain the new speed until the button is pressed
    while (!isKeyPressed(VK_R)) {
      wait(0);
      setGameSpeed(0.25);
    }

    playSound(14);

    // Increase the game speed
    while (game_speed < 1.0) {
      wait(0);
      setGameSpeed(game_speed * 1.09);
    }

    setGameSpeed(1.0);

    // Wait for button release (OFF)
    while (isKeyPressed(VK_R)) {
      wait(0);
    }
  }
}

function playSound(soundId) {
  op(0x018c, 0, 0, 0, soundId);
}

function setGameSpeed(speed) {
  game_speed = speed;
  op(0x015d, speed);
}
