import calculator
from testResult import *

class TestOctInsertion:
    def runTests(self):
        self.calculator = calculator.calculator()
        self.calculator.setType(8)
        t1=self.test1()
        testResult(t1)

        t2=self.test2()
        testResult(t2)

        t3=self.test3()
        testResult(t3)
    
    def test1(self):
        flag = True
        s1 = "q1234567"
        s2 = "1w2w34567"
        s3 = "76543211"
        s4 = "w1e123e467"
        test_strings = [s1, s2, s3, s4]
        results = [1234567, 1234567, 76543211, 1123467]
        for result, string in zip(results, test_strings):
            for ch in string:
                self.calculator.appendValue(ch)
            flag = flag and (int(str(result), 8) == self.calculator.getValue())
            self.calculator.clear()

        return["OctNumbersIsertion", flag]


    def test2(self):
        s1 = "31+77"
        s2 = "-22-15"
        s3 = "16*14"
        s4 = "4400/2"
        s5 = "7%5"
        results = [130, -37, 250, 2200, 2]
        test_strings = [s1, s2, s3, s4, s5]
        flag = True

        for result, string in zip(results, test_strings):
            for ch in string:
                self.calculator.appendValue(ch)
            flag = flag and (int(str(result), 8) == self.calculator.getValue())
            self.calculator.clear()
        
        return["OctMathematicalOperations", flag]

    def test3(self):
        s1 = "abc3+6fgh"
        s2 = "-2d0f4-780"
        s3 = "4f2*3f1"
        s4 = "1a42a2/2a"
        s5 = "13d1%14k"
        results = [11, -274, 1522, 611, 5]
        test_strings = [s1, s2, s3, s4, s5]
        flag = True

        for result, string in zip(results, test_strings):
            for ch in string:
                self.calculator.appendValue(ch)
            flag = flag and (int(str(result), 8) == self.calculator.getValue())
            self.calculator.clear()
        
        return["OctIgnoreBadCharacters", flag] 
