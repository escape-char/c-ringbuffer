#include <check.h> //unit testing library
#include <stdlib.h>
#include <stdio.h>
#include "../ringbuffer/ringbuffer.h"

//buffer to test with
//global so all test functions can use it
RingBuffer* buffer=NULL;
#define BUFFER_SIZE 10

//this is called before
//every test function
void setup(void){
    buffer = (RingBuffer*)calloc(1, sizeof(RingBuffer));
    ringbuffer_create(buffer, BUFFER_SIZE);
}
//this is called after
//every test function
void teardown(void){
    ringbuffer_destroy(buffer);
    free(buffer);
}
START_TEST(test_ringbuffer_create){
    ck_assert_msg(buffer->length == BUFFER_SIZE, "buffer length should updated to reflect new size");

    //head and tail should be 0
    ck_assert_msg(buffer->head == 0 && buffer->tail == 0, "head and tail should be initialized to zero");

    //read and write counters initialize to zero
    ck_assert_msg(buffer->read_count == 0 && buffer->write_count == 0, "read and write counts should be initialized to zero");
}
END_TEST
START_TEST(test_ringbuffer_write){
    uint8_t data[5] = {0xF8, 0x88, 0xFE, 0x22};
    unsigned int i = 0;

    //write data to buffer
    for(; i < 5; i++){
        ringbuffer_write(buffer,data[i]);
    }

    printf("writecount: %d\n", buffer->write_count);
    ck_assert_msg(buffer->write_count == 5, "write count should be increased for each write");
    ck_assert_msg(buffer->tail == 5, "tail should be updated to next index position to write");
    ck_assert_msg(memcmp(buffer->data, &data, 5) == 0, "data in buffer should match input data");
}
END_TEST
START_TEST(test_ringbuffer_read){
    uint8_t data[5] = {0xF8, 0x88, 0xFE, 0x22};
    unsigned int i = 0;
    //write data to buffer
    for(; i < 5; i++){
        ringbuffer_write(buffer,data[i]);
    }
    uint8_t* read_val = calloc(1, sizeof(uint8_t));
    ringbuffer_read(buffer, read_val);
    ck_assert_msg(*read_val == 0xF8, "buffer should read oldest value placed in buffer first");
    ck_assert_msg(buffer->head == 1, "buffer's head should point to next oldest value");
    ck_assert_msg(buffer->read_count == 1, "buffer's read count should increment for each read");
}
END_TEST

//TODO
//test cases for is_empty and is_full
//negative test cases


//testing suite
//put all testing functions here
Suite* serial_suite(void){
    Suite *s = suite_create("ringbuffer");

    //core test cases
    TCase *tc_core = tcase_create("Core");
    tcase_add_checked_fixture(tc_core, setup, teardown);
    tcase_add_test(tc_core, test_ringbuffer_create);
    tcase_add_test(tc_core, test_ringbuffer_write);
    tcase_add_test(tc_core, test_ringbuffer_read);
    suite_add_tcase(s, tc_core); //add test cases to suite

    return s;
}
int main(){

    int number_failed;
    Suite *s = serial_suite();
    SRunner *sr = srunner_create(s);

    //run all the tests
    srunner_run_all(sr, CK_VERBOSE);
    
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
