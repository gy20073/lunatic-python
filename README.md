#### Original Lunatic Python

The original Lunatic Python code can be found on the 'net at http://labix.org/lunatic-python.

This is a fork of a GitHub version by bastibe which is an updated version of the original lunatic-python that works with Python 2.7 and Lua 5.1 that can be found [here](https://github.com/bastibe/lunatic-python)

It adds the possibility to easily exchange [numpy ndarray](http://docs.scipy.org/doc/numpy/reference/generated/numpy.ndarray.html) and [torch tensors](https://github.com/torch/torch7/blob/master/doc/tensor.md) on top of the basic Lunatic Python possibilities.

#### Installing
You need to install [torch](http://torch.ch/docs/getting-started.html#_) and numpy.
Then you can just install with: `python setup.py install`

#### Python `lua` module
The module is composed of a basic interface:
* `lua.execute(code_string)` that execute the string given in the lua space
* `lua.eval(code_string)` that execute the string given in the lua space and returns the value
* `lua.globals()` returns a pointer to all the globals of the lua space. Can be used to access or add elements to the lua global table (`_G`)
* `lua.require(module_string)` performs a lua require on the given module and returns the return value of the require
* `lua.toDict(table)` convert the given lua table (represented as a LuaObject see below) into a python dictionnary
* `lua.toTable(dict)` convert the given python dictionnary into a lua table (represented as a LuaObject see below)

#### Lua `python` module
Not supported right now since it has been removed in the original github repo.
Will look into adding it again soon.

#### Data type correspondance

| Lua | Python |
| --- | ------ |
| nil | None |
| string | string |
| number | number |
| lua bool | python bool |
| torch DoubleTensor | double ndarray |
| torch FloatTensor | float ndarray |
| torch {Long, Int, Byte}Tensor | (int64, int32, int8) ndarray |
| Other | LuaObject* |

* LuaObject is a generic python wrapper for any lua object. It can contain any lua userdata, lightuserdata, table, function or thread object. It allows:
    * printing equivalent to a print in the lua space
    * call as a regular function if the underlying lua object is a function (warning: you cannot use the `:` syntactic sugar from lua, you need to do `obj.func(obj.func, args)`)
    * get and set attributes if the underlying lua object supports it
    * you can iterate on it if the underlying lua object supports it (tables)
    * you can use the `lua.toDict()` and `lua.toTable()` functions to change between a python dictionnary and a lua table (that is handled as a LuaObject)

#### Tests

The following tests script are provided:
* `test.py` shows the main features for standard types, table/dict correspondances and tensor/ndarray correspondances.
* `arrayToTensorTest.py` tests if the tensor created from numpy arrays behave as expected: they do share the same data, the ndarray is properly refcounted, you can never resize the tensor and the ndarray can only be resized after the tensor has been freed.
* `tensorToArray.py` tests if the ndarray created from torch tensors behave as expected: they do share the same data, the storage associated with the original tensor is properly refcounted, you can never resize the ndarray and the tensor and the storage can only be resized after the ndarray has been freed.
