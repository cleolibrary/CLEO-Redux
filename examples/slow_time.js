// Script by Vital

var VK_R = 82;
var game_speed = 1.0;
var player = new Player(0);

while (true) {
  wait(0);

  if (player.isPlaying() && Pad.IsKeyPressed(VK_R)) {
    // Wait for button release (ON)
    while (Pad.IsKeyPressed(VK_R)) {
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
    while (!Pad.IsKeyPressed(VK_R)) {
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
    while (Pad.IsKeyPressed(VK_R)) {
      wait(0);
    }
  }
}

function playSound(soundId) {
  Sound.AddOneOffSound(0, 0, 0, soundId)
}

function setGameSpeed(speed) {
  game_speed = speed;
  Clock.SetTimeScale(speed)
}
