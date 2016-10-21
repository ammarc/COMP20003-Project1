import csv
import time
import subprocess
from subprocess import Popen, PIPE, check_output

out = open('output2.csv', 'w')

count = 0;

for prop in "max avg".split():
		for depth in range(0, 7, 1):
				for i in range (1, 51, 1):
						time.sleep(1)

						cmd = ["./2048", "ai", str(prop), str(depth)]

						count = count + 1

						writer = csv.writer(out, dialect='excel')



						output = check_output(cmd)


						writer.writerow(output.split(","))

						print("Running Test: " + str(count) + " / " + str(2 * 50 * 7))
out.close()
