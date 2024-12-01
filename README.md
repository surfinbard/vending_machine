# Vending Machine 

This C program simulates the operation of a vending machine. It allows users to select products manually or randomly, insert money, and receive change (if applicable). The machine manages product inventory, calculates change based on available coins, and keeps track of sales. 
Don't ask me what currency this is in. I don't know either.

## Features

### Product Selection:
        Manual: Users can choose a product by its code.
        Random: The machine selects a product automatically.

### Money Insertion:
        Accepts values of $5, $2, $1, and $0.5.
        Ensures the inserted amount is sufficient for the selected product.

### Change Dispensing:
        Calculates and returns change based on available coin inventory.
        Alerts the user if exact change cannot be provided.

### Inventory Management:
        Updates product quantities after each sale.
        Notifies the user when a product is out of stock.

### State Transitions:
        Implements a state machine for smooth transitions between different operations (e.g., selection, payment, dispensing).

## How to Run

Compile: Use a C compiler (e.g., gcc) to compile the program:

        gcc vending_machine.c utils.c -o vending_machine -lm

Run:

    ./vending_machine
