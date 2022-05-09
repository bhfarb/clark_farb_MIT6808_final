Sophia Clark and Beatrice Farb MIT 6.808 Final Project, 2022

Find information about use at this link:
https://docs.google.com/presentation/d/1IQof9bFKeyR-1cYYPrUwk6MUfd48uEPlcBPg0_iefa8/edit?usp=sharing

- write_data.ino: upload to Arduino to begin data collection for TDS, turbidity and temperature sensors. Serially prints data and writes it to EEPROM
- read_data.ino: upload to Arduino to read data (via serial port) saved in EEPROM, 4 bytes at a time
- serial_to_csv.py: as data is being serially printed from Arduino, write it to a .csv file
