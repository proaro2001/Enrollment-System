# Enrollment-System

Done by Choi Ka Hin, Malachi Ojala


No memory leaks.

There are two errors found using check-code-coverage.sh:

    1:  Course constructor takes in two strings, which clang only complains about because
        they could be swapped on accident by the user which would mess up the intended input.

    2:  Student constructor takes in a string for first name and last name, which  clang only
        complains about because the user could put them in the wrong order without realizing.

Explanation:
    Both these errors could be fixed by having a single string with the information and then parsing to
    extract the information, but that orignial string could still be formatted by the user incorrectly,
    so it doesn't really matter that there are two parameters with the same data type. 
