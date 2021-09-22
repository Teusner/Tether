# Tether Simulation

Welcome to the Tether documentation. This code provide classes to simulate Tether by dicretizing it into TetherElements.

## Structure of the library

This library provide TetherElement and Tether modules to simulate the Tether by discretizing it into a finit number of elements.
Tether are constitued by a doubly linked list of TetherElement such that each TetherElement own a std::shared_ptr to its neighbors.
On each TetherElement are applied its weight depending on its mass, its buoyancy depending on its volume, its hydrodynamics drag force.
The force applied on each TetherElement from its neighbors is a behavioral force based on a PID cocntroller to reach the correct
distance between each TetherElement.

## Examples

Here is some basic examples to use modules provided by this library.

### TetherElement basics

Example of TetherElement use.
\snippet examples/core/TetherExample.cpp example

### Tether basics

Example of Tether use.
\snippet examples/core/TetherExample.cpp example