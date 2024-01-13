import os
import unittest

class TestHexViewer(unittest.TestCase):
    def setUp(self):
        self.executable = "..\\hex.exe"
        self.temp_dir = "temp"
        self.data_dir = "data"
        try:
            os.mkdir(self.temp_dir)
        except:
            pass

    def test_jpg(self):
        filename = f"{self.data_dir}/test_jpg"
        actual_filename = f"{self.temp_dir}/test_jpg_actual"
        expected_filename = f"{filename}_expected"
        os.system(f"{self.executable} {filename} > {actual_filename}")
        with open(actual_filename, 'r') as actual_file:
            with open(expected_filename, 'r') as expected_file:
                self.assertEqual(actual_file.read(), expected_file.read())
    
    def test_small(self):
        filename = f"{self.data_dir}/test_small"
        actual_filename = f"{self.temp_dir}/test_small_actual"
        expected_filename = f"{filename}_expected"
        os.system(f"{self.executable} {filename} > {actual_filename}")
        with open(actual_filename, 'r') as actual_file:
            with open(expected_filename, 'r') as expected_file:
                self.assertEqual(actual_file.read(), expected_file.read())

    def test_help(self):
        filename = f"{self.data_dir}/test_help"
        actual_filename = f"{self.temp_dir}/test_help_actual"
        expected_filename = f"{filename}_expected"
        os.system(f"{self.executable} > {actual_filename}")
        with open(actual_filename, 'r') as actual_file:
            with open(expected_filename, 'r') as expected_file:
                self.assertEqual(actual_file.read(), expected_file.read())
    
    def test_no_file(self):
        filename = f"{self.data_dir}/test_no_file"
        actual_filename = f"{self.temp_dir}/test_no_file_actual"
        expected_filename = f"{filename}_expected"
        os.system(f"{self.executable} jdfkgjoidjf0gidofgiodj > {actual_filename}")
        with open(actual_filename, 'r') as actual_file:
            with open(expected_filename, 'r') as expected_file:
                self.assertEqual(actual_file.read(), expected_file.read())
    
    def tearDown(self):
        os.system(f"rmdir /q /s {self.temp_dir}")
