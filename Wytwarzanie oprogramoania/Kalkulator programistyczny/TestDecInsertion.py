import calculator
from testResult import *

class TestDecInsertion:
    def runTests(self):
        self.calculator = calculator.calculator()
        self.calculator.setType(10)
        t1=self.test1()
        testResult(t1)

        t2=self.test2()
        testResult(t2)

        t3=self.test3()
        testResult(t3)
    
    def test1(self):
        flag = True
        s1 = "q123456789"
        s2 = "891w2w34567"
        s3 = "8976543211"
        s4 = "w1e123e46879"
        test_strings = [s1, s2, s3, s4]
        results = [123456789, 891234567, 8976543211, 112346879]
        for result, string in zip(results, test_strings):
            for ch in string:
                self.calculator.appendValue(ch)
            flag = flag and (result == self.calculator.getValue())
            self.calculator.clear()

        return["DecNumbersIsertion", flag]


    def test2(self):
        s1 = "19+8"
        s2 = "-29-4"
        s3 = "16*19"
        s4 = "99/3"
        s5 = "9%5"
        results = [27, -33, 304, 33, 4]
        test_strings = [s1, s2, s3, s4, s5]
        flag = True

        for result, string in zip(results, test_strings):
            for ch in string:
                self.calculator.appendValue(ch)
            flag = flag and (result == self.calculator.getValue())
            self.calculator.clear()
        
        return["DecMathematicalOperations", flag]

    def test3(self):
        s1 = "abc9+6fgh"
        s2 = "a9d+2cg"
        s3 = "4f2*3f1"
        s4 = "1a92a2/2a"
        s5 = "10d9%5k"
        results = [15, 11, 1302, 961, 4]
        test_strings = [s1, s2, s3, s4, s5]
        flag = True

        for result, string in zip(results, test_strings):
            for ch in string:
                self.calculator.appendValue(ch)
            flag = flag and (result == self.calculator.getValue())
            self.calculator.clear()
        
        return["DecIgnoreBadCharacters", flag] 
