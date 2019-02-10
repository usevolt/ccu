EESchema Schematic File Version 4
LIBS:ccu-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 13
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L usevolt:MCP2515 U401
U 1 1 5AF25753
P 5900 3500
F 0 "U401" H 5850 4247 60  0000 C CNN
F 1 "MCP2515" H 5850 4141 60  0000 C CNN
F 2 "usevolt:QFN20" H 5900 3850 60  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/20001801H.pdf" H 5900 3850 60  0001 C CNN
F 4 "MICROCHIP" H 5950 4200 60  0001 C CNN "Manufacturer"
F 5 "MCP2515T-I/ML" H 6050 4300 60  0001 C CNN "Manufacturer Part Number"
F 6 "Digikey" H 6150 4400 60  0001 C CNN "1st Source"
F 7 "MCP2515T-I/MLCT-ND" H 6250 4500 60  0001 C CNN "1st Source Part Number"
F 8 "Mouser" H 6350 4600 60  0001 C CNN "2nd Source"
F 9 "579-MCP2515T-I/ML" H 6450 4700 60  0001 C CNN "2nd Source Part Number"
	1    5900 3500
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0102
U 1 1 5AF258EA
P 6700 3300
F 0 "#PWR0102" H 6700 3150 50  0001 C CNN
F 1 "+5V" H 6715 3473 50  0000 C CNN
F 2 "" H 6700 3300 50  0000 C CNN
F 3 "" H 6700 3300 50  0000 C CNN
	1    6700 3300
	1    0    0    -1  
$EndComp
$Comp
L kemet:100nF C401
U 1 1 5AF25A6E
P 6700 3500
F 0 "C401" V 6708 3573 45  0000 L CNN
F 1 "100nF" V 6792 3573 45  0000 L CNN
F 2 "kemet:0603" H 6730 3650 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2062872.pdf?_ga=1.250530118.1948984246.1460023966" H 6604 3509 60  0001 C CNN
F 4 "1288255" H 7004 3909 60  0001 C CNN "1st Source Part Number"
F 5 "C0603C104K5RACTU" H 6804 3709 60  0001 C CNN "Manufacturer Part Number"
F 6 "Farnell" H 6904 3809 60  0001 C CNN "1st Source"
F 7 "KEMET" H 6704 3609 60  0001 C CNN "Manufacturer"
	1    6700 3500
	0    1    1    0   
$EndComp
Wire Wire Line
	6700 3300 6700 3400
Wire Wire Line
	6300 3400 6700 3400
Connection ~ 6700 3400
$Comp
L power:GND #PWR0103
U 1 1 5AF25B0C
P 6700 3800
F 0 "#PWR0103" H 6700 3550 50  0001 C CNN
F 1 "GND" H 6705 3627 50  0000 C CNN
F 2 "" H 6700 3800 50  0000 C CNN
F 3 "" H 6700 3800 50  0000 C CNN
	1    6700 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	6700 3800 6700 3700
Wire Wire Line
	6700 3700 6300 3700
Connection ~ 6700 3700
$Comp
L usevolt:MCP2551_SOIC8 U402
U 1 1 5AF2644A
P 7950 4200
F 0 "U402" H 8000 4504 45  0000 C CNN
F 1 "MCP2551_SOIC8" H 8000 4420 45  0000 C CNN
F 2 "usevolt:SOIC8" H 7830 4350 20  0001 C CNN
F 3 "http://www.microchip.com/mymicrochip/filehandler.aspx?ddocname=en011797" H 7550 4650 60  0001 C CNN
F 4 "9758569" H 8550 5020 60  0001 C CNN "2nd Source Part Number"
F 5 "Digi-Key" H 8250 4720 60  0001 C CNN "1st Source"
F 6 "Farnell" H 8450 4920 60  0001 C CNN "2nd Source"
F 7 "MCP2551-I/SN" H 8150 4620 60  0001 C CNN "Manufacturer Part Number"
F 8 "MCP2551-I/SN-ND" H 8350 4820 60  0001 C CNN "1st Source Part Number"
F 9 "MICROCHIP" H 8100 4500 60  0001 C CNN "Manufacturer"
	1    7950 4200
	-1   0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0104
U 1 1 5AF2657F
P 8400 4000
F 0 "#PWR0104" H 8400 3850 50  0001 C CNN
F 1 "+5V" H 8415 4173 50  0000 C CNN
F 2 "" H 8400 4000 50  0000 C CNN
F 3 "" H 8400 4000 50  0000 C CNN
	1    8400 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	8400 4000 8400 4050
Wire Wire Line
	8400 4100 8250 4100
$Comp
L power:GND #PWR0105
U 1 1 5AF26600
P 8400 4500
F 0 "#PWR0105" H 8400 4250 50  0001 C CNN
F 1 "GND" H 8405 4327 50  0000 C CNN
F 2 "" H 8400 4500 50  0000 C CNN
F 3 "" H 8400 4500 50  0000 C CNN
	1    8400 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	8400 4500 8400 4400
Wire Wire Line
	8400 4300 8250 4300
$Comp
L kemet:100nF C404
U 1 1 5AF2667E
P 8500 4150
F 0 "C404" V 8508 4223 45  0000 L CNN
F 1 "100nF" V 8592 4223 45  0000 L CNN
F 2 "kemet:0603" H 8530 4300 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2062872.pdf?_ga=1.250530118.1948984246.1460023966" H 8404 4159 60  0001 C CNN
F 4 "1288255" H 8804 4559 60  0001 C CNN "1st Source Part Number"
F 5 "C0603C104K5RACTU" H 8604 4359 60  0001 C CNN "Manufacturer Part Number"
F 6 "Farnell" H 8704 4459 60  0001 C CNN "1st Source"
F 7 "KEMET" H 8504 4259 60  0001 C CNN "Manufacturer"
	1    8500 4150
	0    1    1    0   
$EndComp
Wire Wire Line
	8500 4050 8400 4050
Connection ~ 8400 4050
Wire Wire Line
	8400 4050 8400 4100
Wire Wire Line
	8250 4400 8400 4400
Connection ~ 8400 4400
Wire Wire Line
	8400 4400 8400 4300
Wire Wire Line
	8400 4400 8500 4400
Wire Wire Line
	8500 4400 8500 4350
Wire Wire Line
	7550 4300 6750 4300
Wire Wire Line
	6750 4300 6750 4100
Wire Wire Line
	6750 4100 6300 4100
Wire Wire Line
	6300 4000 6600 4000
Wire Wire Line
	6600 4000 6600 4400
Wire Wire Line
	6600 4400 7550 4400
Text HLabel 7300 4100 0    60   Output ~ 0
CAN2H
Text HLabel 7300 4200 0    60   Output ~ 0
CAN2L
Wire Wire Line
	7300 4200 7500 4200
Wire Wire Line
	7550 4100 7400 4100
Wire Wire Line
	5400 3000 5100 3000
Wire Wire Line
	5400 3100 5100 3100
Wire Wire Line
	5400 3200 5100 3200
Wire Wire Line
	5400 3300 5100 3300
Wire Wire Line
	5400 3400 5100 3400
Wire Wire Line
	5400 3500 5100 3500
Text HLabel 5100 3000 0    60   Input ~ 0
SPI_SCK
Text HLabel 5100 3200 0    60   Output ~ 0
SPI_MISO
Text HLabel 5100 3100 0    60   Input ~ 0
SPI_MOSI
Text HLabel 5100 3300 0    60   Input ~ 0
SPI_CS
Text HLabel 5100 3400 0    60   Input ~ 0
SPI_RESET
Text HLabel 5100 3500 0    60   Output ~ 0
SPI_INT
$Comp
L usevolt:XTAL_7A-12.000MAAJ-T X401
U 1 1 5AF2915D
P 6650 2900
F 0 "X401" V 6558 2998 45  0000 L CNN
F 1 "XTAL_7A-12.000MAAJ-T" V 6642 2998 45  0000 L CNN
F 2 "usevolt:XTAL_7A-20.000MAJ" H 6680 3050 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1041607.pdf?_ga=1.226282842.1948984246.1460023966" H 6670 2920 60  0001 C CNN
F 4 "887-1081-1-ND" H 7270 3520 60  0001 C CNN "2nd Source Part Number"
F 5 "Digikey" H 7170 3420 60  0001 C CNN "2nd Source"
F 6 "1841940" H 7070 3320 60  0001 C CNN "1st Source Part Number"
F 7 "7A-12.000MAAJ-T" H 6870 3120 60  0001 C CNN "Manufacturer Part Number"
F 8 "Farnell" H 6970 3220 60  0001 C CNN "1st Source"
F 9 "TXC" H 6770 3020 60  0001 C CNN "Manufacturer"
	1    6650 2900
	0    1    1    0   
$EndComp
$Comp
L kemet:15pF C403
U 1 1 5AF2931E
P 6950 3000
F 0 "C403" H 7000 3199 45  0000 C CNN
F 1 "15pF" H 7000 3115 45  0000 C CNN
F 2 "kemet:0603" H 6980 3150 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2063261.pdf?_ga=1.256885067.1948984246.1460023966" H 6854 3009 60  0001 C CNN
F 4 "1414614" H 7254 3409 60  0001 C CNN "1st Source Part Number"
F 5 "C0603C150J5GACTU" H 7054 3209 60  0001 C CNN "Manufacturer Part Number"
F 6 "Farnell" H 7154 3309 60  0001 C CNN "1st Source"
F 7 "KEMET" H 6954 3109 60  0001 C CNN "Manufacturer"
	1    6950 3000
	1    0    0    -1  
$EndComp
$Comp
L kemet:15pF C402
U 1 1 5AF29386
P 6950 2700
F 0 "C402" H 7000 2899 45  0000 C CNN
F 1 "15pF" H 7000 2815 45  0000 C CNN
F 2 "kemet:0603" H 6980 2850 20  0001 C CNN
F 3 "http://www.farnell.com/datasheets/2063261.pdf?_ga=1.256885067.1948984246.1460023966" H 6854 2709 60  0001 C CNN
F 4 "1414614" H 7254 3109 60  0001 C CNN "1st Source Part Number"
F 5 "C0603C150J5GACTU" H 7054 2909 60  0001 C CNN "Manufacturer Part Number"
F 6 "Farnell" H 7154 3009 60  0001 C CNN "1st Source"
F 7 "KEMET" H 6954 2809 60  0001 C CNN "Manufacturer"
	1    6950 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	6850 3000 6650 3000
Wire Wire Line
	6650 3000 6500 3000
Wire Wire Line
	6500 3000 6500 3100
Wire Wire Line
	6500 3100 6300 3100
Connection ~ 6650 3000
Wire Wire Line
	6300 3000 6400 3000
Wire Wire Line
	6400 3000 6400 2700
Wire Wire Line
	6400 2700 6650 2700
Wire Wire Line
	6650 2700 6850 2700
Connection ~ 6650 2700
$Comp
L power:GND #PWR0106
U 1 1 5AF2AA93
P 7600 3100
F 0 "#PWR0106" H 7600 2850 50  0001 C CNN
F 1 "GND" H 7605 2927 50  0000 C CNN
F 2 "" H 7600 3100 50  0000 C CNN
F 3 "" H 7600 3100 50  0000 C CNN
	1    7600 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	7600 3100 7600 3000
Wire Wire Line
	7600 3000 7150 3000
Wire Wire Line
	7600 3000 7600 2700
Wire Wire Line
	7600 2700 7150 2700
Connection ~ 7600 3000
$Comp
L yageo:120 R401
U 1 1 5B1BA23A
P 7350 3750
F 0 "R401" H 7400 3934 45  0000 C CNN
F 1 "120" H 7400 3850 45  0000 C CNN
F 2 "yageo:0603" H 7380 3900 20  0001 C CNN
F 3 "" H 7319 3789 60  0001 C CNN
F 4 "" H 7719 4189 60  0001 C CNN "1st Source Part Number"
F 5 "Digikey" H 7619 4089 60  0001 C CNN "1st Source"
F 6 "RC0603FR-07120RL" H 7519 3989 60  0001 C CNN "Manufacturer Part Number"
F 7 "YAGEO" H 7419 3889 60  0001 C CNN "Manufacturer"
	1    7350 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	7550 3750 7550 3900
Wire Wire Line
	7550 3900 7500 3900
Wire Wire Line
	7500 3900 7500 4200
Connection ~ 7500 4200
Wire Wire Line
	7500 4200 7550 4200
Wire Wire Line
	7400 4100 7400 3900
Wire Wire Line
	7400 3900 7250 3900
Wire Wire Line
	7250 3900 7250 3750
Connection ~ 7400 4100
Wire Wire Line
	7400 4100 7300 4100
Wire Wire Line
	7050 3400 6700 3400
Wire Wire Line
	7050 3700 6700 3700
$Comp
L usevolt:CAP_TPSB107M006R0250 C1
U 1 1 5C61AE74
P 7050 3600
F 0 "C1" V 6958 3703 45  0000 L CNN
F 1 "CAP_TPSB107M006R0250" V 7042 3703 45  0000 L CNN
F 2 "usevolt:1210_CAP" H 7080 3750 20  0001 C CNN
F 3 "http://datasheets.avx.com/TPS.pdf" H 7050 3540 60  0001 C CNN
F 4 "AVX Corporation" H 7150 3640 60  0001 C CNN "Manufacturer"
F 5 "TPSB107M006R0250" H 7250 3740 60  0001 C CNN "Manufacturer Part Number"
F 6 "Digi-Key" H 7350 3840 60  0001 C CNN "1st Source"
F 7 "478-4978-1-ND" H 7450 3940 60  0001 C CNN "1st Source Part Number"
F 8 "Mouser" H 7550 4040 60  0001 C CNN "2nd Source"
F 9 "581-TPSB107M006R0250" H 7650 4140 60  0001 C CNN "2nd Source Part Number"
	1    7050 3600
	0    1    1    0   
$EndComp
$EndSCHEMATC
