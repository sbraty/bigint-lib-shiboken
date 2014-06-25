project (libbigint)
 set(SOURCE_LIB bigint.cpp)	
 add_definitions ("-DLIBBIGINT_BUILD")
 add_library (libbigint SHARED ${SOURCE_LIB})
 set_target_properties (libbigint PROPERTIES OUTPUT_NAME "bigint") 

