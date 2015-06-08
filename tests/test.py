#!/usr/bin/python

import unittest, os, time
from subprocess import Popen, PIPE

class TestRhock(unittest.TestCase):
    def exec(self, fn, r='a.rhobj', max_time=1.5):
        start = time.time()

        cmd = ['/bin/bash', 'run.sh', fn, r, str(max_time)]
        process = Popen(cmd, stdout=PIPE)
        process.wait()
        val = process.stdout.read()
        process.stdout.close()

        return {'output': val.decode('utf-8'), 'duration': (time.time()-start)}
    
    def shouldReturns(self, fn, val):
        result = self.exec(fn)
        self.assertEqual(result['output'], val)
    
    def shouldEquals(self, fn, val, places=2):
        result = self.exec(fn)
        self.assertAlmostEqual(float(result['output']), val, places)
    
    def multipleShouldReturns(self, fn, r, val):
        result = self.exec(fn, r)
        self.assertEqual(result['output'], val)

    def shouldLast(self, fn, val):
        result = self.exec(fn)
        self.assertAlmostEqual(result['duration'], val, 1)
    
    def multipleShouldLast(self, fn, r, val):
        result = self.exec(fn, r)
        self.assertAlmostEqual(result['duration'], val, 1)

    # Testing basics behaviours
    def test_hello_world(self):
        self.shouldReturns('basics/hello_world.s', "Hello world\n")
    
    def test_1_to_10(self):
        self.shouldReturns('basics/1_to_10.s', "1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n")
    
    def test_add(self):
        self.shouldReturns('basics/add.s', "2\n")
    
    def test_wait(self):
        self.shouldLast('basics/wait.s', 1.0)
    
    def test_vars(self):
        self.shouldReturns('basics/var.s', "x+y=3\n")
    
    def test_func(self):
        self.shouldReturns('basics/func.s', "6\n")

    def test_parallel(self):
        self.shouldReturns('basics/parallel.s', "Main\nParallel\nMain\nMain\nParallel\nMain\n")

    def test_pause_elasped(self):
        self.shouldLast('basics/pause.s', 0.4)

    def test_event(self):
        self.shouldReturns('basics/event.s', "event\n123\n456\n789\n")
    
    def test_call(self):
        self.shouldReturns('basics/call.s', "46\n")

    # Testing interraction between programs
    def test_pg_run(self):
        self.multipleShouldReturns('multiple/running1.s multiple/running2.s', 
                'a.rhobj =b.rhobj', "Program1: running program2\nProgram2 runned\n")

    def test_task2(self):
        self.shouldReturns('multiple/task2.s', "")
    
    def test_task_run(self):
        self.multipleShouldReturns('multiple/task1.s multiple/task2.s', 
                'a.rhobj b.rhobj', "Program1: running Program2 task\nProgram2: task\n")
    
    def test_var2(self):
        self.multipleShouldReturns('multiple/var1.s multiple/var2.s', 
                'a.rhobj b.rhobj', "123\n")
    
    def test_freeze(self):
        self.multipleShouldReturns('multiple/freeze1.s multiple/freeze2.s', 
                'a.rhobj b.rhobj', "1\n")
    
    def test_varset(self):
        self.multipleShouldReturns('multiple/varset1.s multiple/varset2.s', 
                'a.rhobj b.rhobj', "0\n1\n2\n")

    def test_elapsed(self):
        self.multipleShouldLast('multiple/elapsed1.s multiple/elapsed2.s',
                'a.rhobj b.rhobj', 0.3);

    # Testing errors
    def shouldError(self, fn, code):
        result = self.exec(fn)
        self.assertEqual(result['output'], 'ERROR['+str(code)+']'+"\n")
    
    def test_bad_var(self):
        self.shouldError('errors/bad_var.s', 5)
    
    def test_stack_overflow(self):
        self.shouldError('errors/stack_overflow.s', 6)
    
    def test_stack_underflow(self):
        self.shouldError('errors/stack_underflow.s', 7)

    def test_bad_jump(self):
        self.shouldError('errors/bad_jmp.s', 13)

    def test_bad_call(self):
        self.shouldError('errors/bad_call.s', 14)
    
    def test_call_overflow(self):
        self.shouldError('errors/call_overflow.s', 9)

    # Testing stdlib
    def test_cos(self):
        self.shouldEquals('std/cos.s', 0.866);

    def test_sin(self):
        self.shouldEquals('std/sin.s', 0.707);

    def test_sqrt(self):
        self.shouldEquals('std/sqrt.s', 142);

    def test_sqrt2(self):
        self.shouldEquals('std/sqrt2.s', 123);
    
    def test_neg(self):
        self.shouldReturns('std/neg.s', "-50\n")

    def test_chrono1(self):
        self.shouldLast('std/chrono.s', 1.0)
    
    def test_chrono1(self):
        self.shouldEquals('std/chrono2.s', 1)

if __name__ == '__main__':
    unittest.main()
