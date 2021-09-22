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

Example of TetherElement use. To instanciate a TetherElement you need to give its mass \f$m\f$, its volume \f$v\f$, the target length \f$l\f$ of the links
between each TetherElement and optionnally an initial state vector \f$X_0 (x_0, y_0, z_0)\f$. Then you can access to the TetherElement parameters and state,
and you can update its state by simulating a new step with a time-step \f$h\f$.

\snippet examples/core/TetherElementExample.cpp example

### Tether basics

Example of Tether use. To instanciate a Tether, you need to give the initial length \f$L\f$ of the Tether and number of TetherElement \f$n\f$
which will be used to simulate the Tether. Then you can access to the Tether parameters and you can update the state of the Tether by providing a 
time-step \f$h\f$. This method will browse the doubly linked list and to call each TetherElement step method.

\snippet examples/core/TetherExample.cpp example