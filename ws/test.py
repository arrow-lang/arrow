# -*- coding: utf-8 -*-
from __future__ import print_function
from subprocess import Popen, PIPE
from os import path
import sys

_passed = 0
_failed = 0
_xfailed = 0
_xpassed = 0


def read_suffix(filename, suffix):
    try:
        with open(path.splitext(filename)[0] + suffix, 'rb') as stream:
            return stream.read()

    except:
        return None


def get_expected(filename, item):
    fn = path.splitext(filename)[0] + "." + item
    if path.exists(fn):
        with open(fn, "rb") as stream:
            return stream.read().decode('utf-8')

    return ""


def print_test(file_, status):
    global _passed
    global _failed
    global _xfailed
    global _xpassed

    # Check if we are "expected" to fail
    xfail = read_suffix(file_.abspath(), ".xfail") is not None

    filename = path.relpath(file_.abspath())
    if not status:
        if xfail:
            _xfailed += 1
            print("\033[30;1m{:<72}: {}\033[0m".format(filename, 'XFAIL'))
        else:
            _failed += 1
            print("\033[31m{:<72}: {}\033[0m".format(filename, 'FAIL'))

    else:
        if xfail:
            _xpassed += 1
            print("\033[31m{:<72}: {}\033[0m".format(filename, 'XPASS'))
        else:
            _passed += 1
            print("{:<72}: \033[32m{}\033[0m".format(filename, 'PASS'))


def print_sep(msg, sep="-", width=80, end="\n"):
    width -= len(msg) + 2
    left = right = width // 2

    if width % 2 != 0:
        right += 1

    print(sep * left, msg, sep * right, end=end)


def print_report():
    print()

    message = []
    if _passed:
        message.append("{} passed".format(_passed))

    if _failed:
        message.append("{} failed".format(_failed))

    if _xfailed:
        message.append("{} xfailed".format(_xfailed))

    if _xpassed:
        message.append("{} xpassed".format(_xpassed))

    message = ', '.join(message)

    if not _failed:
        sys.stdout.write("\033[1;32m")
        print_sep(message, sep='=')
        sys.stdout.write("\033[0m")

    else:
        sys.stdout.write("\033[1;31m")
        print_sep(message, sep='=')
        sys.stdout.write("\033[0m")


def run_(name, ctx, binary_path):
    print()
    print_sep(name)

    fail = name.endswith("-fail")
    key = name
    if fail:
        key = name.split("-fail")[0]

    for file_ in ctx.path.ant_glob("test/%s/*.as" % name):
        # Execute the handler
        handler = globals()["handle_%s" % key.replace("-", "_")]
        test = handler(
            handle_fail_ if fail else handle_, binary_path, file_.abspath())

        # Print result
        print_test(file_, test)


def handle_(binary_path, filename, *args, **kwargs):
    transform_stdout = kwargs.pop("transform_stdout", None)

    filename = path.relpath(filename)

    process = Popen(
        [binary_path] + list(args) + [filename], stdout=PIPE, stderr=PIPE,
        cwd=path.join(path.dirname(__file__), ".."),
    )

    stdout, _ = process.communicate()
    stdout = stdout.decode('utf-8')
    if transform_stdout:
        stdout = transform_stdout(stdout)

    expected = get_expected(filename, "stdout")
    test = True

    if len(stdout) > 0:
        test = test and (len(expected) > 0 and expected == stdout)

    test = test and process.returncode == 0
    return test


def handle_fail_(binary_path, filename, *args, **kwargs):
    filename = path.relpath(filename)
    process = Popen(
        [binary_path] + list(args) + [filename], stdout=PIPE, stderr=PIPE,
        cwd=path.join(path.dirname(__file__), ".."),
    )

    _, stderr = process.communicate()
    stderr = stderr.decode('utf-8')

    expected = get_expected(filename, "stderr")
    test = len(expected) > 0 and expected == stderr and process.returncode == 1

    return test


def handle_read(fn, binary_path, filename):
    return fn(binary_path, filename, "--read")


def handle_tokenize(fn, binary_path, filename):
    return fn(binary_path, filename, "--tokenize")


def handle_parse(fn, binary_path, filename):
    return fn(binary_path, filename, "--parse")


def handle_compile(fn, binary_path, filename):
    def transform(stdout):
        lines = stdout.strip().split("\n")[4:]
        lines.append("")

        return "\n".join(lines)

    return fn(binary_path, filename, "--compile",
              transform_stdout=transform)


def handle_run(_, binary_path, filename):
    filename = path.relpath(filename)
    p = Popen(
        [binary_path, "--compile", filename], stdout=PIPE, stderr=PIPE,
        cwd=path.join(path.dirname(__file__), ".."),
    )
    interpreter = Popen(["lli"], stdin=p.stdout, stdout=PIPE, stderr=PIPE)

    stdout, _ = interpreter.communicate()

    expected = get_expected(filename, "stdout")
    test = expected == stdout.decode('utf-8') and interpreter.returncode == 0

    return test


# def handle_run_fail(binary_path, filename):
#     filename = path.relpath(filename)
#     p = Popen(
#         [binary_path, filename], stdout=PIPE, stderr=PIPE,
#         cwd=path.join(path.dirname(__file__), ".."),
#     )
#     interpreter = Popen(["lli"], stdin=p.stdout, stdout=PIPE, stderr=PIPE)
#
#     stdout, _ = interpreter.communicate()
#
#     expected = get_expected(filename, "stdout")
#     test = expected == stdout.decode('utf-8') and interpreter.returncode != 0
#
#     return test


def run(ctx):
    print_sep("test session starts", "=", end="")

    binary_path = ctx.path.make_node("build/arrow").abspath()

    run_("tokenize", ctx, binary_path)
    # run_("tokenize-fail", ctx, binary_path)
    # run_("parse", ctx, binary_path)
    # run_("parse-fail", ctx, binary_path)
    # run_("compile", ctx, binary_path)
    # run_("compile-fail", ctx, binary_path)
    # run_("run", ctx, binary_path)

    print_report()

    return _failed == 0
