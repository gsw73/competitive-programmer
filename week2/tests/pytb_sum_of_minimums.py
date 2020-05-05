import subprocess
import random
import time


def get_sum_of_mins(array_A=None):
    sum_of_mins = 0
    current_min = 0
    for left in range(len(array_A)):
        for right in range(left, len(array_A)):
            current_min = array_A[left] if left == right else min(current_min, array_A[right])
            sum_of_mins += current_min

    return sum_of_mins


def main():
    tests = []
    testnum = 0
    my_executable = '../../cmake-build-debug/sum_of_minimums'
    smoke_test_status = 'PASS'

    # test 1
    test1 = {'n': 4, 'ar': [3, 1, 2, 3]}
    test1['sum_mins'] = get_sum_of_mins(test1['ar'])
    test1['input'] = str(test1['n']) + '\n{ar_str}'.format(ar_str=' '.join(str(val) for val in test1['ar']))
    test1['output'] = str(test1['sum_mins'])
    tests.append(test1)

    # test 2
    test2 = {'n': 1, 'ar': [387], 'sum_mins': 387}
    test2['input'] = str(test2['n']) + '\n{ar_str}'.format(ar_str=' '.join(str(val) for val in test2['ar']))
    test2['output'] = str(test2['sum_mins'])
    tests.append(test2)

    # test 3
    test3 = {'n': 2000}
    test3['ar'] = [random.randint(1, 1000000) for x in range(test3['n'])]
    test3['sum_mins'] = get_sum_of_mins(array_A=test3['ar'])
    test3['input'] = str(test3['n']) + '\n{ar_str}'.format(ar_str=' '.join(str(val) for val in test3['ar']))
    test3['output'] = str(test3['sum_mins'])
    tests.append(test3)

    # test 4
    test4 = {'n': 2000}
    test4['ar'] = [1000000 for x in range(test4['n'])]
    test4['sum_mins'] = 2001000000000
    test4['input'] = str(test4['n']) + '\n{ar_str}'.format(ar_str=' '.join(str(val) for val in test4['ar']))
    test4['output'] = str(test4['sum_mins'])
    tests.append(test4)

    # test 5
    test5 = {'n': 5, 'ar': [6, 7, 6, 4, 1]}
    test5['sum_mins'] = get_sum_of_mins(test5['ar'])
    test5['input'] = str(test5['n']) + '\n{ar_str}'.format(ar_str=' '.join(str(val) for val in test5['ar']))
    test5['output'] = str(test5['sum_mins'])
    tests.append(test5)

    for test in tests:
        testnum += 1
        start_time = time.time()
        my_test_run = subprocess.run(my_executable, input=test['input'], capture_output=True, text=True)
        end_time = time.time()
        proc_time = end_time - start_time

        # remove newline
        my_stdout = my_test_run.stdout[:-1]
        pf = 'PASS' if my_stdout == test['output'] else 'FAIL'

        print('Test{tnum} time={t:.6}s:  n={n} A (first 20):\n{ar}\nresult={res} expected={exp}, P/F={pf}\n'.format(
            tnum=testnum,
            t=proc_time,
            n=test['n'],
            ar=' '.join(str(val) for val in test['ar'][:20]),
            res=my_stdout,
            exp=test['output'],
            pf=pf))
        smoke_test_status = 'FAIL' if pf == 'FAIL' else smoke_test_status

    # after all tests complete
    if smoke_test_status == 'PASS':
        msg = 'S M O K E  T E S T S  P A S S E D'
    else:
        msg = 'S M O K E  T E S T S  F A I L E D'

    print(msg)


if __name__ == '__main__':
    main()
