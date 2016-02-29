#! /usr/bin/env python3
# -*- coding: UTF-8 -*-

import sys
import os
import subprocess
import re


failedtest = re.compile(r'^\s*Polly \:\: (?P<testpath>\S*)\s*$',re.MULTILINE)

def main():
  script = sys.argv[0]
  scriptdir = os.path.dirname(script)
  cwd = os.path.curdir
  lit_check = sys.argv[1:]

  with subprocess.Popen(lit_check, stdout=subprocess.PIPE,universal_newlines=True) as p:
        stdout, stderr = p.communicate()
        retcode = p.poll()
        if retcode==0:
            print("lit passed all tests")
            return

  for x in failedtest.finditer(stdout):
      testpath = x.group('testpath')
      print("Updating test", testpath,'...')
      subprocess.check_call([sys.executable,os.path.join(cwd,'bin','update_check.py'), '-i', testpath])

if __name__ == '__main__':
    main()
