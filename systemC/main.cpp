#include "TB.h"

int sc_main(int argc, char **argv) {
    TB testbench("test_bench_inst");

    sc_trace_file* VCDFile;
    VCDFile = sc_create_vcd_trace_file("waveForm");
        sc_trace(VCDFile, testbench.clk, "clk");
        sc_trace(VCDFile, testbench.rst, "rst");
        sc_trace(VCDFile, testbench.start, "start");
        sc_trace(VCDFile, testbench.done, "done");
        sc_trace(VCDFile, testbench.UUT->CT->ps, "ps");
    sc_start(305000, SC_NS);
    testbench.UUT->DP->RF->memdump();
    return 0;
}