#include <stdio.h>
#include <libcouchbase/couchbase.h>
#include <libcouchbase/api3.h>
#include <stdlib.h>
#include <string.h> /* strlen */
#ifdef _WIN32
#define PRIx64 "I64x"
#else
#include <inttypes.h>
#endif
static void
die(lcb_t instance, const char *msg, lcb_error_t err)
{
    fprintf(stderr, "%s. Received code 0x%X (%s)\n",
        msg, err, lcb_strerror(instance, err));
    exit(EXIT_FAILURE);
}

static void
op_callback(lcb_t instance, int cbtype, const lcb_RESPBASE *rb)
{
    fprintf(stderr, "=== %s ===\n", lcb_strcbtype(cbtype));
    if (rb->rc == LCB_SUCCESS) {
        fprintf(stderr, "KEY: %.*s\n", (int)rb->nkey, (char*)rb->key);
        fprintf(stderr, "CAS: 0x%"PRIx64"\n", rb->cas);
        if (cbtype == LCB_CALLBACK_GET) {
            const lcb_RESPGET *rg = (const lcb_RESPGET *)rb;
            fprintf(stderr, "VALUE: %.*s\n", (int)rg->nvalue, (char*)rg->value);
            fprintf(stderr, "FLAGS: 0x%x\n", rg->itmflags);
        }
    } else {
        die(instance, lcb_strcbtype(cbtype), rb->rc);
    }
}

int main(int argc, char *argv[])
{
    // Init lcb_error, lcb_t, lcb_create_st, lcb_CMDSTORE, lcb_CMDGET 
    lcb_error_t err;
    lcb_t instance;
    struct lcb_create_st create_options = { 0 };
    lcb_CMDSTORE scmd = { 0 };
    lcb_CMDGET gcmd = { 0 };
    create_options.version = 3;

    // test the argument
    //"couchbase://localhost/bucket-test"
    if (argc < 2) {
        fprintf(stderr, "Usage: %s [couchbase://localhost/bucket-test] [ password ] [ username ] \n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // tansfer the argument 
    create_options.v.v3.connstr = argv[1];
    if (argc > 2) {
        create_options.v.v3.passwd = argv[2];
    }
    if (argc > 3) {
        create_options.v.v3.username = argv[3];
    }

    // create the couchbase handle  
    err = lcb_create(&instance, &create_options);
    if (err != LCB_SUCCESS) {
        die(NULL, "Couldn't create couchbase handle", err);
    }

    // connect the couchbase bucket 
    err = lcb_connect(instance);
    if (err != LCB_SUCCESS) {
        die(instance, "Couldn't schedule connection", err);
    }
    lcb_wait(instance);

    // test the connect status 
    err = lcb_get_bootstrap_status(instance);
    if (err != LCB_SUCCESS) {
        die(instance, "Couldn't bootstrap from cluster", err);
    }
    
    // install callpack
    /* Assign the handlers to be called for the operation types */
    lcb_install_callback3(instance, LCB_CALLBACK_GET, op_callback);
    lcb_install_callback3(instance, LCB_CALLBACK_STORE, op_callback);
    
    // set key and value 
    LCB_CMD_SET_KEY(&scmd, "key-02", strlen("key-02"));
    LCB_CMD_SET_VALUE(&scmd, "value-02", strlen("value-02"));
    
    // store the item  
    scmd.operation = LCB_SET;
    err = lcb_store3(instance, NULL, &scmd);
    if (err != LCB_SUCCESS) {
        die(instance, "Couldn't schedule storage operation", err);
    }

    /* The store_callback is invoked from lcb_wait() */
    fprintf(stderr, "Will wait for storage operation to complete..\n");
    lcb_wait(instance);
    
    // retrieve the item 
    /* Now fetch the item back */
    LCB_CMD_SET_KEY(&gcmd, "key-02", strlen("key-02"));
    err = lcb_get3(instance, NULL, &gcmd);
    if (err != LCB_SUCCESS) {
        die(instance, "Couldn't schedule retrieval operation", err);
    }

    /* Likewise, the get_callback is invoked from here */
    fprintf(stderr, "Will wait to retrieve item..\n");
    lcb_wait(instance);

    /* Now that we're all done, close down the connection handle */
    lcb_destroy(instance);
    return 0;
}
