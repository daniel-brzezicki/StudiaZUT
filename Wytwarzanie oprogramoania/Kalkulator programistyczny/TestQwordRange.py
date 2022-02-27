import calculator
from testResult import *

class TestQwordRange:
    def runTests(self):
        self.calculator = calculator.calculator()
        self.calculator.setType(10)
        self.calculator.setSize(64)

        t1=self.test1()
        testResult(t1)

        t2=self.test2()
        testResult(t2)

        t3=self.test3()
        testResult(t3)

    def test1(self):
        flag = True
        for i in range(-9223372036854775808, 9223372036854775807, int(9223372036854775808/25)):
            tostring = str(i)
            for ch in tostring:
                self.calculator.appendValue(ch)
            flag = flag and (self.calculator.getValue() == i)
            self.calculator.clear()
            
        return["QWordGoodRange", flag] 

    def test2(self):
        flag = True
        s1 = "-9223372036854775809" # -922337203685477580
        s2 = "9223372036854775808" # 922337203685477580
        
        for ch in s1:
            self.calculator.appendValue(ch)
        flag = flag and self.calculator.getValue() == -922337203685477580
        self.calculator.clear()

        for ch in s2:
            self.calculator.appendValue(ch)
        flag = flag and self.calculator.getValue() == 922337203685477580
        self.calculator.clear()

        return["QWordBadRange", flag] 
    
    def test3(self):
        flag = True
        s1 = "-9223372036854775809 + 5" # -922337203685477580 + 5 == -922337203685477575
        s2 = "9223372036854775808 + 2" # 922337203685477580 + 2 == 922337203685477582
        
        for ch in s1:
            self.calculator.appendValue(ch)
        flag = flag and self.calculator.getValue() == -922337203685477575
        self.calculator.clear()

        for ch in s2:
            self.calculator.appendValue(ch)
        flag = flag and self.calculator.getValue() == 922337203685477582
        self.calculator.clear()

        return["QWordOperatorRange", flag] 
        
