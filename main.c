#include <stdio.h>
#include <string.h>

#define TOTAL_MENU_ITEMS 6
#define MAX_ORDER_ITEMS 20
#define DISCOUNT_THRESHOLD 500.00
#define DISCOUNT_PERCENTAGE 10.00

// Structure to store menu item details
typedef struct {
    int id;
    char name[30];
    float price;
} MenuItem;

// Structure to store ordered item details
typedef struct {
    int itemId;
    char name[30];
    int quantity;
    float unitPrice;
    float subtotal;
} OrderItem;

// Global menu definition
MenuItem menu[TOTAL_MENU_ITEMS] = {
    {1, "Veg Burger",       80.00},
    {2, "Cheese Sandwich",  60.00},
    {3, "Masala Dosa",      90.00},
    {4, "Cold Coffee",      50.00},
    {5, "French Fries",     70.00},
    {6, "Samosa (2 pcs)",   30.00}
};

// Function prototypes
void displayMenu();
int findItemIndex(int id);
void takeOrder(OrderItem orders[], int *orderCount);
void generateBill(OrderItem orders[], int orderCount);

int main() {
    OrderItem orders[MAX_ORDER_ITEMS];
    int orderCount = 0;
    int choice;

    do {
        printf("\n=========================================\n");
        printf("       SMART CANTEEN MANAGEMENT\n");
        printf("=========================================\n");
        printf("1. View Menu\n");
        printf("2. Take / Add Order\n");
        printf("3. Generate Bill & Checkout\n");
        printf("4. Reset Current Order\n");
        printf("5. Exit\n");
        printf("-----------------------------------------\n");
        printf("Enter your choice (1-5): ");

        if (scanf("%d", &choice) != 1) {
            printf("\n[Error] Invalid input! Please enter a number.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }

        switch (choice) {
            case 1:
                displayMenu();
                break;
            case 2:
                takeOrder(orders, &orderCount);
                break;
            case 3:
                if (orderCount == 0) {
                    printf("\n[Notice] No items ordered yet! Please add items first.\n");
                } else {
                    generateBill(orders, orderCount);
                    orderCount = 0; // Reset order after checkout
                }
                break;
            case 4:
                orderCount = 0;
                printf("\n[Success] Current order has been reset.\n");
                break;
            case 5:
                printf("\nThank you for using Smart Canteen System. Have a great day!\n");
                break;
            default:
                printf("\n[Error] Invalid choice! Please select an option between 1 and 5.\n");
        }
    } while (choice != 5);

    return 0;
}

// Displays available items in tabular format
void displayMenu() {
    printf("\n-----------------------------------------\n");
    printf("              CANTEEN MENU               \n");
    printf("-----------------------------------------\n");
    printf("%-6s %-20s %-10s\n", "ID", "Item Name", "Price (INR)");
    printf("-----------------------------------------\n");
    for (int i = 0; i < TOTAL_MENU_ITEMS; i++) {
        printf("%-6d %-20s %8.2f\n", menu[i].id, menu[i].name, menu[i].price);
    }
    printf("-----------------------------------------\n");
    printf("* Special Offer: Get %.0f%% off on orders above INR %.2f!\n", 
           DISCOUNT_PERCENTAGE, DISCOUNT_THRESHOLD);
}

// Searches menu by item ID; returns array index or -1 if not found
int findItemIndex(int id) {
    for (int i = 0; i < TOTAL_MENU_ITEMS; i++) {
        if (menu[i].id == id) {
            return i;
        }
    }
    return -1;
}

// Handles user order input with boundary and validation checks
void takeOrder(OrderItem orders[], int *orderCount) {
    int itemId, qty;
    char addMore;

    displayMenu();

    do {
        if (*orderCount >= MAX_ORDER_ITEMS) {
            printf("\n[Notice] Order list is full! Maximum %d items reached.\n", MAX_ORDER_ITEMS);
            break;
        }

        printf("\nEnter Item ID to order: ");
        if (scanf("%d", &itemId) != 1) {
            printf("[Error] Invalid input. Enter numeric ID.\n");
            while (getchar() != '\n');
            continue;
        }

        int index = findItemIndex(itemId);
        if (index == -1) {
            printf("[Error] Item ID %d not found in menu. Please check the ID.\n", itemId);
            continue;
        }

        printf("Enter Quantity for %s: ", menu[index].name);
        if (scanf("%d", &qty) != 1 || qty <= 0) {
            printf("[Error] Invalid quantity! Quantity must be greater than 0.\n");
            while (getchar() != '\n');
            continue;
        }

        // Check if item already exists in current order; if so, update quantity
        int existingIndex = -1;
        for (int i = 0; i < *orderCount; i++) {
            if (orders[i].itemId == itemId) {
                existingIndex = i;
                break;
            }
        }

        if (existingIndex != -1) {
            orders[existingIndex].quantity += qty;
            orders[existingIndex].subtotal = orders[existingIndex].quantity * orders[existingIndex].unitPrice;
            printf("[Updated] %s quantity updated to %d.\n", 
                   orders[existingIndex].name, orders[existingIndex].quantity);
        } else {
            orders[*orderCount].itemId = itemId;
            strcpy(orders[*orderCount].name, menu[index].name);
            orders[*orderCount].quantity = qty;
            orders[*orderCount].unitPrice = menu[index].price;
            orders[*orderCount].subtotal = qty * menu[index].price;
            (*orderCount)++;
            printf("[Added] %d x %s added to cart.\n", qty, menu[index].name);
        }

        printf("Do you want to add another item? (y/n): ");
        scanf(" %c", &addMore);

    } while (addMore == 'y' || addMore == 'Y');
}

// Generates an itemized receipt with tax, discount, and final amount
void generateBill(OrderItem orders[], int orderCount) {
    float subtotal = 0.0;
    float discount = 0.0;
    float finalAmount = 0.0;

    for (int i = 0; i < orderCount; i++) {
        subtotal += orders[i].subtotal;
    }

    if (subtotal > DISCOUNT_THRESHOLD) {
        discount = (subtotal * DISCOUNT_PERCENTAGE) / 100.00;
    }
    finalAmount = subtotal - discount;

    printf("\n========================================================\n");
    printf("                  CAMPUS CANTEEN BILL                   \n");
    printf("========================================================\n");
    printf("%-4s %-20s %-8s %-10s %-10s\n", "S.N", "Item Description", "Qty", "Rate", "Total (INR)");
    printf("--------------------------------------------------------\n");

    for (int i = 0; i < orderCount; i++) {
        printf("%-4d %-20s %-8d %-10.2f %-10.2f\n", 
               i + 1, 
               orders[i].name, 
               orders[i].quantity, 
               orders[i].unitPrice, 
               orders[i].subtotal);
    }

    printf("--------------------------------------------------------\n");
    printf("%-44s : INR %8.2f\n", "Subtotal", subtotal);

    if (discount > 0.0) {
        printf("%-44s : INR -%7.2f\n", "Discount (10% on > 500)", discount);
    } else {
        printf("%-44s : INR %8.2f\n", "Discount Applied", 0.00);
    }

    printf("========================================================\n");
    printf("%-44s : INR %8.2f\n", "NET PAYABLE AMOUNT", finalAmount);
    printf("========================================================\n");
    printf("               Thank You! Visit Again.                 \n");
    printf("========================================================\n");
}
