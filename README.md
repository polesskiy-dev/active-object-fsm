# active-object-fsm
Minimalistic implementation of Active Object pattern + FSM for embedded systems.

## Initialization

	$ git submodule init && git submodule update
	$ make # compile to bin/

## Documentation

[Doxygen docs](https://polesskiy-dev.github.io/active-object-fsm/)

## Examples

[Blinky: simple LED on/off demo](./examples/simple-blinky-fsm/README.md)

TODO: make naming conventions e.g.:

- types
    - CAPITAL_CASE_T for template types
    - CAPITAL_CASE for enums
    - CAPITAL_CASE for typedefs (???)
    - CAPITAL_CASE for #define
- functions
    - MODULE_PascalCase for module public functions
    - camelCase for module private functions
- variables
    - MODULE_camelCase for module global variables
    - camelCase for local variables

