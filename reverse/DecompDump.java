// Ghidra headless post-script: dump all decompiled functions to /out/<name>.c
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionManager;
import java.io.PrintWriter;
import java.io.File;

public class DecompDump extends GhidraScript {
    @Override
    public void run() throws Exception {
        DecompInterface di = new DecompInterface();
        di.openProgram(currentProgram);
        File out = new File("/out/" + currentProgram.getName() + ".c");
        PrintWriter pw = new PrintWriter(out);
        FunctionManager fm = currentProgram.getFunctionManager();
        int n = 0;
        for (Function f : fm.getFunctions(true)) {
            try {
                DecompileResults r = di.decompileFunction(f, 120, monitor);
                if (r != null && r.decompileCompleted()) {
                    pw.println("/* === " + f.getName() + " @ " + f.getEntryPoint() + " === */");
                    pw.println(r.getDecompiledFunction().getC());
                    pw.println();
                    n++;
                }
            } catch (Exception e) {
                // skip functions the decompiler chokes on
            }
        }
        pw.close();
        println("DECOMPILED " + n + " functions -> " + out);
    }
}
