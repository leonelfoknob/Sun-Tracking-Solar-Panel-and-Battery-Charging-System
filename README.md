This project is designed to maximize solar energy efficiency by implementing an automated sun-tracking system that follows the sun's position throughout the day. The system controls a solar panel's movement using a servo motor, ensuring optimal orientation for energy collection. Additionally, the system monitors and displays the battery level in real-time on a webpage accessible through a local network, providing insights into energy storage.

Components Used:
- LDR Sensors (2x):
Function: Light-dependent resistors (LDRs) are used to detect sunlight. Their resistance changes with the intensity of light, which allows the system to determine the optimal direction for the solar panel.
Position: Two LDRs are positioned on the edges of the solar panel to track the sun’s movement on the x-axis.
- Solar Panel:
Type: The panel captures solar energy, converting it into electrical energy to charge the battery.
Function: It generates DC electricity that powers the system and charges the 7.4V battery.
- STM32F103 Microcontroller:
Role: The STM32F103 serves as the brain of the system, controlling the servo motor based on input from the LDR sensors.
Motor Control: It adjusts the solar panel’s position by rotating the servo motor along the x-axis, ensuring the panel remains aligned with the sun.
- Servo Motor (1x):
Movement: Controls the solar panel’s angle on the x-axis, adjusting it based on the sensor inputs to follow the sun’s movement.
Precision: Accurate angular adjustments are made to improve sunlight capture.
- ESP32 Microcontroller:
Networking: The ESP32 connects to the local Wi-Fi or Ethernet to allow real-time monitoring of battery status.
Battery Level Monitoring: A voltage divider circuit is used to measure the 7.4V battery's charge level, sending data to the ESP32 for display on the local network webpage.
- Voltage Divider Circuit:
Purpose: Scales down the battery voltage to a safe level for the ESP32 to read and monitor the charge level in real-time.
- Lithium-Ion Battery (7.4V):
Type: Two 3.7V lithium-ion batteries connected in series to provide 7.4V.
2S BMS (Battery Management System): Protects the battery by managing charging and discharging cycles, preventing overcharging and ensuring system safety.

************* System Functionality: ****************
- Sun Tracking: The LDR sensors send signals to the STM32F103, which adjusts the solar panel’s position to follow the sun throughout the day. The servo motor ensures precise movement on the x-axis.
- Real-Time Battery Monitoring: The ESP32 constantly checks the battery level using the voltage divider and displays this information on a custom-built webpage, accessible through Wi-Fi. This allows users to track energy storage status conveniently on their devices.
- Expandable Design: The project is designed to be scalable, making it adaptable to larger real-life solar tracking and energy storage systems
************** Circuit Diagram *********************
The project includes a detailed circuit diagram outlining the connections between the solar panel, LDR sensors, STM32F103 microcontroller, ESP32, servo motor, and the voltage divider. [it will be in directory with name circuit_diagram]

************** Additional Features *****************
- Local Network Access: The ESP32 facilitates real-time access to the battery level from any device connected to the local network, providing convenience and ease of monitoring.
- Webpage Interface: A simple and user-friendly interface allows users to view battery status in real time, helping track the performance of the solar system.
- Future Scalability: The design is expandable for larger installations in real-world solar energy systems.

************ Project Video *************************
A full demonstration of the project is available on YouTube, showcasing the system's sun-tracking capabilities, real-time battery monitoring, and network accessibility. 
[Link of video's project: https://youtu.be/PefNpsHqoHA?si=hutHc0BRugH5mU4n]

**** For more information feel free to contact us on our social media or on our webpage. ***
- instagram : https://instagram.com/makin_afleo?igshid=MmIzYWVlNDQ5Yg==
- youtube : https://www.youtube.com/channel/UC4JMOTgAy32O7BfJBDLREKQ
- webpage : https://makinafleo.com/
