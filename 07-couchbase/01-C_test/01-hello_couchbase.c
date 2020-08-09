/*************************************************************************
	> File Name: hello1.c
	> Author: 
	> Mail: 
	> Created Time: Mo 11 Nov 2019 16:14:16 CET
 ************************************************************************/

#include <string.h>
#include <libcouchbase/couchbase.h>

// check cakkback
static void opCallback(lcb_t instance, 
                       int cbtype, 
                       const lcb_RESPBASE *rb) 
{
    fprintf(stderr, "%.*s: %s... ", (int)rb->nkey, (char*)rb->key, lcb_strcbtype(cbtype));
    if (rb->rc != LCB_SUCCESS) 
    {
        fprintf(stderr, "%s\n", lcb_strerror(NULL, rb->rc));
    } 
    else 
    {
        fprintf(stderr, "OK");
        if (cbtype == LCB_CALLBACK_GET) {
            const lcb_RESPGET *rg = (const lcb_RESPGET *)rb;
            fprintf(stderr, "... Value: %.*s\n", (int)rg->nvalue, (char*)rg->value);
        } else {
            fprintf(stderr, "\n");
        }
    }
}

int storeAndRetrieveKey()
{
    
    // Initializingi----------------------------------------------
    // assert宏的原型定义在<assert.h>中，其作用是如果它的条件返回错误，则终止程序执行
    assert(lcb_version_g >= 0x020506 && "This example requires 2.5.6 or greater");
    // lcb_t handle, a library-allocated handle, A connection to a bucket within the cluster is represented by the lcb_t 
    // The handle is first initialized with a Connection String containing the server's address (localhost) and the bucket name (default). see below
    lcb_t instance;
    // The connection string is placed into the creation options structure (lcb_create_st)
    struct lcb_create_st options;
    // C库函数 void *memset(void *str, int c, size_t n) 复制字符 c（一个无符号字符）到参数 str 所指向的字符串的前 n 个字符, this step is to initialize the option 
    memset(&options, 0, sizeof options);
    // 设置 options, 也就是设置 lcb_create_st, the connection string 
    options.version = 3;
    options.v.v3.connstr = "couchbase://localhost/bucket-test";
    options.v.v3.username = "fog-ws";
    options.v.v3.passwd = "shan1123";
    // lcb_create(): create the new instance with options, return an error handle lcb_error_t
    lcb_error_t rc = lcb_create(&instance, &options);
    
    // Connecting----------------------------------------------------
    // lcb_connect(): connect couchbase bucket  
    lcb_connect(instance);
    // lcb_wait(): wait for the connection to complete
    lcb_wait(instance);
    // After the wait is complete, the lcb_get_bootstrap_status() function is called to determine if the initial connection was successful or not  

    // Installing callbacks------------------------------------------
    // The library delivers most operation status codes and responses via specially installed callbacks
    // In this case we install callbacks for storage operations and retrieval operations
    // lcb_install_callback3(resp, cookie, err)
    lcb_install_callback3(instance, LCB_CALLBACK_GET, opCallback);
    lcb_install_callback3(instance, LCB_CALLBACK_STORE, opCallback);

    // Scheduling operations
    // After the callbacks have been installed, operations to store and retrieve an item from the cluster are initialized. 
    // The operations are expressed in terms of command structures,  
    // item is initialized with key and value, 这里有点问题，这里用的数据结构是lcb_CMDSTORE
    lcb_CMDSTORE scmd = { 0 };
    LCB_CMD_SET_KEY(&scmd, "key", 3);
    LCB_CMD_SET_VALUE(&scmd, "false", 5);

    // store the item , 网页上是 lcb_store_cmd_t
    scmd.operation = LCB_SET;
    lcb_store3(instance, NULL, &scmd);
    lcb_wait(instance);

    // retrieve the item，网页上是 lcb_get_cmd_t 
    lcb_CMDGET gcmd = { 0 };
    LCB_CMD_SET_KEY(&gcmd, "key", 3);
    lcb_get3(instance, NULL, &gcmd);
    lcb_wait(instance);
    lcb_destroy(instance);

    return 0;
}

int main()
{
    storeAndRetrieveKey(); 
}
