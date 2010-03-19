#!/usr/bin/env python
#
# step-test.py
# 
# Author
#     Andrew Brown


def main():
	
	# Start
	print ""
	print "****************************************"
	print "Step Test"
	print "****************************************"
	print ""
	
	# Get height of the tree
	height = input("Please enter the height of the tree: ")
	print "You entered:", height
	
	# Calculate steps
	print "Calculating steps..."
	steps = list()
	total = 0
	for level in range(0,height):
		total += pow(8,level)
		steps.append(total)
	
	# Print steps
	print "Printing steps:"
	for step in steps:
		print " ", step
	
	# Finish
	print ""
	print "****************************************"
	print "Step Test"
	print "****************************************"
	print ""


if __name__ == '__main__': main()
