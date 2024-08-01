import ctypes
import os

# Load the shared library
lib = ctypes.CDLL(os.path.abspath("libdisk_scheduling.so"))

# Define the argument and return types for each function
lib.FCFS.argtypes = (ctypes.POINTER(ctypes.c_int), ctypes.c_int, ctypes.c_int)
lib.FCFS.restype = ctypes.c_int

lib.SSTF.argtypes = (ctypes.POINTER(ctypes.c_int), ctypes.c_int, ctypes.c_int)
lib.SSTF.restype = ctypes.c_int

lib.SCAN.argtypes = (ctypes.POINTER(ctypes.c_int), ctypes.c_int, ctypes.c_int, ctypes.c_int)
lib.SCAN.restype = ctypes.c_int

lib.LOOK.argtypes = (ctypes.POINTER(ctypes.c_int), ctypes.c_int, ctypes.c_int)
lib.LOOK.restype = ctypes.c_int

lib.C_SCAN.argtypes = (ctypes.POINTER(ctypes.c_int), ctypes.c_int, ctypes.c_int, ctypes.c_int)
lib.C_SCAN.restype = ctypes.c_int

lib.C_LOOK.argtypes = (ctypes.POINTER(ctypes.c_int), ctypes.c_int, ctypes.c_int)
lib.C_LOOK.restype = ctypes.c_int


def fcfs(requests, starting_head):
    n = len(requests)
    arr = (ctypes.c_int * n)(*requests)
    return lib.FCFS(arr, n, starting_head)


def sstf(requests, starting_head):
    n = len(requests)
    arr = (ctypes.c_int * n)(*requests)
    return lib.SSTF(arr, n, starting_head)


def scan(requests, starting_head, cylinders):
    n = len(requests)
    arr = (ctypes.c_int * n)(*requests)
    return lib.SCAN(arr, n, starting_head, cylinders)


def look(requests, starting_head):
    n = len(requests)
    arr = (ctypes.c_int * n)(*requests)
    return lib.LOOK(arr, n, starting_head)


def c_scan(requests, starting_head, cylinders):
    n = len(requests)
    arr = (ctypes.c_int * n)(*requests)
    return lib.C_SCAN(arr, n, starting_head, cylinders)


def c_look(requests, starting_head):
    n = len(requests)
    arr = (ctypes.c_int * n)(*requests)
    return lib.C_LOOK(arr, n, starting_head)
