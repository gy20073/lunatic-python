local lp = require("lpython")
local py_glob = lp.globals()
local gc = lp.import("gc")

lp.execute([[def fn(a, b=2):
	print("type", type(b))
	print("args", a, b)]])

local t = {b=1}
local kw = lp.kw(t)
t = nil
collectgarbage()
collectgarbage()

print(kw)
py_glob.fn(2, kw)
py_glob.fn(2, kw)

kw = nil
collectgarbage()
collectgarbage()

py_glob.fn(3)

gc.collect()
gc.collect()

py_glob.fn(4)

print("done")

local t = {b=1}
t[{}] = 3
local kw = lp.kw(t)

print("Trying to pass the following as keyword, should fail")
print(kw)
py_glob.fn(2, kw)
print("You should NEVER gget here")
