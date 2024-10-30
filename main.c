#include "webshop.h"
#include <stdio.h>

int main() {
    int choice;
    WebshopStore webshopStore;
    Cart cart;

    initializeWebshopStore(&webshopStore);
    initializeCart(&cart);

    do {
        // Display menu
        printf("----------------------------------------------\n");
        printf("Menu:\n");
        printf("1. Load webshop store from a file\n");
        printf("2. Write the content of the store to a file\n");
        printf("3. Display Available Items\n");
        printf("4. Insert an item to cart\n");
        printf("5. Display Cart Items\n");
        printf("6. Get the price of cart\n");
        printf("7. Buy the products\n");
        printf("8. Exit\n");
        printf("----------------------------------------------\n");

        // Get user choice
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                loadWebshopStoreFromFile(&webshopStore);
                break;
            case 2:
                writeWebshopStoreToFile(&webshopStore);
                break;
            case 3:
            	printf("----------------------------------------------\n");
			    displayAvailableItems(&webshopStore);
			    printf("----------------------------------------------\n");
			    break;
			case 4:
				displayAvailableItems(&webshopStore);
                insertItemToCart(&webshopStore, &cart);
                break;
            case 5:
            	printf("----------------------------------------------\n");
            	displayCartItems(&cart);
            	break;
            case 6:
            	printf("===========================\n");
            	displayCartItems(&cart);
                getPriceOfCart(&cart);
                printf("===========================\n");
                break;
            case 7:
                buyProducts(&webshopStore, &cart);
                break;
            case 8:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }

    } while (choice != 8);

    // Cleanup
    freeWebshopStore(&webshopStore);
    freeCart(&cart);

    return 0;
}
