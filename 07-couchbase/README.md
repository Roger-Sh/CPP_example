## 数据库couchbase
### 1. 为啥要用couchbase
Couchbase，是MemBase与couchDb这两个NoSQL数据库的合并的产物，
是一个分布式的面向文档的NoSQL数据库管理系统,即拥有CouchDB的简单和可靠以及Memcached的高性能。
Couchbase Server 可以被用作一个：

	1. 管理缓存层
	2. key-value 存储
	3. 文档型数据库

Couchbase 是一个高性能、分布式、面向文档的NoSQL数据库。Couchbase 提供了一些和其他一些领先的NoSQL数据库相似的功能或者增强功能．

	1. 可伸缩性(Scalability)
	2. 自动分片集群技术
	3. 高性能 高吞吐量 和低延迟
	4. 集群高可用性
	5. 跨数据中心复制
	6. 数据局部性(Data Locality)
	7. 支持常用的面向对象语言
	8. 管理和监控图形用户界面

### 2. CouchBASE Server 安装 
CouchBASE Server 下载：

	//官网下载企业版，ubuntu16.04 直接下载安装即可
	//或者社区版
	couchbase-server-enterprise_5.5.0-ubuntu14.04_amd64.deb

访问http://localhost:8091/即可看到我们的Couchbase信息。可以新建一个集群
页面分为几个标签页：

	1. Cluster Dashboard - Couchbase 概览，显示我们的所有的Cluster / Buckets / Servers 信息。
	2. Server  - 服务器节点，对于服务器节点的管理，包括增加、修改和删除。
	3. Buckets，此页面可以对Buckets进行增加 / 删除 / 修改 / flush，Bucket有三种类型：	
		- Couchbase
		- Memcached
		- Epheneral
	4. Query，可以在此处输入类SQL语句(N1ql)进行数据的增删改查操作。
	5. Indexs，索引索引主要用于加快数据查询的效率。Couchbase的索引一般是放在单节点的。
	6. 其他，Secrity / Log / Settings

### 3. Node.js Client
Node.js是一个轻量级平台，它构建在V8 JavaScript引擎上，用于开发高效的可扩展网络应用程序。Node.js是为数据密集型实时应用而设计的。Couchbase提供了一个Node.js客户端库，用于访问存储在Couchbase服务器中的文档(documents)。Node.js客户端库具有对JSON的内置支持，并随着扩展的Couchbase集群自动缩放。使用CoucBaseServer与Node.js客户端库来对存储在Couchbase中的文档执行CRUD（创建、检索、更新、删除）操作。我们还将使用视图查询CoucBase Server。

####3.1. node.js client 安装

```shell
$ sudo git clone https://github.com/nodejs/node.git
$ sudo chmod -R 755 node
$ cd node
$ sudo ./configure
$ sudo make		//这一步时间很长
$ sudo make install
$ node --version		//查看node版本
```

#### 3.2. 创建一个测试脚本

```shell
$ vi test.js 
//把下面的代码粘帖到刚才创建的文件里
var http = require('http');
http.createServer(function (req, res) {
	res.writeHead(200, {'Content-Type': 'text/plain'});
	res.end('Hello World\n');
}).listen(3003, '127.0.0.1');
	console.log('Server running at http://127.0.0.1:3003/');
//运行
$ node test.js
Server running at http://127.0.0.1:3003/
//访问测试
//terminal 运行
curl http://localhost:3003/
//浏览器输入
curl http://localhost:3003/
// 输出
Hello World
```

### 4. C-Client and CXX-Wrapper

#### 4.1. Install

C-Client 下载编译 :

```shell
//方法一 compile by yourself
$ git clone https://github.com/couchbase/libcouchbase.git
$ cd libcouchbase && mkdir build && cd build
$ ../cmake/configure
$ make
$ ctest
$ sudo make install //将编译好的结果安装到系统
//生成html帮助文档：
$ make -f doc/Makefile public 

//方法二 
// Only needed during first-time setup:
wget http://packages.couchbase.com/releases/couchbase-release/couchbase-release-1.0-6-amd64.deb
sudo dpkg -i couchbase-release-1.0-6-amd64.deb
// Will install or upgrade packages
sudo apt-get update
sudo apt-get install libcouchbase-dev libcouchbase2-bin build-essential
```

CXX-Wrapper:

```shell
$ git clone https://github.com/couchbaselabs/libcouchbase-cxx.git
// 生成html帮助文档
$ make -f doc/Makefile public 

// compile the example.cpp, use CMakeLists.txt
$ mkdir build && cd build
$ cmake ..
$ make 
$ cd bin/ && ./example
```

#### 4.2. Example 

##### example 01: simple example 

Basic connection to bucket, add item, retrieve item

Compile and run:

```shell
$ gcc 01-hello_couchbase.c -o hello_couchbase -lcouchbase
$ ./01-hello_couchbase
key: STORE... OK
key: GET... OK... Value: true
```

##### example 02: simple example

Basic connection to bucket, add item, retrieve item

Compile and run:

```shell
$ gcc 02-hello_couchbase.c -o 02-hello_couchbase -lcouchbase
$ ./02-hello_couchbase couchbase://localhost/bucket-test shan1123 fog-ws
Will wait for storage operation to complete..
=== STORE ===
KEY: key-02
CAS: 0x15d761f3b8810000
Will wait to retrieve item..
=== GET ===
KEY: key-02
CAS: 0x15d761f3b8810000
VALUE: value-02
FLAGS: 0x0
```

##### example 03: example with different operations

Document operation:

-   add document	
-   get document
-   update document (Replace an existing document)
-   delete document
-   Append data to the end of a document
-   Prepend data to the beginning of a document

Operation from CouchBase:

-   LCB_ADD only creates the document if it does not already exist. It fails if the document is already present.
-   LCB_REPLACE only replaces the document if it already exists. It fails unless the document is already present.
-   LCB_SET unconditionally stores the document to the cluster, regardless of whether it already exists or not.

Bulk operations:

Bulk operations are operations that are scheduled in bulk to the network, saving on bandwidth and latency. Rather than performing and waiting for one operation at a time, you can schedule multiple operations and then wait for them all to complete. There are two ways to perform bulk operations.

-   schedule operations one at a time
-   schedule operations all at once

Compile and run

```shell
$ gcc 03-documente.c -o 03-documente -lcouchbase
$ ./03-documente  
```

##### example 04

minimal example

Compile and run

```shell
gcc 04-minimal.c -o 04-minimal -lcouchbase
./04-minimal couchbase://localhost/bucket-name username password
STORED "foo" CAS: 1574158180635049984
GOT "foo" CAS: 1574158180635049984 FLAGS:0x0 SIZE:3
bar
```

##### example cxx_test

This example shows how to connect Couchbase and upsert item with cxx. 

Use makefile to create the build forder.