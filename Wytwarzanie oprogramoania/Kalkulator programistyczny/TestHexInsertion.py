import calculator
from testResult import *

class TestHexInsertion:
    def runTests(self):
        self.calculator = calculator.calculator()
        self.calculator.setType(16)
        t1=self.test1()
        testResult(t1)

        t2=self.test2()
        testResult(t2)

        t3=self.test3()
        testResult(t3)
    
    def test1(self):
        flag = True
        s1 = "ff+ed"
        s2 = "10+f"
        s3 = "f-5"
        s4 = "f*e"
        test_strings = [s1, s2, s3, s4]
        results = [492, 31, 10, 210]
        for result, string in zip(results, test_strings):
            for ch in string:
                self.calculator.appendValue(ch)
            flag = flag and (result == self.calculator.getValue())
            self.calculator.clear()

        return["HexNumbersIsertion", flag]


    def test2(self):
        s1 = "a+a"
        s2 = "-f-f"
        s3 = "b*b"
        s4 = "c/c"
        s5 = "f%a"
        results = [20, -30, 121, 1, 5]
        test_strings = [s1, s2, s3, s4, s5]
        flag = True

        for result, string in zip(results, test_strings):
            for ch in string:
                self.calculator.appendValue(ch)
            flag = flag and (result == self.calculator.getValue())
            self.calculator.clear()
        
        return["HexMathematicalOperations", flag]

    def test3(self):
        s1 = "96fgh"
        s2 = "a92cg"
        s3 = "y4f2h1"
        s4 = "ahaha"
        s5 = "1d95k"
        results = [2415, 43308, 20257, 2730, 7573]
        test_strings = [s1, s2, s3, s4, s5]
        flag = True

        for result, string in zip(results, test_strings):
            for ch in string:
                self.calculator.appendValue(ch)
            flag = flag and (result == self.calculator.getValue())
            self.calculator.clear()
        
        return["HexIgnoreBadCharacters", flag] 
