--****** VHDL Design file for a Binary to Seven Segment Driver ***
library IEEE;
use IEEE.std_logic_1164.all;

Entity Keyboard_7_Segment is 
port(	PS2_CLK: in  STD_LOGIC;
		PS2_DAT: in STD_LOGIC;
		CLK_7: in STD_LOGIC;
		New_Key: out STD_LOGIC; --rising a falling edge both delayed 1 clock 7 
		LED_out: out STD_LOGIC_VECTOR (6 downto 0));
End Keyboard_7_Segment;

--****** This Case statement is very close to a truth table ***

Architecture Structure of Keyboard_7_Segment is
Signal Q: STD_LOGIC_VECTOR (21 Downto 0);
Signal Make_Code : STD_LOGIC_VECTOR (7 downto 0);
Signal LED: STD_LOGIC_VECTOR (6 downto 0);
Signal Change : STD_LOGIC; 
Signal Done : STD_LOGIC;
Signal New_pulse: STD_LOGIC;
Begin



Process (PS2_Clk) --22 bit Shift Register
	BEGIN
		IF (PS2_Clk'EVENT AND PS2_Clk = '1') THEN -- Synchronous controls start here
			Q <= PS2_DAT & Q(21 DOWNTO 1); -- Right Shift
		END IF;
END PROCESS;

Process (CLK_7)
	BEGIN
		IF (CLK_7'Event AND CLK_7 = '1') THEN
			If Q(8 DOWNTO 1) = X"F0" THEN
				Done <='1';
			Else
				Done <= '0';
			End IF;
		END IF;
END PROCESS;

Process (CLK_7)
	BEGIN
		IF (CLK_7'Event AND CLK_7 = '1') THEN
			If Done= '1' THEN
				Change <='1';
			Else
				Change <= '0';
			End IF;
		END IF;
END PROCESS;

Process (New_Pulse)
	BEGIN
		IF (New_Pulse'Event AND New_Pulse = '1') THEN
			LED_out <= LED;
		END IF;
END PROCESS;
-- This outputs a pulse for 1 CLK_7 Cycle every time a new key is pressed
	New_Pulse <= ((Change XOR Done) AND (Done)); 
	
-- This flip flop delays the New_Key signal until after the 7 segment data is fully latch
-- by 1 clock 7 cycle.  Both rising and falling edges should work with this addition.	
	Process (CLK_7)
	BEGIN
		IF (CLK_7'Event AND CLK_7 = '1') THEN
			New_Key <= New_Pulse;
		END IF;
END PROCESS;

Process(Q)
Begin
Make_Code <= Q(19 downto 12);

Case Make_Code is
--  A zero turns that Segment 0n and a 1 turns it off
--   comment       Segment"6543210"  Low Active LED's

when X"1D"=> LED <= "0110101";  -- the Wkey
when X"1B"=> LED <= "1110011";  -- the S key
when X"1C"=> LED <= "0100000";   --the A key
when X"23"=> LED <= "1100000";  -- the D key
when X"32"=> LED <= "0000000";  -- the B key
when X"21"=> LED <= "0000000";  -- the C key
when X"24"=> LED <= "0000110";  -- the Ekey
when X"2B"=> LED <= "0001110";  -- the Fkey
when X"34"=> LED <= "0010000";  -- the Gkey
when X"33"=> LED <= "0001000";  -- the Hkey
when X"43"=> LED <= "0011000";  -- the Ikey
when X"3B"=> LED <= "0000000";  -- the Jkey
when X"42"=> LED <= "0001110";  -- the Kkey
when X"4B"=> LED <= "0000110";  -- the Lkey
when X"3A"=> LED <= "0001010";  -- the Mkey
when X"31"=> LED <= "0001010";  -- the Nkey
when X"44"=> LED <= "0000010";  -- the Okey
when X"4D"=> LED <= "0001100";  -- the Pkey
when X"15"=> LED <= "0011000";  -- the Qkey
when X"2D"=> LED <= "0001110";  -- the Rkey
when X"2C"=> LED <= "0000110";  -- the Tkey
when X"3C"=> LED <= "0000000";  -- the Ukey
when X"2A"=> LED <= "0000010";  -- the Vkey
when X"22"=> LED <= "0001000";  -- the Xkey
when X"35"=> LED <= "0010000";  -- the Ykey
when X"1A"=> LED <= "0000100";  -- the Zkey
when X"45"=> LED <= "0000000";  -- the 0key
when X"16"=> LED <= "0011000";  -- the 1key
when X"1E"=> LED <= "0000100";  -- the 2key
when X"26"=> LED <= "0010000";  -- the 3key
when X"25"=> LED <= "0011000";  -- the 4key
when X"2E"=> LED <= "0010010";  -- the 5key
when X"36"=> LED <= "0000010";  -- the 6key
when X"3D"=> LED <= "0011000";  -- the 7key
when X"3E"=> LED <= "0000000";  -- the 8key
when X"46"=> LED <= "0011000";  -- the 9key
when X"0E"=> LED <= "0011110";  -- the `key
when X"4E"=> LED <= "0011110";  -- the -key
when X"55"=> LED <= "0011110";  -- the =key
when X"5D"=> LED <= "0011110";  -- the \key
when X"66"=> LED <= "0011110";  -- the BKSPkey
when X"29"=> LED <= "0011110";  -- the SPACEkey
when X"0D"=> LED <= "0011110";  -- the TABkey
when X"58"=> LED <= "0011110";  -- the CAPSkey
when X"12"=> LED <= "0011110";  -- the L SHFTkey
when X"14"=> LED <= "0011110";  -- the L CTRLkey
when X"11"=> LED <= "0011110";  -- the L ALTkey
when X"59"=> LED <= "0011110";  -- the R SHFTkey
when X"5A"=> LED <= "0000110";  -- the ENTERkey
when X"76"=> LED <= "0011110";  -- the ESCkey
when X"05"=> LED <= "0011110";  -- the F1key
when X"06"=> LED <= "0011110";  -- the F2key
when X"04"=> LED <= "0011110";  -- the F3key
when X"0C"=> LED <= "0011110";  -- the F4key
when X"03"=> LED <= "0011110";  -- the F5key
when X"0B"=> LED <= "0011110";  -- the F6key
when X"83"=> LED <= "0011110";  -- the F7key
when X"0A"=> LED <= "0011110";  -- the F8key
when X"01"=> LED <= "0011110";  -- the F9key
when X"09"=> LED <= "0011110";  -- the F10key
when X"78"=> LED <= "0011110";  -- the F11key
when X"07"=> LED <= "0011110";  -- the F12key
when X"00"=> LED <= "0011110";  -- the 0key
when X"7E"=> LED <= "0011110";  -- the SCROLLkey
when X"54"=> LED <= "0011110";  -- the [key
when X"77"=> LED <= "0011110";  -- the NUMkey
when X"7C"=> LED <= "0011110";  -- the KP *key
when X"7B"=> LED <= "0011110";  -- the KP -key
when X"79"=> LED <= "0011110";  -- the KP +key
when X"71"=> LED <= "0011110";  -- the KP .key
when X"70"=> LED <= "0000000";  -- the KP 0key
when X"69"=> LED <= "0011000";  -- the KP 1key
when X"72"=> LED <= "0000100";  -- the KP 2key
when X"7A"=> LED <= "0010000";  -- the KP 3key
when X"6B"=> LED <= "0011000";  -- the KP 4key
when X"73"=> LED <= "0010010";  -- the KP 5key
when X"74"=> LED <= "0000010";  -- the KP 6key
when X"6C"=> LED <= "0011000";  -- the KP 7key
when X"75"=> LED <= "0000000";  -- the KP 8key
when X"7D"=> LED <= "0011000";  -- the KP 9key
when X"5B"=> LED <= "0011110";  -- the ]key
when X"4C"=> LED <= "0011110";  -- the ;key
when X"52"=> LED <= "0011110";  -- the 'key
when X"41"=> LED <= "0011110";  -- the ,key
when X"49"=> LED <= "0011110";  -- the .key

when others => LED <= "0111111";--For all other keys print a "-"
End Case;
End process;
End Structure;
