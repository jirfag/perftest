import random;
import sys

for _ in range(int(sys.argv[1])):
	sys.stdout.write(random.choice([chr(i) for i in range(32, 127)]))
