import calculator
from testResult import *

class TestByteRange:
    def runTests(self):
        self.calculator = calculator.calculator()
        self.calculator.setType(10)
        self.calculator.setSize(8)

        t1=self.test1()
        testResult(t1)

        t2=self.test2()
        testResult(t2)

        t3=self.test3()
        testResult(t3)

    def test1(self):
        flag = True
        for i in range(-128, 128, 1):
            tostring = str(i)
            for ch in tostring:
                self.calculator.appendValue(ch)
            flag = flag and (self.calculator.getValue() == i)
            self.calculator.clear()
            
        return["ByteGoodRange", flag] 

    def test2(self):
        flag = True
        s1 = "-129" # -12
        s2 = "291" # 29
        
        for ch in s1:
            self.calculator.appendValue(ch)
        flag = flag and self.calculator.getValue() == -12
        self.calculator.clear()

        for ch in s2:
            self.calculator.appendValue(ch)
        flag = flag and self.calculator.getValue() == 29
        self.calculator.clear()

        return["ByteBadRange", flag] 
    
    def test3(self):
        flag = True
        s1 = "-129+5" # -12 + 5 == -7
        s2 = "291+8" # 29 + 8 == 37
        
        for ch in s1:
            self.calculator.appendValue(ch)
        flag = flag and self.calculator.getValue() == -7
        self.calculator.clear()

        for ch in s2:
            self.calculator.appendValue(ch)
        flag = flag and self.calculator.getValue() == 37
        self.calculator.clear()

        return["ByteOperatorRange", flag] 
        
