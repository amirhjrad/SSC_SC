// #include "SSC.h"

// int sc_main(int argc, char **argv) {
//     sc_signal<sc_logic> clk, rst, start, done;

//     SSC UUT("SSC_ins");
//         UUT.clk(clk);
//         UUT.rst(rst);
//         UUT.start(start);
//         UUT.done(done);

//     sc_trace_file* VCDFile;
//     VCDFile = sc_create_vcd_trace_file("waveForm");
//         sc_trace(VCDFile, clk, "clk");
//         sc_trace(VCDFile, rst, "rst");
//         sc_trace(VCDFile, start, "start");
//         sc_trace(VCDFile, done, "done");
//         sc_trace(VCDFile, UUT.CT->ps, "ps");


//     start = sc_logic_0;
//     // rst = sc_logic_1;
//     sc_start(10, SC_NS);
//     int i =0;

//     while (1)
//     {
//         clk = sc_logic_1;
//         rst = sc_logic_0;
//         if(i > 100)
//             start = sc_logic_0;
//         else start = sc_logic_1;
//         sc_start(10, SC_NS);
//         clk = sc_logic_0;
//         sc_start(10, SC_NS);
//         i += 1;
//         if (done == '1'){
//             cout << "done\n";
//             break;
//         }
//     }
    
//     sc_start(10,SC_NS);
//     return 0;
// }