--****** VHDL Design file for a Binary to Seven Segment Driver ***
library IEEE;
use IEEE.std_logic_1164.all;

Entity Pattern_2 is 
	port(Data_in: in  STD_LOGIC_VECTOR (3 downto 0);
	     LED: out STD_LOGIC_VECTOR (6 downto 0));
End Pattern_2;

--****** This Case statement is very close to a truth table ***

Architecture Structure of Pattern_2 is
Begin
	Process(Data_in)
	Begin
		Case Data_in is
		--  A zero turns that Segment 0n and a 1 turns it off
		--   comment       Segment"6543210"  Low Active LED's
			
			when "0000" => LED <= "1011111";
			when "0001" => LED <= "1111110";
			when "0010" => LED <= "1111101";
			when "0011" => LED <= "0111111";
			
			when "0100" => LED <= "1101111";
			when "0101" => LED <= "1110111";
			when "0110" => LED <= "1111011";
			when "0111" => LED <= "0111111";
			
			when "1000" => LED <= "1011111";
			when "1001" => LED <= "1111110";
			when "1010" => LED <= "1111101";
			when "1011" => LED <= "0111111";
			
			when "1100" => LED <= "1101111";
			when "1101" => LED <= "1110111";
			when "1110" => LED <= "1111011";
			when "1111" => LED <= "0111111";
			
			when others => LED <= "0111111";--this should never occur
		End Case;
	End process;
End Structure;
