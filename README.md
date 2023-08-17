![CI Status](https://github.com/polesskiy-dev/active-object-fsm/actions/workflows/ci.yml/badge.svg?branch=main)
[![Documentation](https://img.shields.io/badge/docs-Doxygen-blue.svg)](https://polesskiy-dev.github.io/active-object-fsm/)
![GitHub release (with filter)](https://img.shields.io/github/v/release/polesskiy-dev/active-object-fsm)

# active-object-fsm
Minimalistic implementation of Active Object pattern + FSM for embedded systems.

## Initialization

	$ git submodule init && git submodule update
	$ make # compile to bin/

## Documentation

[Doxygen docs](https://polesskiy-dev.github.io/active-object-fsm/)

## Examples

[Blinky: simple LED on/off demo](./examples/simple-blinky-fsm/README.md)

[Request: retry/timeout, transition table demo](./examples/request-fsm/README.md)

[Request: retry after delay + rety/timeout, transition table demo](./examples/request-retry-fsm/README.md)

## Advantages

Preprocessor templates allow strict typings and debugger suggestions, all types and enums have human-readable names, e.g. from [Request demo](./examples/request-fsm/README.md):

![types](https://raw.githubusercontent.com/polesskiy-dev/active-object-fsm/main/docs/active-object-typings.png)

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
  - UPPER_CASE_T for macros types
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
It seems that it's hard to check coverage on macros.

Based on [Codecov](https://about.codecov.io/):

[How to Set Up Codecov with C and GitHub Actions in 2022](https://about.codecov.io/blog/how-to-set-up-codecov-with-c-and-github-actions/)


