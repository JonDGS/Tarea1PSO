module cronometro 
(
		input  logic       clk,                                    //                                 clk.clk
		output logic [6:0] display0,   //   pio_display_0_external_connection.export
		output logic [6:0] display1,   //   pio_display_1_external_connection.export
		output logic [6:0] display2,   //   pio_display_2_external_connection.export
		output logic [6:0] display3,   //   pio_display_3_external_connection.export
		output logic [6:0] display4,   //   pio_display_4_external_connection.export
		output logic [6:0] display5,   //   pio_display_5_external_connection.export
		input  logic       init,     //     pio_sw_init_external_connection.export
		input  logic [1:0] selector, // pio_sw_selector_external_connection.export
		input  logic       stop,     //     pio_sw_stop_external_connection.export
		input  logic      reset//                               reset.reset_n
	);
	
	
	platform plat (
	
		.clk_clk(clk),                                    //                                 clk.clk
		.pio_display_0_external_connection_export(display0),   //   pio_display_0_external_connection.export
		.pio_display_1_external_connection_export(display1),   //   pio_display_1_external_connection.export
		.pio_display_2_external_connection_export(display2),   //   pio_display_2_external_connection.export
		.pio_display_3_external_connection_export(display3),   //   pio_display_3_external_connection.export
		.pio_display_4_external_connection_export(display4),   //   pio_display_4_external_connection.export
		.pio_display_5_external_connection_export(display5),   //   pio_display_5_external_connection.export
		.pio_sw_init_external_connection_export(!init),     //     pio_sw_init_external_connection.export
		.pio_sw_selector_external_connection_export(selector), // pio_sw_selector_external_connection.export
		.pio_sw_stop_external_connection_export(!stop),     //     pio_sw_stop_external_connection.export
		.reset_reset_n(reset)    
	
	);
	
	
	
	
endmodule 

