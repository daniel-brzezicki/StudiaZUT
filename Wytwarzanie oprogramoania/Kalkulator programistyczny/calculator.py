import numpy as np

class calculator:
    def __init__(self):
        self.value = "0" 
        self.type = 10
        self.size = 64
        self.operations = ["+", "-", "/", "%", ".", "*", "(", ")", "&", "|", "~", "^"]
        self.numbers = ["0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "a", "b", "c", "d", "e", "f"]
        self.tempstr = ""
        self.new_expression = True
        self.last_value = 0

    def getString(self):
        val = self.getValue()
        if self.type == 2:
            return bin(val)
        elif self.type == 8:
            return oct(val)
        elif self.type == 16:
            return hex(val)
        return str(val)

    def getValue(self):
        temp = 0
        
        if len(self.tempstr) != 0:
            if self.value == "0" and not self.tempstr in self.operations:
                self.value = self.tempstr
            elif self.value == "0" and self.tempstr in self.operations:
                self.value = "0"
            else:
                self.value += self.tempstr
            self.tempstr = ""
            self.new_expression = True

        res = eval(self.value)
        self.value = str(res)

        return res

    def getType(self):
        return self.type

    def getSize(self):
        return self.size

    def getBinary(self):
        start_index = 2
        val = self.getValue()
        if val < 0:
            start_index = 3
        array=[int(x)for x in bin(val)[start_index:]]

        while len(array)!=self.size:
            array.insert(0,0)
        
        return array

    def setType(self, new_type):
        self.type = new_type

    def bindigits(self, n, bits):
        s = bin(n & int("1"*bits, 2))[2:]
        return ("{0:0>%s}" % (bits)).format(s)

    def setSize(self, new_size):
        val = self.getValue()
        old_size = self.size
        self.size = new_size
        self.value = str(val)
        if new_size < old_size:
            in_bytes = self.bindigits(self.getValue(), old_size)
            in_bytes = in_bytes[new_size:]
            new_value = 0
            if in_bytes[0] == "1":
                new_value = -(2**(new_size - 1))
            
            for i in range (1, len(in_bytes)):
                if in_bytes[i] == "1":
                    new_value += (2**(new_size - 1 - i))
            self.value = str(new_value)

    def appendValue(self, value):
        if isinstance(value, int):
            value = str(value)

        if len(value) != 1:
            return

        for op in self.operations:
            if value == op:
                self.tempstr += value
                self.new_expression = True
                return
        
        for n in range(self.type):
            if self.numbers[n] == value.lower():
                if self.new_expression == True:
                    self.new_expression = False
                    self.last_value = 0
                    if self.type == 2:
                        self.tempstr += "0b"
                    elif self.type == 8:
                        self.tempstr += "0o"
                    elif self.type == 16:
                        self.tempstr += "0x"

                self.tempstr += value
                self.last_value = eval(self.tempstr)
                if self.last_value > 2 ** (self.size - 1) - 1 or self.last_value < -(2 ** (self.size - 1)):
                    self.tempstr = self.tempstr[:-1]

                return
        

    def clear(self):
        self.value = "0"

        
    




    
        