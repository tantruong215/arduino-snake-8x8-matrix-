# Joystick Calibration

Proper calibration of your joystick ensures accurate movement in the Snake game. Follow these steps to set the home (center) position using the built‑in `calibrateJoystick()` function.

## 1. Wiring Check

1. **Connect joystick VCC** to Arduino 5V (pin labeled `joystickVCC`)
2. **Connect joystick GND** to Arduino GND (`joystickGND`)
3. **Connect X-axis output** to analog pin A2 (`joystickX`)
4. **Connect Y-axis output** to analog pin A3 (`joystickY`)

Ensure all connections are secure before powering your board.

## 2. Using `calibrateJoystick()`

In your sketch’s `setup()` function, call:

```cpp
initialize();        // set up pins and matrices
calibrateJoystick(); // measure and store home position
```

### What it does

* Reads the X and Y analog values **10 times** in quick succession.
* Averages these readings to determine the joystick’s center position (`joystickHome.x` and `joystickHome.y`).
* Stores the results in the global `joystickHome` variable for subsequent movement detection.

## 3. Calibration Procedure

1. **Power on** your Arduino with the joystick in its resting (center) position.
2. **Do not touch** the joystick until calibration completes.
3. The code will automatically:

   * Take 10 analog readings on both axes.
   * Compute the average for X and Y.
   * Save those as the neutral thresholds.

Once calibration finishes, you can move the joystick freely without affecting the stored center until the next reboot or call.

## 4. Troubleshooting

* **Unstable readings**: Ensure your joystick operates smoothly and isn’t physically skewed. Clean any debris around the gimbal.

* **Drift at rest**: Add a small deadzone in code by increasing `joystickThreshold` or manually adjust in code:

  ```cpp
  const int joystickThreshold = 200; // a larger threshold reduces drift sensitivity
  ```

* **Recalibration**: To recalibrate without resetting the Arduino, you can call `calibrateJoystick()` again—perhaps via a button press in your `loop()`.

