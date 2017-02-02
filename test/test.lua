local lp = require("lpython")
local py = lp.builtins()
local py_globals = lp.globals()
local gc = lp.import("gc")
local np = lp.import("numpy")

local torch = require("torch")

local t = torch.rand(4,4)

local try_resize = function(t)
	t:resize(t:size(1)+1, t:size(2)+1)
	return t
end

print("Creating npy array")
py_globals.t = t

local ok, res = pcall(try_resize, t)
if ok then
	error("You should not be able to resize this tensor")
else
	print("Unresizable tensor")
end

print("Deleting npy array")
lp.execute("del t")

local ok, res = pcall(try_resize, t)
if not ok then
	error("You should be able to resize this tensor")
else
	print("Resizable tensor")
end

print("Creating npy array t")
py_globals.t = t

print("Creating npy array t2")
py_globals.t2 = t

print("Same tensor passed twice to python")

print("Deleting npy array t2")
lp.execute("del t")

local ok, res = pcall(try_resize, t)
if ok then
	error("You should not be able to resize this tensor")
else
	print("Unresizable tensor")
end
