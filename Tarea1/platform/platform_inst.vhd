	component platform is
		port (
			clk_clk                                    : in  std_logic                    := 'X';             -- clk
			pio_display_0_external_connection_export   : out std_logic_vector(6 downto 0);                    -- export
			pio_display_1_external_connection_export   : out std_logic_vector(6 downto 0);                    -- export
			pio_display_2_external_connection_export   : out std_logic_vector(6 downto 0);                    -- export
			pio_display_3_external_connection_export   : out std_logic_vector(6 downto 0);                    -- export
			pio_display_4_external_connection_export   : out std_logic_vector(6 downto 0);                    -- export
			pio_display_5_external_connection_export   : out std_logic_vector(6 downto 0);                    -- export
			pio_sw_init_external_connection_export     : in  std_logic                    := 'X';             -- export
			pio_sw_selector_external_connection_export : in  std_logic_vector(1 downto 0) := (others => 'X'); -- export
			pio_sw_stop_external_connection_export     : in  std_logic                    := 'X';             -- export
			reset_reset_n                              : in  std_logic                    := 'X'              -- reset_n
		);
	end component platform;

	u0 : component platform
		port map (
			clk_clk                                    => CONNECTED_TO_clk_clk,                                    --                                 clk.clk
			pio_display_0_external_connection_export   => CONNECTED_TO_pio_display_0_external_connection_export,   --   pio_display_0_external_connection.export
			pio_display_1_external_connection_export   => CONNECTED_TO_pio_display_1_external_connection_export,   --   pio_display_1_external_connection.export
			pio_display_2_external_connection_export   => CONNECTED_TO_pio_display_2_external_connection_export,   --   pio_display_2_external_connection.export
			pio_display_3_external_connection_export   => CONNECTED_TO_pio_display_3_external_connection_export,   --   pio_display_3_external_connection.export
			pio_display_4_external_connection_export   => CONNECTED_TO_pio_display_4_external_connection_export,   --   pio_display_4_external_connection.export
			pio_display_5_external_connection_export   => CONNECTED_TO_pio_display_5_external_connection_export,   --   pio_display_5_external_connection.export
			pio_sw_init_external_connection_export     => CONNECTED_TO_pio_sw_init_external_connection_export,     --     pio_sw_init_external_connection.export
			pio_sw_selector_external_connection_export => CONNECTED_TO_pio_sw_selector_external_connection_export, -- pio_sw_selector_external_connection.export
			pio_sw_stop_external_connection_export     => CONNECTED_TO_pio_sw_stop_external_connection_export,     --     pio_sw_stop_external_connection.export
			reset_reset_n                              => CONNECTED_TO_reset_reset_n                               --                               reset.reset_n
		);

