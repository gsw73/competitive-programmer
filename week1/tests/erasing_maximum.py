import subprocess


def main():
    executable = '../../cmake-build-debug/erasing_maximum'
    tests = []
    smoke_test_status = 'PASS'
    test4_input_str = ''
    test4_output_str = ''

    test1 = {'input':'3\n1 3 2', 'output':'1 2'}
    tests.append(test1)
    test2 = {'input':'7\n4 1 4 2 4 3 4', 'output':'4 1 4 2 3 4'}
    tests.append(test2)
    test3 = {'input':'18\n1 2 3 4 4 8 2 3 8 4 1 7 8 2 8 3 8 9', 'output':'1 2 3 4 4 8 2 3 8 4 1 7 8 2 8 3 8'}
    tests.append(test3)

    test4_input = [ 99, 98, 97, 100, 23, 1, 5, 99, 99, 88, 99, 23, 99 ]
    test4_output = [ 99, 98, 97, 23, 1, 5, 99, 99, 88, 99, 23, 99 ]
    for val in test4_input:
        test4_input_str = test4_input_str + str(val) + ' '
    for val in test4_output:
        if test4_output_str != '':
            test4_output_str += ' '
        test4_output_str = test4_output_str + str(val)
    test4_length = len(test4_input)
    test4 = {'input':'{l}\n{seq}'.format(l=test4_length, seq=test4_input_str), 'output':test4_output_str}
    tests.append(test4)

    for test in tests:
        # run the test
        my_test_run = subprocess.run([executable], input=test['input'], capture_output=True, text=True)

        # sometimes I have a \n at end of result, sometimes not; remove it here
        my_stdout = my_test_run.stdout[0:-1] if my_test_run.stdout[-1] == '\n' else my_test_run.stdout

        # check pass/fail
        pf = 'PASS' if my_stdout == test['output'] else 'FAIL'
        print('stdin:\n{myin}\nresult: {myout}, expected: {exp}, P/F: {pf}\n'.format(myin=test['input'],
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
