import sys
import gc as gc
import numpy as np
print "----- import lua -----"
import lua
lg = lua.globals()

print "----- ndarray = np.random.rand(3,4) -----"
ndarray = np.random.rand(3,4)
print "Initial refcount: " + str(sys.getrefcount(ndarray))
print "----- lg.tensor = ndarray -----"
lg.tensor = ndarray
print "Refcount should be 2+1: " + str(sys.getrefcount(ndarray))
print "----- lua.execute('print(tensor:size())') -----"
lua.execute('print(tensor:size())')
print "----- ndarray.resize(20) -----"
try:
    ndarray.resize(20)
    print("Error you should not be able to resize this array")
except Exception as e:
    print("Message:")
    print(e)
    print("This is expected")
print "----- lua.execute('tensor:resize(20)') -----"
try:
    print("Message:")
    lua.execute('tensor:resize(20)')
    print("Error you should not be able to resize this tensor")
except Exception as e:
    print(e)
    print("This is expected")
print "----- lg.tensor = None -----"
lg.tensor = None
lua.execute('collectgarbage()')
print "Refcount should be 3-1: " + str(sys.getrefcount(ndarray))
print "----- This will now work since the tensor has been freed -----"
print "----- ndarray.resize(20) -----"
ndarray.resize(20)

print "----- finished -----"
