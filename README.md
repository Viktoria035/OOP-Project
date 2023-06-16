# OOP-Project-Simplified Taxi Company System (Uber)

## Description

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
### *Login - access the system with -> < Username >, then < password >;
### *Logout;
## Client commands:
```
 -> Create order - set origin and destination;
 ***
 -> Check order (only existent one could be checked) - info about the order and the driver;
 ***
 -> Cancel order(only order is status: < awaitingDriver >, < inProgress > or < accepted > could be canceled;
 ***
 -> Pay driver -  set amount of money to the order and then they will be transfert to the driver(of the chosen order) bank account;
 ***
 -> Rate driver - through this you express an opinion about the service offered by the driver;
 ***
 -> Add money - transfer money to your bank account;
 ```
 ## Driver commands:
 ```
 -> Change address;
 -> Check messages - info for the order who are offered to or already accept from the driver;
 -> Accept order;
 -> Finish order;
 -> Decline order - offer the order to the next driver;
 -> Accept payment;
 ```
 
