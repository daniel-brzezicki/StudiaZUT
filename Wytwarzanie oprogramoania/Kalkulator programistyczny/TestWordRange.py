import calculator
from testResult import *

class TestWordRange:
    def runTests(self):
        self.calculator = calculator.calculator()
        self.calculator.setType(10)
        self.calculator.setSize(16)

        t1=self.test1()
        testResult(t1)

        t2=self.test2()
        testResult(t2)

        t3=self.test3()
        testResult(t3)

    def test1(self):
        flag = True
        for i in range(-32768, 32767, int(32767/25)):
            tostring = str(i)
            for ch in tostring:
                self.calculator.appendValue(ch)
            flag = flag and (self.calculator.getValue() == i)
            self.calculator.clear()
            
        return["WordGoodRange", flag] 

    def test2(self):
        flag = True
        s1 = "-32769" # -3276
        s2 = "32768" # 3276
        
        for ch in s1:
            self.calculator.appendValue(ch)
        flag = flag and self.calculator.getValue() == -3276
        self.calculator.clear()

        for ch in s2:
            self.calculator.appendValue(ch)
        flag = flag and self.calculator.getValue() == 3276
        self.calculator.clear()

        return["WordBadRange", flag] 
    
    def test3(self):
        flag = True
        s1 = "-32769 + 5" # -3276 + 5 == -3271
        s2 = "32768 + 2" # 3276 + 2 == 3278
        
        for ch in s1:
            self.calculator.appendValue(ch)
        flag = flag and self.calculator.getValue() == -3271
        self.calculator.clear()

        for ch in s2:
            self.calculator.appendValue(ch)
        flag = flag and self.calculator.getValue() == 3278
        self.calculator.clear()

        return["WordOperatorRange", flag] 
        
