# Philosophers

A C implementation of the classic Dining Philosophers problem using threads and mutexes.

## About

This project simulates the Dining Philosophers problem where N philosophers sit around a table with N forks. Each philosopher needs 2 forks to eat and alternates between eating, sleeping, and thinking. The goal is to prevent deadlocks and starvation while ensuring thread safety.

## The Problem

- Philosophers sit around a circular table
- Each philosopher needs 2 adjacent forks to eat
- After eating, they sleep, then think
- The simulation ends if a philosopher dies (exceeds time limit without eating)
- Optional: Stop when all philosophers have eaten a specified number of times

## Usage

```bash
make
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_must_eat]
```

### Parameters:
- `number_of_philosophers`: Number of philosophers (and forks)
- `time_to_die`: Max time (ms) a philosopher can go without eating
- `time_to_eat`: Time (ms) it takes to eat
- `time_to_sleep`: Time (ms) spent sleeping
- `number_of_times_each_must_eat`: Optional stopping condition

### Examples:
```bash
./philo 5 800 200 200     # 5 philosophers, basic simulation
./philo 4 410 200 200     # 4 philosophers, tight timing
./philo 5 800 200 200 7   # Stop when each has eaten 7 times
```

## Implementation Features

- **Thread Safety**: All shared resources protected by mutexes
- **Deadlock Prevention**: Smart fork ordering (even/odd philosopher strategy)
- **Starvation Prevention**: Thread staggering and timing optimizations
- **Precise Timing**: Millisecond-accurate death detection
- **Clean Termination**: Proper cleanup of threads and resources

## Output Format

```
timestamp_in_ms philosopher_id action
```

Actions: `has taken a [left/right] fork`, `is eating`, `is sleeping`, `is thinking`, `died`

Example:
```
0 1 has taken a left fork
0 1 has taken a right fork
0 1 is eating
200 1 is sleeping
400 1 is thinking
```

## Project Structure

```
├── main.c          # Entry point and argument validation
├── includes/philo.h # Data structures and function declarations
└── src/
    ├── init.c      # Initialization functions
    ├── philo.c     # Core philosopher logic
    ├── utils.c     # Utility functions
    └── valid.c     # Input validation
```

## Building

```bash
make        # Compile
make clean  # Remove object files
make fclean # Remove all generated files
make re     # Clean and rebuild
```

---
*42 School Project - Concurrent Programming with Threads*
