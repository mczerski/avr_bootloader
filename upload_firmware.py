import serial
import sys

port = sys.argv[1]

serial = serial.Serial(port, 115200, parity=serial.PARITY_NONE, rtscts=False, xonxoff=True, timeout=3)

firmware = sys.stdin.read().strip().split('\n')
for no, line in enumerate(firmware):
	line += '\n'
	serial.write(line)
	result = serial.read(1)
	if result != '.':
		raise Exception('communication error: %s' % result)
	sys.stdout.write("%d%%\r" % (int(100.0*no/len(firmware))))
	sys.stdout.flush()
result = serial.read(2)
print '\n' + result

