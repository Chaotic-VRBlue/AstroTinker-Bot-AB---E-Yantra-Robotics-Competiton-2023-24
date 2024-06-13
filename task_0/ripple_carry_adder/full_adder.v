// Verilog code for Full Adder
// Define Full Adder module
module full_adder (
    input a, b, cin, // Define input ports a, b and c_in
    output sum , c_out // Define output ports sum and c_out
);

assign sum = a ^ b ^ cin; // Define Sum logic
assign c_out = ((a & b) | (cin & (a ^ b))); // Define Carry_out logic

endmodule 