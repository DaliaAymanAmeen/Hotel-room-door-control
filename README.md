# Hotel-room-door-control

The main building block is TivaC board.
The designed control board shall lock and unlock a solenoid lock. The control board gets its inputs from the hotel receptionist’s PC through UART or from the guest using keypad.

## Mode of operations: 

1. Setup 
   * Store the room no in the control board (To be done via UART connection with PC) 

2. Status of the room (To be done via UART connection with PC)
   * Free
   * Occupied 
   * Room Cleaning

3. Set password (To be done via UART connection with PC)
   * Store 4 digit password by the receptionist’s PC while check-in
   
4. Open the door using the password by the guest using the password
   * Check the password and unlock the solenoid

