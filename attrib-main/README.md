# Attrib Command

Displays, sets, or removes attributes assigned to files or directories. If used without parameters, attrib displays attributes of all files in the current directory.

## Syntax & Parameters
See [documentation](docs/attrib.md).

## License
Licensed under the MIT LIcense, See [LICENSE](LICENSE) file.

## Implementation Status

### functions

* [x] (no arguments) Display file attributes
* [x] (+*) Sets an attribute.
* [x] (-*) Clears an attribute.
* [x] (/S) Processes matching files in the current folder and all subfolders.
* [x] (/D) Processes folders as well.
* [ ] (/L) Work on the attributes of the Symbolic Link versus the target of the Symbolic Link.
