# RC Toy Boat Conversion (ESP8266 + L298N + Servo Rudder)

This project converts a cheap toy RC boat into a WiFi-controlled boat using:
- **ESP8266** (boat firmware)
- **L298N** dual H-bridge (2x DC motors)
- **Servo** for rudder steering
- A handheld controller built from an **Arduino UNO R4 WiFi + Modulino joystick**

The README is a build log with photos, wiring, and lessons learned (including how we stopped snapping the rudder off).

---

## Demo Video

🎥 **Video:** *(add link here)*
- Recommended: upload to YouTube (unlisted) and paste the link.
- Alternate: store via Git LFS or as a GitHub Release asset.

Example thumbnail link:

[RC Boat Demo](https://youtube.com/shorts/XjPl-BF36Mk)

---

## Build Log (Photos + Steps)

> Photos live in `docs/` and are referenced below.

### 1) Cut out top + add splash cover
Cut out the middle of the toy boat top and **super-glue** a plastic cover in place for splash protection.

![Step 1 - toyboat top](docs/01-Toy-Boat-Top.HEIC)

### 2) Attach rudder (epoxy centered on stern)
Rudder mount is centered on the stern using plastic epoxy.

![Step 2 - rudder attached](docs/02-rudder-attached.HEIC)

### 3) Epoxy four posts for the L298N mount
Set **4 posts in epoxy** to hold the L298N motor driver above the hull.

![Step 3 - posts for L298N](docs/03-posts-l298n.HEIC)

### 4) Epoxy motors + servo
Epoxy:
- **2x DC motors** (propulsion)
- **1x servo** (rudder control)

![Step 4 - motors and servo](docs/04-motors-and-servo.HEIC)

### 5) L298N motor outputs wiring
Motor wiring on the L298N output terminals:

- **Motor 1**: `+ -> OUT2`, `- -> OUT1`
- **Motor 2**: `+ -> OUT4`, `- -> OUT3`

![Step 5 - L298N motor wiring](docs/05-l298n-outs.HEIC)

### 6) Build a boat holder (rudder broke twice)
We snapped the rudder off twice, so we built a holder/stand to keep the boat stable during work + testing.

![Step 6 - boat holder](docs/06-boat-holder.HEIC)

### 7) Connect L298N EN/IN + servo signal to ESP8266 (pin map)
Pin mapping (ESP8266 GPIO):

```cpp
motor1Pin1  = GPIO12;
motor1Pin2  = GPIO14;
enable1Pin  = GPIO13;

motor2Pin1  = GPIO4;
motor2Pin2  = GPIO5;
enable2Pin  = GPIO15;

servoPin    = GPIO0;
```

### Power + grounds

- **Servo VIN** → ESP8266 **3V3** and **GND**
- **6V (4x AAA)** battery pack → **VIN** on ESP8266
- **All grounds** tied together to a **common central point**

![Step 7 - connect ESP pins](docs/07-esp-pins.HEIC)

---

### 8) Two power switches

- **Switch #1:** controls power to the **L298N**
- **Switch #2:** controls power to the **ESP8266** (also powers the **servo**)

![Step 8 - power switches](docs/08-power-switches.HEIC)

---

### 9) Paper-clip linkage from servo horn to rudder

Stretch out a paper clip to connect the servo horn to the rudder.  
Loop it around the connectors so it won’t pop off easily.

![Step 9 - connect servo to rudder](docs/09-servo-rudder.HEIC)

---

### 10) Install propeller screws onto motor shafts

Insert the propeller screws onto the motor/propeller shafts.

![Step 10 - install propeller screws](docs/10-propeller-screws.HEIC)

---

### 11) Check trim in a sink

Check the boat trim in a bathroom sink:

- Ensure it sits level
- Not too heavy at stern or bow
- Rudder centered

![Step 11 - trim test](docs/11-trim-test.HEIC)

---

### 12) Extra water protection (plastic wrap + electrical tape)

Cover the hull with plastic wrap and use electrical tape to hold it down as an extra splash barrier.

![Step 12 - extra protection](docs/12-extra-protection.HEIC)
---

### 13) Reattach the toy boat top

Reconnect the boat top to complete the assembly.

![Step 13 - reattach top](docs/13-reattach-top.HEIC)

---

### 14) Build the controller (UNO R4 WiFi + Modulino joystick)

Controller build:

- Arduino UNO R4 WiFi
- Modulino joystick
- On/off switch
- 9V battery on the back, secured with electrical tape

![Step 14 - build controller](docs/14-build-controller.HEIC)
---

## Wiring Summary

### L298N ↔ Motors

| Motor | L298N Terminal | Polarity |
|------:|----------------|----------|
| 1     | OUT2 / OUT1    | + / -    |
| 2     | OUT4 / OUT3    | + / -    |

### ESP8266 ↔ L298N + Servo

| Function     | ESP8266 GPIO |
|--------------|--------------|
| Motor1 IN1   | GPIO12       |
| Motor1 IN2   | GPIO14       |
| Motor1 EN    | GPIO13       |
| Motor2 IN1   | GPIO4        |
| Motor2 IN2   | GPIO5        |
| Motor2 EN    | GPIO15       |
| Servo signal | GPIO0        |

---

## Parts List (BOM)

### Boat
- Toy RC boat hull + top
- Plastic wrap (splash shield)
- Plastic epoxy / epoxy putty
- Super glue
- Electrical tape
- Paper clip (rudder linkage)

### Electronics (boat)
- ESP8266 dev board (NodeMCU-style)
- L298N motor driver
- 2x small DC motors + props + screws
- 1x servo motor
- 2x on/off switches
- 4x AAA battery pack (6V) for ESP8266 VIN and servo (and shared grounds)
- 9V for motor driver

### Controller
- Arduino UNO R4 WiFi
- Modulino joystick
- On/off switch
- 9V battery

---

## Notes / Lessons Learned
- The rudder is fragile—use a holder/stand while working and testing.
- First attempt: servo worked but DC motors did not. I was using 4x AAA for DC motors. When I upgraded to 9V, the motors worked without issue. 
- Second attempt: boat spun uncontrollably. propellers must spin in opposite direction to move in a straight line. Fixed via software upgrade.
- Third attempt: power was on for all electronics but no signals were being tx/rx from controller to boat. Upgraded controller to 9V and it worked fine after that. 
- Still an issue: left screw often times doesn't spin. Actively troubleshooting. 
- There is a constant humming which i take to be due to not turning pins to LOW when not using. Actively troubleshooting.
- The design decision to use 1x joystick was not smart. You can't do fast turns because when you move joystick all the way to side, it completely slows down (y moves towards center). I'm considering using the button in the joystick and writing code that uses that as a speed autopilot so I can maintain a faster speed while moving rudder. 

---

## License
MIT

