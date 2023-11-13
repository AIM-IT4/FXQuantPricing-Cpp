# FX Derivative Pricing Models

This repository contains implementations of various financial models used to price FX derivatives. Each model captures different aspects of market behavior and mathematics to value financial derivatives accurately.

## Models Included

- `BlackScholes.cpp`: Implementation of the Black-Scholes model for European options.
- `FiniteDiffMethod.cpp`: Finite difference method for options pricing using numerical solutions to PDEs.
- `MonteCarlo.cpp`: Monte Carlo simulation for options pricing under stochastic processes.
- `QuadratureMethod.cpp`: Numerical integration using quadrature methods to price options.

## Getting Started

To run these models, you will need a C++ compiler that supports C++11 or later. The code has been tested with GCC and Clang.

### Prerequisites

- C++ compiler
- Make (optional for building)

### Building the Code

To build a specific model, you can use the following command in the terminal:

```bash
g++ -o ModelName ModelName.cpp -std=c++11
