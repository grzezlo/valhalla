#include "test.h"

#include "include/config.h"
#include "thor/edgestatus.h"

using namespace std;
using namespace valhalla::baldr;
using namespace valhalla::thor;

namespace {

void TryGet(const EdgeStatus& edgestatus, const GraphId& edgeid,
               const EdgeStatusType expected) {
  EdgeStatusType r = edgestatus.Get(edgeid);
  if (r != expected)
    throw runtime_error("EdgeStatus get test failed");
}

void TestStatus() {
  EdgeStatus edgestatus;

  // Add some edges
  edgestatus.Set(GraphId(555, 1, 100100), kPermanent);
  edgestatus.Set(GraphId(555, 2, 100100), kPermanent);
  edgestatus.Set(GraphId(555, 3, 100100), kPermanent);
  edgestatus.Set(GraphId(555, 1, 55555), kTemporary);
  edgestatus.Set(GraphId(555, 2, 55555), kTemporary);
  edgestatus.Set(GraphId(555, 3, 55555), kTemporary);
  edgestatus.Set(GraphId(555, 1, 1), kPermanent);
  edgestatus.Set(GraphId(555, 2, 1), kPermanent);
  edgestatus.Set(GraphId(555, 3, 1), kPermanent);

  // Test various get
  TryGet(edgestatus, GraphId(555, 1, 100100), kPermanent);
  TryGet(edgestatus, GraphId(555, 2, 100100), kPermanent);
  TryGet(edgestatus, GraphId(555, 3, 100100), kPermanent);
  TryGet(edgestatus, GraphId(555, 1, 55555), kTemporary);
  TryGet(edgestatus, GraphId(555, 2, 55555), kTemporary);
  TryGet(edgestatus, GraphId(555, 3, 55555), kTemporary);
  TryGet(edgestatus, GraphId(555, 1, 1), kPermanent);
  TryGet(edgestatus, GraphId(555, 2, 1), kPermanent);
  TryGet(edgestatus, GraphId(555, 3, 1), kPermanent);

  // Clear and make sure all status are kUnreached
  edgestatus.Init();
  TryGet(edgestatus, GraphId(555, 1, 100100), kUnreached);
  TryGet(edgestatus, GraphId(555, 2, 100100), kUnreached);
  TryGet(edgestatus, GraphId(555, 3, 100100), kUnreached);
  TryGet(edgestatus, GraphId(555, 1, 55555), kUnreached);
  TryGet(edgestatus, GraphId(555, 2, 55555), kUnreached);
  TryGet(edgestatus, GraphId(555, 3, 55555), kUnreached);
  TryGet(edgestatus, GraphId(555, 1, 1), kUnreached);
  TryGet(edgestatus, GraphId(555, 2, 1), kUnreached);
  TryGet(edgestatus, GraphId(555, 3, 1), kUnreached);
}

}

int main() {
  test::suite suite("edgestatus");

  // Test setting status, getting status, and clearing
  suite.test(TEST_CASE(TestStatus));

  return suite.tear_down();
}
