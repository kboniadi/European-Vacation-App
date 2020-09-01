# European Vacation App
Your team is to write a program that reads data and stores it in a data
structure of your choice. Your program must have the ability to hold
the names of at least 30 European cities (the initial data contains 11
cities) and their corresponding traditional food items (up to six per
city). Your program will be used to allow perspective European
travelers to plan their summer vacation. Your team will need to
provide the ability to modify information related to the traditional food
items (such as adding new food items, changing a price of a food
item, or deleting a food item).

---

## Table of Contents
- [Installation](#installation)
- [Features](#features)
- [Team](#team)
- [FAQ](#faq)
- [Support](#support)
- [License](#license)

---

## Installation

### Clone

- Clone this repo to your local machine using `https://github.com/kboniadi/European-Vacation-App.git`

### Setup

- Download Qt from https://www.qt.io/download

> make a build directory and then cd into it

```shell
$ mkdir qt/_build
$ cd qt/_build
```

> generate a Makefile using qmake  and then run make

```shell
$ path/to/Qt/5.xx.x/compiler_name/bin/qmake ../app/
$ make
```

> run the executable

```shell
$ ./app
```
- See the [Support](#support) section if you run into any problems
---

## Features
1. Display the list of European cities and their distances from Berlin.

2. Display all the traditional food items for any given city.

3. Provide the capability to visit the initial 11 European cities starting at Berlin.
  - a. Plan the trip starting at Berlin then visit each of the other European cities in the most efficient order (recursively choose the city closest to the previous city)
  - b. Display the total distance traveled
  
4. Offer the option to plan the shortest trip starting at Paris
  - a. Obtain the “number” of European cities to visit
  - b. Visit the “number” of cities specified (including Paris)
  - c. Plan the trip starting at Paris then visit the closest city to Paris, then visit the closest city to that city and so on (recursively choose the city closest to the previous city)
  - d. Display the total distance traveled
  - e. Allow the traveler to purchase multiple traditional food items when visiting the European cities
  
5. Offer the option to plan a custom trip
  - a. Allow a traveler to select the starting European city they wish to visit
  - b. Then allow a traveler to select all other European cities they wish to visit
  - c. Plan the trip starting with the selected city then visit each of the other European cities in the most efficient order (recursively choose the city closest to the previous city).
  - d. Display the total distance traveled
  - e. Allow the traveler to purchase multiple traditional food items when visiting the European cities

6. When taking any trip:
  - a. A traveler can purchase multiple traditional food items
  - b. Your team must keep track of the number of traditional food items purchased at each city
  - c. Display the total amount spent at each European city and a grand total for all cities visited

7. Maintenance (administrator only - requires a password to gain access)
  - a. Provide the capability to add new European cities and their corresponding food items by having your program read from the input file given to the class
  - b. Provide the capability to change the prices of the traditional food items
  - c. Provide the capability to add new traditional food items
  - d. Provide the capability to delete traditional food items
  
8. Provide the capability to visit the 13 European cities starting at Berlin.
  - a. Plan the trip starting at Berlin then visit each of the other European cities in the most efficient order (recursively choose the city closest to the previous city)
  - b. Allow the traveler to purchase multiple traditional food items when visiting the European cities
  
---
  
## Team
- **Kord Boniadi** - something
- **Weston Mathews** - something else
- **Noah Vaks** - another thing
- **Bryson Bisuno** - one more thing

---

## FAQ

---

## Support

---

## License

[![License](http://img.shields.io/:license-mit-blue.svg?style=flat-square)](http://badges.mit-license.org)
- **[MIT license](http://opensource.org/licenses/mit-license.php)**
- Copyright 2020 © *Team name*
