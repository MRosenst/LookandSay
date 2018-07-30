#!/usr/bin/python

import sys


def las(n):
	if n == 0:
		return "1"

	cur = ""

	count = [0, 0, 0, 0]
	for c in las(n-1):

		if int(c) == 1:
			count[1] += 1
			if count[2] != 0:
				cur += str(count[2])
				cur += "2"
				count[2] = 0

			if count[3] != 0:
				cur += str(count[3])
				cur += "3"
				count[3] = 0
		elif int(c) == 2:
			count[2] += 1
			if count[1] != 0:
				cur += str(count[1])
				cur += "1"
				count[1] = 0

			if count[3] != 0:
				cur += str(count[3])
				cur += "3"
				count[3] = 0

		elif int(c) == 3:
			count[3] += 1
			if count[1] != 0:
				cur += str(count[1])
				cur += "1"
				count[1] = 0

			if count[2] != 0:
				cur += str(count[2])
				cur += "2"
				count[2] = 0

	if count[1] != 0:
		cur += str(count[1])
		cur += "1"
		count[1] = 0
	if count[2] != 0:
		cur += str(count[2])
		cur += "2"
		count[2] = 0
	if count[3] != 0:
		cur += str(count[3])
		cur += "3"
		count[3] = 0

	return cur







if len(sys.argv) != 2:
	print("error:  invalid input")
	sys.exit(1)

try:
	n = int(sys.argv[1])
except ValueError:
	print("error:  invalid input")
	sys.exit(1)


print(las(n))
