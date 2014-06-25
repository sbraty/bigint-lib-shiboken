#!/usr/bin/python
# -*- coding: utf-8 -*-

import sys
import bigint as BigInt

if len(sys.argv) != 5:
	print "command <number_1> <sign> <number_2> <out_file>";
	sys.exit();

a = BigInt.BigInt()
a.ReadFromFile(sys.argv[1])
b = BigInt.BigInt()
b.ReadFromFile(sys.argv[3])
c = BigInt.BigInt()

if sys.argv[2] == "+":
	c = a+b;
elif sys.argv[2] == "-":
	c = a-b;
elif sys.argv[2] == "*":
	c = a*b;
elif sys.argv[2] == "/":
	c = a/b;
elif sys.argv[2] == "*":
	c = a*b;
elif sys.argv[2] == "^":
	c = a^b;
else:
	print "command <number_1> <sign> <number_2> <out_file>"

c.WriteToFile(sys.argv[4])
