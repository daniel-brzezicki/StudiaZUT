import TestInitiation
import calculator
import TestBinInsertion
import TestOctInsertion
import TestDecInsertion
import TestHexInsertion
import TestByteRange
import TestDwordRange
import TestWordRange
import TestQwordRange
import TestCast

if __name__ == "__main__":
    test1 = TestInitiation.TestInitiation()
    test1.runTests() 

    test2 = TestBinInsertion.TestBinInsertion()
    test2.runTests()

    test3 = TestOctInsertion.TestOctInsertion()
    test3.runTests()

    test4 = TestDecInsertion.TestDecInsertion()
    test4.runTests()

    test4 = TestHexInsertion.TestHexInsertion()
    test4.runTests()

    test5 = TestByteRange.TestByteRange()
    test5.runTests()

    test6 = TestDwordRange.TestDwordRange()
    test6.runTests()

    test7 = TestWordRange.TestWordRange()
    test7.runTests()

    test8 = TestQwordRange.TestQwordRange()
    test8.runTests()

    test9 = TestCast.TestCast()
    test9.runTests()
