#### Original Lunatic Python

The original Lunatic Python code can be found on the 'net at http://labix.org/lunatic-python.

This is a fork of a GitHub version which is an updated version of lunatic-python that works with Python 2.7 and Lua 5.1 that can be found [here](https://github.com/bastibe/lunatic-python)

This fork adds the possibility to easily exchange [numpy ndarray](http://docs.scipy.org/doc/numpy/reference/generated/numpy.ndarray.html) and [torch tensors](https://github.com/torch/torch7/blob/master/doc/tensor.md) on top of the basic Lunatic Python possibilities.

Right now, this has a lot of dependencies on code from [fblualib](https://github.com/facebook/fblualib). It is planned to remove them in the future since they make it complicated to install and are way too heavy for what they are used for.

#### Installing
To install you will need some external libraries before using the setup.py script.
You need to install [torch](http://torch.ch/docs/getting-started.html#_) and numpy of course, then:

##### Ubuntu 14.04
If you use Ubuntu 14.04 you can use the 'install.sh' script to install all dependecies and the 'lua' package (tested on a vanilla install just after torch install).

##### Others
Otherwise, you need to install:
* [folly](https://github.com/facebook/folly)
* [thrift](https://github.com/facebook/fbthrift)
* [thpp](https://github.com/facebook/thpp)

And then you can install the `lua` module using the standard `setup.py`.

#### Python `lua` module
The module is composed of a basic interface:
* `lua.execute(code_string)` that execute the string given in the lua space
* `lua.eval(code_string)` that execute the string given in the lua space and returns the value
* `lua.globals()` returns a pointer to all the globals of the lua space. Can be used to access or add elements to the lua global table (`_G`)
* `lua.require(module_string)` performs a lua require on the given module and returns the return value of the require
* `lua.toDict(table)` convert the given lua table (represented as a LuaObject see below) into a python dictionnary
* `lua.toTable(dict)` convert the given python dictionnary into a lua table (represented as a LuaObject see below)

#### Data type correspondance

| Lua | Python |
| --- | ------ |
| nil | None |
| string | string |
| number | number |
| lua bool | python bool |
| torch DoubleTensor | double ndarray |
| torch FloatTensor | float ndarray |
| torch Tensor (int64, int32, int8) | (int64, int32, int8) ndarray |
| Other | LuaObject* |

* LuaObject is a generic python wrapper for any lua object. It can contain any lua userdata, lightuserdata, table, function or thread object. It allows:
* printing equivalent to a print in the lua space
* call as a regular function if the underlying lua object is a function (warning: you cannot use the `:` syntactic sugar from lua, you need to do `obj.func(obj.func, args)`)
* get and set attributes if the underlying lua object supports it
* you can iterate on it if the underlying lua object supports it (tables)
* you can use the `lua.toDict()` and `lua.toTable()` functions to change between a python dictionnary and a lua table (that is handled as a LuaObject)


#### TODO

* Preload properly all the '.so'
* Try to use directly the TH API to handle Tensors to remove dependencies on folly, thrift and thpp.

#### Notes

For the first point of the TODO, maybe create a two level library similar to what is done by [lupa](https://github.com/scoder/lupa/blob/master/lupa/__init__.py)

For the fblualib dependency, all the corresponding source and headers are in the `fblualib-*` folders. What we use from this source is:
* `PyObjectHandle` from `Utils.h`. This is just a wrapper over `PyObject`s this can be removed with some extra `Py_INCREF` calls.
* `LuaToPythonConverter` class from `LuaToPython.h`. In practice, the only thing used in this class is the `convertTensor` function used to create a numpy array from a Torch tensor.
* `NumpyArrayAllocator` and the corresponding `thpp` calls made in the `pushTensor` function in `pythoninlua.cpp`. This is the function creating a Torch tensor from a numpy array.