#!/usr/bin/python

import sys
import pylibmc

memc = pylibmc.Client(["localhost:11211"])

if memc is None:
    print "failed to create client"
    exit(1)

memc.behaviors["binary_protocol"] = 1;

if memc.set("some_key", "this is a value") is None:
    print "failed to set record"
    exit(1)

print memc.get("some_key")
