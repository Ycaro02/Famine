#include <assert.h>
#include "libft.h"

void test_vector_add() {
    vec2_u32 a = {1, 2};
    vec2_u32 b = {3, 4};
    VECTOR_ADD(u32, 2, a, b);
    assert(a[0] == 4 && a[1] == 6);
}

void test_vector_sub() {
    vec2_u32 a = {4, 6};
    vec2_u32 b = {3, 4};
    VECTOR_SUB(u32, 2, a, b);
    assert(a[0] == 1 && a[1] == 2);
}

void test_vector_mul() {
    vec2_u32 a = {2, 3};
    vec2_u32 b = {3, 4};
    VECTOR_MUL(u32, 2, a, b);
    assert(a[0] == 6 && a[1] == 12);
}

void test_vector_div() {
    vec2_u32 a = {6, 12};
    vec2_u32 b = {3, 4};
    VECTOR_DIV(u32, 2, a, b);
    assert(a[0] == 2 && a[1] == 3);
}


void test_vector_mul_float() {
    vec2_float a = {1.0f, 2.0f};
    vec2_float b = {3.0f, 4.0f};
    VECTOR_MUL(float, 2, a, b);
    assert(a[0] == 3.0f && a[1] == 8.0f);
}

void test_vector_div_float() {
    vec2_float a = {3.0f, 8.0f};
    vec2_float b = {3.0f, 4.0f};
    VECTOR_DIV(float, 2, a, b);
    assert(a[0] == 1.0f && a[1] == 2.0f);
}

void test_vector_float_display() {
    vec2_float a = {1.0f, 2.0f};
	vec3_f32 b = {1.0f, 2.0f, 3.0f};
	vec4_f32 c = {1.0f, 2.0f, 3.0f, 4.0f};

    VECTOR_FLOAT_DISPLAY(2, a);
	VECTOR_FLOAT_DISPLAY(3, b);
	VECTOR_FLOAT_DISPLAY(4, c);
}

void test_vector_int_display() {
    vec2_s32 a = {1, 2};
    VECTOR_INT_DISPLAY(2, a);
}

void test_vector_uint_display() {
    vec2_u32 a = {1, 2};
    VECTOR_UINT_DISPLAY(2, a);
}


int main() {
    test_vector_add();
    test_vector_sub();
    test_vector_mul();
    test_vector_div();
	test_vector_mul_float();
    test_vector_div_float();
    test_vector_float_display();
    test_vector_int_display();
    test_vector_uint_display();
    return 0;
}
