import subprocess


def main():
    tests = []
    testnum = 0
    my_executable = '../../cmake-build-debug/compare_sums'
    EQ = 'SUM(A)=SUM(B)'
    GT = 'SUM(A)>SUM(B)'
    LT = 'SUM(A)<SUM(B)'
    smoke_test_status = 'PASS'

    # test1
    test1 = {'n': 2, 'arA':['1.500', '1.500'], 'arB':['1.000', '2.000']}
    test1['input'] = str(test1['n']) + '\n' + '{line2}\n{line3}'.format(
        line2=' '.join(val for val in test1['arA']),
        line3=' '.join(val for val in test1['arB'])
    )
    test1['output'] = EQ
    tests.append(test1)
    
    # test 2
    test2 = {'n': 1, 'arA':['2.000'], 'arB':['1.123']}
    test2['input'] = str(test2['n']) + '\n' + '{line2}\n{line3}'.format(
        line2=' '.join(val for val in test2['arA']),
        line3=' '.join(val for val in test2['arB'])
    )
    test2['output'] = GT
    tests.append(test2)

    # test 3
    test3 = {'n': 3, 'arA':['1.000', '2.000', '3.000'], 'arB':['1.001', '2.001', '3.001']}
    test3['input'] = str(test3['n']) + '\n' + '{line2}\n{line3}'.format(
        line2=' '.join(val for val in test3['arA']),
        line3=' '.join(val for val in test3['arB'])
    )
    test3['output'] = LT
    tests.append(test3)
    
    # test 4
    test4 = {'n': 3, 'arA':['0.059', '0.060', '0.022'], 'arB':['0.043', '0.031', '0.067']}
    test4['input'] = str(test4['n']) + '\n' + '{line2}\n{line3}'.format(
        line2=' '.join(val for val in test4['arA']),
        line3=' '.join(val for val in test4['arB'])
    )
    test4['output'] = EQ
    tests.append(test4)

    # test 5
    test5 = {'n': 100}
    test5['arA'] = ['1000.000' for val in range(99)]
    test5['arA'].append('999.987')
    test5['arB'] = ['1000.000' for val in range(99)]
    test5['arB'].append('999.986')
    test5['input'] = str(test5['n']) + '\n' + '{line2}\n{line3}'.format(
        line2=' '.join(val for val in test5['arA']),
        line3=' '.join(val for val in test5['arB'])
    )
    test5['output'] = GT
    tests.append(test5)

    # test 6
    test6 = {'n': 12}
    test6['arA'] = '59.817 18.506 232.138 147.107 64.898 71.866 93.036 125.764 177.597 150.949 115.519 153.925'.split(' ')
    test6['arB'] = '82.505 96.629 158.467 149.776 184.887 97.629 66.071 137.763 61.851 141.297 52.113 182.134'.split(' ')
    test6['input'] = str(test6['n']) + '\n' + '{line2}\n{line3}'.format(
        line2=' '.join(val for val in test6['arA']),
        line3=' '.join(val for val in test6['arB'])
    )
    test6['output'] = EQ
    tests.append(test6)
    
    # test 7
    test7 = {'n': 50}
    test7['arA'] = '469.535 246.763 283.747 295.695 229.783 374.355 295.133 302.161 184.576 310.073 137.268 276.906 199.164 111.689 437.301 164.382 44.009 402.991 390.828 201.062 316.322 279.748 346.087 201.720 152.900 232.002 320.228 224.417 426.945 478.357 138.702 257.197 447.792 253.887 179.199 466.306 269.709 113.093 464.118 452.788 128.636 337.047 133.596 213.138 450.218 176.727 290.933 458.967 446.190 96.837'.split(' ')
    test7['arB'] = '172.313 163.509 259.028 120.292 184.008 160.263 441.009 284.403 420.302 406.195 457.258 140.107 168.283 294.508 425.616 125.685 332.320 271.583 481.448 293.877 119.600 282.749 270.843 277.349 178.084 263.597 443.042 296.504 260.843 257.500 386.195 451.946 145.851 244.443 131.006 141.182 147.590 394.375 338.149 447.720 163.699 160.120 362.978 295.421 502.392 520.076 226.303 128.956 258.266 412.441'.split(' ')
    test7['input'] = str(test7['n']) + '\n' + '{line2}\n{line3}'.format(
        line2=' '.join(val for val in test7['arA']),
        line3=' '.join(val for val in test7['arB'])
    )
    test7['output'] = EQ
    tests.append(test7)
    
    for test in tests:
        testnum += 1
        my_test_run = subprocess.run(my_executable, input=test['input'], capture_output=True, text=True)

        # remove newline
        my_stdout = my_test_run.stdout[:-1]
        pf = 'PASS' if my_stdout == test['output'] else 'FAIL'
        print('Test{tnum}: \n{tinput}\nstdout:\nres={toutput}, exp={texp}, p/f={pf}\n'.format(
            tnum=test['n'],
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
