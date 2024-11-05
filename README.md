# Hack assembler

C Implementation of the Hack assembler for the Hack computing system described in nand2tetris.

## TODOS:

### Phase 1
- [x] Instruction translation module
- [x] Organize files into modules and helper functions
- [x] Write build scripts
- [x] Unit-testing library
- [x] Unit-test instruction translation module
- [x] Tokenization module
- [x] Unit-test tokenization module
- [x] Parsing module creating instructions from tokens
- [x] Unit-test parsing module
- [x] Add module to read an input file and write to an output one
- [x] Add module to read lines, parse, and translate
- [x] Test the assembler with simpler hack asm files

### Phase 2
- [x] hash-table for symbols
- [x] Unit-test hash-table
- [x] Symbol parsing phase
- [x] Unit-test symbol parsing phase
- [x] Symbol substitution phase
- [x] Test the assembler with programs written in hack asm

### Nice to have
- [x] Build script
- [x] Script to test parsing asm files
- [ ] Refactor structs and enums to use typedef
- [ ] Refactor naming
- [ ] Document main functions
- [ ] Errors should mention file line
- [ ] Produce debug output
- [ ] Colorful test outputs
- [ ] Test results for all suites in the end
- [ ] String describing assertions in case of errors

