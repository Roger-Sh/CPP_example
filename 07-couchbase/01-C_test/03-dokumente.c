/*************************************************************************
> File Name: 03-server_manage.c
> Author: 
> Mail: 
> Created Time: Mo 18 Nov 2019 11:01:15 CET
************************************************************************/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <libcouchbase/couchbase.h>

#ifdef _WIN32
#define PRIu64 "I64u"
#else
#include <inttypes.h>
#endif

// store_callback(), check store status 
static void store_callback( lcb_t instance,
                           const void *cookie,
                           lcb_storage_t operation,
                           lcb_error_t err,
                           const lcb_store_resp_t *resp)
{
    if (err == LCB_SUCCESS) 
    {
        fprintf(stderr, "STORED \"");
        fwrite(resp->v.v0.key, sizeof(char), resp->v.v0.nkey, stderr);
        fprintf(stderr, "\" CAS: %"PRIu64"\n", resp->v.v0.cas);
    }
    else 
    {
        fprintf(stderr, "STORE ERROR: %s (0x%x)\n",
                lcb_strerror(instance, err), err);
        exit(EXIT_FAILURE);
    }

    (void)cookie;
    (void)operation;
}

// get_callback(), check retrieving status 
static void get_callback(   lcb_t instance, 
                         const void *cookie, 
                         lcb_error_t err, 
                         const lcb_get_resp_t *resp)
{
    if(err == LCB_SUCCESS)
    {
        printf("Received document: %.*s\n", (int)resp->v.v0.nbytes, (char*)resp->v.v0.bytes);
    }
    else
    {
        fprintf(stderr, "Couldn't retrieve item: %s\n", lcb_strerror(instance, err));
    }
}

// remove_callback(), check removing status
static void remove_callback(    lcb_t instance,
                            const void *cookie,
                            lcb_error_t err,
                            const lcb_remove_resp_t *resp)
{
    if(err == LCB_SUCCESS)
    {
        //printf("Remove document: %.*s\n", (int)resp->v.v0.nbytes, (char*)resp->v.v0.bytes);    
    }
    else
    {
        fprintf(stderr, "Couldn't remove item: %s\n", lcb_strerror(instance, err));
    }
}

// storeDoc(), store documente  
static void storeDoc(lcb_t instance) 
{
    // Creating documents
    // store_callback 
    lcb_set_store_callback(instance, store_callback);

    // store_cmd  
    struct lcb_store_cmd_st cmd = { 0 };
    const struct lcb_store_cmd_st *cmdlist = &cmd;

    // document with json, key  
    const char *doc = "{ \"json\" : \"data\"   }";
    const char *key = "a_simple_key";

    // cmd options  
    cmd.v.v0.key = key;
    cmd.v.v0.nkey = strlen(key);
    cmd.v.v0.bytes = doc;
    cmd.v.v0.nbytes = strlen(doc);
    cmd.v.v0.operation = LCB_SET;

    // lcb_store() 
    lcb_error_t err = lcb_store(instance, NULL, 1, &cmdlist);

    // check error 
    if (err == LCB_SUCCESS) 
    {
        lcb_wait(instance);     
    }
    else 
    {
        fprintf(stderr, "Couldn’t schedule operation: %s\n", lcb_strerror(instance, err));    
    }
}

// storeTest(), store document, test 
static void storeTest(lcb_t instance)
{
    // callback 
    lcb_set_store_callback(instance, store_callback);

    // store_cmd 
    struct lcb_store_cmd_st cmd = { 0 };
    const struct lcb_store_cmd_st *cmdlist = &cmd;

    // document and key 
    const char *doc = "{ \"v\": 100.1, \"list\": [1,2,3,4,5,6,7], \"talk\": \"About Foo.\"  }";
    const char *key = "json-test";

    // cmd options 
    cmd.v.v0.key = key;
    cmd.v.v0.nkey = strlen(key);
    cmd.v.v0.bytes = doc;
    cmd.v.v0.nbytes = strlen(doc);
    cmd.v.v0.operation = LCB_SET;

    // lcb_store() 
    lcb_error_t err = lcb_store(instance, NULL, 1, &cmdlist);

    // check error 
    if (err == LCB_SUCCESS) 
    {
        lcb_wait(instance);     
    }
    else 
    {
        fprintf(stderr, "Couldn’t schedule operation: %s\n", lcb_strerror(instance, err));    
    }

}

// bulk_storeDoc_once(), bulk operations, store Doc once at a time
static void bulk_storeDoc_once(lcb_t instance)
{  
    // callback
    lcb_set_store_callback(instance, store_callback);

    // store_cmd 
    lcb_store_cmd_t scmd = { 0 };
    const lcb_store_cmd_t *cmdlist = &scmd;

    // init for bulk 
    unsigned ii;
    lcb_error_t err;
    scmd.v.v0.operation = LCB_SET;

    // loop for operations 
    for(ii = 0; ii < 10; ++ii)
    {
        char kbuf[4096];
        char vbuf[4096];

        // key and value 
        sprintf(kbuf, "Key_once_%u", ii);
        sprintf(vbuf, "{\"value\":%u}", ii);

        // cmd options
        scmd.v.v0.key = kbuf;
        scmd.v.v0.nkey = strlen(kbuf);
        scmd.v.v0.bytes = vbuf;
        scmd.v.v0.nbytes = strlen(vbuf);

        // lcb_store() 
        err = lcb_store(instance, NULL, 1, &cmdlist);

        // check error 
        if(err != LCB_SUCCESS)
        {
            fprintf(stderr, "Couldn't schedule storage for %s! %s\n", kbuf, lcb_strerror(NULL, err));
        }
    }
    lcb_wait(instance); 
}

//bulk_removeDoc_once(), bulk operations, remove Doc once at a time
static void bulk_removeDoc_once(lcb_t instance)
{
    // callback 
    lcb_set_remove_callback(instance, remove_callback);

    // remove_cmd 
    lcb_remove_cmd_t rcmd = { 0 };
    const lcb_remove_cmd_t *rcmdlist = &rcmd;

    // init for bulk 
    unsigned jj;
    lcb_error_t err;

    // loop for operations 
    for(jj = 0; jj < 10; ++jj)
    {
        // key 
        char kbuf_remove[4096];
        sprintf(kbuf_remove, "Key_once_%u", jj);

        // rcmd options 
        rcmd.v.v0.key = kbuf_remove;
        rcmd.v.v0.nkey = strlen(kbuf_remove);

        // lcb_remove() 
        err = lcb_remove(instance, NULL, 1, &rcmdlist);

        // check error 
        if(err != LCB_SUCCESS)
        {
            printf("Couldn't schedule remove operation: %s\n", lcb_strerror(instance, err));
        }
    }
    lcb_wait(instance); 
}

// bulk_storeDoc_all, bulk operations, store Doc all at a time
static void bulk_storeDoc_all(lcb_t instance)
{
    // callback
    lcb_set_store_callback(instance, store_callback);
    
    // array for store_cmd 
    lcb_store_cmd_t *cmds;
    const lcb_store_cmd_t **cmdlist;
    
    // init for bulk 
    unsigned ii;
    lcb_error_t err;
    const int ncommands = 5;

    // calloc() for memory
    cmds = calloc(ncommands, sizeof(*cmds));
    cmdlist = calloc(ncommands, sizeof(*cmdlist));

    // loop for operations
    for (ii = 0; ii < ncommands; ++ii)
    {
        // key and value 
        char kbuf[4096], vbuf[4096];
        sprintf(kbuf, "Key_all_%u", ii);
        sprintf(vbuf, "{\"value\":%u}", ii);
        
        // iterate for cmd in cmds 
        lcb_store_cmd_t *cmd = cmds + ii;

        // save all operations in array 'cmdlist'
        cmd->v.v0.operation = LCB_SET;
        cmd->v.v0.key = strdup(kbuf); // need to free this later.
        cmd->v.v0.nkey = strlen(kbuf);
        cmd->v.v0.bytes = strdup(vbuf);
        cmd->v.v0.nbytes = strlen(vbuf);
        cmdlist[ii] = cmd;
    }

    // lcb_store()
    err = lcb_store(instance, NULL, ncommands, cmdlist);
   
    // check error 
    if(err != LCB_SUCCESS)
    {
        printf("Couldn't schedule remove operation: %s\n", lcb_strerror(instance, err));
    }
    else
    {
        lcb_wait(instance);
    }

    // release the memory
    free(cmds);
    free(cmdlist);
}

// getDoc(), retrieving document 
static void getDoc(lcb_t instance) 
{
    // get_callback  
    lcb_set_get_callback(instance, get_callback);

    // get_cmd 
    lcb_get_cmd_t cmd = { 0 };
    const lcb_get_cmd_t *cmdlist = { &cmd };

    // cmd options 
    const char *key = "a_simple_key";
    cmd.v.v0.key = key;
    cmd.v.v0.nkey = strlen(key);

    // lcb_get() 
    lcb_error_t err = lcb_get(instance, NULL, 1, &cmdlist);

    // check error 
    if (err == LCB_SUCCESS) 
    {
        lcb_wait(instance);
    }
    else 
    {
        fprintf(stderr, "Couldn’t schedule get operation: %s\n", lcb_strerror(instance, err));
    }
}

// removeDoc(), remove document
static void removeDoc(lcb_t instance)
{
    //remove_callback 
    lcb_set_remove_callback(instance, remove_callback);

    // remove_cmd 
    lcb_remove_cmd_t cmd = { 0 };
    const lcb_remove_cmd_t *cmdlist = &cmd;

    // cmd options 
    cmd.v.v0.key = "deleteme";
    cmd.v.v0.nkey = strlen("deleteme");

    // lcb_remove()
    lcb_error_t err = lcb_remove(instance,NULL, 1, &cmdlist);

    // check error
    if(err != LCB_SUCCESS)
    {
        printf("Couldn't schedule remove operation: %s\n", lcb_strerror(instance, err));
    }
    else
    {
        lcb_wait(instance);
    }
}

int main(int argc, char *argv[])
{
    // connection parameters 
    struct lcb_create_st cropts;

    // void *memset(void *str, int c, size_t n), init the str 
    memset(&cropts, 0, sizeof cropts);

    // cropts opstions
    cropts.version = 3;
    // couchbase://host1.net;host2.net/mybucket // multiple hosts
    cropts.v.v3.connstr = "couchbase://localhost/bucket-test";
    cropts.v.v3.passwd = "shan1123";
    cropts.v.v3.username = "fog-ws";

    // Initializing the client handle
    lcb_t instance = NULL;
    // error detection
    lcb_error_t err_create = lcb_create(&instance, &cropts);
    if (err_create != LCB_SUCCESS) {
        fprintf(stderr, "Could not create library handle: %s\n", lcb_strerror(NULL, err_create));
    }

    // connect to the cluster
    lcb_connect(instance);
    lcb_wait(instance);     
    // error detection
    lcb_error_t err_connect = lcb_get_bootstrap_status(instance);
    if(err_connect != LCB_SUCCESS){
        fprintf(stderr, "Couldn't bootstrap: %s\n", lcb_strerror(instance, err_connect));
    }

    // store document 
    storeDoc(instance);

    // get document 
    getDoc(instance);

    // storeTest 
    storeTest(instance);

    // remove document
    //removeDoc(instance);

    // bulk_storeDoc_once()
    bulk_storeDoc_once(instance);

    // bulk_storeDoc_all()
    bulk_storeDoc_all(instance);

    // bulk_removeDoc_once 
    //bulk_removeDoc_once(instance);

    //closing the connection
    lcb_destroy(instance);

    return 0;
}





