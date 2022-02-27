import calculator
from testResult import *

class TestBinInsertion:
    def runTests(self):
        self.calculator = calculator.calculator()
        self.calculator.setType(2)
        t1=self.test1()
        testResult(t1)

        t2=self.test2()
        testResult(t2)

        t3=self.test3()
        testResult(t3)

        t4=self.test4()
        testResult(t4)

        t5=self.test5()
        testResult(t5)
    
    def test1(self):
        flag = True
        s1 = "q1"
        s2 = "1ww"
        s3 = "11"
        s4 = "w1e1"
        test_strings = [s1, s2, s3, s4]
        for s in test_strings:
            count_ones = 0
            for ch in s:
                self.calculator.appendValue(ch)
                if ch == "1":
                    count_ones += 1
            flag = flag and ((2**(count_ones) - 1) == self.calculator.getValue())
            self.calculator.clear()

        return["BinOnesIsertion", flag]


    def test2(self):
        flag = True
        s1 = "q0"
        s2 = "0ww"
        s3 = "00"
        s4 = "w0e0"
        test_strings = [s1, s2, s3, s4]
        for s in test_strings:
            for ch in s:
                self.calculator.appendValue(ch)
            flag = flag and (0 == self.calculator.getValue())
            self.calculator.clear()

        return["BinZerosIsertion", flag]

    def test3(self):
        flag = True
        s1 = "+"
        s2 = "01+10"
        s3 = "0w1+e1q0"
        s4 = "010+101="
        
        results = [0, 3, 3, 7]
        test_strings = [s1, s2, s3, s4]

        for result, test in zip(results, test_strings):
            for ch in test:
                self.calculator.appendValue(ch)
            flag = flag and (result == self.calculator.getValue())
            self.calculator.clear()
        
        return["BinPlusOperationsIsertion", flag]

    def test4(self):
        s1 = "10+11"
        s2 = "-101-10"
        s3 = "11*11"
        s4 = "1000/10"
        s5 = "101%10"
        results = [5, -7, 9, 4, 1]
        test_strings = [s1, s2, s3, s4, s5]
        flag = True

        for result, string in zip(results, test_strings):
            for ch in string:
                self.calculator.appendValue(ch)
            flag = flag and (result == self.calculator.getValue())
            self.calculator.clear()
        
        return["BinMathematicalOperations", flag]

    def test5(self):
        s1 = "abc10+11fgh"
        s2 = "-1d0f1-1f0"
        s3 = "1f1*1f1"
        s4 = "1a00a0/10a"
        s5 = "10d1%10k"
        results = [5, -7, 9, 4, 1]
        test_strings = [s1, s2, s3, s4, s5]
        flag = True

        for result, string in zip(results, test_strings):
            for ch in string:
                self.calculator.appendValue(ch)
            flag = flag and (result == self.calculator.getValue())
            self.calculator.clear()
        
        return["BinIgnoreBadCharacters", flag] 
