# arduino-snake-8x8-matrix-

A classic Snake game on an 8×8 LED matrix, controlled via a joystick and potentiometer.

## Repository Structure

- **src/**: Arduino sketch (SnakeGame.ino)
- **wiring/**: wiring diagram (wiring-diagram.png)
- **docs/**: documentation (joystick-calibration.md)

## Usage

1. Open src/SnakeGame.ino in the Arduino IDE.  
2. Install the [LedControl library](https://github.com/wayoda/LedControl).  
3. Wire up the LED matrix, joystick, potentiometer, and button per the diagram in wiring/wiring-diagram.png.  
4. Upload to your Arduino and enjoy!

## Customization

- Adjust initialSnakeLength, intensity, or logarithmity in the sketch.  
- Tweak speed and modes via the potentiometer and joystick click.

