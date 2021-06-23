#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <err.h>

#include "unity.h"
#include "lists.h"

void setUp(void) { }
void tearDown(void) { }

//{{{void test_uint32_t_array(void)
void test_uint32_t_array(void)
{
    /*
    struct uint32_t_array
    {
        uint32_t num, size, *data;
    };

    struct uint32_t_array *uint32_t_array_init(uint32_t init_size);
    void uint32_t_array_destroy(struct uint32_t_array **ua);
    uint32_t uint32_t_array_add(struct uint32_t_array *ua, uint32_t val);
    uint32_t *uint32_t_array_get(struct uint32_t_array *ua, uint32_t index);
    */

    struct uint32_t_array *ua = uint32_t_array_init(10);

    TEST_ASSERT_EQUAL(10, ua->size);
    TEST_ASSERT_EQUAL(0, ua->num);

    uint32_t ret = uint32_t_array_add(ua, 5);

    TEST_ASSERT_EQUAL(10, ua->size);
    TEST_ASSERT_EQUAL(0, ret);
    TEST_ASSERT_EQUAL(1, ua->num);
    TEST_ASSERT_EQUAL(5, ua->data[0]);

    uint32_t *ret_p = uint32_t_array_get(ua, 0);
    TEST_ASSERT_EQUAL(5, *ret_p);

    ret_p = uint32_t_array_get(ua, 100);
    TEST_ASSERT_EQUAL(NULL, ret_p);


    uint32_t i;
    for (i = 0; i < 10; ++i) {
        ret = uint32_t_array_add(ua, 5);
        TEST_ASSERT_EQUAL(i + 1, ret);
    }

    TEST_ASSERT_EQUAL(20, ua->size);
    TEST_ASSERT_EQUAL(11, ua->num);

    FILE *fp = fopen("test_file.dat", "wb");
    if (fp == NULL)
        err(1, "Could not open test_file.dat");

    ret = uint32_t_array_write(ua, fp);

    TEST_ASSERT_EQUAL(1 + ua->num, ret);

    fclose(fp);
   
    fp = fopen("test_file.dat", "rb");
    if (fp == NULL)
        err(1, "Could not open test_file.dat");


    struct uint32_t_array *ub = uint32_t_array_read(fp);

    TEST_ASSERT_EQUAL(ua->num, ub->num);

    fclose(fp);

    for (i = 0; i < ua->num; ++i) {
        TEST_ASSERT_EQUAL(ua->data[i], ub->data[i]);
    }

    uint32_t_array_destroy(&ua);
    uint32_t_array_destroy(&ub);
}
//}}}

//{{{void test_uint32_t_sparse_matrix(void)
void test_uint32_t_sparse_matrix(void)
{
    struct uint32_t_sparse_matrix *m = uint32_t_sparse_matrix_init(10, 10);

    TEST_ASSERT_EQUAL(10, m->size);
    TEST_ASSERT_EQUAL(0, m->rows);

    uint32_t ret = uint32_t_sparse_matrix_add(m, 3, 10);

    TEST_ASSERT_EQUAL(10, m->data[3]->data[0]);

    ret = uint32_t_sparse_matrix_add(m, 20, 99);

    TEST_ASSERT_EQUAL(99, m->data[20]->data[0]);

    uint32_t *ret_p = uint32_t_sparse_martix_get(m, 3, 0);
    TEST_ASSERT_EQUAL(10, *ret_p);

    ret_p = uint32_t_sparse_martix_get(m, 20, 0);
    TEST_ASSERT_EQUAL(99, *ret_p);
 
    FILE *fp = fopen("test_matrix_file.dat", "wb");
    if (fp == NULL)
        err(1, "Could not open test_matrix_file.dat");

    ret = uint32_t_sparse_matrix_write(m, fp);
    fclose(fp);
    TEST_ASSERT_EQUAL(24, ret);

    fp = fopen("test_matrix_file.dat", "rb");
    struct uint32_t_sparse_matrix *m1 = uint32_t_sparse_matrix_read(fp);
    fclose(fp);

    ret_p = uint32_t_sparse_martix_get(m1, 20, 0);
    TEST_ASSERT_EQUAL(99, *ret_p);

    uint32_t_sparse_matrix_destroy(&m);
    uint32_t_sparse_matrix_destroy(&m1);
}
//}}}