EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 2
Title "STM32F04K6Tx MCU"
Date "2020-01-09"
Rev "0"
Comp "G. Keeth"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MCU_ST_STM32F0:STM32F042K6Tx U?
U 1 1 5E3538D8
P 5350 3600
AR Path="/5E3538D8" Ref="U?"  Part="1" 
AR Path="/5E34A630/5E3538D8" Ref="U1"  Part="1" 
F 0 "U1" H 5800 2600 50  0000 C CNN
F 1 "STM32F042K6Tx" H 5800 2500 50  0000 C CNN
F 2 "Package_QFP:LQFP-32_7x7mm_P0.8mm" H 4950 2700 50  0001 R CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/DM00105814.pdf" H 5350 3600 50  0001 C CNN
	1    5350 3600
	1    0    0    -1  
$EndComp
Text HLabel 4400 4400 0    50   Input ~ 0
BOOT0
Text HLabel 4400 3500 0    50   BiDi ~ 0
PF1
Text HLabel 4400 3700 0    50   BiDi ~ 0
PB0
Text HLabel 4400 3800 0    50   BiDi ~ 0
PB1
Text HLabel 4400 3900 0    50   BiDi ~ 0
PB3
Text HLabel 4400 4000 0    50   BiDi ~ 0
PB4
Text HLabel 4400 4100 0    50   BiDi ~ 0
PB5
Text HLabel 4400 4200 0    50   BiDi ~ 0
PB6
Text HLabel 4400 4300 0    50   BiDi ~ 0
PB7
Wire Wire Line
	4850 3700 4400 3700
Wire Wire Line
	4400 3500 4850 3500
Wire Wire Line
	4850 3800 4400 3800
Wire Wire Line
	4400 3900 4850 3900
Wire Wire Line
	4850 4000 4400 4000
Wire Wire Line
	4400 4200 4850 4200
Wire Wire Line
	4850 4100 4400 4100
Wire Wire Line
	4400 4300 4850 4300
Wire Wire Line
	4850 4400 4400 4400
Text HLabel 6800 4000 2    50   BiDi ~ 0
USB_DM
Text HLabel 6800 4100 2    50   BiDi ~ 0
USB_DP
Text HLabel 6800 4200 2    50   BiDi ~ 0
PA13_SWDIO
Text HLabel 6800 4300 2    50   BiDi ~ 0
PA14_SWCLK
Text HLabel 6800 4400 2    50   BiDi ~ 0
PA15
Text HLabel 6800 3900 2    50   BiDi ~ 0
PA10
Text HLabel 6800 3800 2    50   BiDi ~ 0
PA9
Text HLabel 6800 2900 2    50   BiDi ~ 0
PA0
Text HLabel 6800 3000 2    50   BiDi ~ 0
PA1
Text HLabel 6800 3100 2    50   BiDi ~ 0
PA2
Text HLabel 6800 3200 2    50   BiDi ~ 0
PA3
Text HLabel 6800 3300 2    50   BiDi ~ 0
PA4
Text HLabel 6800 3400 2    50   BiDi ~ 0
PA5
Text HLabel 6800 3500 2    50   BiDi ~ 0
PA6
Text HLabel 6800 3600 2    50   BiDi ~ 0
PA7
Text HLabel 6800 3700 2    50   BiDi ~ 0
PA8
$Comp
L power:GND #PWR?
U 1 1 5E35A4F6
P 5350 4800
AR Path="/5E35A4F6" Ref="#PWR?"  Part="1" 
AR Path="/5E34A630/5E35A4F6" Ref="#PWR032"  Part="1" 
F 0 "#PWR032" H 5350 4550 50  0001 C CNN
F 1 "GND" H 5355 4627 50  0000 C CNN
F 2 "" H 5350 4800 50  0001 C CNN
F 3 "" H 5350 4800 50  0001 C CNN
	1    5350 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	5350 4800 5350 4700
Wire Wire Line
	5250 4600 5250 4700
Wire Wire Line
	5250 4700 5350 4700
Connection ~ 5350 4700
Wire Wire Line
	5350 4700 5350 4600
$Comp
L power:VDDA #PWR?
U 1 1 5E35F70E
P 5350 2350
AR Path="/5E35F70E" Ref="#PWR?"  Part="1" 
AR Path="/5E34A630/5E35F70E" Ref="#PWR031"  Part="1" 
F 0 "#PWR031" H 5350 2200 50  0001 C CNN
F 1 "VDDA" H 5437 2387 50  0000 L CNN
F 2 "" H 5350 2350 50  0001 C CNN
F 3 "" H 5350 2350 50  0001 C CNN
	1    5350 2350
	1    0    0    -1  
$EndComp
$Comp
L power:VDD #PWR?
U 1 1 5E35F714
P 5250 2350
AR Path="/5E35F714" Ref="#PWR?"  Part="1" 
AR Path="/5E34A630/5E35F714" Ref="#PWR030"  Part="1" 
F 0 "#PWR030" H 5250 2200 50  0001 C CNN
F 1 "VDD" H 5197 2387 50  0000 R CNN
F 2 "" H 5250 2350 50  0001 C CNN
F 3 "" H 5250 2350 50  0001 C CNN
	1    5250 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	5250 2600 5450 2600
Wire Wire Line
	5450 2600 5450 2700
Wire Wire Line
	5250 2600 5250 2700
Wire Wire Line
	5350 2700 5350 2350
Wire Wire Line
	5250 2350 5250 2600
Connection ~ 5250 2600
Wire Wire Line
	5850 2900 6800 2900
Wire Wire Line
	5850 3000 6800 3000
Wire Wire Line
	5850 3100 6800 3100
Wire Wire Line
	5850 3200 6800 3200
Wire Wire Line
	5850 3300 6800 3300
Wire Wire Line
	5850 3400 6800 3400
Wire Wire Line
	5850 3500 6800 3500
Wire Wire Line
	5850 3600 6800 3600
Wire Wire Line
	5850 3700 6800 3700
Wire Wire Line
	5850 3800 6800 3800
Wire Wire Line
	5850 3900 6800 3900
Wire Wire Line
	5850 4000 6800 4000
Wire Wire Line
	5850 4100 6800 4100
Wire Wire Line
	5850 4200 6800 4200
Wire Wire Line
	5850 4300 6800 4300
Wire Wire Line
	5850 4400 6800 4400
Text HLabel 4400 2900 0    50   Input ~ 0
NRST
Wire Wire Line
	4850 2900 4400 2900
$Comp
L Device:C C8
U 1 1 5E42B871
P 8350 5450
F 0 "C8" H 8465 5496 50  0000 L CNN
F 1 "10n" H 8465 5405 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 8388 5300 50  0001 C CNN
F 3 "~" H 8350 5450 50  0001 C CNN
	1    8350 5450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E42CD6A
P 8350 5750
AR Path="/5E42CD6A" Ref="#PWR?"  Part="1" 
AR Path="/5E34A630/5E42CD6A" Ref="#PWR036"  Part="1" 
F 0 "#PWR036" H 8350 5500 50  0001 C CNN
F 1 "GND" H 8355 5577 50  0000 C CNN
F 2 "" H 8350 5750 50  0001 C CNN
F 3 "" H 8350 5750 50  0001 C CNN
	1    8350 5750
	1    0    0    -1  
$EndComp
Wire Wire Line
	8350 5750 8350 5600
Wire Wire Line
	8350 5050 8350 5300
$Comp
L Device:C C9
U 1 1 5E42F0AC
P 8800 5450
F 0 "C9" H 8915 5496 50  0000 L CNN
F 1 "1u" H 8915 5405 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 8838 5300 50  0001 C CNN
F 3 "~" H 8800 5450 50  0001 C CNN
	1    8800 5450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E42F0B2
P 8800 5750
AR Path="/5E42F0B2" Ref="#PWR?"  Part="1" 
AR Path="/5E34A630/5E42F0B2" Ref="#PWR038"  Part="1" 
F 0 "#PWR038" H 8800 5500 50  0001 C CNN
F 1 "GND" H 8805 5577 50  0000 C CNN
F 2 "" H 8800 5750 50  0001 C CNN
F 3 "" H 8800 5750 50  0001 C CNN
	1    8800 5750
	1    0    0    -1  
$EndComp
Wire Wire Line
	8800 5750 8800 5600
Wire Wire Line
	8800 5050 8800 5300
$Comp
L Device:C C11
U 1 1 5E4309C2
P 9850 5450
F 0 "C11" H 9965 5496 50  0000 L CNN
F 1 "100n" H 9965 5405 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 9888 5300 50  0001 C CNN
F 3 "~" H 9850 5450 50  0001 C CNN
	1    9850 5450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E4309C8
P 9850 5750
AR Path="/5E4309C8" Ref="#PWR?"  Part="1" 
AR Path="/5E34A630/5E4309C8" Ref="#PWR042"  Part="1" 
F 0 "#PWR042" H 9850 5500 50  0001 C CNN
F 1 "GND" H 9855 5577 50  0000 C CNN
F 2 "" H 9850 5750 50  0001 C CNN
F 3 "" H 9850 5750 50  0001 C CNN
	1    9850 5750
	1    0    0    -1  
$EndComp
Wire Wire Line
	9850 5750 9850 5600
Wire Wire Line
	9850 5050 9850 5300
$Comp
L Device:C C12
U 1 1 5E4309D0
P 10300 5450
F 0 "C12" H 10415 5496 50  0000 L CNN
F 1 "4.7u" H 10415 5405 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 10338 5300 50  0001 C CNN
F 3 "~" H 10300 5450 50  0001 C CNN
	1    10300 5450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E4309D6
P 10300 5750
AR Path="/5E4309D6" Ref="#PWR?"  Part="1" 
AR Path="/5E34A630/5E4309D6" Ref="#PWR044"  Part="1" 
F 0 "#PWR044" H 10300 5500 50  0001 C CNN
F 1 "GND" H 10305 5577 50  0000 C CNN
F 2 "" H 10300 5750 50  0001 C CNN
F 3 "" H 10300 5750 50  0001 C CNN
	1    10300 5750
	1    0    0    -1  
$EndComp
Wire Wire Line
	10300 5750 10300 5600
Wire Wire Line
	10300 5050 10300 5300
$Comp
L Device:C C10
U 1 1 5E433D07
P 9400 5450
F 0 "C10" H 9515 5496 50  0000 L CNN
F 1 "100n" H 9515 5405 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 9438 5300 50  0001 C CNN
F 3 "~" H 9400 5450 50  0001 C CNN
	1    9400 5450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E433D0D
P 9400 5750
AR Path="/5E433D0D" Ref="#PWR?"  Part="1" 
AR Path="/5E34A630/5E433D0D" Ref="#PWR040"  Part="1" 
F 0 "#PWR040" H 9400 5500 50  0001 C CNN
F 1 "GND" H 9405 5577 50  0000 C CNN
F 2 "" H 9400 5750 50  0001 C CNN
F 3 "" H 9400 5750 50  0001 C CNN
	1    9400 5750
	1    0    0    -1  
$EndComp
Wire Wire Line
	9400 5750 9400 5600
Wire Wire Line
	9400 5050 9400 5300
$Comp
L power:VDD #PWR?
U 1 1 5E435C97
P 9400 5050
AR Path="/5E435C97" Ref="#PWR?"  Part="1" 
AR Path="/5E34A630/5E435C97" Ref="#PWR039"  Part="1" 
F 0 "#PWR039" H 9400 4900 50  0001 C CNN
F 1 "VDD" H 9417 5223 50  0000 C CNN
F 2 "" H 9400 5050 50  0001 C CNN
F 3 "" H 9400 5050 50  0001 C CNN
	1    9400 5050
	1    0    0    -1  
$EndComp
$Comp
L power:VDD #PWR?
U 1 1 5E4362B8
P 9850 5050
AR Path="/5E4362B8" Ref="#PWR?"  Part="1" 
AR Path="/5E34A630/5E4362B8" Ref="#PWR041"  Part="1" 
F 0 "#PWR041" H 9850 4900 50  0001 C CNN
F 1 "VDD" H 9867 5223 50  0000 C CNN
F 2 "" H 9850 5050 50  0001 C CNN
F 3 "" H 9850 5050 50  0001 C CNN
	1    9850 5050
	1    0    0    -1  
$EndComp
$Comp
L power:VDD #PWR?
U 1 1 5E43652A
P 10300 5050
AR Path="/5E43652A" Ref="#PWR?"  Part="1" 
AR Path="/5E34A630/5E43652A" Ref="#PWR043"  Part="1" 
F 0 "#PWR043" H 10300 4900 50  0001 C CNN
F 1 "VDD" H 10317 5223 50  0000 C CNN
F 2 "" H 10300 5050 50  0001 C CNN
F 3 "" H 10300 5050 50  0001 C CNN
	1    10300 5050
	1    0    0    -1  
$EndComp
$Comp
L power:VDDA #PWR?
U 1 1 5E43682E
P 8800 5050
AR Path="/5E43682E" Ref="#PWR?"  Part="1" 
AR Path="/5E34A630/5E43682E" Ref="#PWR037"  Part="1" 
F 0 "#PWR037" H 8800 4900 50  0001 C CNN
F 1 "VDDA" H 8817 5223 50  0000 C CNN
F 2 "" H 8800 5050 50  0001 C CNN
F 3 "" H 8800 5050 50  0001 C CNN
	1    8800 5050
	1    0    0    -1  
$EndComp
$Comp
L power:VDDA #PWR?
U 1 1 5E436C19
P 8350 5050
AR Path="/5E436C19" Ref="#PWR?"  Part="1" 
AR Path="/5E34A630/5E436C19" Ref="#PWR035"  Part="1" 
F 0 "#PWR035" H 8350 4900 50  0001 C CNN
F 1 "VDDA" H 8367 5223 50  0000 C CNN
F 2 "" H 8350 5050 50  0001 C CNN
F 3 "" H 8350 5050 50  0001 C CNN
	1    8350 5050
	1    0    0    -1  
$EndComp
$Comp
L Oscillator:ASV-xxxMHz X?
U 1 1 5E43DA78
P 2800 3400
AR Path="/5E43DA78" Ref="X?"  Part="1" 
AR Path="/5E34A630/5E43DA78" Ref="X1"  Part="1" 
F 0 "X1" H 3144 3446 50  0000 L CNN
F 1 "ASV-8.000MHz" H 3144 3355 50  0000 L CNN
F 2 "Oscillator:Oscillator_SMD_Abracon_ASV-4Pin_7.0x5.1mm" H 3500 3050 50  0001 C CNN
F 3 "http://www.abracon.com/Oscillators/ASV.pdf" H 2700 3400 50  0001 C CNN
	1    2800 3400
	1    0    0    -1  
$EndComp
$Comp
L power:VDD #PWR?
U 1 1 5E43DA7E
P 2800 3000
AR Path="/5E43DA7E" Ref="#PWR?"  Part="1" 
AR Path="/5E34A630/5E43DA7E" Ref="#PWR028"  Part="1" 
F 0 "#PWR028" H 2800 2850 50  0001 C CNN
F 1 "VDD" H 2817 3173 50  0000 C CNN
F 2 "" H 2800 3000 50  0001 C CNN
F 3 "" H 2800 3000 50  0001 C CNN
	1    2800 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	2800 3000 2800 3050
NoConn ~ 2500 3400
$Comp
L power:GND #PWR?
U 1 1 5E43DA86
P 2800 3800
AR Path="/5E43DA86" Ref="#PWR?"  Part="1" 
AR Path="/5E34A630/5E43DA86" Ref="#PWR029"  Part="1" 
F 0 "#PWR029" H 2800 3550 50  0001 C CNN
F 1 "GND" H 2805 3627 50  0000 C CNN
F 2 "" H 2800 3800 50  0001 C CNN
F 3 "" H 2800 3800 50  0001 C CNN
	1    2800 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	2800 3700 2800 3750
$Comp
L Device:C C?
U 1 1 5E43DA8D
P 2100 3400
AR Path="/5E43DA8D" Ref="C?"  Part="1" 
AR Path="/5E34A630/5E43DA8D" Ref="C7"  Part="1" 
F 0 "C7" H 2215 3446 50  0000 L CNN
F 1 "10n" H 2215 3355 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2138 3250 50  0001 C CNN
F 3 "~" H 2100 3400 50  0001 C CNN
	1    2100 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	2100 3250 2100 3050
Wire Wire Line
	2100 3050 2800 3050
Connection ~ 2800 3050
Wire Wire Line
	2800 3050 2800 3100
Wire Wire Line
	2100 3550 2100 3750
Wire Wire Line
	2100 3750 2800 3750
Connection ~ 2800 3750
Wire Wire Line
	2800 3750 2800 3800
Wire Wire Line
	3100 3400 4850 3400
$Comp
L power:VDD #PWR?
U 1 1 5E447A2C
P 6200 1850
AR Path="/5E447A2C" Ref="#PWR?"  Part="1" 
AR Path="/5E34A630/5E447A2C" Ref="#PWR033"  Part="1" 
F 0 "#PWR033" H 6200 1700 50  0001 C CNN
F 1 "VDD" H 6217 2023 50  0000 C CNN
F 2 "" H 6200 1850 50  0001 C CNN
F 3 "" H 6200 1850 50  0001 C CNN
	1    6200 1850
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG?
U 1 1 5E447A32
P 6850 2050
AR Path="/5E447A32" Ref="#FLG?"  Part="1" 
AR Path="/5E34A630/5E447A32" Ref="#FLG02"  Part="1" 
F 0 "#FLG02" H 6850 2125 50  0001 C CNN
F 1 "PWR_FLAG" H 6850 2223 50  0000 C CNN
F 2 "" H 6850 2050 50  0001 C CNN
F 3 "~" H 6850 2050 50  0001 C CNN
	1    6850 2050
	-1   0    0    1   
$EndComp
$Comp
L power:VDDA #PWR?
U 1 1 5E447A38
P 6850 1850
AR Path="/5E447A38" Ref="#PWR?"  Part="1" 
AR Path="/5E34A630/5E447A38" Ref="#PWR034"  Part="1" 
F 0 "#PWR034" H 6850 1700 50  0001 C CNN
F 1 "VDDA" H 6867 2023 50  0000 C CNN
F 2 "" H 6850 1850 50  0001 C CNN
F 3 "" H 6850 1850 50  0001 C CNN
	1    6850 1850
	1    0    0    -1  
$EndComp
$Comp
L Device:Net-Tie_2 NT?
U 1 1 5E447A3E
P 6500 1950
AR Path="/5E447A3E" Ref="NT?"  Part="1" 
AR Path="/5E34A630/5E447A3E" Ref="NT1"  Part="1" 
F 0 "NT1" H 6500 2131 50  0000 C CNN
F 1 "Net-Tie_2" H 6500 2040 50  0000 C CNN
F 2 "NetTie:NetTie-2_SMD_Pad0.5mm" H 6500 1950 50  0001 C CNN
F 3 "~" H 6500 1950 50  0001 C CNN
	1    6500 1950
	1    0    0    -1  
$EndComp
Wire Wire Line
	6200 1850 6200 1950
Wire Wire Line
	6200 1950 6400 1950
Wire Wire Line
	6600 1950 6850 1950
Wire Wire Line
	6850 1950 6850 1850
Wire Wire Line
	6850 2050 6850 1950
Connection ~ 6850 1950
Text Label 3950 3400 0    50   ~ 0
clkin
$EndSCHEMATC
