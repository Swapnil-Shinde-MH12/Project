# Monte Carlo Simulation on Barrier Option Pricing using openACC
Project Overview

Objective: To implement and accelerate a Monte Carlo simulation for pricing barrier options using OpenACC, a directive-based parallel programming model for GPU and multi-core CPU acceleration.
1. Understanding Barrier Options

Barrier options are a type of exotic option whose payoff depends on whether the underlying asset’s price reaches a certain barrier level during the option's life. Common types include:

    Knock-In Options: Become active when the barrier is breached.
    Knock-Out Options: Become void if the barrier is breached.

2. Monte Carlo Simulation for Option Pricing

Monte Carlo simulations involve generating a large number of random paths for the underlying asset's price and computing the average payoff to estimate the option price.
3. Setting Up the Project
3.1. Prerequisites

    Knowledge of Financial Mathematics: Understanding of option pricing and Monte Carlo methods.
    Programming Skills: Familiarity with C/C++/Fortran.
    OpenACC: Basic understanding of OpenACC directives and GPU programming.

3.2. Tools Required

    Compiler: A compiler that supports OpenACC (e.g., NVIDIA HPC SDK, PGI Compilers).
    Development Environment: A GPU-enabled workstation or cloud instance with OpenACC support.
