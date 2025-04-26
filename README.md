# OOP-Project-Simplified Taxi Company System (Uber)

## Description
A simplified taxi company system. Every user has a type - client or driver. Each of them registers with different kinds of data. After a successful registration, you should log in to perform any other actions on your account. There are different commands depending on the type of the current user. For example, only a client should be able to create an order. This order will be offered to the closest driver (depending on the current location of both). The driver can accept or decline the order. If declined, the order will be offered to the next closest driver. Once the order is accepted, the client can cancel it before it has been finished.

After finishing the order, the next steps are simple:
1. Pay driver (client)
2. Accept payment (driver)
3. Rate driver (client)

Once the status of the order is set to "rated," this indicates that the order is finished, and no further action is required.

---

## Prerequisites
- **Operating System**: Windows
- **Compiler**: `g++` (MinGW or MSYS2 recommended)
- **VS Code**: Ensure you have the C++ extension installed

---

## Project Structure
```
Uber/
    main.cpp    # Entry point of the program
    headers/    # Header files (.h/.hpp)
    src/        # Source files (.cpp)
    project.exe # Compiled executable (generated after build)
    clients.txt # Sample data for clients (created once you make registration)
    drivers.txt # Sample data for drivers (created once you make registration)
    orders.txt  # Sample data for orders (created once you make registration)
```

---

## How to Build and Run the Project

### Option 1: Using VS Code Build Task
1. Open the folder `OOP_Project` in Visual Studio Code.
2. Press `Ctrl+Shift+B` to open the build menu.
3. Select **"C/C++: g++.exe build entire project"**.
4. This will compile all `.cpp` files and generate the `project.exe` executable in the `Uber` directory.

### Option 2: Using the Terminal
1. Open a terminal and navigate to the project directory.
2. Run the following command to build the project:
   ```
   g++ -fdiagnostics-color=always -g Uber/main.cpp Uber/src/*.cpp -o Uber/project.exe
   ```
3. Navigate to the `Uber` directory:
   ```
   cd Uber
   ```
4. Run the executable:
   ```
   ./project.exe
   ```

> **Note**: Ensure all `.txt` files (e.g., `clients.txt`, `drivers.txt`, `orders.txt`) are in the same directory as the executable (`Uber/`).

---

## Commands

### Generic Commands
#### Registration
```
-------Client-------
1. Username
2. Password
3. First name
4. Last name

-------Driver-------
1. Username
2. Password
3. First name
4. Last name
5. Car number
6. Phone number
```

#### Login
- Access the system with: `<Username>`, then `<Password>`.

#### Logout
- Leave the system.

---

### Client Commands
- **Create Order**: Set origin and destination.
- **Check Order**: View info about the order and the driver.
- **Cancel Order**: Cancel orders with status `<awaitingDriver>`, `<inProgress>`, or `<accepted>`.
- **Pay Driver**: Set the amount of money for the order and transfer it to the driver's bank account.
- **Rate Driver**: Express an opinion about the service offered by the driver.
- **Add Money**: Transfer money to your account.

---

### Driver Commands
- **Change Address**: Update your current address.
- **Check Messages**: View general information about current orders.
- **Accept Order**: Accept an order offered to you.
- **Finish Order**: Mark an order as completed.
- **Decline Order**: Offer the order to the next driver.
- **Accept Payment**: Confirm receipt of payment.
