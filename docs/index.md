# Tether Simulation

Welcome to the tether::Tether documentation. This code provide classes to simulate tether::Tether by dicretizing it into tether::TetherElement.

## Structure of the library

This library provide tether::TetherElement and tether::Tether modules to simulate the tether::Tether by discretizing it into a finit number of elements.
Tether are constitued by a doubly linked list of tether::TetherElement such that each tether::TetherElement own a std::shared_ptr to its neighbors.
On each tether::TetherElement are applied its weight depending on its mass, its buoyancy depending on its volume, its hydrodynamics drag force.
The force applied on each tether::TetherElement from its neighbors is a behavioral force based on a PID cocntroller to reach the correct
distance between each tether::TetherElement.

## Examples

Here is some basic examples to use modules provided by this library.

### TetherElement basics

Example of tether::TetherElement use. To instanciate a tether::TetherElement you need to give its mass \f$m\f$, its volume \f$v\f$, the target length \f$l\f$ of the links
between each tether::TetherElement and optionnally an initial state vector \f$X_0 (x_0, y_0, z_0)\f$. Then you can access to the tether::TetherElement parameters and state,
and you can update its state by simulating a new step with a time-step \f$h\f$.

\snippet examples/core/TetherElementExample.cpp example

### Tether basics

Example of tether::Tether use. To instanciate a tether::Tether, you need to give the initial length \f$L\f$ of the tether::Tether and number of tether::TetherElement \f$n\f$
which will be used to simulate the tether::Tether. Then you can access to the tether::Tether parameters and you can update the state of the tether::Tether by providing a 
time-step \f$h\f$. This method will browse the doubly linked list and to call each tether::TetherElement step method.

\snippet examples/core/TetherExample.cpp example