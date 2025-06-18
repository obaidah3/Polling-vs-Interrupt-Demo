# Arduino Polling vs Interrupt Demo 🚦

This project demonstrates the difference between **Polling** and **Interrupts** in embedded systems using an Arduino Uno (or compatible board), push buttons, an LED, and an LCD display.

---

## 🎥 **Demo Video**

Watch the experiment in action here:  
[![Demo Video](https://img.youtube.com/vi/0/0.jpg)](https://github.com/user-attachments/assets/ca6f329c-1239-41fb-87ec-cb944817b139)

👉 Or download it directly: [Download demo.mp4](https://github.com/user-attachments/assets/ca6f329c-1239-41fb-87ec-cb944817b139)


---

## 📌 **Project Description**

- **Polling Button**
  - Checks the button state periodically.
  - Turns on the LED for 0.5 seconds.
  - Runs a long dummy task to simulate a busy CPU.
  - Shows how the polling button may be slow to respond while the CPU is busy.
  - Measures and displays the total response time.

- **Interrupt Button**
  - Uses an external interrupt pin.
  - Responds immediately to a button press, even during long tasks.
  - Shows the power of interrupts in real-time systems.
  - Measures and displays the interrupt response time.

---

## ⚙️ **Hardware Required**

- ✅ Arduino Uno (or compatible)
- ✅ LCD 16x2 (with 6 digital pins)
- ✅ 2 Push buttons (active low with internal pull-up)
- ✅ 1 LED (built-in LED on pin 13 or external)
- ✅ Wires & breadboard

---

## 🔌 **Wiring**

![Image](https://github.com/user-attachments/assets/8ee3465c-ab31-4f32-a752-4086dcbc78c5)


| Component      | Arduino Pin |
|----------------|--------------|
| Polling Button | Pin 8        |
| Interrupt Button | Pin 3 (interrupt pin) |
| LCD RS         | Pin 12       |
| LCD EN         | Pin 11       |
| LCD D4         | Pin 7        |
| LCD D5         | Pin 6        |
| LCD D6         | Pin 5        |
| LCD D7         | Pin 4        |
| LED            | Pin 13       |

Buttons should be connected **active low** (connected to GND, using `INPUT_PULLUP`).

---

## 🧩 **How It Works**

1. **Polling Button**
   - When pressed, it turns on the LED and runs a long loop.
   - During this loop, pressing it again won't have an immediate effect.
   - Response time is measured and displayed.

2. **Interrupt Button**
   - When pressed, it triggers an interrupt service routine (ISR).
   - It immediately interrupts any running task to blink the LED.
   - Response time is measured and displayed.

---

## 📟 **Serial Output**

- Shows when buttons are pressed.
- Displays the measured response time for polling and interrupt methods.

---

## 📊 **LCD Display**

- Shows current status: `Polling` or `Interrupt`
- Displays the LED state.
- Shows the last measured response times for both methods.

---

## ▶️ **How to Use**

1. Connect the circuit as described.
2. Upload `main.ino` to your Arduino board.
3. Open Serial Monitor at 9600 baud.
4. Press the **Polling button** and observe delay.
5. During polling task, press the **Interrupt button** and notice the immediate reaction.
6. Compare the response times on LCD and Serial Monitor.

---

## ✨ **Key Learning**

> ⚡ **Polling** can be slow and block the system during heavy tasks.  
> ⚡ **Interrupts** react instantly and ensure quick response even if the system is busy.

---

## 📄 **License**

This project is open-source and free to use for learning purposes.

---

## ✅ **Author**

- 👤 *AbdulRahman Essam*
---

**Have fun experimenting! 🚀**
