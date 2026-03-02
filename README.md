# philosophers (42 School)

## 📋 Description
This project is an introduction to multi-threading and process synchronization. It is a simulation of the **Dining Philosophers problem**, a classic synchronization challenge, implemented in C using threads and mutexes.

## 🧠 Implementation Logic (Score: 100/100)
The goal is to prevent philosophers from starving by managing their access to shared resources (forks) without creating deadlocks or data races.

- **Multi-threading**: Each philosopher runs in its own thread, executing a routine of eating, sleeping, and thinking.
- **Resource Management (Mutexes)**: Forks are protected by mutexes to ensure that no two philosophers can hold the same fork at the same time.
- **Thread Safety**: I used mutexes to protect shared data, such as the "death flag" and meal timestamps, preventing data races during simultaneous read/write operations.
- **Monitoring**: A dedicated monitoring logic (`check_death.c`) constantly checks if a philosopher has exceeded their "time to die," ensuring the simulation stops immediately upon a death.
- **Precision**: Implementation of a custom `usleep` to overcome the standard function's imprecision, ensuring the simulation remains accurate even with many threads.

## 📂 Project Structure
- `src/main.c`: Entry point and global simulation control.
- `src/init.c` & `init_utils.c`: Setup of the table, philosophers, and mutexes.
- `src/philo_routine.c`: The main lifecycle (eat, sleep, think) for each thread.
- `src/check_death.c`: Independent monitoring to handle starvation detection.
- `lib/`: Contains custom `libft` and `ft_printf` used for utility and display.

## 🛠️ Usage & Compilation
The Makefile handles the recursive compilation of dependencies.
```bash
make
```
To execute, the program requires 4 or 5 arguments: number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

```bash
Example (Survival):
./philo 5 800 200 200
```
```bash
Example (Death):
./philo 4 310 200 100
```
