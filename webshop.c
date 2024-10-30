#include "webshop.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void freeWebshopStore(WebshopStore* webshopStore) {
    free(webshopStore->products);
}

void initializeWebshopStore(WebshopStore* webshopStore) {
    webshopStore->products = NULL;
    webshopStore->size = 0;
    webshopStore->capacity = 0;
}

void loadWebshopStoreFromFile(WebshopStore* webshopStore) {
    char filename[100];
    printf("Enter filename to load from: ");
    scanf("%s", filename);

    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error: Unable to open file.\n");
        return;
    }

    // Allocate memory for products
    webshopStore->capacity = 10; // Initial capacity
    webshopStore->products = malloc(webshopStore->capacity * sizeof(Product));
    webshopStore->size = 0;

    // Assuming each line in the file is in the format: name price quantity
    while (fscanf(file, "%s %d %d", webshopStore->products[webshopStore->size].name,
                                 &webshopStore->products[webshopStore->size].price,
                                 &webshopStore->products[webshopStore->size].quantity) == 3) {
        webshopStore->size++;

        if (webshopStore->size >= webshopStore->capacity) {
            webshopStore->capacity += 10;
            webshopStore->products = realloc(webshopStore->products, webshopStore->capacity * sizeof(Product));
        }
    }

    fclose(file);
}

void writeWebshopStoreToFile(const WebshopStore* webshopStore) {
    char filename[100];
    printf("Enter filename to write to: ");
    scanf("%s", filename);

    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Error: Unable to open file.\n");
        return;
    }

    for (int i = 0; i < webshopStore->size; i++) {
        fprintf(file, "%s %d %d\n", webshopStore->products[i].name,
                                     webshopStore->products[i].price,
                                     webshopStore->products[i].quantity);
    }

    fclose(file);
}

void displayAvailableItems(const WebshopStore* webshopStore) {
    printf("Available Items in Webshop:\n");
    for (int i = 0; i < webshopStore->size; i++) {
        printf("%d. %s - Price: %d, Quantity: %d\n", i + 1,
               webshopStore->products[i].name,
               webshopStore->products[i].price,
               webshopStore->products[i].quantity);
    }
    printf("\n");
}

void buyProducts(WebshopStore* webshopStore, Cart* cart) {
    for (int i = 0; i < cart->size; i++) {
        int productIndex = -1;
        for (int j = 0; j < webshopStore->size; j++) {
            if (strcmp(cart->items[i].name, webshopStore->products[j].name) == 0) {
                productIndex = j;
                break;
            }
        }

        if (productIndex == -1 || cart->quantities[i] > webshopStore->products[productIndex].quantity) {
            printf("Error: %d %s are missing.\n", cart->quantities[i] - webshopStore->products[productIndex].quantity, cart->items[i].name);
            webshopStore->products[productIndex].quantity = 0;
        } else {
            ; //webshopStore->products[productIndex].quantity -= cart->quantities[i];
        }
    }

    printf("Products bought successfully!\n");

    // Clear cart
    freeCart(cart);
    initializeCart(cart);
}

void freeCart(Cart* cart) {
    free(cart->items);
    free(cart->quantities);
}

void initializeCart(Cart* cart) {
    cart->items = NULL;
    cart->quantities = NULL;
    cart->size = 0;
    cart->capacity = 0;
}

void insertItemToCart(const WebshopStore* webshopStore, Cart* cart) {
    char itemName[50];
    int quantity;
    
    printf("Enter product name: ");
    scanf("%s", itemName);
    
    int productIndex = -1;
    for (int i = 0; i < webshopStore->size; i++) {
        if (strcmp(itemName, webshopStore->products[i].name) == 0) {
            productIndex = i;
            break;
        }
    }

    if (productIndex == -1) {
        printf("Error: Product not found in the store.\n");
        return;
    }

    printf("Enter quantity: ");
    scanf("%d", &quantity);

    if (quantity <= 0 || quantity > webshopStore->products[productIndex].quantity) {
        printf("Error: Invalid quantity.\n");
        return;
    }

    for (int i = 0; i < cart->size; i++) {
        if (strcmp(itemName, cart->items[i].name) == 0) {
            cart->quantities[i] += quantity;
            webshopStore->products[productIndex].quantity -= quantity;
            return;
        }
    }

    cart->size++;
    if (cart->size >= cart->capacity) {
        cart->capacity += 10;
        cart->items = realloc(cart->items, cart->capacity * sizeof(Product));
        cart->quantities = realloc(cart->quantities, cart->capacity * sizeof(int));
    }

    strcpy(cart->items[cart->size - 1].name, webshopStore->products[productIndex].name);
    cart->items[cart->size - 1].price = webshopStore->products[productIndex].price;
    cart->quantities[cart->size - 1] = quantity;
	webshopStore->products[productIndex].quantity -= quantity;
}

void displayCartItems(const Cart* cart) {
    if (cart->size == 0) {
        printf("Cart is empty.\n\n");
        return;
    }

    printf("Items in Cart:\n");
    for (int i = 0; i < cart->size; i++) {
        printf("%d. %s - Price: %d, Quantity: %d\n", i + 1,
               cart->items[i].name,
               cart->items[i].price,
               cart->quantities[i]);
    }
    printf("\n");
}

void getPriceOfCart(const Cart* cart) {
    int totalPrice = 0;
    for (int i = 0; i < cart->size; i++) {
        totalPrice += cart->items[i].price * cart->quantities[i];
    }

    printf("Total price of cart: %d\n", totalPrice);
}

