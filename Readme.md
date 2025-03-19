# Philosophers

I never thought philosophy would be so deadly

## Overview
Philosophers is a multithreading project written in C that simulates the famous "Dining Philosophers" problem. The goal is to manage multiple philosophers who alternate between eating, thinking, and sleeping while preventing data races and deadlocks.

## Features
- Multithreading implementation using pthreads (mandatory part)
- Mutex-protected shared resources
- Avoidance of race conditions and deadlocks
- Precise logging of philosopher states
- Simulation parameters:
  - Number of philosophers
  - Time to die
  - Time to eat
  - Time to sleep
  - Optional: Number of times each philosopher must eat

## Installation & Usage
### Compilation
```sh
make -C philo
```

### Running the Simulation
```sh
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```
Example:
```sh
./philo 5 800 200 200
```

## Requirements
- C compiler (`gcc`)
- `pthread` library

## Project Structure
```
philosophers/
├── src/         # Source files
├── includes/    # Header files
├── Makefile     # Build instructions
└── README.md    # Project documentation
```

## Authors
- De Win Guillaume
