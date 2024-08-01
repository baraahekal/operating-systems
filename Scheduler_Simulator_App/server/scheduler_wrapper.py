import ctypes
from ctypes import Structure, c_int, POINTER
from typing import List


class Result(Structure):
    _fields_ = [("total_distance", c_int),
                ("seek_sequence", POINTER(c_int)),
                ("sequence_length", c_int)]


lib = ctypes.CDLL("./libdisk_scheduling.so")

lib.FCFS.argtypes = (POINTER(c_int), c_int, c_int)
lib.FCFS.restype = Result

lib.SSTF.argtypes = (POINTER(c_int), c_int, c_int)
lib.SSTF.restype = Result

lib.SCAN.argtypes = (POINTER(c_int), c_int, c_int, c_int)
lib.SCAN.restype = Result

lib.LOOK.argtypes = (POINTER(c_int), c_int, c_int)
lib.LOOK.restype = Result

lib.C_SCAN.argtypes = (POINTER(c_int), c_int, c_int, c_int)
lib.C_SCAN.restype = Result

lib.C_LOOK.argtypes = (POINTER(c_int), c_int, c_int)
lib.C_LOOK.restype = Result

lib.free_result.argtypes = (Result,)
lib.free_result.restype = None


def extract_result(result):
    seek_sequence = [result.seek_sequence[i] for i in range(result.sequence_length)]
    lib.free_result(result)
    return {"total_distance": result.total_distance, "seek_sequence": seek_sequence}


def fcfs(requests: List[int], starting_head: int):
    num_requests = len(requests)
    arr = (c_int * num_requests)(*requests)
    result = lib.FCFS(arr, num_requests, starting_head)
    return extract_result(result)


def sstf(requests: List[int], starting_head: int):
    num_requests = len(requests)
    arr = (c_int * num_requests)(*requests)
    result = lib.SSTF(arr, num_requests, starting_head)
    return extract_result(result)


def scan(requests: List[int], starting_head: int, cylinders: int):
    num_requests = len(requests)
    arr = (c_int * num_requests)(*requests)
    result = lib.SCAN(arr, num_requests, starting_head, cylinders)
    return extract_result(result)


def look(requests: List[int], starting_head: int):
    num_requests = len(requests)
    arr = (c_int * num_requests)(*requests)
    result = lib.LOOK(arr, num_requests, starting_head)
    return extract_result(result)


def c_scan(requests: List[int], starting_head: int, cylinders: int):
    num_requests = len(requests)
    arr = (c_int * num_requests)(*requests)
    result = lib.C_SCAN(arr, num_requests, starting_head, cylinders)
    return extract_result(result)


def c_look(requests: List[int], starting_head: int):
    num_requests = len(requests)
    arr = (c_int * num_requests)(*requests)
    result = lib.C_LOOK(arr, num_requests, starting_head)
    return extract_result(result)
