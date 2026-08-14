# Ghidra headless post-script: dump all decompiled functions
import os
from ghidra.app.decompiler import DecompInterface
from ghidra.util.task import ConsoleTaskMonitor

prog = currentProgram
name = prog.getName()
out = "/out/%s.c" % name
di = DecompInterface(); di.openProgram(prog)
mon = ConsoleTaskMonitor()
fm = prog.getFunctionManager()
n = 0
with open(out, "w") as f:
    for fn in fm.getFunctions(True):
        try:
            r = di.decompileFunction(fn, 120, mon)
            if r and r.decompileCompleted():
                f.write("/* === %s @ %s === */\n" % (fn.getName(), fn.getEntryPoint()))
                f.write(r.getDecompiledFunction().getC())
                f.write("\n\n"); n += 1
        except Exception as e:
            pass
print("DECOMPILED %d functions -> %s" % (n, out))
