// AstroTinker Bot : Task 2A : UART Transmitter
/*
Instructions
-------------------
Students are not allowed to make any changes in the Module declaration.

This file is used to generate UART Tx data packet to transmit the messages based on the input data.

Recommended Quartus Version : 20.1
The submitted project file must be 20.1 compatible as the evaluation will be done on Quartus Prime Lite 20.1.

Warning: The error due to compatibility will not be entertained.
-------------------
*/

/*
Module UART Transmitter

Input:  clk_50M - 50 MHz clock
        data    - 8-bit data line to transmit
Output: tx      - UART Transmission Line
*/

// module declaration
module uart_tx(
    input  clk_50M,
    input  [7:0] data,
    output reg tx
);

//////////////////DO NOT MAKE ANY CHANGES ABOVE THIS LINE//////////////////

initial begin
	 tx = 1;
end

////////// Add your code here ///////////////////

reg [8:0] counter = 9'b000000000;
reg [3:0] bit = 4'b0000;
always @ (posedge clk_50M) begin
	if(!data) tx <= 1'b1;
	else begin
		if(counter <= 9'b110110010 && bit == 4'b0000) begin        //  && counter != 9'b000000000
			tx <= 1'b0;
			counter <= counter + 1'b1;
			if (counter == 9'b110110001) begin
				bit <= 4'b0001;
				counter <= 9'b000000000;
			end
		end
		else if(counter <= 9'b110110010 && bit == 4'b0001) begin
			tx <= data[0];
			counter <= counter + 1'b1;
			if (counter == 9'b110110001) begin
				bit <= bit + 1'b1;
				counter <= 9'b000000000;
			end
		end
		else if(counter <= 9'b110110010 && bit == 4'b0010) begin
			tx <= data[1];
			counter <= counter + 1'b1;
			if (counter == 9'b110110001) begin
				bit <= bit + 1'b1;
				counter <= 9'b000000000;
			end
		end
		else if(counter <= 9'b110110010 && bit == 4'b0011) begin
			tx <= data[2];
			counter <= counter + 1'b1;
			if (counter == 9'b110110001) begin
				bit <= bit + 1'b1;
				counter <= 9'b000000000;
			end
		end
		else if(counter <= 9'b110110010 && bit == 4'b0100) begin
			tx <= data[3];
			counter <= counter + 1'b1;
			if (counter == 9'b110110001) begin
				bit <= bit + 1'b1;
				counter <= 9'b000000000;
			end
		end
		else if(counter <= 9'b110110010 && bit == 4'b0101) begin
			tx <= data[4];
			counter <= counter + 1'b1;
			if (counter == 9'b110110001) begin
				bit <= bit + 1'b1;
				counter <= 9'b000000000;
			end
		end
		else if(counter <= 9'b110110010 && bit == 4'b0110) begin
			tx <= data[5];
			counter <= counter + 1'b1;
			if (counter == 9'b110110001) begin
				bit <= bit + 1'b1;
				counter <= 9'b000000000;
			end
		end
		else if(counter <= 9'b110110010 && bit == 4'b0111) begin
			tx <= data[6];
			counter <= counter + 1'b1;
			if (counter == 9'b110110001) begin
				bit <= bit + 1'b1;
				counter <= 9'b000000000;
			end
		end
		else if(counter <= 9'b110110010 && bit == 4'b1000) begin
			tx <= data[7];
			counter <= counter + 1'b1;
			if (counter == 9'b110110001) begin
				bit <= bit + 1'b1;
				counter <= 9'b000000000;
			end
		end
		else begin
			tx <= 1'b1;
			counter <= counter + 1'b1;
			if (counter == 9'b110110001) begin
				bit = 4'b0000;
				counter <= 9'b000000000;
				if(counter == 9'b000000000) tx <= 1'b0;
			end
		end
	end
end

//////////////////DO NOT MAKE ANY CHANGES BELOW THIS LINE//////////////////

endmodule