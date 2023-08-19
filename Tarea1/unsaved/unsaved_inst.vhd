	component unsaved is
		port (
			clk_clk                                    : in  std_logic                    := 'X';             -- clk
			reset_reset_n                              : in  std_logic                    := 'X';             -- reset_n
			pio_display_0_external_connection_export   : out std_logic_vector(7 downto 0);                    -- export
			pio_display_1_external_connection_export   : out std_logic_vector(7 downto 0);                    -- export
			pio_display_2_external_connection_export   : out std_logic_vector(7 downto 0);                    -- export
			pio_display_4_external_connection_export   : out std_logic_vector(7 downto 0);                    -- export
			pio_display_5_external_connection_export   : out std_logic_vector(7 downto 0);                    -- export
			pio_display_3_external_connection_export   : out std_logic_vector(7 downto 0);                    -- export
			pio_sw_selector_external_connection_export : in  std_logic_vector(1 downto 0) := (others => 'X'); -- export
			pio_sw_init_external_connection_export     : in  std_logic                    := 'X';             -- export
			pio_sw_stop_external_connection_export     : in  std_logic                    := 'X'              -- export
		);
	end component unsaved;

	u0 : component unsaved
		port map (
			clk_clk                                    => CONNECTED_TO_clk_clk,                                    --                                 clk.clk
			reset_reset_n                              => CONNECTED_TO_reset_reset_n,                              --                               reset.reset_n
			pio_display_0_external_connection_export   => CONNECTED_TO_pio_display_0_external_connection_export,   --   pio_display_0_external_connection.export
			pio_display_1_external_connection_export   => CONNECTED_TO_pio_display_1_external_connection_export,   --   pio_display_1_external_connection.export
			pio_display_2_external_connection_export   => CONNECTED_TO_pio_display_2_external_connection_export,   --   pio_display_2_external_connection.export
			pio_display_4_external_connection_export   => CONNECTED_TO_pio_display_4_external_connection_export,   --   pio_display_4_external_connection.export
			pio_display_5_external_connection_export   => CONNECTED_TO_pio_display_5_external_connection_export,   --   pio_display_5_external_connection.export
			pio_display_3_external_connection_export   => CONNECTED_TO_pio_display_3_external_connection_export,   --   pio_display_3_external_connection.export
			pio_sw_selector_external_connection_export => CONNECTED_TO_pio_sw_selector_external_connection_export, -- pio_sw_selector_external_connection.export
			pio_sw_init_external_connection_export     => CONNECTED_TO_pio_sw_init_external_connection_export,     --     pio_sw_init_external_connection.export
			pio_sw_stop_external_connection_export     => CONNECTED_TO_pio_sw_stop_external_connection_export      --     pio_sw_stop_external_connection.export
		);

