# Smart Canteen Management System

A lightweight, console-based billing and order management application built in standard C. This project models an automated canteen kiosk that handles item selection, cart updates, order itemization, automatic discount calculations, and receipt generation.

---

## Features

- **Interactive Menu Display**: Clean tabular format displaying items, IDs, and prices in INR.
- **Dynamic Order Processing**:
  - Add items by numeric ID with quantity selection.
  - Automatically merges duplicate items by updating quantities and calculating subtotals.
  - Input validation for quantities and IDs with input buffer cleanup to prevent infinite loops.
- **Discount Engine**: Automatically applies a **10% discount** whenever the subtotal exceeds **INR 500.00**.
- **Itemized Billing**: Clean formatted receipt breakdown showing serial numbers, quantities, rates, subtotals, discount deductions, and final net payable amount.
- **Order Reset & State Management**: Cart can be cleared manually or resets automatically upon invoice checkout.

---

## Data Structures & Core Logic

- **`MenuItem` Structure**: Stores fixed catalog items (`id`, `name`, `price`).
- **`OrderItem` Structure**: Tracks live orders (`itemId`, `name`, `quantity`, `unitPrice`, `subtotal`).
- **Array of Structs**: Used for storing cart entries with a hard cap set by `MAX_ORDER_ITEMS`.
- **Pass-by-Reference**: Updates cart counter variables across function boundaries (`int *orderCount`).

---

## File Structure

```text
├── main.c        # Complete source code containing canteen business logic
├── README.md     # Documentation and usage guide
```

---

## Prerequisites

A standard C compiler (e.g., `gcc`, `clang`, or MSVC):
- Linux / macOS: `gcc` or `clang`
- Windows: MinGW or MSVC

---

## Compilation and Execution

### Using GCC (Linux / macOS / Windows MinGW)

1. **Clone the repository:**
   ```bash
   git clone https://github.com/<your-username>/smart-canteen-management.git
   cd smart-canteen-management
   ```

2. **Compile the code:**
   ```bash
   gcc main.c -o canteen
   ```

3. **Run the executable:**
   - **Linux / macOS:**
     ```bash
     ./canteen
     ```
   - **Windows:**
     ```cmd
     canteen.exe
     ```

---

## Sample Execution Workflow

```text
=========================================
       SMART CANTEEN MANAGEMENT
=========================================
1. View Menu
2. Take / Add Order
3. Generate Bill & Checkout
4. Reset Current Order
5. Exit
-----------------------------------------
Enter your choice (1-5): 2

-----------------------------------------
              CANTEEN MENU               
-----------------------------------------
ID     Item Name            Price (INR)
-----------------------------------------
1      Veg Burger                 80.00
2      Cheese Sandwich            60.00
3      Masala Dosa                90.00
4      Cold Coffee                50.00
5      French Fries               70.00
6      Samosa (2 pcs)             30.00
-----------------------------------------
* Special Offer: Get 10% off on orders above INR 500.00!

Enter Item ID to order: 1
Enter Quantity for Veg Burger: 4
[Added] 4 x Veg Burger added to cart.
Do you want to add another item? (y/n): y

Enter Item ID to order: 3
Enter Quantity for Masala Dosa: 3
[Added] 3 x Masala Dosa added to cart.
Do you want to add another item? (y/n): n
```

### Sample Bill Output

```text
========================================================
                  CAMPUS CANTEEN BILL                   
========================================================
S.N  Item Description     Qty      Rate       Total (INR)
--------------------------------------------------------
1    Veg Burger           4        80.00      320.00    
2    Masala Dosa          3        90.00      270.00    
--------------------------------------------------------
Subtotal                                     : INR   590.00
Discount (10% on > 500)                      : INR -  59.00
========================================================
NET PAYABLE AMOUNT                           : INR   531.00
========================================================
               Thank You! Visit Again.                 
========================================================
```

---

## License

This project is licensed under the [MIT License](LICENSE).