# OOP-Project-Simplified Taxi Company System (Uber)

## Description
A simplified taxi company system. Every user has a type - client or driver. Each of them registers with different kind of data. After a successful registration you should login to do any other actions to your account. There are different commands depending on the type of the current user, for example only a client should be able to create an order. This order will be offered to the closest driver (depending on the current location of both). The driver can accept or decline the order. If he declines it, then the order will be offered to the next closest driver. Once the order is accepted, the client can cancel, before it has been finished.
After finishing the order the next steps are simple:
1. Pay driver(client)
2. Accept payment (driver)
3. Rate driver (client)
Once the status of the order is set to “rated”, this indicates that the order is finished and no further action is required.
# Commands:
## Generic:
### *Registration:
```
-------Client-------
1.Username;
2.Password;
3.First name;
4.Last name;

-------Driver-------
1.Username;
2.Password;
3.First name;
4.Last name;
5.Car number;
6.Phone number;
```
### *Login:
##### -> Access the system with: < Username >, then < password >;
### *Logout;
##### -> Leave the system;
## Client commands:
```
 -> Create order - set origin and destination;
 ***
 -> Check order (only orders that exist can be checked) - info about the order and the driver;
 ***
 -> Cancel order(only order with status: < awaitingDriver >, < inProgress > or < accepted > could be cancelled;
 ***
 -> Pay driver - sets amount of money for the order and transfers it to the driver(of the chosen order) bank account;
 ***
 -> Rate driver - through this you express an opinion about the service offered by the driver;
 ***
 -> Add money - transfer money to your account;
 ```
 ## Driver commands:
 ```
 -> Change address;
 ***
 -> Check messages – general information about the current orders;
 ***
 -> Accept order;
 ***
 -> Finish order;
 ***
 -> Decline order - offer the order to the next driver;
 ***
 -> Accept payment;
 ```

