*This project has been created as part of the 42 curriculum by vnaoussi.*

## Description
The **Philosophers** project is a simulation of the classic "Dining Philosophers" synchronization problem. It serves as an introduction to concurrent programming using threads and mutexes in C.

The goal is to manage multiple philosophers sitting at a round table with a bowl of spaghetti in the middle. Philosophers alternate between eating, thinking, and sleeping. However, there are only as many forks as philosophers, and a philosopher needs two forks to eat. The challenge is to implement a logic that prevents philosophers from starving while avoiding deadlocks and data races.

## Instructions

### Compilation
To compile the project, run the following command in the terminal:
```bash
make
```
This will generate the `philo` executable.

### Execution
The program takes 4 or 5 arguments:
```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

- `number_of_philosophers`: The number of philosophers and forks.
- `time_to_die` (ms): Time after which a philosopher dies if they haven't started eating.
- `time_to_eat` (ms): Time it takes for a philosopher to eat.
- `time_to_sleep` (ms): Time a philosopher spends sleeping.
- `[number_of_times_each_philosopher_must_eat]` (optional): The simulation stops if all philosophers eat at least this many times.

### Example
```bash
./philo 5 800 200 200
```

## Resources
- [all materials and concepts for project](https://medium.com/@ruinadd/philosophers-42-guide-the-dining-philosophers-problem-893a24bc0fe2)
- [keys concepts](https://42-fran-byte-f94097.gitlab.io/docs/philosophers/philosophers-approach-en/#/)
- [tester and visualizer](https://rom98759.github.io/Philosophers-visualizer/)

### AI Usage
AI (Gemini CLI) was used during this project for the following tasks:
- **Testing and Validation**: Automated stress testing with various edge cases (1 philosopher, high number of philosophers).
- **Debugging**: Analysis of memory leaks using Valgrind logs.
- **Documentation**: Assistance in drafting this README according to subject requirements.
