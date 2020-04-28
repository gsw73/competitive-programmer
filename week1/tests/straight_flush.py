import sys
import os.path
import subprocess


# Fully Automated Random testing
# create set of 52 playing cards and randomly choose five cards, pass to stdin of straight_flush
# and check whether or not result is correct

# Directed Testing
# run in loop with manually created five-card tests and correct answer

def main():
    print('hello Python world')

    executable = '../../cmake-build-debug/straight_flush'
    test1 = {'input': 'AD KH QH JS TC', 'output': 'NO'}
    test2 = {'input': '2H 3H 4H 5H 6H', 'output': 'YES'}
    test3 = {'input': '2D 3D AD 4D 5D', 'output': 'YES'}
    test4 = {'input': 'AD 2D 3H 4D 5D', 'output': 'NO'}
    test5 = {'input': 'AC JC TC KC QC', 'output': 'YES'}
    test6 = {'input': 'KS 2S 3S 4S AS', 'output': 'NO'}
    test7 = {'input': 'AC JC TD KH QS', 'output': 'NO'}

    tests = [test1, test2, test3, test4, test5, test6, test7]

    for test in tests:
        my_test_run = subprocess.run([executable], input=test['input'], capture_output=True, text=True)
        pf = 'PASS' if my_test_run.stdout == test['output'] else 'FAIL'
        print('stdin: {myin}, result: {myout}, expected: {exp}, P/F: {pf}'.format(myin=test['input'],
                                                                                  myout=my_test_run.stdout,
                                                                                  exp=test['output'], pf=pf))

    return


if __name__ == '__main__':
    main()
