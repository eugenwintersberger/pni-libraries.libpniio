import sys
import unittest
sys.path.insert(0,"../")

from pni.nx.h5 import NXFile

from pni.utils import Array
from pni.utils import Float32Scalar


#implementing test fixture
class NXFileTest(unittest.TestCase):
    def setUp(self):
        pass

    def tearDown(self):
        pass

    def test_creation(self):
        f = NXFile()

        f.filename = "test.h5"
        f.overwrite = True
        f.read_only = True

        f.create()
        f.close()
    
        f.overwrite = False
        self.assertRaises(UserWarning,f.create)

    def test_attributes(self):
        pass

