#!/usr/bin/env python 
# xor.py
# 
# Author
#     Andrew Brown <adb1413@rit.edu>
from copy import copy


class Vector:
	'''Two-dimensional vector with x and y attributes'''
	def __init__(self, x=0, y=0):
		self.x = x
		self.y = y
	def __copy__(self):
		return Vector(self.x, self.y)
	def __str__(self):
		return "(%d,%d)" % (self.x,self.y)
	def __getitem__(self,i):
		if (i == 0):
			return self.x
		elif (i == 1):
			return self.y
		else:
			raise Exception, "Index '%d' out of bounds." % i
	def __setitem__(self,i,value):
		if (i == 0):
			self.x = value;
		elif (i == 1):
			self.y = value;
		else:
			raise Exception, "Index '%d' out of bounds." % i
	def dump(self):
		print self.__str__()


class Extent:
	'''Minimum and maximum boundaries of a shape defined by two corners.'''
	def __init__(self, lower=Vector(), upper=Vector(), label=0):
		self.lower = lower
		self.upper = upper
		self.label = label
	def __copy__(self):
		return Extent(copy(self.lower), copy(self.upper), self.label)
	def __str__(self):
		return "lower=%s upper=%s label=%d" % (self.lower,self.upper,self.label)
	def dump(self):
		print self.__str__()


def knife(extent, at, on):
	'''Split the extent in two at a certain point in one axis'''
	pieces = list()
	e = copy(extent)
	e.upper[on] = at
	pieces.append(e)
	e = copy(extent)
	e.lower[on] = at
	pieces.append(e)
	return pieces


def xor(A, B):
	'''Return the sections that do not overlap in two extents.'''
	pieces = dict()
	pieces[A.label] = list()
	pieces[B.label] = list()
	low = A
	high = B
	for i in range(0,2):
		if low.lower[i] > high.lower[i]:
			low, high = high, low
		if high.lower[i] < low.upper[i]:
			result = knife(low, high.lower[i], i)
			pieces[low.label].append(result[0])
			low = result[1]
			result = knife(high, low.upper[i], i)
			pieces[high.label].append(result[1])
			high = result[0]
	return pieces


def main():
	'''Print the pieces in the XOR operation'''
	pieces = xor(Extent(Vector(3,3),Vector(7,7),5), Extent(Vector(1,1),Vector(5,5),10))
	for k,v in pieces.items():
		print k
		for e in v:
			print "  %s" % e


if __name__ == '__main__':
	main()
