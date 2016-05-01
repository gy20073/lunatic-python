package = "lpython"
version = "scm-1"

source = {
   url = "git://github.com/albanD/lunatic-python"
}

description = {
   summary = "Package to use lunatic-python inside lua.",
   detailed = [[
   ]],
   homepage = "https://github.com/albanD/lunatic-python"
}

dependencies = {
   "torch >= 7.0",
}

build = {
   type = "command",
   build_command = [[cmake -E make_directory build && cd build && cmake .. -DLUALIB=$(LUALIB) -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH="$(LUA_BINDIR)/.." -DCMAKE_INSTALL_PREFIX="$(PREFIX)" && $(MAKE)]],
   install_command = "cd build && $(MAKE) install"
}