EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
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
L Device:Battery_Cell BT?
U 1 1 69F880B7
P 7850 3000
F 0 "BT?" H 7968 3096 50  0001 L CNN
F 1 "2s LiPo" H 7968 3050 50  0000 L CNN
F 2 "" V 7850 3060 50  0001 C CNN
F 3 "~" V 7850 3060 50  0001 C CNN
	1    7850 3000
	1    0    0    -1  
$EndComp
$Comp
L MCU_Module:Arduino_UNO_R3 A?
U 1 1 69F86528
P 5900 2700
F 0 "A?" H 5900 3881 50  0001 C CNN
F 1 "Arduino Uno" H 6469 1519 50  0000 C CNN
F 2 "Module:Arduino_UNO_R3" H 5900 2700 50  0001 C CIN
F 3 "https://www.arduino.cc/en/Main/arduinoBoardUno" H 5900 2700 50  0001 C CNN
	1    5900 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 3800 5800 4000
Wire Wire Line
	5800 1550 5800 1700
$Comp
L Motor:Motor_Servo M?
U 1 1 69F925BC
P 4750 2850
F 0 "M?" H 4744 3194 50  0000 C CNN
F 1 "Motor_Servo" H 4744 3103 50  0000 C CNN
F 2 "" H 4750 2660 50  0001 C CNN
F 3 "http://forums.parallax.com/uploads/attachments/46831/74481.png" H 4750 2660 50  0001 C CNN
	1    4750 2850
	-1   0    0    -1  
$EndComp
$Comp
L Sensor_Pressure:BMP280 U?
U 1 1 69F960B9
P 7250 3400
F 0 "U?" H 7480 3496 50  0000 L CNN
F 1 "BMP388" H 7480 3405 50  0000 L CNN
F 2 "Package_LGA:Bosch_LGA-8_2x2.5mm_P0.65mm_ClockwisePinNumbering" H 7250 2700 50  0001 C CNN
F 3 "https://ae-bst.resource.bosch.com/media/_tech/media/datasheets/BST-BMP280-DS001.pdf" H 7250 3400 50  0001 C CNN
	1    7250 3400
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small_US R?
U 1 1 69FA24D7
P 4200 2250
F 0 "R?" H 4268 2296 50  0001 L CNN
F 1 "10kOhm" H 4268 2250 50  0000 L CNN
F 2 "" H 4200 2250 50  0001 C CNN
F 3 "~" H 4200 2250 50  0001 C CNN
	1    4200 2250
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small_US R?
U 1 1 69FA47AC
P 4550 3500
F 0 "R?" H 4618 3546 50  0000 L CNN
F 1 "220Ohm" H 4618 3455 50  0000 L CNN
F 2 "" H 4550 3500 50  0001 C CNN
F 3 "~" H 4550 3500 50  0001 C CNN
	1    4550 3500
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_MEC_5G SW?
U 1 1 69F9DD1C
P 4700 1900
F 0 "SW?" H 4700 2185 50  0001 C CNN
F 1 "Switch" H 4691 1780 50  0000 C CNN
F 2 "" H 4700 2100 50  0001 C CNN
F 3 "http://www.apem.com/int/index.php?controller=attachment&id_attachment=488" H 4700 2100 50  0001 C CNN
	1    4700 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 4000 7250 4000
Wire Wire Line
	7250 3700 7250 4000
Wire Wire Line
	6400 3500 6850 3500
Wire Wire Line
	6850 3300 6700 3300
Wire Wire Line
	6700 3300 6700 3400
Wire Wire Line
	6700 3400 6400 3400
Wire Wire Line
	5800 1550 7250 1550
Wire Wire Line
	7250 3000 7250 1550
$Comp
L Device:LED D?
U 1 1 69F950E2
P 5000 3400
F 0 "D?" H 4993 3617 50  0000 C CNN
F 1 "LED" H 4993 3526 50  0000 C CNN
F 2 "" H 5000 3400 50  0001 C CNN
F 3 "~" H 5000 3400 50  0001 C CNN
	1    5000 3400
	1    0    0    -1  
$EndComp
Connection ~ 7250 1550
Wire Wire Line
	7850 2900 7850 3100
Wire Wire Line
	7850 4000 7250 4000
Connection ~ 7250 4000
Wire Wire Line
	5150 3400 5400 3400
Wire Wire Line
	4850 3400 4550 3400
Wire Wire Line
	4550 3600 4550 4000
Connection ~ 5800 4000
Wire Wire Line
	4550 4000 5200 4000
Wire Wire Line
	5050 2950 5200 2950
Wire Wire Line
	5200 2950 5200 4000
Connection ~ 5200 4000
Wire Wire Line
	5200 4000 5800 4000
Wire Wire Line
	5050 2750 5300 2750
Wire Wire Line
	5300 2750 5300 3300
Wire Wire Line
	5300 3300 5400 3300
Wire Wire Line
	5050 2850 5200 2850
Wire Wire Line
	5200 2850 5200 1550
Wire Wire Line
	5200 1550 5800 1550
Connection ~ 5800 1550
Wire Wire Line
	4500 1900 4200 1900
Wire Wire Line
	4200 1900 4200 2150
Wire Wire Line
	4200 2350 4200 4000
Wire Wire Line
	4200 4000 4550 4000
Connection ~ 4550 4000
Wire Wire Line
	4900 1900 4900 1550
Wire Wire Line
	4900 1550 5200 1550
Connection ~ 5200 1550
Wire Wire Line
	4900 1900 4900 2500
Wire Wire Line
	4900 2500 5350 2500
Wire Wire Line
	5350 2500 5350 3200
Wire Wire Line
	5350 3200 5400 3200
Connection ~ 4900 1900
$Comp
L Sensor_Pressure:MPXA6115A U?
U 1 1 69FE8775
P 8800 1950
F 0 "U?" H 8371 1996 50  0000 R CNN
F 1 "MPX5010DP" H 8371 1905 50  0000 R CNN
F 2 "" H 8300 1600 50  0001 C CNN
F 3 "http://www.nxp.com/files/sensors/doc/data_sheet/MPXA6115A.pdf" H 8800 2550 50  0001 C CNN
	1    8800 1950
	1    0    0    -1  
$EndComp
Wire Wire Line
	8800 1550 8800 1650
Wire Wire Line
	8800 2250 8800 4000
Wire Wire Line
	8800 4000 7850 4000
Connection ~ 7850 4000
Wire Wire Line
	9200 1950 9200 2700
Wire Wire Line
	9200 2700 6400 2700
Connection ~ 7850 3100
Wire Wire Line
	7850 3100 7850 4000
Wire Wire Line
	7250 1550 7850 1550
Wire Wire Line
	7850 2800 7850 1550
Connection ~ 7850 1550
Wire Wire Line
	7850 1550 8800 1550
$EndSCHEMATC
