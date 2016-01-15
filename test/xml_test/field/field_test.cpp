
#include <boost/test/unit_test.hpp>
#include "../../base_fixture.hpp"

struct field_test_fixture : base_fixture
{
    field_test_fixture():
        base_fixture("field_test.nx")
    {}
};

BOOST_GLOBAL_FIXTURE(field_test_fixture)
