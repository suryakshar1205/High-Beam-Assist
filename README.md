# High-Beam-Assist
A smart high beam assist system using ESP32, LDRs, and RELAY to automatically switch between high and low beams based on ambient light, enhancing safety during night-time driving.

Detailed Project Explanation for README.md
The High Beam Assist System is a smart, automated headlight control system designed to improve night-time driving safety by dynamically adjusting headlight intensity. The system uses LDR sensors to monitor ambient light, such as oncoming vehicle headlights. When bright light is detected, the system automatically switches the headlights from high beam to low beam, preventing glare for other drivers.

At the core of the system is the ESP32 microcontroller, which processes real-time analog signals from the LDRs. The Exponential Moving Average (EMA) algorithm is applied to smooth fluctuations in the LDR values, ensuring stable and accurate light detection. Based on the average LDR readings, the ESP32 sends PWM (Pulse Width Modulation) signals to a MOSFET to adjust the brightness of the LED headlights.

Operation:
High Beam Mode: When no oncoming vehicles are detected (low LDR readings), the headlights remain in high beam mode for maximum visibility.
Low Beam Mode: When oncoming headlights are detected, the system switches to one of four low beam stages, reducing glare for other drivers.
PWM Control: The brightness adjustment is smooth and continuous, thanks to PWM control over the MOSFET, which modulates the current flowing to the headlights.
System Highlights:
Real-time Detection: The system continuously monitors ambient light and responds in real time.
Energy Efficiency: By switching to low beam when needed, the system optimizes energy use.
High-Speed Switching: The MOSFET provides fast and efficient switching between high and low beams.
This project enhances driving safety and comfort by minimizing manual headlight adjustment and ensuring that other drivers are not blinded by excessive glare from high beams
