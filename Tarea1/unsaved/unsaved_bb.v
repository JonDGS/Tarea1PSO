
module unsaved (
	clk_clk,
	reset_reset_n,
	pio_display_0_external_connection_export,
	pio_display_1_external_connection_export,
	pio_display_2_external_connection_export,
	pio_display_4_external_connection_export,
	pio_display_5_external_connection_export,
	pio_display_3_external_connection_export,
	pio_sw_selector_external_connection_export,
	pio_sw_init_external_connection_export,
	pio_sw_stop_external_connection_export);	

	input		clk_clk;
	input		reset_reset_n;
	output	[7:0]	pio_display_0_external_connection_export;
	output	[7:0]	pio_display_1_external_connection_export;
	output	[7:0]	pio_display_2_external_connection_export;
	output	[7:0]	pio_display_4_external_connection_export;
	output	[7:0]	pio_display_5_external_connection_export;
	output	[7:0]	pio_display_3_external_connection_export;
	input	[1:0]	pio_sw_selector_external_connection_export;
	input		pio_sw_init_external_connection_export;
	input		pio_sw_stop_external_connection_export;
endmodule
