import subprocess


def main():
    tests = []
    testnum = 0
    my_executable = '../../cmake-build-debug/yet_another_sum'
    smoke_test_status = 'PASS'
    pf = 'FAIL'

    # test 1
    test1 = {'input': '1\n3', 'output': '3.3333333333'}
    tests.append(test1)

    # test 2
    test2 = {'input': '1\n-4', 'output': '-4.2500000000'}
    tests.append(test2)

    # test 3
    test3 = {'input': '4\n-2 -3 1 2', 'output': '-1.3333333333'}
    tests.append(test3)

    # test 4
    test4 = {'input': '6\n1000000000 -999999999 999999993 -999999997 999999123 -999999125', 'output': '-5.0000000000'}
    tests.append(test4)

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
