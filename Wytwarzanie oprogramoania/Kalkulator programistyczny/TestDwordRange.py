import calculator
from testResult import *

class TestDwordRange:
    def runTests(self):
        self.calculator = calculator.calculator()
        self.calculator.setType(10)
        self.calculator.setSize(32)

        t1=self.test1()
        testResult(t1)

        t2=self.test2()
        testResult(t2)

        t3=self.test3()
        testResult(t3)

    def test1(self):
        flag = True
        for i in range(-2147483648, 2147483647, int(2147483648/25)):
            tostring = str(i)
            for ch in tostring:
                self.calculator.appendValue(ch)
            flag = flag and (self.calculator.getValue() == i)
            self.calculator.clear()
            
        return["DWordGoodRange", flag] 

    def test2(self):
        flag = True
        s1 = "-2147483649" # -214748364
        s2 = "2147483648" # 214748364
        
        for ch in s1:
            self.calculator.appendValue(ch)
        flag = flag and self.calculator.getValue() == -214748364
        self.calculator.clear()

        for ch in s2:
            self.calculator.appendValue(ch)
        flag = flag and self.calculator.getValue() == 214748364
        self.calculator.clear()

        return["DWordBadRange", flag] 
    
    def test3(self):
        flag = True
        s1 = "-2147483649 + 5" # -214748364 + 5 == -214748359
        s2 = "2147483648 + 2" # 214748364 + 2 == 214748366
        
        for ch in s1:
            self.calculator.appendValue(ch)
        flag = flag and self.calculator.getValue() == -214748359
        self.calculator.clear()

        for ch in s2:
            self.calculator.appendValue(ch)
        flag = flag and self.calculator.getValue() == 214748366
        self.calculator.clear()

        return["DWordOperatorRange", flag] 
        
