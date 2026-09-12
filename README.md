# Nbody-project
Numeric simulation of the n-body problem (developed mostly in C++20).

## Description
The project consists of simulating the time evolution of a system of bodies interacting through gravitational interactions. 

For each body the resulting force is calculaed as:

$$
\mathbf{F}_i = G \sum_{j \neq i} \frac{m_i m_j}{r_{ij}^3}(\mathbf{r}_j-\mathbf{r}_i)
$$

## Features
- Simulation of $N$ bodies
- Gravitational interactions
- Numerical integration
- Visualisation of the trajectories

# Requirements
- C++20
- CMake

# Build
```shell
cmake -S . -B build -G "Ninja Multi-Config"
cmake --build build --config Debug
cmake --build build --config Debug --target test
cmake --build build --config Release 
cmake --build build --config Release --target test
```

# Run
./build/<executable>

# Project structure
```text
.
├── apps/
├── include/
├── src/
├── tests/
├── .clang-format
├── .gitignore
├── CMakeLists.txt
├── LICENSE
└── README.md
```

# To-do list

- [ ] Initialize the repository
- [ ] Implement `Body`
- [ ] Implement the simulation
- [ ] Implement numerical integration
- [ ] Add tests
- [ ] Add visualization
