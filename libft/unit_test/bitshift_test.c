#include "../bitshift_utils.h"
#include <assert.h>
#include <stdio.h>

void test_s32StoreValues(void) {
    s32 result = s32StoreValues(0x12, 0x34, 0x56, 0x78);
    assert(result == 0x12345678);
}

void test_s32ValueGet(void) {
    s32 container = 0x12345678;
    assert(s32ValueGet(container, BYTE1_SHIFT) == 0x12);
    assert(s32ValueGet(container, BYTE2_SHIFT) == 0x34);
    assert(s32ValueGet(container, BYTE3_SHIFT) == 0x56);
    assert(s32ValueGet(container, BYTE4_SHIFT) == 0x78);
}

void test_s32ValueGetByte(void) {
    s32 container = 0x12345678; // Exemple de valeur pour le test

    // Test extraction de chaque octet
    assert(s32ValueGetByte(container, 0) == 0x78); // Teste l'octet le moins significatif
    assert(s32ValueGetByte(container, 1) == 0x56); // Teste le deuxième octet
    assert(s32ValueGetByte(container, 2) == 0x34); // Teste le troisième octet
    assert(s32ValueGetByte(container, 3) == 0x12); // Teste l'octet le plus significatif
}

void test_u8StoreValues(void) {
    // Test with specific bit values
    u8 result = u8StoreValues(1, 0, 1, 0, 1, 0, 1, 0);
    assert(result == 0xAA); // 10101010 in binary

    result = u8StoreValues(0, 1, 0, 1, 0, 1, 0, 1);
    assert(result == 0x55); // 01010101 in binary
}

void test_combined_s32_u8_store(void) {
    // Use s32StoreValues to store values in each byte of the container
    s32 container = s32StoreValues(0x12, 0x34, 0x56, 0x78);

	assert(s32ValueGetByte(container, 3) == 0x12); // Verify the most significant byte
	assert(s32ValueGetByte(container, 2) == 0x34); // Verify the second byte
	assert(s32ValueGetByte(container, 1) == 0x56); // Verify the third byte
	assert(s32ValueGetByte(container, 0) == 0x78); // Verify the least significant byte

    // Use u8StoreValues to create a new byte value with specific bits
    u8 modifiedByte = u8StoreValues(1, 1, 1, 1, 0, 0, 0, 0); // Creates 0xF0

    // Update a specific byte in the container with the new value
    // Assuming we want to replace the least significant byte (0x78) by 0xF0
    // We need to reconstruct the container with the modified byte
    container = s32StoreValues(s32ValueGetByte(container, 3), s32ValueGetByte(container, 2), s32ValueGetByte(container, 1), modifiedByte);

    // Verify that the container contains the expected values
    assert(s32ValueGetByte(container, 3) == 0x12); // Verify the most significant byte
    assert(s32ValueGetByte(container, 2) == 0x34); // Verify the second byte
    assert(s32ValueGetByte(container, 1) == 0x56); // Verify the third byte
    assert(s32ValueGetByte(container, 0) == modifiedByte); // Verify the least significant byte

	u8 modifiedByte2 = u8StoreValues(0, 0, 1, 0, 0, 1, 1, 0);  // 0b00100110

	container = s32StoreValues(s32ValueGetByte(container, 3), s32ValueGetByte(container, 2), modifiedByte2, s32ValueGetByte(container, 0));
	assert(s32ValueGetByte(container, 3) == 0x12); // Verify the most significant byte
	assert(s32ValueGetByte(container, 2) == 0x34); // Verify the third byte
	assert(s32ValueGetByte(container, 1) == modifiedByte2); // Verify the second byte
	assert(s32ValueGetByte(container, 0) == modifiedByte); // Verify the least significant byte

	u8 byte = s32ValueGetByte(container, 1);

	assert(byte == 0b00100110);
	assert(u8ValueGet(byte, 7) == 0);
	assert(u8ValueGet(byte, 6) == 0);
	assert(u8ValueGet(byte, 5) == 1);
	assert(u8ValueGet(byte, 4) == 0);
	assert(u8ValueGet(byte, 3) == 0);
	assert(u8ValueGet(byte, 2) == 1);
	assert(u8ValueGet(byte, 1) == 1);
	assert(u8ValueGet(byte, 0) == 0);

    printf("Combined s32 and u8 store test passed.\n");
}

void test_u8ValueGet(void) {
    u8 container = 0b10101010; // 0xAA
    assert(u8ValueGet(container, 7) == 1);
    assert(u8ValueGet(container, 6) == 0);
    assert(u8ValueGet(container, 6) != 1);
    assert(u8ValueGet(container, 5) == 1);
    assert(u8ValueGet(container, 0) == 0);

    container = 0b01010101; // 0x55
    assert(u8ValueGet(container, 7) == 0);
    assert(u8ValueGet(container, 6) == 1);
    assert(u8ValueGet(container, 5) == 0);
    assert(u8ValueGet(container, 0) == 1);
}

void test_u8ValueSet(void) {
	u8 container = 0b00000000; // 0xAA
	container = u8ValueSet(container, 7, 1);
	assert(container == 0b10000000); // 0x80

	container = u8ValueSet(container, 6, 1);
	assert(container == 0b11000000); // 0x7A

	container = u8ValueSet(container, 5, 1);
	assert(container == 0b11100000); // 0x7A

	container = u8ValueSet(container, 3, 1);
	assert(container == 0b11101000); // 0x7A

	container = u8ValueSet(container, 0, 1);
	assert(container == 0b11101001); // 0x7A

	container = u8ValueSet(container, 7, 0);
	assert(container == 0b01101001); // 0x7A

	container = u8ValueSet(container, 6, 0);
	assert(container == 0b00101001); // 0x7A

	printf("u8ValueSet test passed.\n");
}

int main(void) {
    // Run tests
    test_s32StoreValues();
    test_s32ValueGet();
	test_s32ValueGetByte();
    printf("All bitshift_utils tests passed.\n");

    test_u8StoreValues();
    test_u8ValueGet();
	test_u8ValueSet();
    printf("All u8 bit manipulation tests passed.\n");

	test_combined_s32_u8_store();
    return 0;
}
