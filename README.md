# DataCruncher
**DataCruncher** is an (hopefully) easy to use c++ implementation for processesing array data.

[![Build Status](https://travis-ci.org/gitdev1234/DataCruncher.svg?branch=master)](https://travis-ci.org/gitdev1234/DataCruncher)

The DataCruncher project consist out of two main parts:
1. VectorData class
2. DataCruncher class

VectorData is an subclass of `std::Vector<double>` with additional arithmetical operators and a maximum and minimum value. When using the arithmetical operators VectorData provides the functionality to keep the data within the min-max-range.

DataCruncher is class which contains an instance of VectorData and provides functions to process the data within this VectorData-object. 
Additionally the DataCruncher class provides functions for loading and saving the data from text or binary files.

## Testing
The datacruncher project is tested with the c++ header-only unit-testing framework "catch" (https://github.com/philsquared/Catch).

The test-documentation can be found within the [**docs**](https://github.com/gitdev1234/DataCruncher/tree/master/DataCruncher/docs) folder.
The test-code can be found within the [**test**](https://github.com/gitdev1234/DataCruncher/tree/master/DataCruncher/test) folder.

## Programming style
* == !Attention! Please note that this project is developed as a C++ - beginner - project. Therefore the design, syntax and the programming style might not be perfect. == *

The code of this project is based on a styleguide which can be found within the [**docs**](https://github.com/gitdev1234/DataCruncher/tree/master/DataCruncher/docs) folder.
