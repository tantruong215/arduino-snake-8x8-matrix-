# Wiring Diagram for Arduino-Snake-8x8-Matrix

Connect the components as follows:
                              ┌───────────────┐
                              │   Arduino     │
                              │    Nano       │
                              └───────────────┘
                                  │    │    │
                          +5V ─────┘    │    │
                          GND ──────────┘    │
                              A2 ─── Joystick X (A2)
                              A3 ─── Joystick Y (A3)
                              A5 ─── Potentiometer wiper (A5)
                              D2 ─── Push-button input (digital 2, INPUT_PULLUP)
                              D10 ── LED Matrix CLK (digital 10)
                              D11 ── LED Matrix CS  (digital 11)
                              D12 ── LED Matrix DIN (digital 12)  
          ┌────────────────────────────────────────────────────┐
           │                     Joystick                     │
           │  +5V ─ VCC    GND ─ GND    A2 ─ X-axis (A2)       │
           │                           A3 ─ Y-axis (A3)       │
           └────────────────────────────────────────────────────┘
             ┌────────────────────────────────────────────────────┐
           │                8×8 LED Matrix + MAX7219           │
           │  VCC ─ +5V    GND ─ GND                          │
           │  DIN ─ D12    CLK ─ D10     CS ─ D11              │
           └────────────────────────────────────────────────────┘
            ┌────────────────────────────────────────────────────┐
           │               Potentiometer (10 kΩ)               │
           │  +5V ─ VCC    GND ─ GND    A5 ─ Wiper (A5)        │
           └────────────────────────────────────────────────────┘
            ┌────────────────────────────────────────────────────┐
           │                   Push-Button                     │
           │  +5V ─ one leg   D2 ─ other leg (INPUT_PULLUP)    │
           └────────────────────────────────────────────────────┘
    
            

          
        

