#                                     Modular_Watering_System

The purpose of this project was to design a modular watering system that can be adapted to suit the needs of each user.
I got the inspiration for this project because I like plants and gardening and I am curently living in a small apartment and i like to have plants around me

Because of the design it can be used in both traditional garden configurations but also hydroponic systems. be it vertical or horizontal.

#  How it works: 

![Watering_sys_Logic_Diagram](https://github.com/user-attachments/assets/a4ee5ebb-5f17-4780-8c1c-0948d087130f)

# Diagram

[Hydrophonics.pdf](https://github.com/user-attachments/files/19392879/Hydrophonics.pdf)

#  Components

- Arduino uno
- 12v submersible water pump
- Hygrometer(soil moisture sensor), 1 per plant or parcel, depending on the use case
- DHT 11 or DHT 12 for ambient temperature and humidity readings
- Relays:
          * 1 for pump
          * 1 per plant or parcel, depending on the use case
- LCD screen
- Buttons for menu operation
- Power supply, batteries or transformer
- HC-SR04 ultra-sonic sensor

#  Known issues

- Depending on the hygrometers used the system may not read soil humidity corectly
- If small delay isn't present in the Loop section, LCD refreshes to quickly
- On my arduino sleep mode doesnt always work and stops program in it's place
- Not enough ports on my arduino, enough with curent configuration for 2 plants or levels/parcels
