-- megafunction wizard: %LPM_MULT%
-- GENERATION: STANDARD
-- VERSION: WM1.0
-- MODULE: altsquare 

-- ============================================================
-- File Name: randomnumber.vhd
-- Megafunction Name(s):
-- 			altsquare
--
-- Simulation Library Files(s):
-- 			altera_mf
-- ============================================================
-- ************************************************************
-- THIS IS A WIZARD-GENERATED FILE. DO NOT EDIT THIS FILE!
--
-- 7.2 Build 207 03/18/2008 SP 3 SJ Web Edition
-- ************************************************************


--Copyright (C) 1991-2007 Altera Corporation
--Your use of Altera Corporation's design tools, logic functions 
--and other software and tools, and its AMPP partner logic 
--functions, and any output files from any of the foregoing 
--(including device programming or simulation files), and any 
--associated documentation or information are expressly subject 
--to the terms and conditions of the Altera Program License 
--Subscription Agreement, Altera MegaCore Function License 
--Agreement, or other applicable license agreement, including, 
--without limitation, that your use is for the sole purpose of 
--programming logic devices manufactured by Altera and sold by 
--Altera or its authorized distributors.  Please refer to the 
--applicable agreement for further details.


LIBRARY ieee;
USE ieee.std_logic_1164.all;

LIBRARY altera_mf;
USE altera_mf.all;

ENTITY randomnumber IS
	PORT
	(
		clock		: IN STD_LOGIC ;
		dataa		: IN STD_LOGIC_VECTOR (23 DOWNTO 0);
		ena		: IN STD_LOGIC ;
		result		: OUT STD_LOGIC_VECTOR (31 DOWNTO 0)
	);
END randomnumber;


ARCHITECTURE SYN OF randomnumber IS

	SIGNAL sub_wire0	: STD_LOGIC_VECTOR (31 DOWNTO 0);



	COMPONENT altsquare
	GENERIC (
		data_width		: NATURAL;
		lpm_type		: STRING;
		pipeline		: NATURAL;
		representation		: STRING;
		result_alignment		: STRING;
		result_width		: NATURAL
	);
	PORT (
			ena	: IN STD_LOGIC ;
			clock	: IN STD_LOGIC ;
			data	: IN STD_LOGIC_VECTOR (23 DOWNTO 0);
			result	: OUT STD_LOGIC_VECTOR (31 DOWNTO 0)
	);
	END COMPONENT;

BEGIN
	result    <= sub_wire0(31 DOWNTO 0);

	altsquare_component : altsquare
	GENERIC MAP (
		data_width => 24,
		lpm_type => "ALTSQUARE",
		pipeline => 1,
		representation => "UNSIGNED",
		result_alignment => "MSB",
		result_width => 32
	)
	PORT MAP (
		ena => ena,
		clock => clock,
		data => dataa,
		result => sub_wire0
	);



END SYN;

-- ============================================================
-- CNX file retrieval info
-- ============================================================
-- Retrieval info: PRIVATE: AutoSizeResult NUMERIC "0"
-- Retrieval info: PRIVATE: B_isConstant NUMERIC "0"
-- Retrieval info: PRIVATE: ConstantB NUMERIC "0"
-- Retrieval info: PRIVATE: INTENDED_DEVICE_FAMILY STRING "Cyclone II"
-- Retrieval info: PRIVATE: LPM_PIPELINE NUMERIC "1"
-- Retrieval info: PRIVATE: Latency NUMERIC "1"
-- Retrieval info: PRIVATE: OptionalSum NUMERIC "0"
-- Retrieval info: PRIVATE: SYNTH_WRAPPER_GEN_POSTFIX STRING "0"
-- Retrieval info: PRIVATE: SignedMult NUMERIC "0"
-- Retrieval info: PRIVATE: USE_MULT NUMERIC "0"
-- Retrieval info: PRIVATE: ValidConstant NUMERIC "0"
-- Retrieval info: PRIVATE: WidthA NUMERIC "24"
-- Retrieval info: PRIVATE: WidthB NUMERIC "8"
-- Retrieval info: PRIVATE: WidthP NUMERIC "32"
-- Retrieval info: PRIVATE: WidthS NUMERIC "1"
-- Retrieval info: PRIVATE: aclr NUMERIC "0"
-- Retrieval info: PRIVATE: clken NUMERIC "1"
-- Retrieval info: PRIVATE: optimize NUMERIC "0"
-- Retrieval info: CONSTANT: DATA_WIDTH NUMERIC "24"
-- Retrieval info: CONSTANT: LPM_TYPE STRING "ALTSQUARE"
-- Retrieval info: CONSTANT: PIPELINE NUMERIC "1"
-- Retrieval info: CONSTANT: REPRESENTATION STRING "UNSIGNED"
-- Retrieval info: CONSTANT: RESULT_ALIGNMENT STRING "MSB"
-- Retrieval info: CONSTANT: RESULT_WIDTH NUMERIC "32"
-- Retrieval info: USED_PORT: clock 0 0 0 0 INPUT NODEFVAL clock
-- Retrieval info: USED_PORT: dataa 0 0 24 0 INPUT NODEFVAL dataa[23..0]
-- Retrieval info: USED_PORT: ena 0 0 0 0 INPUT NODEFVAL ena
-- Retrieval info: USED_PORT: result 0 0 32 0 OUTPUT NODEFVAL result[31..0]
-- Retrieval info: CONNECT: @data 0 0 24 0 dataa 0 0 24 0
-- Retrieval info: CONNECT: result 0 0 32 0 @result 0 0 32 0
-- Retrieval info: CONNECT: @clock 0 0 0 0 clock 0 0 0 0
-- Retrieval info: CONNECT: @ena 0 0 0 0 ena 0 0 0 0
-- Retrieval info: LIBRARY: altera_mf altera_mf.altera_mf_components.all
-- Retrieval info: GEN_FILE: TYPE_NORMAL randomnumber.vhd TRUE
-- Retrieval info: GEN_FILE: TYPE_NORMAL randomnumber.inc TRUE
-- Retrieval info: GEN_FILE: TYPE_NORMAL randomnumber.cmp FALSE
-- Retrieval info: GEN_FILE: TYPE_NORMAL randomnumber.bsf TRUE FALSE
-- Retrieval info: GEN_FILE: TYPE_NORMAL randomnumber_inst.vhd FALSE
-- Retrieval info: LIB_FILE: altera_mf
