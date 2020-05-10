import subprocess


def main():
    tests = []
    testnum = 0
    my_executable = '../../cmake-build-debug/round_up'
    smoke_test_status = 'PASS'
    pf = 'FAIL'

    # test 1
    test1 = {'input': '1 2', 'output': '1'}
    tests.append(test1)

    # test 2
    test2 = {'input': '1 -2', 'output': '0'}
    tests.append(test2)

    # test 3
    test3 = {'input': '10 10', 'output': '1'}
    tests.append(test3)

    # test 4
    test4 = {'input': '1024 -1024', 'output': '-1'}
    tests.append(test4)

    # test 5
    test5 = {'input': '0 -5', 'output': '0'}
    tests.append(test5)

    # test 6
    test6 = {'input': '0 6', 'output': '0'}
    tests.append(test6)

    # test 7
    test7 = {'input': '-1000000000 1000000000', 'output': '-1'}
    tests.append(test7)

    # test 8
    test8 = {'input': '-1000000000 999999999', 'output': '-1'}
    tests.append(test8)

    # test 9
    test9 = {'input': '999999999 -1000000000', 'output': '0'}
    tests.append(test9)

    # test 10
    test10 = {'input': '999999999 1000000000', 'output': '1'}
    tests.append(test10)

    for test in tests:
        testnum += 1
        my_test_run = subprocess.run(my_executable, input=test['input'], capture_output=True, text=True)

        # remove newline
        my_stdout = my_test_run.stdout[:-1]
        pf = 'PASS' if my_stdout == test['output'] else 'FAIL'
        print('Test{tnum}: \n{tinput}\nres={toutput}, exp={texp}, p/f={pf}\n'.format(
            tnum=testnum,
            tinput=test['input'],
            toutput=my_stdout,
            texp=test['output'],
            pf=pf
        ))

    smoke_test_status = 'FAIL' if pf == 'FAIL' else smoke_test_status

    # after all tests complete
    if smoke_test_status == 'PASS':
        msg = 'S M O K E  T E S T S  P A S S E D'
    else:
        msg = 'S M O K E  T E S T S  F A I L E D'

    print(msg)

    return


if __name__ == '__main__':
    main()
