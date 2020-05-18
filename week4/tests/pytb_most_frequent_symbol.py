import subprocess
import input_most_frequent_symbol as myin


def main():
    tests = []
    testnum = 0
    my_executable = '../../cmake-build-debug/most_frequent_symbol'
    smoke_test_status = 'PASS'
    pf = 'FAIL'

    # test1
    test1 = {'st': 'abacaba', 'q': 3, 'queries': '1 1\n1 7\n2 4'}
    test1['output'] = 'a\na\nc'
    test1['input'] = test1['st'] + '\n' + str(test1['q']) + '\n' + test1['queries']
    tests.append(test1)
    
    # test2
    test2 = {'st': 'abcadada', 'q': 9, 'queries': '2 7\n3 8\n1 2\n4 4\n5 8\n5 7\n2 6\n5 6\n1 8'}
    test2['output'] = 'd\na\nb\na\nd\nd\na\nd\na'
    test2['input'] = test2['st'] + '\n' + str(test2['q']) + '\n' + test2['queries']
    tests.append(test2)
    
    # test3
    test3 = {'st': 'abba', 'q': 6, 'queries': '1 1\n2 2\n1 2\n2 3\n1 1\n2 4\n'}
    test3['output'] = 'a\nb\nb\nb\na\nb'
    test3['input'] = test3['st'] + '\n' + str(test3['q']) + '\n' + test3['queries']
    tests.append(test3)

    # test4
    test4 = myin.testa
    tests.append(test4)

    for test in tests:
        testnum += 1
        my_test_run = subprocess.run(my_executable, input=test['input'], capture_output=True, text=True)

        # remove newline
        my_stdout = my_test_run.stdout[:-1]
        pf = 'PASS' if my_stdout == test['output'] else 'FAIL'
        print('Test{tnum}:\nINPUT:\n{tinput}\nstdout=\n{tstdout}\nexp=\n{texp}\np/f={tpf}\n'.format(
            tnum=testnum,
            tinput=test['input'],
            tstdout=my_stdout,
            texp=test['output'],
            tpf=pf
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
