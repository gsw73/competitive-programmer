import subprocess
import binary_knapsack_input as bki


def main():
    tests = []
    testnum = 0
    my_executable = '../../cmake-build-debug/binary_knapsack'
    smoke_test_status = 'PASS'
    pf = 'FAIL'

    # test1
    test1 = {'n': 3, 'wmax': 5, 'wv_pairs': '1 3\n1 2\n1 1\n', 'output': '6'}
    test1['input'] = str(test1['n']) + ' ' + str(test1['wmax']) + '\n' + test1['wv_pairs']
    tests.append(test1)

    # test2
    test2 = {'n': 5, 'wmax': 10, 'wv_pairs': '1 4\n2 5\n1 2\n4 6\n8 12', 'output': '18'}
    test2['input'] = str(test2['n']) + ' ' + str(test2['wmax']) + '\n' + test2['wv_pairs']
    tests.append(test2)

    # test3
    test3 = {'n': 1, 'wmax': 5, 'wv_pairs': '8 3', 'output': '0'}
    test3['input'] = str(test3['n']) + ' ' + str(test3['wmax']) + '\n' + test3['wv_pairs']
    tests.append(test3)

    # test4
    test4 = {'n': 5, 'wmax': 8, 'wv_pairs': '2 3\n4 3\n4 7\n2 3\n2 4', 'output': '14'}
    test4['input'] = str(test4['n']) + ' ' + str(test4['wmax']) + '\n' + test4['wv_pairs']
    tests.append(test4)

    # test5
    test5 = {'n': 3, 'wmax': 75, 'wv_pairs': '64 100\n32 98\n32 1', 'output': '100'}
    test5['input'] = str(test5['n']) + ' ' + str(test5['wmax']) + '\n' + test5['wv_pairs']
    tests.append(test5)

    # test6
    test6 = {'n': 2, 'wmax': 1073741824, 'wv_pairs': '1073741824 1\n1073741824 1000000', 'output': '1000000'}
    test6['input'] = str(test6['n']) + ' ' + str(test6['wmax']) + '\n' + test6['wv_pairs']
    tests.append(test6)

    # test7
    test7 = {'n': 6, 'wmax': 40, 'wv_pairs': '1 7 4 8 4 4 8 5 8 9 16 6', 'output': '35'}
    test7['input'] = str(test7['n']) + ' ' + str(test7['wmax']) + '\n' + test7['wv_pairs']
    tests.append(test7)

    # test8
    test8 = {'n': 3, 'wmax': 1073741824, 'wv_pairs': '1073741824 5\n1073741824 6\n1 2', 'output': '6'}
    test8['input'] = str(test8['n']) + ' ' + str(test8['wmax']) + '\n' + test8['wv_pairs']
    tests.append(test8)

    # test9
    test9 = {'n': 3, 'wmax': 1073741824, 'wv_pairs': '1073741824 5\n1073741824 10\n1 2', 'output': '10'}
    test9['input'] = str(test9['n']) + ' ' + str(test9['wmax']) + '\n' + test9['wv_pairs']
    tests.append(test9)

    # test10
    test10 = {'n': 10, 'wmax': 12, 'wv_pairs': '1 6 1 3 1 9 2 4 2 10 4 2 4 1 8 1 8 9 8 6', 'output': '34'}
    test10['input'] = str(test10['n']) + ' ' + str(test10['wmax']) + '\n' + test10['wv_pairs']
    tests.append(test10)

    # test11
    bki.test11['n'] = 100
    bki.test11['wmax'] = 68335
    bki.test11['output'] = '42707'
    bki.test11['input'] = str(bki.test11['n']) + ' ' + str(bki.test11['wmax']) + '\n' + bki.test11['wv_pairs']
    tests.append(bki.test11)

    for test in tests:
        testnum += 1
        my_test_run = subprocess.run(my_executable, input=test['input'], capture_output=True, text=True)

        # remove newline
        my_stdout = my_test_run.stdout[:-1]
        pf = 'PASS' if my_stdout == test['output'] else 'FAIL'
        print('Test{tnum}:\nINPUT:\n{tinput}\nstdout={toutput}, exp={texp}, p/f={pf}\n'.format(
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
