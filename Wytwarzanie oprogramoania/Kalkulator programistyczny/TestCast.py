import calculator
from testResult import *

class TestCast:
    def runTests(self):
        self.calculator = calculator.calculator()
        self.calculator.setType(2)

        st = "11111111111"
        for ch in st:
            self.calculator.appendValue(ch)

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

        t6=self.test6()
        testResult(t6)

        t7=self.test7()
        testResult(t7)


    def test1(self):
        self.calculator.setType(8)
        flag = "0o3777" == self.calculator.getString()
        return["CastOct", flag] 

    def test2(self):
        self.calculator.setType(10)
        flag = "2047" == self.calculator.getString()
        return["CastDec", flag] 

    def test3(self):
        self.calculator.setType(16)
        flag = "0x7ff" == self.calculator.getString()
        return["CastHex", flag] 

    def test4(self):
        self.calculator.clear()
        self.calculator.setType(10)
        self.calculator.setSize(8)
        flag = True
        min_byte = "127"
        for ch in min_byte:
            self.calculator.appendValue(ch)
        flag = flag and self.calculator.getValue() == 127
        self.calculator.setSize(16)
        flag = flag and self.calculator.getValue() == 127
        return["CastByteToWord", flag]    

    def test5(self):
        self.calculator.clear()
        self.calculator.setType(10)
        self.calculator.setSize(8)
        flag = True
        min_byte = "-128"
        for ch in min_byte:
            self.calculator.appendValue(ch)
        flag = flag and self.calculator.getValue() == -128
        self.calculator.setSize(16)
        flag = flag and self.calculator.getValue() == -128
        return["CastByteToWordNegative", flag]    

    def test6(self):
        self.calculator.clear()
        self.calculator.setType(10)
        self.calculator.setSize(16)
        flag = True
        for i in range(-128, 128, 8):
            for ch in str(i):
                self.calculator.appendValue(ch)
            flag = flag and self.calculator.getValue() == i
            self.calculator.setSize(8)
            flag = flag and self.calculator.getValue() == i

            self.calculator.setSize(16)
            self.calculator.clear()
        return["CastWordToByteInformation", flag]    

    def test7(self):
        self.calculator.clear()
        self.calculator.setType(10)
        self.calculator.setSize(16)
        flag = True
        tests = ["265", "-129", "309", "-300"]
        results = [9, 127, 53, -44]
        for test, result in zip(tests, results):
            for ch in test:
                self.calculator.appendValue(ch)
            flag = flag and self.calculator.getValue() == int(test)
            self.calculator.setSize(8)
            flag = flag and self.calculator.getValue() == result
            self.calculator.setSize(16)
            self.calculator.clear()
        return["CastWordToByteLostInformation", flag]    