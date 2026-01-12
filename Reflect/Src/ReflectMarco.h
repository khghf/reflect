#pragma once
#define ENABLE_PARSER
#ifdef ENABLE_PARSER
	#ifdef __clang__
		#define CLASS(...)__attribute__((annotate("reflect_class")))
		#define FUNCTION(...)__attribute__((annotate("reflect_function")))
		#define PROPERTY(...)__attribute__((annotate("reflect_property")))
	#else
		#define CLASS(...)
		#define FUNCTION(...)
		#define PROPERTY(...)
	#endif // __clang__
#else
	#define CLASS(...)
	#define FUNCTION(...)
	#define PROPERTY(...)
#endif // ENABLE_PARSER
