#ifndef WEBSHOP_H
#define WEBSHOP_H

typedef struct {
    char name[50];
    int price;
    int quantity;
} Product;

typedef struct {
    Product* products;
    int size;
    int capacity;
} WebshopStore;

typedef struct {
    Product* items;
    int* quantities;
    int size;
    int capacity;
} Cart;

void freeCart(Cart* cart);
void initializeCart(Cart* cart);
void insertItemToCart(const WebshopStore* webshopStore, Cart* cart);
void displayCartItems(const Cart* cart);
void getPriceOfCart(const Cart* cart);

void freeWebshopStore(WebshopStore* webshopStore);
void initializeWebshopStore(WebshopStore* webshopStore);
void loadWebshopStoreFromFile(WebshopStore* webshopStore);
void writeWebshopStoreToFile(const WebshopStore* webshopStore);
void displayAvailableItems(const WebshopStore* webshopStore);
void buyProducts(WebshopStore* webshopStore, Cart* cart);

#endif
