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
- Magnum

# Magnum
To install Magnum via package manager we follow the [Getting started](https://doc.magnum.graphics/magnum/getting-started.html) page. Following **option B** we install Magnum and let CMake find it. Using MacOS we provide an essential installation guide:
```shell
brew install --HEAD mosra/magnum/corrade
brew install --HEAD mosra/magnum/magnum
```

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

- [X] Initialize the repository
- [X] Implement `Body`
- [ ] Implement the simulation
- [ ] Implement numerical integration
- [ ] Add tests
- [ ] Add visualization
