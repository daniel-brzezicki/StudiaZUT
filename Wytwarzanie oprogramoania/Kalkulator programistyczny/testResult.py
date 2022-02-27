def testResult(r):
    WHITE = '\033[00m'


    if(r[1]==True):
        COLOR='\033[92m'
    else:
        COLOR='\033[91m'


    print(f"{WHITE}test name: {r[0]}, pass: {COLOR}{r[1]}{WHITE}")