### cmake 是什么
CMake是一个跨平台的安装（编译）工具，可以用简单的语句来描述所有平台的安装(编译过程)。Linux/Ubuntu上基本都预先安装好了cmake工具，用sudo apt-get install也可以自动安装。要使用cmake必须在工程的每个文件夹中都编写CMakeLists.txt，尤其注意C、M、L是大写，并且是复数形式。
### 例子1
ex1:
-main.cpp
	
		#main.cpp
		#include <iostream>
		int main() {
   		std::cout << "Hello, world!" << std::endl;
   		return 0;
		}

-CMakeLists.txt
	
		#CMakeLists.txt
		#第一句是指生成一个名为hello_world的工程；第二句为基于main.cpp生成名为hello的可执行文件
		PROJECT(hello_world)
		ADD_EXECUTABLE(hello main.cpp)
		
在terminal中，将路径改为当前文件夹中，先后运行

		$cmake .
		$make

###例子2
上述编译方法有个很大的问题，原本文件中仅有源文件和CMakeLists.txt，但是编译之后，文件夹中的文件如下所示：

		CMakeCache.txt  cmake_install.cmake  hello     Makefile
		CMakeFiles      CMakeLists.txt       main.cpp
多了很多编译过程文件和结果文件，这样的方式显然是不方便的。如果能够把编译的过程文件和结果文件放在另一个文件夹，那么文件结构就比较清晰，可以方便地编辑、修改源文件。
建立ex2文件夹，并且在ex2中建立src文件夹，和build文件夹。
首先，在ex2文件夹中，建立CMakeLists.txt，第一行是建立名为hello_world的工程，第二行添加src子文件夹
ex2/：
CMakeLists.txt

		#CMakeLists.txt
		PROJECT(hello_world)
		ADD_SUBDIRECTORY(src)

ex2/src/:
CMakelists.txt

		ADD_EXECUTABLE(hello main.cpp)
main.cpp

		#main.cpp
		#include <iostream> 
		int main() {
    		std::cout << "Hello, world!" << std::endl;
    		return 0;
		}

ex2/build/:
		
		$cmake ..
		$make