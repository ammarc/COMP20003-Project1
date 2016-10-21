import csv

import subprocess
from subprocess import Popen, PIPE


for depth in range(1, 7, 1):
	for prop in "max avg".split():
		for i in range (0, 3, 1):

		# cmd = ["./2048", "ai", "max", str(depth)]

		# Open/Create the output file
		# out = open('/output.csv', 'a+')
		# print(str(depth) + ",")
		# out = subprocess.call(["./2048", "ai", "max", str(depth)]))
		# result = subprocess.Popen(cmd, stdout=subprocess.PIPE)
		# print("\n")


		# writer = csv.writer(out, delimiter=',', quotechar='', quoting=csv.QUOTE_MINIMAL)

		# for row in reader:
    	#		writer.writerow(row)

		# result = subprocess.Popen(cmd, stdout=subprocess.PIPE)
		#out = result.stdout.read()
		# out = result.stdout.read()
		#writer = csv.writer(out, de)
		#csv.write(out)
			print ("Depth: "+str(depth) + " Test: " + str(i) + " Type: " + str(prop))
			subprocess.call(["./2048", "ai", str(prop), str(depth)])

#out.close()
