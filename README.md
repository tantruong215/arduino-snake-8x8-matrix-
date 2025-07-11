# Arduino Snake on 8×8 LED Matrix

A classic Snake game running on an 8×8 LED matrix, controlled via a joystick, potentiometer, and button.

## Repository Structure

```
arduino-snake-8x8-matrix/
├── .gitignore
├── README.md          # Project overview and setup
├── src/
│   └── SnakeGame.ino  # Arduino sketch
├── wiring/
│   ├── wiring-diagram.md  # ASCII wiring diagram
│   └── wiring-diagram.png # Graphical wiring diagram
└── docs/
    └── joystick-calibration.md  # Joystick calibration guide
```

## Usage

1. Open `src/SnakeGame.ino` in the Arduino IDE.
2. Install the [LedControl library](https://github.com/wayoda/LedControl).
3. Wire components according to `wiring/wiring-diagram.png` (or `.md`).
4. Upload to your Arduino Nano and enjoy the Snake game!

## Controls & Features

* **Joystick** (A2/A3): Move snake up/down/left/right.
* **Button** (D2): Click to select game mode, pause, or reset when held.
* **Potentiometer** (A5): Adjust snake speed and select mode level.
* **EEPROM**: Stores high score across resets.
* **Game Modes**:

  * Wrap-around (classic)
  * Wall hit (die on edge)
  * Speed challenge (increasing speed)
  * Reverse controls (inverts periodically)

## Customization

* Modify `Pin` struct values to change pin assignments.
* Tweak `initialSnakeLength`, `intensity`, or `logarithmity` in the sketch.
* Update mode labels in `modeNames` array.

---

**Author:** Tan Truong

*Changelog:* `chore: add project structure and README` (commit **8b08a73**)
