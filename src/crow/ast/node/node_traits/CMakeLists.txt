# Add source files
target_sources(${TARGET_CROW_LIB} PRIVATE
	args.cpp
	body.cpp
	condition.cpp
	binding_expr.cpp
	expr.cpp
	identifier.cpp
	init_expr.cpp
	node_position.cpp
	params.cpp
	type_annotation.cpp
	then.cpp
	alt.cpp
	unary_operator.cpp
	binary_operator.cpp
	type_data.cpp
	attribute_data.cpp
)
