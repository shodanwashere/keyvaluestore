# KeyValueStore
A library based on Amazon's Key-value Store, written as a project for the **Distributed Systems** curricular unit of the school year of 2022/2023, Bachelor's Degree in Computer Engineering at the Faculty of Sciences of the University of Lisbon (Faculdade de Ciências da Universidade de Lisboa)
## Authors
- Nuno Dias, fc56330 (me)
- Bruna Santos, fc56328
- Pedro Pinto, fc56369
## Updates
- **0.1** (October 5th, 18:04) :: Finished the `data`, `entry` and `tree` modules, all of which pass all the tests supplied by the teachers

## Building and using
Integrate this library into your own project if you want and write your own makefile, but if you're a **FCUL Distributed Systems teacher evaluating this** (you sneaky little man), just drop your source `test-*.c` files into the included source folder, then, from the project's root directory use:
```
$ make
```
to build all the tests. After that, you'll find all of the test binaries in the `binary` directory.

If you wish to build only a specific test, specify which one (without the `.c` extension):
```
$ make test_tree
```