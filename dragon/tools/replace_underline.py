#!/usr/bin/env python
#coding=utf-8

import sys, os, stat, uuid

UPPER_LETTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

def to_low_name(name):
	result = ""
	
	for c in name:
		if c in UPPER_LETTERS and c.upper() == c:
			if c.upper() != name[0]:
				result += "_"
			result += c.lower()
		else:
			result += c
		
	return result;
	
def replace_line(name):
	result = ""
	
	for c in name:
		if c == "_":
			result += "-"
		else:
			result += c
		
	return result;
	
def walk(path):
	for item in os.listdir(path):
		subpath = os.path.join(path, item)
		mode = os.stat(subpath)[stat.ST_MODE]
		if not stat.S_ISDIR(mode):
			temp_item = uuid.uuid1().get_hex()
			os.rename(item, temp_item)
			os.rename(temp_item, replace_line(item))
			
walk(os.getcwd());