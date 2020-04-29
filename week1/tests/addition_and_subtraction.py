import subprocess


def main():
    executable = '../../cmake-build-debug/addition_and_subtraction'
    tests = []
    smoke_test_status = 'PASS'

    test1 = {'input': '2 1 3', 'output': '3'}
    tests.append(test1)
    test2 = {'input': '2 0 3', 'output': '-1'}
    tests.append(test2)
    test3 = {'input': '2 1 1000', 'output': '1997'}
    tests.append(test3)
    test4 = {'input': '2 0 1000', 'output': '999'}
    tests.append(test4)
    test5 = {'input': '999 1000 1', 'output': '1997'}
    tests.append(test5)
    test6 = {'input': '47 12 817', 'output': '45'}
    tests.append(test6)

    for test in tests:
        # run the test
        my_test_run = subprocess.run([executable], input=test['input'], capture_output=True, text=True)

        # sometimes I have a \n at end of result, sometimes not; remove it here
        my_stdout = my_test_run.stdout[0:-1] if my_test_run.stdout[-1] == '\n' else my_test_run.stdout

        # check pass/fail
        pf = 'PASS' if my_stdout == test['output'] else 'FAIL'
        print('stdin: {myin}, result: {myout}, expected: {exp}, P/F: {pf}'.format(myin=test['input'],
                                                                                  myout=my_stdout,
                                                                                  exp=test['output'], pf=pf))
        smoke_test_status = 'FAIL' if pf == 'FAIL' else smoke_test_status

    # after all tests complete
    if smoke_test_status == 'PASS':
        msg = 'S M O K E  T E S T S  P A S S E D'
    else:
        msg = 'S M O K E  T E S T S  F A I L E D'

    print(msg)

    return 0


if __name__ == '__main__':
    main()
