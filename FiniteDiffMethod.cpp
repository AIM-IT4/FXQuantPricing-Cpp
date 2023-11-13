#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

// Pricing an FX derivative (European call option) using the Finite Difference Method

// Black-Scholes parameters for the FX rate
const double volatility = 0.20; // Volatility of the underlying FX rate
const double riskFreeRate = 0.05; // Domestic risk-free interest rate
const double foreignRate = 0.02; // Foreign risk-free interest rate
const double strike = 100.0; // Strike price of the option
const double maturity = 1.0; // Time to maturity in years

// Grid parameters
const int assetPriceSteps = 200; // Number of asset price steps
const int timeSteps = 100; // Number of time steps
const double maxAssetPrice = 200.0; // Maximum asset price considered
const double minAssetPrice = 0.0; // Minimum asset price considered
const double dS = (maxAssetPrice - minAssetPrice) / assetPriceSteps;
const double dt = maturity / timeSteps;

// Finite Difference Method
std::vector<double> FiniteDifferenceMethod() {
    std::vector<double> prices(assetPriceSteps + 1);
    std::vector<double> oldValues(assetPriceSteps + 1);
    std::vector<double> newValues(assetPriceSteps + 1);

    // Set up the initial conditions for the call option payoff
    for (int i = 0; i <= assetPriceSteps; ++i) {
        prices[i] = i * dS;
        oldValues[i] = std::max(0.0, prices[i] - strike);
    }

    // Time-stepping
    for (int j = 1; j <= timeSteps; ++j) {
        // Boundary conditions
        newValues[0] = 0; // Option is worthless when asset price is 0
        newValues[assetPriceSteps] = maxAssetPrice - strike * exp(-riskFreeRate * (maturity - j * dt)); // Linear payoff minus discounted strike

        for (int i = 1; i < assetPriceSteps; ++i) {
            // Compute the finite differences
            double delta = (oldValues[i + 1] - oldValues[i - 1]) / (2 * dS);
            double gamma = (oldValues[i + 1] - 2 * oldValues[i] + oldValues[i - 1]) / (dS * dS);

            // Apply the explicit finite difference approximation for the Black-Scholes PDE
            newValues[i] = oldValues[i] + dt * (0.5 * volatility * volatility * prices[i] * prices[i] * gamma
                                                 + (riskFreeRate - foreignRate) * prices[i] * delta
                                                 - riskFreeRate * oldValues[i]);
        }

        oldValues = newValues;
    }

    return newValues;
}

int main() {
    std::vector<double> optionPrices = FiniteDifferenceMethod();

    // Output the option prices
    for (int i = 0; i <= assetPriceSteps; ++i) {
        std::cout << "Asset Price " << i * dS << ", Option Price: " << optionPrices[i] << std::endl;
    }

    return 0;
}
