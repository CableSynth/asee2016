--****** VHDL Design file for a Binary to Seven Segment Driver ***
library IEEE;
use IEEE.std_logic_1164.all;

Entity Seven_Seg_2_Binary is 
	port(Seven_Seg_in: in  STD_LOGIC_VECTOR (6 downto 0);
	     Binary_out: out STD_LOGIC_VECTOR (3 downto 0));
End Seven_Seg_2_Binary;

--****** This Case statement is very close to a truth table ***

Architecture Structure of Seven_Seg_2_Binary is
Begin
	Process(Seven_Seg_in)
	Begin
		Case Seven_Seg_in is
		--  This is ROM will take in 7 Segment Data and output its Binary number
		--  only the numbers 0-9 and A-F work  all other values are set to return 0
			
			when "1000000" => Binary_out <= "0000"; -- Zero 0
			when "1111001" => Binary_out <= "0001"; -- 1
			when "0100100" => Binary_out <= "0010"; -- 2
			when "0110000" => Binary_out <= "0011"; -- 3
			
			when "0011001" => Binary_out <= "0100";
			when "0010010" => Binary_out <= "0101";
			when "0000010" => Binary_out <= "0110";
			when "1111000" => Binary_out <= "0111";
			
			when "0000000" => Binary_out <= "1000";
			when "0011000" => Binary_out <= "1001";
			when "0001000" => Binary_out <= "1010";
			when "0000011" => Binary_out <= "1011";
			
			when "1000110" => Binary_out <= "1100";
			when "0100001" => Binary_out <= "1101";
			when "0000110" => Binary_out <= "1110";
			when "0001110" => Binary_out <= "1111";
			
			when others => Binary_out <= "0000";--this will occur for all kinds of input values
		End Case;
	End process;
End Structure;
