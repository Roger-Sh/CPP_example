# Find "set (srcs", and add a new entry there, e.g.,
set (   srcs
        #src/conditional_removal.cpp
        # ...
        src/bilateral.cpp)
    )

# Find "set (incs", and add a new entry there, e.g.,
set (   incs
        #include pcl/${SUBSYS_NAME}/conditional_removal.h
        # ...
        include pcl/${SUBSYS_NAME}/bilateral.h
    )

# Find "set (impl_incs", and add a new entry there, e.g.,
set (   impl_incs
        #include/pcl/${SUBSYS_NAME}/impl/conditional_removal.hpp
        # ...
        include/pcl/${SUBSYS_NAME}/impl/bilateral.hpp
    )
