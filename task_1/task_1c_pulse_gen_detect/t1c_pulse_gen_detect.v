// AstroTinker Bot : Task 1C : Pulse Generator and Detector
/*
Instructions
-------------------
Students are not allowed to make any changes in the Module declaration.

This file is used to design a module which will generate a 10us pulse and detect incoming pulse signal.

Recommended Quartus Version : 20.1
The submitted project file must be 20.1 compatible as the evaluation will be done on Quartus Prime Lite 20.1.

Warning: The error due to compatibility will not be entertained.
-------------------
*/

// t1c_pulse_gen_detect
//Inputs : clk_50M, reset, echo_rx
//Output : trigger, distance, pulses, state

// module declaration
module t1c_pulse_gen_detect (
    input clk_50M, reset, echo_rx,
    output reg trigger, out,
    output reg [21:0] pulses,
    output reg [1:0] state
);

initial begin
    trigger = 0; out = 0; pulses = 0; state = 0;
end


//////////////////DO NOT MAKE ANY CHANGES ABOVE THIS LINE//////////////////

/*
Add your logic here
*/

reg [9:0] counter = 10'b0000000000;
reg [15:0] loop = 16'b0;
always @ (posedge clk_50M) begin
	if (reset) begin
		trigger <= 1'b0;
		
		out <= 1'b0;
		pulses <= 22'b0;
		state <= 2'b0;
		counter <= 10'b0; // Reset the counter
		loop <= 16'b0;
	end
	else if (counter <= 10'b0000110001) begin       //delay for 1 us       counter comes here
		trigger <= 1'b0;
		counter <= counter + 10'b0000000001;
	end
	else if (counter <= 10'b1000100101) begin       //generate a 10 us trigger
		trigger <= 1'b1;
		counter <= counter + 10'b0000000001;
	end
	else if (counter > 10'b1000100101) begin
		if (loop <= 16'b1100001101001111) begin
			trigger <= 1'b0;
			loop <= loop + 1'b1;
			if (echo_rx) pulses <= pulses + 1'b1;
		end
		else begin
			if (pulses == 22'b111001011100010) out <= out + 1'b1;
			trigger <= 1'b0;
			loop = 0;
			counter = 10'b0;
		end
	end
end

//////////////////DO NOT MAKE ANY CHANGES BELOW THIS LINE//////////////////

endmodule
