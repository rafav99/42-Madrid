# Philosophers

A simulation of the dining philosophers problem in C using **POSIX threads and mutexes**.

Each philosopher alternates between eating, sleeping and thinking while sharing forks with neighbors. The implementation tracks starvation, synchronizes access to shared resources and supports stopping once everyone reaches a meal quota.

```bash
make -C philosophers
./philosophers/philo 5 800 200 200 5
make -C philosophers test
```

Arguments: `count time_to_die_ms time_to_eat_ms time_to_sleep_ms [meal_target]`.

**Focus:** concurrency, scheduling, resource management and synchronization.
