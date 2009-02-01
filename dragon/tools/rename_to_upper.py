#!/usr/bin/env python
#coding=utf-8

import sys, os, stat, uuid

UPPER_LETTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

def to_low_name(name):
	result = ""
	
	for c in name:
		if c in UPPER_LETTERS and c.upper() == c:
			if c.upper() != name[0]:
				result += "-"
			result += c.lower()
		else:
			result += c
		
	return result;

def to_upper_name(name):
	result = ""
	
	if name in ["all.h", "config.h", "dragon.h", "SConscript"]:
		return name;
		
	for i in range(0,len(name)):
		c = name[i]
		
		if i==0 or (i>0 and name[i-1]=="-"):
			result += c.upper()
		else:
			result += c
	
	name = result;
	result = ""
	
	for i in range(0,len(name)):
		c = name[i]
		
		if c!="-":
			result += c
	
	return result;
	
def cpp_to_cc(name):
	result = name
	
	if name.endswith("cpp"):
		result = name[0:len(name) - 3] + "cc"
		
	return result;

def low_rename(parent, item):
	file = os.path.join(parent, item)
	temp_file = os.path.join(parent, uuid.uuid1().get_hex())
	target_file = os.path.join(parent, to_upper_name(item))
	
	os.rename(file, temp_file)
	os.rename(temp_file, target_file)
	#print target_file
	
def handle_item(parent, item):
	low_rename(parent, item)
	

def walk(path):
	for item in os.listdir(path):
		subpath = os.path.join(path, item)
		mode = os.stat(subpath)[stat.ST_MODE]
		if not stat.S_ISDIR(mode):
			handle_item(path, item)
		else:
			walk(subpath)
			
walk(os.getcwd());
print "ok"