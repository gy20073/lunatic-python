#!/usr/bin/python

import ctypes
luajitlib = ctypes.CDLL("libluajit.so", mode=ctypes.RTLD_GLOBAL)
follylib = ctypes.CDLL("libfolly.so", mode=ctypes.RTLD_GLOBAL)
THlib = ctypes.CDLL("libTH.so", mode=ctypes.RTLD_GLOBAL)
luaTlib = ctypes.CDLL("libluaT.so", mode=ctypes.RTLD_GLOBAL)

import numpy as np

import lua
lua.require("torch")
lua.require("nn")
lua.execute('torch.setdefaulttensortype("torch.FloatTensor")')

lua.execute("net = nn.Sequential()")
lua.execute("net:add(nn.Linear(10,5))")
net = lua.eval("net")
print("net:")
print(net)
inp = np.ndarray(10, dtype='float32')
print("input:")
print(inp)
output = net.forward(net, inp)
print("output:")
print(output)