from ctypes import cdll, c_char_p
lib = cdll.LoadLibrary('clib/libhelper.so')

class Helper(object):
    def __init__(self):
        self.obj = lib.Helper_new()

    def hello(self):
        lib.hello(self.obj)
    
    def read(self, doc):
        lib.read(self.obj, c_char_p(doc));