![CI Status](https://github.com/polesskiy-dev/active-object-fsm/actions/workflows/ci.yml/badge.svg?branch=main)
[![Documentation](https://img.shields.io/badge/docs-Doxygen-blue.svg)](https://polesskiy-dev.github.io/active-object-fsm/)
![GitHub release (with filter)](https://img.shields.io/github/v/release/polesskiy-dev/active-object-fsm)

# active-object-fsm
Minimalistic implementation of Active Object pattern + FSM for embedded systems. Static memory allocation only.

## Features
- [x] Active Object pattern (Actors) [wiki Actors](https://en.wikipedia.org/wiki/Actor_model)
- [x] Finite State Machine (Moore+Mealy) [wiki FSM](https://en.wikipedia.org/wiki/Finite-state_machine)
- [x] Transition table 
- [x] State entry/transition/exit actions
- [ ] 100% Code coverage

## Documentation

[Doxygen docs](https://polesskiy-dev.github.io/active-object-fsm/)

## Initialization

	$ git submodule init && git submodule update --remote
	$ make # compile to bin/

## Examples

[TODO: Blinky: simple LED on/off demo](./examples/simple-blinky-fsm/README.md)

[TODO: Request: retry/timeout, transition table demo](./examples/request-fsm/README.md)

[TODO: Request: retry after delay + rety/timeout, transition table demo](./examples/request-retry-fsm/README.md)

## Side notes

### Naming conventions
- file names
  - snake_case
- variables
  - MODULE_camelCase for module global variables
  - camelCase for local variables
- functions
  - MODULE_PascalCase for module public functions
  - _camelCase for module private functions
- types
  - UPPER_CASE for #define or constants
  - UPPER_CASE for enums
  - TPascalCase for typedef struct
  - PascalCase for struct

### Docs diagrams
Diagrams are generated with help of [Graphviz]() .dot engine.
To generate locally:
```
$ brew install graphviz # install Graphviz (MacOS)
$ for file in ./**/*.gv; do dot -Tsvg "$file" > "${file%.gv}.svg"; done # dot -Tsvg file.gv > file.svg  
```

### TODO: Code coverage

Based on [Codecov](https://about.codecov.io/):

[How to Set Up Codecov with C and GitHub Actions in 2022](https://about.codecov.io/blog/how-to-set-up-codecov-with-c-and-github-actions/)


