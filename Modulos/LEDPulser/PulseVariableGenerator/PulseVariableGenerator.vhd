----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    17:03:06 07/30/2016 
-- Design Name: 
-- Module Name:    PulseVariableGenerator - Behavioral 
-- Project Name: 
-- Target Devices: 
-- Tool versions: 
-- Description: 
--
-- Dependencies: 
--
-- Revision: 
-- Revision 0.01 - File Created
-- Additional Comments: 

----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.numeric_std.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity PulseVariableGenerator is
    Port ( clk : in  STD_LOGIC;
			  value : in	STD_LOGIC_VECTOR(7 DOWNTO 0);
           Pulse : out  STD_LOGIC;
			  A : in  STD_LOGIC;
			  B : out  STD_LOGIC;
			  AB : out  STD_LOGIC;
			  Trigger : out  STD_LOGIC);
			  
end PulseVariableGenerator;

architecture Behavioral of PulseVariableGenerator is

	constant duty        : integer := 1;				-- Time of pulse in high state 25 ns
	signal tmp_clk 		: std_logic := '0';
	constant duty_T        : integer := 2;				-- (3) Time of pulse in high state 1 us
	signal tmp_clk_T 		: std_logic := '0';
	signal SignalPulse 		: std_logic := '0';
	signal decimal_value : integer := 0;
	signal min_freq		: integer := 999311;				-- count for a frequency of 100 Hz
	signal max_count 	   : integer := 0;  		-- 58783 for a signal of 1700 Hz
		
begin

-- Generation of a pulse with variable frequency 

decimal_value <= to_integer(unsigned(value));
max_count <= min_freq / (decimal_value + 1);

my_div: process (clk,tmp_clk)              
      variable div_cnt : integer := 0;   
   begin
      if (rising_edge(clk)) then 
			if (div_cnt <= duty) then
				tmp_clk <= '1';
				div_cnt := div_cnt + 1;
         elsif (div_cnt = MAX_COUNT) then 
            tmp_clk <= not tmp_clk; 
            div_cnt := 0; 
         else
				tmp_clk <= '0';
            div_cnt := div_cnt + 1; 
         end if; 
      end if; 
      Trigger <= tmp_clk; 
   end process my_div; 



-- Generation of a trigger signal

my_trigger: process (clk,tmp_clk)              
      variable div_cnt_T : integer := 0;   
   begin
      if (rising_edge(clk)) then 
			if (div_cnt_T <= duty_T) then
				tmp_clk_T <= '1';
				div_cnt_T := div_cnt_T + 1;
         elsif (div_cnt_T = MAX_COUNT) then 
            tmp_clk_T <= not tmp_clk_T; 
            div_cnt_T := 0; 
         else
				tmp_clk_T <= '0';
            div_cnt_T := div_cnt_T + 1; 
         end if; 
      end if; 
      SignalPulse <= tmp_clk_T; 
   end process my_trigger; 
	
AB <= A and SignalPulse;
B <= SignalPulse;
end Behavioral;