# aed-schedule

## Table of contents
* [General info](#general-info)
* [Technologies](#technologies)
* [Setup](#setup)

## General info
The main purpose of this project is to manage schedules after they have been elaborated.
The system includes various functionalities related to schedules, such as modifying,
searching, viewing, sorting, listing, among others.
	
## Technologies
Project is created with:
* C++: 11
* Doxygen: 1.9.1
* Visual studio code: 1.83.1
	
## Setup
To run this project, clone it to your computer in a directory chosen by you:

```
$ git remote add origin git@github.com:yourusername/aed-schedule.git
```

Then, we need to compile the project using CMAKE File:

- Go to schedule-build directory:

```
$ cd schedule-build
```

- For first compile generate a native build system:

```
$ cmake ../
```

- Compile/link the project (also in the schedule-build directory):

```
$ cmake --build .
```

- Try to use it (It doesn't work for some reason):

```
$ aed-schedule 
```

- To see documentation:

```
$ cd html
$ open index.html
```


