print "----- import lua -----"
import lua
import numpy as np
print "----- lg = lua.globals() -----"
lg = lua.globals()
print "lg:", lg
print "lg._G:", lg._G
print "lg['_G']:", lg['_G']
print "----- lg.foo = \"bar\" -----"
lg.foo = 'bar'
print "----- lg.tmp = [] -----"
lg.tmp = []
print "----- print lg.tmp -----"
print lg.tmp
print "----- lua.execute(\"xxx = {1,2,3,foo={4,5}}\") -----"
lua.execute("xxx = {1,2,3,foo={4,5}}")
print "----- print lg.xxx[1] -----"
print lg.xxx[1]
print "----- print lg.xxx[2] -----"
print lg.xxx[2]
print "----- print lg.xxx[3] -----"
print lg.xxx[3]
print "----- print lg.xxx['foo'][1] -----"
print lg.xxx['foo'][1]
print "lua.require =", lua.require
try:
    lua.require("foo")
except:
    print "lua.require('foo') raised an exception"

print """----- pythonDict = {"coucou": 1, "truc": 2} -----"""
pythonDict = {"coucou": 1, "truc": 2}
print(pythonDict)
print "----- luaTable = lua.toTable(pythonDict) -----"
luaTable = lua.toTable(pythonDict)
print(luaTable)
print "----- lg.luaTable = luaTable -----"
lg.luaTable = luaTable
print '----- lua.execute("""for u,v in pairs(luaTable) do print("key: "..u.."/val: "..v) end""") -----'
lua.execute("""for u,v in pairs(luaTable) do print("key: '"..u.."' val: '"..v.."'") end""")
print "----- pythonDict = lua.toDict(lg.luaTable) -----"
pythonDict = lua.toDict(lg.luaTable)
print(pythonDict)

print "----- torch set default tensor -----"
lua.execute('torch.setdefaulttensortype("torch.FloatTensor")')
print "----- lua.execute('tensor = torch.rand(2,3)') -----"
lua.execute('tensor = torch.rand(2,3)')
print "----- print lg.tensor.shape -----"
print lg.tensor.shape
print "----- print lg.tensor -----"
print lg.tensor
print "----- lua.execute('tensor[1][1] = 10') -----"
lua.execute('tensor[1][1] = 10')
print "----- print lg.tensor -----"
print lg.tensor
print "----- lua.execute('print(tensor)') -----"
lua.execute('print(tensor)')

print "----- nparray = np.random.rand(3,4) -----"
nparray = np.random.rand(3,4)
print "----- print nparray.shape -----"
print nparray.shape
print "----- print nparray -----"
print nparray
print "----- lg.nparray = nparray -----"
lg.nparray = nparray
print "----- lua.execute('print(nparray:size())') -----"
lua.execute('print(nparray:size())')
print "----- lua.execute('print(nparray)') -----"
lua.execute('print(nparray)')

print "----- finished -----"
