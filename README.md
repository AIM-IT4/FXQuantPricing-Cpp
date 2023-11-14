
# FX Derivative Pricing Models

This repository contains implementations of various FX derivative pricing models written in C++. Each model is encapsulated in its own file for modularity and ease of use.

## Models Included

- `BlackScholes.cpp`: Implementation of the Black-Scholes model for option pricing.
- `FiniteDiffMethod.cpp`: Utilizes the finite difference method to solve the Black-Scholes PDE for option pricing.
- `MonteCarlo.cpp`: A Monte Carlo simulation-based approach to pricing FX derivatives.
- `QuadratureMethod.cpp`: Prices FX derivatives using numerical integration techniques.
- `SABRHagan.cpp`: Stochastic Volatility model for pricing Vanilla FX Option 

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites

What things you need to install the software and how to install them

```
g++ compiler with C++11 support or later
make (optional for building)
```

### Installing

A step by step series of examples that tell you how to get a development environment running

Clone the repository to your local machine:

```bash
git clone https://github.com/yourusername/fx-derivative-pricing.git
cd fx-derivative-pricing
```

To compile a specific model, use the following command:

```bash
g++ -o BlackScholes BlackScholes.cpp
```

Replace `BlackScholes.cpp` with the name of the model file you wish to compile.

## Running the tests

Explain how to run the automated tests for this system.

## Usage

Provide examples on how to use the compiled programs. For example:

```bash
./BlackScholes
```

## Contributing

Please contact here: jha.8@iitj.ac.in , and the process for submitting pull requests to us.

## Authors

* **Amit Jha** - *Initial work* - [AIM-IT4](https://github.com/AIM-IT4)

See also the list of [contributors](https://github.com/yourusername/fx-derivative-pricing/contributors) who participated in this project.



## Acknowledgments

* Hat tip to anyone whose code was used
* Inspiration
* etc
