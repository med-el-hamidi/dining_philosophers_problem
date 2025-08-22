# Dining Philosophers Problem

> A pthreads + mutexes simulation of the classic Dining Philosophers problem, focusing on thread safety, deadlock avoidance, and precise timing.

![Language](https://img.shields.io/badge/C-pthread-blue)
![Build](https://img.shields.io/badge/build-make-brightgreen)
[![License](https://img.shields.io/badge/License-MIT-blue.svg)](https://github.com/med-el-hamidi/dining_philosophers_problem/blob/main/LICENSE.md)

---

## Overview
This project simulates philosophers (threads) sharing forks (mutexes). Philosophers loop through **think → eat → sleep**, and a **monitor thread** ends the simulation when:
1) a philosopher exceeds `time_to_die`, or  
2) all philosophers reach `meals_required` (if provided).

---

## Features
- POSIX threads (`pthread`) with strict mutex protection
- Dedicated print mutex for clean logs
- Per-philosopher mutex guarding `last_meal`
- Alternating fork order + staggered thinking to reduce deadlock risk
- Input validation with overflow detection
- Clean teardown (destroy mutexes, free memory)
- Single-philosopher edge case handled

---

## How It Works
- Each philosopher needs both adjacent forks (mutexes) to eat.
- `monitor` checks:
  - death condition: `now - last_meal >= time_to_die`
  - completion: everyone ate `meals_required` times (when provided)

---

## Requirements
- C compiler (GCC/Clang)
- POSIX threads (pthreads)
- Make

---

## Build
```bash
make
```
Usage
```bash
./philo number_of_philos time_to_die time_to_eat time_to_sleep [meals_required]
```
Arguments

number_of_philos — number of philosophers (and forks)

time_to_die — ms before a philosopher dies without starting to eat

time_to_eat — ms spent eating

time_to_sleep — ms spent sleeping

meals_required (optional) — stop when each philosopher ate this many times

Omit to run until a death occurs

Examples
```bash
# Run until someone dies
./philo 5 800 200 200

# Stop when each philosopher ate 7 times
./philo 5 800 200 200 7
```
