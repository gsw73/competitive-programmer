import subprocess
import argparse
import random
import time


def check_9s(num_str):
    all_nines = True
    mylength = 0

    for char in num_str:
        if char.isdecimal():
            mylength = mylength + 1
            if char != '9':
                all_nines = False

    return mylength, all_nines


def get_num_str(str_len=10):
    digits_str = '0123456789'
    digits_list = list(digits_str)
    all_nines = True

    my_num_str = ''
    for i in range(str_len):
        my_num_str = my_num_str + random.choice(digits_list)
        all_nines = False if my_num_str[-1] != '9' else all_nines

    return my_num_str, all_nines


def main():
    parser = argparse.ArgumentParser(description='Test program 1.3, Increment, with two Methods.')
    parser.add_argument('-m', '--method', type=str, choices=['time', 'memory', 'getline'],
                        default='memory',
                        help='chooses input operator as memory:>>-to-c++-string, time:cin.get(char&), and getline:cin.getline(char*)')
    options = parser.parse_args()

    executable = '../../cmake-build-debug/increment'
    method1 = [executable]
    method2 = [executable, '2']
    method3 = [executable, '3']
    method = method2 if options.method == 'time' else method1 if options.method == 'memory' else method3
    method_str = '2/time' if options.method == 'time' else '1/mem' if options.method == 'memory' else '3/getline'
    tests = []
    smoke_test_status = 'PASS'

    test1 = {'input': '1', 'output': '1'}
    tests.append(test1)
    test2 = {'input': '9', 'output': '2'}
    tests.append(test2)

    test3_input_st = '235817923775927835900283752'
    test3_input_len = len(test3_input_st)
    test3_output_len = test3_input_len + 1 if test3_input_st[-1] == '9' else test3_input_len
    test3 = {'input': test3_input_st, 'output': str(test3_output_len)}
    tests.append(test3)

    test4_input_len = 5
    test4_input_str, incr = get_num_str(test4_input_len)
    test4_output_len = test4_input_len + 1 if incr else test4_input_len
    test4 = {'input': test4_input_str, 'output': str(test4_output_len)}
    tests.append(test4)

    test5_input_len = 1000000
    test5_input_str, incr = get_num_str(test5_input_len)
    test5_output_len = test5_input_len + 1 if incr else test5_input_len
    test5 = {'input': test5_input_str, 'output': str(test5_output_len)}
    tests.append(test5)

    test6 = {'input': '999919 '}
    test6_input_len, all_nines = check_9s( test6['input'])
    test6_output_len = test6_input_len + 1 if all_nines else test6_input_len
    test6['output'] = str(test6_output_len)
    tests.append(test6)

    test7_input_str = '899999999999999999999999999999'
    test7_input_len, all_nines = check_9s(test7_input_str)
    test7_output_len = test7_input_len + 1 if all_nines else test7_input_len
    test7 = {'input': test7_input_str, 'output': str(test7_output_len)}
    tests.append(test7)

    test8 = {'input': '   999   ', 'output': '4'}
    tests.append(test8)

    # test 9
    test9_input_len = 1000000
    test9_input_str = ''
    for val in range(test9_input_len):
        test9_input_str += '9'
    test9_output_len = test9_input_len + 1
    test9 = {'input': test9_input_str, 'output': str(test9_output_len)}
    tests.append(test9)

    # test 10
    test10_input_len = 1000000
    test10_input_str = ''
    for val in range(test10_input_len):
        if val == 436789:
            test10_input_str += '3'
        else:
            test10_input_str += '9'
    test10 = {'input': test10_input_str, 'output': str(test10_input_len)}
    tests.append(test10)


    for test in tests:
        # run the test
        start_time = time.time()
        my_test_run = subprocess.run(method, input=test['input'], capture_output=True, text=True)
        end_time = time.time()
        proc_time = end_time - start_time

        # sometimes I have a \n at end of result, sometimes not; remove it here
        my_stdout = my_test_run.stdout[0:-1] if my_test_run.stdout[-1] == '\n' else my_test_run.stdout

        # check pass/fail
        pf = 'PASS' if my_stdout == test['output'] else 'FAIL'
        print(
            'Method{meth} time={t:.6}s stdin (first 100 digits):\n{myin}\nresult: {myout}, expected: {exp}, P/F: {pf}\n'.format(
                meth=method_str,
                myin=test['input'][0:100],
                myout=my_stdout,
                exp=test['output'],
                pf=pf,
                t=proc_time))
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
