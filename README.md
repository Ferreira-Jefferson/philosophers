# Philosophers

This repository contains the 42 School "Dining Philosophers" project. It includes two implementations:

- `philo/` — mandatory part (threads + mutexes)
- `philo_bonus/` — bonus part (processes + semaphores)

The goal is to simulate N philosophers that alternately think, eat and sleep. Each philosopher needs two forks (shared resources) to eat. The program must avoid deadlocks and starvation and follow the project's timing and printing rules.

## Table of contents

- [About](#about)
- [Project structure](#project-structure)
- [Behavior and rules](#behavior-and-rules)
- [Usage](#usage)
- [Testing examples](#testing-examples)
- [Makefile targets](#makefile-targets)
- [License](#license)

## About

The simulation receives runtime arguments that define how many philosophers there are and timing parameters. Each philosopher is represented either by a thread (`philo`) or a process (`philo_bonus`). The implementation focuses on correct synchronization, precise timing, and clean termination.

Key constraints and goals:

- Correctly coordinate access to forks (mutexes or semaphores).
- Avoid deadlocks and ensure each philosopher can eat when allowed.
- Stop the simulation when a philosopher dies (didn't start eating within `time_to_die`) or when each philosopher has eaten the required number of times (if provided).
- Respect required printing format and avoid interleaved output.

## Project structure

Use the tree-style layout below (examples of the main files present in each folder):

```
philosophers/
├── philo/                    # mandatory implementation (threads + mutexes)
│   ├── philo                 # binary after make
│   ├── core.c
│   ├── monitor.c
│   ├── philosophers.c
│   ├── utils_core.c
│   ├── utils_init.c
│   ├── utils.c
│   ├── libft.c
│   ├── philosophers.h
|	└── Makefile 
├── philo_bonus/             # bonus implementation (processes + semaphores)
│   ├── philo_bonus           # binary after make
│   ├── core_bonus.c
│   ├── monitor_bonus.c
│   ├── philosophers_bonus.c
│   ├── utils_core.c
│   ├── utils_init_bonus.c
│   ├── utils_bonus.c
│   ├── libft_bonus.c
│   └── Makefile 
├── LICENSE
└── README.md
```

## Behavior and rules

Command-line arguments (common pattern used by most 42 implementations):

```
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

- `number_of_philosophers` — number of philosophers and forks.
- `time_to_die` — time in milliseconds: if a philosopher doesn't start eating within this time since their last meal or since the simulation started, they die.
- `time_to_eat` — time in milliseconds a philosopher spends eating (they hold forks during this time).
- `time_to_sleep` — time in milliseconds a philosopher spends sleeping.
- `number_of_times_each_philosopher_must_eat` (optional) — if all philosophers eat at least this many times, the simulation stops.

Output format (each action printed on its own line):

```
<timestamp_in_ms> <philosopher_id> <action>
```

Actions include:
- `has taken a fork`
- `is eating`
- `is sleeping`
- `is thinking`
- `died`

The timestamp is the time since the simulation start.

## Usage

Clone the repository:

```bash
git clone https://github.com/Ferreira-Jefferson/philosophers.git
cd philosophers
```

Create the executable:

```bash
cd philo && make
cd ../philo_bonus && make
```

Run the mandatory (threaded) version (note the `cd` into the folder before running):

```bash
cd philo
./philo 5 800 200 200
```

Run the bonus (process) version:

```bash
cd philo_bonus
./philo_bonus 5 800 200 200
```

With the optional meals limit:

```bash
cd philo
./philo 4 410 200 200 7
```

Notes:

- Use `Ctrl+C` to stop a long-running or stuck simulation. The programs should also terminate by themselves when the stopping condition is met.
- The exact binaries are created inside `philo/` and `philo_bonus/` after running `make` in the project root or in each subfolder.


## Testing examples

Small sample invocations and expected behavior (timing may vary depending on the system):

- Single philosopher dying because they can't grab two forks:

```bash
cd philo
./philo 1 800 200 200
```

- Many philosophers, short times (should finish or detect death quickly):

```bash
cd philo
./philo 5 800 200 200
```

- Stop after each philosopher eats N times:

```bash
cd philo
./philo 4 410 200 200 7
```

## Makefile targets

- `make` — build the project (both parts if configured).
- `make clean` — remove object files.
- `make fclean` — remove object files and binaries.
- `make re` — rebuild from scratch.

Check the `Makefile` inside `philo/` and `philo_bonus/` for exact targets and behavior.

## License

This project is distributed under the GNU General Public License v3.0. See the [LICENSE](LICENSE) file in the repository root for details.

---

*Project developed as part of the 42*
