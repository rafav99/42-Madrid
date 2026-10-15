# Philosophers

A C simulation of the dining philosophers problem, developed as part of my programming work at **42 Madrid**.

The simulation uses POSIX threads and mutexes to represent philosophers competing for shared forks. A monitoring loop detects starvation and stops the program when someone dies, or once everyone has eaten the requested number of times.

## Build

Requirements: a C11 compiler, `make`, and POSIX threads (Linux or a compatible Unix environment).

```bash
make
```

## Run

```bash
./philo 5 800 200 200 5
```

Arguments:

```text
./philo <philosophers> <time_to_die_ms> <time_to_eat_ms> <time_to_sleep_ms> [meals_per_philosopher]
```

All supplied numbers must be positive integers. The final argument is optional; without it, the simulation runs until a philosopher dies.

Each log line contains a timestamp in milliseconds, a philosopher ID, and an action. Time starts at simulation initialization.

## Tests

```bash
make test
```

The test script checks single-philosopher behavior, odd and even populations, meal-count termination, starvation, invalid input, and repeated concurrent runs. Timing-sensitive tests are not a substitute for stress testing on the target machine.

For an additional concurrency check with GCC's ThreadSanitizer:

```bash
cc -Wall -Wextra -Werror -std=c11 -pthread -fsanitize=thread -g philosophers.c -o philo_tsan
./philo_tsan 5 800 100 100 3
```

## Notes

This portfolio copy is a revised version of my [original `philosophers` repository](https://github.com/rafav99/philosophers). It improves input validation, termination, timing, fork acquisition, resource cleanup and reproducible testing. The original repository has not been modified.

As with other scheduling-based simulations, exact event timings depend on the operating system and machine load.
