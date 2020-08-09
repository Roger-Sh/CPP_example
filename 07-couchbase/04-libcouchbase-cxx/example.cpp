#include <libcouchbase/couchbase++.h>
#include <libcouchbase/couchbase++/views.h>
#include <libcouchbase/couchbase++/query.h>
#include <libcouchbase/couchbase++/endure.h>
#include <libcouchbase/couchbase++/logging.h>
#include <cassert>      //library for error
#include <iostream>
#include <vector>

using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::map;
using std::vector;

using namespace Couchbase;

int main(int argc, const char **argv)
{
    // Connect to the client
    // string connstr(argc > 1 ? argv[1] : "couchbase://localhost/default");
    string connstr("couchbase://localhost/bucket-test");
    // Couchbase::Client h(connstr);
    Couchbase::Client h(connstr, "shan1123", "fog-ws");
    // Connect status 
    Status rv = h.connect();
    if (!rv.success()) {
        cout << "Couldn't connect to '" << connstr << "'. " << "Reason: " << rv << endl;
        exit(EXIT_FAILURE);
    }

    // store the item, get the store status: cas
    // : Got status for store. Cas=15d7552fbbf10000
    auto sres = h.upsert("cxx-test",
            "{ \"v\": 100.1, \"list\": [1,2,3,4,5,6,7], \"talk\": \"About Foo.\" }"); //json -> string 
    cout << "Got status for store. Cas=" << std::hex << sres.cas() << endl;

    // get the item, use the item name - key
    // : Got value: { "v": 100.1, "list": [1,2,3,4,5,6,7], "talk": "About Foo." }
    auto gres = h.get("cxx-test");
    cout << "Got value: " << gres.value() << std::endl;

    // this key "non-exist-key" dosn't exist
    // : Got status for non-existent key: [0xd]: The key does not exist on the server
    gres = h.get("non-exist-key");
    cout << "Got status for non-existent key: " << gres.status() << endl;
    bool status_gres_false = gres.status();
    cout << status_gres_false << endl;

    // this key "exist-key" should exist before test 
    gres = h.get("exist-key");
    cout << "Got status for existent key: " << gres.status() << endl;
    bool status_gres_true = gres.status();
    cout << status_gres_true << endl;
    

    // bulk operation, all at a time 
    // bulk Store 
    BatchCommand<UpsertCommand, StoreResponse> bulkStore(h);
    for (size_t ii = 0; ii < 10; ii++) {
        bulkStore.add("Key", "Value");
    }
    bulkStore.submit();
    h.wait();

    // bulkGet 
    BatchCommand<GetCommand, GetResponse> bulkGet(h);
    for (size_t ii = 0; ii < 10; ii++) {
        bulkGet.add("Key");
    }
    bulkGet.submit();
    h.wait();

    // Callback 
    CallbackCommand<GetCommand, GetResponse> cbGet(h, [](GetResponse& resp)
    {
        cout << "Got response for: " << resp.key() << endl;
        cout << "  Status: " << resp.status() << endl;
        cout << "  Value: " << resp.value() << endl;
    });
    cbGet.add("Key");
    cbGet.submit();
    h.wait();
    //  Got response for: Key
    //      Status: [0x0]: Success (Not an error)
    //      Value: Value

    h.upsert("foo", "FOOVALUE");
    h.upsert("bar", "BARVALUE");
    h.upsert("baz", "BAZVALUE");

    //! Use durability requirements
    //: Endure Status: [0x0]: Success (Not an error)
    sres = h.upsert("toEndure", "toEndure");
    cout << "Endure Status: "
            << h.endure(EndureCommand("toEndure", sres.cas()),
                DurabilityOptions(PersistTo::MASTER)).status()
                << endl;

    //! Remove the items we just created
    //h.remove("foo");
    //h.remove("bar");
    //h.remove("baz");

    // connect to beer-sample 
    string connstr2(argc > 2 ? argv[2] : "couchbase://localhost/beer-sample");
    Couchbase::Client h1{connstr, "shan1123", "fog-ws"};
    
    // connect status 
    Status rv1 = h1.connect();
    if (!rv1.success()) {
        cout << "Couldn't connect to '" << connstr2 << "'. " << "Reason: " << rv1 << endl;
        exit(EXIT_FAILURE);
    }

    // set ViewCommand vCmd 
    Status status;
    ViewCommand vCmd("beer", "brewery_beers");
    vCmd.include_docs();
    vCmd.limit(10);
    vCmd.skip(10);
    vCmd.descending(true);
    vCmd.reduce(false);

    //: using options: limit=10&skip=10&descending=true&descending=false&
    cout << "using options: " << vCmd.get_options() << endl;

    // ViewQuery 
    ViewQuery query(h1, vCmd, status);
    if (!status) {
        cerr << "Error with view command: " << status << endl;
    }
    
    // loop to print the ViewQuery 
    size_t numRows = 0;
    for (auto ii : query) {
            cout << "Key: " << ii.key() << endl;
            cout << "Value: " << ii.value() << endl;
            cout << "DocID: " << ii.docid() << endl;

            if (ii.has_document()) {
                string value = ii.document().value();
                cout << "Document: " << value << endl;
            } else {
                cout << "NO DOCUMENT!" << endl;
            }
        numRows ++;
    }

    // check query status 
    cout << "Got: " << std::dec << numRows << " rows" << endl;
    if (!query.status()) {
        cerr << "Problem with query: " << query.status() << endl;
    }



/*

    // async query 
    cout << "Using async query.." << endl;
    // Async
    CallbackViewQuery asyncQuery(h1, vCmd, status,
        [](ViewRow&& row, CallbackViewQuery*) {
            cout << "Key: " << row.key() << endl;
            cout << "Value: " << row.value() << endl;
            cout << "DocID: " << row.docid() << endl;

            if (row.has_document()) 
            {
                string value = row.document().value();
                cout << "Document: " << value << endl;
            } 
            else 
            {
                cout << "NO DOCUMENT!" << endl;
            }
        },
        [](ViewMeta&& meta, CallbackViewQuery*) {
        cout << "View complete: " << endl;
        cout << "  Status: " << meta.status() << endl;
        cout << "  Body: " << meta.body() << endl;
        }
                               );
    h.wait();

*/

/*

    // Issue the N1QL request:
    auto m = Query::execute(h, "CREATE PRIMARY INDEX ON `travel-sample`");
    cout << "Index creation: " << endl
         << "  Status: " << m.status() << endl
         << "  Body: " << m.body() << endl;

    // Get the count of airports per country:
    QueryCommand qcmd(
        "SELECT t.country, COUNT(t.country)"
        "FROM `travel-sample` t GROUP BY t.country");

    Query q(h, qcmd, status);
    if (!status) {
        cout << "Couldn't issue query: " << status;
    }
    for (auto row : q) {
        cout << "Row: " << row.json() << endl;
    }
    if (!q.status()) {
        cout << "Couldn't execute query: " << q.status() << endl;
        cout << "Body is: " << q.meta().body() << endl;
    }
*/

    return 0;
}
