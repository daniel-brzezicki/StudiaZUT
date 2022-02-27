import calculator
from testResult import *

class TestInitiation:
    def runTests(self):
        self.calculator = calculator.calculator()
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
        return ["calculatorCreaton", isinstance(self.calculator, calculator.calculator)]

    def test2(self):
        return["calculatorDefaultValue", self.calculator.getValue()==0]

    def test3(self):
        return["calculatorDefaultType", self.calculator.getType()==10]

    def test4(self):
        return["calculatorDefaultSize", self.calculator.getSize()==64]

    def test5(self):
        array=self.calculator.getBinary()
            
        return["calculatorDefaultBinary", 
        isinstance(array,list) and
        len(array)==self.calculator.getSize() and
        sum(array)==0
        ]
