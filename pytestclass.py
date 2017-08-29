import unittest
import sum

class TestSumMethods(unittest.TestCase):

  def test_output(self):
    self.assertEqual(sum.sum(5, 1), 6)

if __name__ == '__main__':
  unittest.main()