#-----------------------------------------------------------------
#      ___     ___ 
#     |   |   |   |
#     |   |   |   |
#     |   |___|   |
#     |    ___    |
#     |   |   |   |
#     |   |   |   |
#     |___|   |___| alley, Universidad Industrial de Santander
#                   Copyright, Jesus Pe#a Rodriguez, 2016
#-----------------------------------------------------------------
""" First algorithm test to work with the Red Pitaya Oscope
"""

#!/usr/bin/python

import sys
import redpitaya_scpi as scpi
import matplotlib.pyplot as plot

file = 'Prueba.txt'
Data = open(file,'w')
Data.close()

if len(sys.argv) > 1:
    print(sys.argv[1])
else:
    IP = '192.168.0.52' # Red Piyata IP

rp_s = scpi.scpi(IP)

rp_s.tx_txt('ACQ:DEC 1')
rp_s.tx_txt('ACQ:TRIG:LEVEL 30')	# Trigger level 1 Volt

NPulses =  1000  # Number of pulses

for j in range(0, NPulses):

	rp_s.tx_txt('ACQ:START')
	rp_s.tx_txt('ACQ:TRIG EXT_PE')

	while 1:
    		rp_s.tx_txt('ACQ:TRIG:STAT?')
    		if rp_s.rx_txt() == 'TD':
        		break

	rp_s.tx_txt('ACQ:SOUR1:DATA?')
	buff_string = rp_s.rx_txt()
	buff_string = buff_string.strip('{}\n\r').replace("  ", "").split(',')
	buff = map(float, buff_string)
	

	for i in range(8000, 8500):

        	Data = open(file,'a')
        	Data.write(str(buff[i]) + '\t')

	Data.write('\n')
	Data.close()
	print 'Pulse ' + str(j) + ' Adquiriendo...'

