# Simple C Webshop Console Application

This repository contains a simple webshop console application written in C. It allows users to interact with a basic online store interface to view, add to, and purchase items through a command-line interface.

## Features

1. **Load Store Inventory from File** - Load a predefined inventory of products from a text file.
2. **Save Store Inventory to File** - Save the current state of the store’s inventory to a file.
3. **Display Available Products** - View all products available in the store along with their prices and quantities.
4. **Add Items to Cart** - Select a product and quantity to add to your cart.
5. **View Cart Items** - Display items currently in your cart.
6. **Calculate Cart Total** - View the total price of all items in the cart.
7. **Finalize Purchase** - Confirm purchase to update stock levels and clear the cart.

## Files

- `main.c`: Contains the primary application logic and menu system.
- `webshop.h`: Header file defining structs for `Product`, `WebshopStore`, and `Cart`, along with function declarations.
- `webshop.c`: Implements functions for inventory management, cart handling, and I/O operations.

