import sys
import gc
import numpy as np
print "----- import lua -----"
import lua
lg = lua.globals()


print "----- lua.execute('tensor = torch.rand(2,3)') -----"
lua.execute('tensor = torch.rand(2,3)')
print "----- ndarray = lg.tensor -----"
ndarray = lg.tensor
print "----- Verify that our storage has 2 references -----"
print "----- lua.execute('print(tensor:cdata().storage.refcount)') -----"
gc.collect()
lua.execute('collectgarbage()')
lua.execute('collectgarbage()')
lua.execute('print(tensor:cdata().storage.refcount)')
print "----- print ndarray -----"
print ndarray
print "----- lua.execute('tensor[1][1] = 10') -----"
lua.execute('tensor[1][1] = 10')
print "----- print ndarray -----"
print ndarray
print "----- lua.execute('print(tensor)') -----"
lua.execute('print(tensor)')
print "----- ndarray = None -----"
ndarray = None
print ndarray
print "----- Verify that our storage has only 1 remaining reference -----"
print "----- lua.execute('print(tensor:cdata().storage.refcount)') -----"
gc.collect()
lua.execute('collectgarbage()')
lua.execute('collectgarbage()')
lua.execute('print(tensor:cdata().storage.refcount)')

print "----- ndarray = lg.tensor -----"
ndarray = lg.tensor
print "----- lua.execute('print(tensor:cdata().storage.refcount)') -----"
gc.collect()
lua.execute('collectgarbage()')
lua.execute('collectgarbage()')
lua.execute('print(tensor:cdata().storage.refcount)')
print "----- ndarray.resize(20) -----"
try:
    ndarray.resize(20)
    print("Error you should not be able to resize this array")
except Exception as e:
    print("Error message:")
    print(e)
    print("Failed as expected")
print "----- lua.execute('tensor:resize(10)') -----"
try:
    print("Error message:")
    lua.execute('tensor:resize(10)')
    print("Error you should not be able to resize this tensor")
except Exception as e:
    print(e)
    print("Failed as expected")


print "----- ndarray = None -----"
ndarray = None
print ndarray
print "----- Verify that our storage has only 1 remaining reference -----"
print "----- lua.execute('print(tensor:cdata().storage.refcount)') -----"
gc.collect()
lua.execute('collectgarbage()')
lua.execute('collectgarbage()')
lua.execute('print(tensor:cdata().storage.refcount)')
print "----- This will now work since the numpy array has been freed -----"
print "----- lua.execute('tensor:resize(10)') -----"
lua.execute('tensor:resize(10)')

print "----- finished -----"
