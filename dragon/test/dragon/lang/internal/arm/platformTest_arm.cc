/*
* Copyright 2013 the original author or authors.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

/**********************************************************************
 * Author:      Owen Wu/wcw/yubing
 * Email:       yubing744@163.com
 * Created:     2013/07/13
 **********************************************************************/

#include <gtest/gtest.h>
#include <typeinfo>

#include <dragon/lang/internal/platform.h>

Import dragon::lang::internal;


/*

dragon/test/dragon/lang/internal/arm/platformTest_arm.cc:115
dragon/test/dragon/lang/internal/arm/platformTest_arm.cc:116
0x0003daa0: ldr	r0, [r11, #-8]                                                   # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_float_Test::TestBody()+120
0x0003daa4: ldr	r1, [r11, #-12]                                                  # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_float_Test::TestBody()+124
0x0003daa8: ldr	r2, [r11, #-16]                                                  # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_float_Test::TestBody()+128
0x0003daac: ldr	r3, [r11, #-20]                                                  # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_float_Test::TestBody()+132
0x0003dab0: bl	0x3d970 <invoke_test_float_04(float, float, float, float)>        # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_float_Test::TestBody()+136
dragon/test/dragon/lang/internal/arm/platformTest_arm.cc:117
0x0003dab4: ldr	r3, [r11, #-24]                                                  # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_float_Test::TestBody()+140
0x0003dab8: str	r3, [sp]                                                         # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_float_Test::TestBody()+144
0x0003dabc: ldr	r3, [r11, #-28]                                                  # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_float_Test::TestBody()+148
0x0003dac0: str	r3, [sp, #4]                                                     # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_float_Test::TestBody()+152
0x0003dac4: ldr	r0, [r11, #-8]                                                   # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_float_Test::TestBody()+156
0x0003dac8: ldr	r1, [r11, #-12]                                                  # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_float_Test::TestBody()+160
0x0003dacc: ldr	r2, [r11, #-16]                                                  # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_float_Test::TestBody()+164
0x0003dad0: ldr	r3, [r11, #-20]                                                  # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_float_Test::TestBody()+168
0x0003dad4: bl	0x3d8e8 <invoke_test_float_03(float, float, float, float, float, float)> # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_float_Test::TestBody()+172
dragon/test/dragon/lang/internal/arm/platformTest_arm.cc:118
0x0003dad8: ldr	r3, [r11, #-24]                                                  # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_float_Test::TestBody()+176
0x0003dadc: str	r3, [sp]                                                         # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_float_Test::TestBody()+180
0x0003dae0: ldr	r3, [r11, #-28]                                                  # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_float_Test::TestBody()+184
0x0003dae4: str	r3, [sp, #4]                                                     # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_float_Test::TestBody()+188
0x0003dae8: ldr	r3, [r11, #-32]                                                  # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_float_Test::TestBody()+192
0x0003daec: str	r3, [sp, #8]                                                     # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_float_Test::TestBody()+196
0x0003daf0: ldr	r3, [r11, #-36]	; 0x24                                           # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_float_Test::TestBody()+200
0x0003daf4: str	r3, [sp, #12]                                                    # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_float_Test::TestBody()+204
0x0003daf8: ldr	r0, [r11, #-8]                                                   # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_float_Test::TestBody()+208
0x0003dafc: ldr	r1, [r11, #-12]                                                  # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_float_Test::TestBody()+212
0x0003db00: ldr	r2, [r11, #-16]                                                  # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_float_Test::TestBody()+216
0x0003db04: ldr	r3, [r11, #-20]                                                  # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_float_Test::TestBody()+220
0x0003db08: bl	0x3d840 <invoke_test_float_02(float, float, float, float, float, float, float, float)> # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_float_Test::TestBody()+224
dragon/test/dragon/lang/internal/arm/platformTest_arm.cc:119
0x0003db0c: ldr	r3, [r11, #-24]                                                  # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_float_Test::TestBody()+228
0x0003db10: str	r3, [sp]                                                         # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_float_Test::TestBody()+232
0x0003db14: ldr	r3, [r11, #-28]                                                  # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_float_Test::TestBody()+236
0x0003db18: str	r3, [sp, #4]                                                     # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_float_Test::TestBody()+240
0x0003db1c: ldr	r3, [r11, #-32]                                                  # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_float_Test::TestBody()+244
0x0003db20: str	r3, [sp, #8]                                                     # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_float_Test::TestBody()+248
0x0003db24: ldr	r3, [r11, #-36]	; 0x24                                           # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_float_Test::TestBody()+252
0x0003db28: str	r3, [sp, #12]                                                    # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_float_Test::TestBody()+256
0x0003db2c: ldr	r3, [r11, #-40]	; 0x28                                           # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_float_Test::TestBody()+260
0x0003db30: str	r3, [sp, #16]                                                    # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_float_Test::TestBody()+264
0x0003db34: ldr	r3, [r11, #-44]	; 0x2c                                           # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_float_Test::TestBody()+268
0x0003db38: str	r3, [sp, #20]                                                    # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_float_Test::TestBody()+272
0x0003db3c: ldr	r3, [r11, #-48]	; 0x30                                           # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_float_Test::TestBody()+276
0x0003db40: str	r3, [sp, #24]                                                    # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_float_Test::TestBody()+280
0x0003db44: ldr	r3, [r11, #-52]	; 0x34                                           # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_float_Test::TestBody()+284
0x0003db48: str	r3, [sp, #28]                                                    # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_float_Test::TestBody()+288
0x0003db4c: ldr	r3, [r11, #-56]	; 0x38                                           # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_float_Test::TestBody()+292
0x0003db50: str	r3, [sp, #32]                                                    # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_float_Test::TestBody()+296
0x0003db54: ldr	r0, [r11, #-8]                                                   # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_float_Test::TestBody()+300
0x0003db58: ldr	r1, [r11, #-12]                                                  # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_float_Test::TestBody()+304
0x0003db5c: ldr	r2, [r11, #-16]                                                  # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_float_Test::TestBody()+308
0x0003db60: ldr	r3, [r11, #-20]                                                  # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_float_Test::TestBody()+312
0x0003db64: bl	0x3d748 <invoke_test_float_01(float, float, float, float, float, float, float, float, float, float, float, float, float)> # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_float_Test::TestBody()+316

TEST(Dragon_Lang_Internal_platformTest_arm, Invoke_Multi_Args_float) {
	float a1 = 1;
	float b1 = 2;
	float c1 = 3;
	float d1 = 4;
	float e1 = 5;
	float f1 = 6;
	float g1 = 7;
	float h1 = 8;
	float i1 = 9;
	float j1 = 10;
	float k1 = 11;
	float l1 = 12;
	float m1 = 13;

	invoke_test_float_04(a1, b1, c1, d1);
	invoke_test_float_03(a1, b1, c1, d1, e1, f1);
	invoke_test_float_02(a1, b1, c1, d1, e1, f1, g1, h1);
	invoke_test_float_01(a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1);
}
*/

//------------------------------------------------------------
// func pointer invoke test
// 

/*
dragon/test/dragon/lang/internal/arm/platformTest_arm.cc:193
0x0003e7fc: str	r0, [r11, #-56]	; 0x38                                           # Dragon_Lang_Internal_platformTest_arm_func_pointer_invoke_test_Test::TestBody()+20
dragon/test/dragon/lang/internal/arm/platformTest_arm.cc:194
0x0003e800: mov	r3, #1                                                           # Dragon_Lang_Internal_platformTest_arm_func_pointer_invoke_test_Test::TestBody()+24
0x0003e804: str	r3, [r11, #-20]                                                  # Dragon_Lang_Internal_platformTest_arm_func_pointer_invoke_test_Test::TestBody()+28
dragon/test/dragon/lang/internal/arm/platformTest_arm.cc:195
0x0003e808: mov	r3, #2                                                           # Dragon_Lang_Internal_platformTest_arm_func_pointer_invoke_test_Test::TestBody()+32
0x0003e80c: str	r3, [r11, #-24]                                                  # Dragon_Lang_Internal_platformTest_arm_func_pointer_invoke_test_Test::TestBody()+36
dragon/test/dragon/lang/internal/arm/platformTest_arm.cc:196
dragon/test/dragon/lang/internal/arm/platformTest_arm.cc:197
0x0003e810: ldr	r0, [r11, #-20]                                                  # Dragon_Lang_Internal_platformTest_arm_func_pointer_invoke_test_Test::TestBody()+40
0x0003e814: ldr	r1, [r11, #-24]                                                  # Dragon_Lang_Internal_platformTest_arm_func_pointer_invoke_test_Test::TestBody()+44
0x0003e818: bl	0x3e768 <dd_add(int, int)>                                        # Dragon_Lang_Internal_platformTest_arm_func_pointer_invoke_test_Test::TestBody()+48
0x0003e81c: mov	r3, r0                                                           # Dragon_Lang_Internal_platformTest_arm_func_pointer_invoke_test_Test::TestBody()+52
0x0003e820: str	r3, [r11, #-28]                                                  # Dragon_Lang_Internal_platformTest_arm_func_pointer_invoke_test_Test::TestBody()+56
dragon/test/dragon/lang/internal/arm/platformTest_arm.cc:198
dragon/test/dragon/lang/internal/arm/platformTest_arm.cc:199
0x0003e7f4: ldr	r4, [pc, #448]	; 0x3e9bc <Dragon_Lang_Internal_platformTest_arm_func_pointer_invoke_test_Test::TestBody()+468> # Dragon_Lang_Internal_platformTest_arm_func_pointer_invoke_test_Test::TestBody()+12
0x0003e7f8: add	r4, pc, r4                                                       # Dragon_Lang_Internal_platformTest_arm_func_pointer_invoke_test_Test::TestBody()+16
0x0003e824: ldr	r3, [pc, #404]	; 0x3e9c0 <Dragon_Lang_Internal_platformTest_arm_func_pointer_invoke_test_Test::TestBody()+472> # Dragon_Lang_Internal_platformTest_arm_func_pointer_invoke_test_Test::TestBody()+60
0x0003e828: ldr	r3, [r4, r3]                                                     # Dragon_Lang_Internal_platformTest_arm_func_pointer_invoke_test_Test::TestBody()+64
0x0003e82c: str	r3, [r11, #-32]                                                  # Dragon_Lang_Internal_platformTest_arm_func_pointer_invoke_test_Test::TestBody()+68
dragon/test/dragon/lang/internal/arm/platformTest_arm.cc:200
0x0003e830: ldr	r3, [r11, #-32]                                                  # Dragon_Lang_Internal_platformTest_arm_func_pointer_invoke_test_Test::TestBody()+72
0x0003e834: ldr	r0, [r11, #-20]                                                  # Dragon_Lang_Internal_platformTest_arm_func_pointer_invoke_test_Test::TestBody()+76
0x0003e838: ldr	r1, [r11, #-24]                                                  # Dragon_Lang_Internal_platformTest_arm_func_pointer_invoke_test_Test::TestBody()+80
0x0003e83c: blx	r3                                                               # Dragon_Lang_Internal_platformTest_arm_func_pointer_invoke_test_Test::TestBody()+84
0x0003e840: mov	r3, r0                                                           # Dragon_Lang_Internal_platformTest_arm_func_pointer_invoke_test_Test::TestBody()+88
0x0003e844: str	r3, [r11, #-36]	; 0x24    
 */

/*
typedef int (ADD_FUNC)(int a, int b);

int dd_add(int a, int b) {
	return a + b;
}

TEST(Dragon_Lang_Internal_platformTest_arm, func_pointer_invoke_test) {
	int a = 1;
	int b = 2;

	int c1 = dd_add(a, b);

	ADD_FUNC* add_func = &dd_add;
	int c2 = add_func(a, b);

	EXPECT_EQ(true, c1 == c2);
}
*/

//------------------------------------------------------------
// double return invoke test
// 
/*
dragon/test/dragon/lang/internal/arm/platformTest_arm.cc:239
0x0003e9d0: push     {r11, lr}                                                       # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+0
0x0003e9d4: add     r11, sp, #4                                                      # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+4
0x0003e9d8: sub     sp, sp, #24                                                      # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+8
0x0003e9dc: str     r0, [r11, #-16]                                                  # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+12
0x0003e9e0: strd     r2, [r11, #-28]     ; 0xffffffe4                                    # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+16
dragon/test/dragon/lang/internal/arm/platformTest_arm.cc:240
0x0003e9e4: ldrd     r0, [r11, #-28]     ; 0xffffffe4                                    # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+20
0x0003e9e8: ldrd     r2, [r11, #4]                                                   # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+24
0x0003e9ec: bl     0x156a4 <__aeabi_dadd>                                            # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+28
0x0003e9f0: mov     r2, r0                                                           # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+32
0x0003e9f4: mov     r3, r1                                                           # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+36
0x0003e9f8: mov     r0, r2                                                           # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+40
0x0003e9fc: mov     r1, r3                                                           # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+44
0x0003ea00: ldrd     r2, [r11, #12]                                                  # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+48
0x0003ea04: bl     0x156a4 <__aeabi_dadd>                                            # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+52
0x0003ea08: mov     r2, r0                                                           # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+56
0x0003ea0c: mov     r3, r1                                                           # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+60
0x0003ea10: mov     r0, r2                                                           # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+64
0x0003ea14: mov     r1, r3                                                           # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+68
0x0003ea18: ldrd     r2, [r11, #20]                                                  # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+72
0x0003ea1c: bl     0x156a4 <__aeabi_dadd>                                            # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+76
0x0003ea20: mov     r2, r0                                                           # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+80
0x0003ea24: mov     r3, r1                                                           # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+84
0x0003ea28: mov     r0, r2                                                           # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+88
0x0003ea2c: mov     r1, r3                                                           # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+92
0x0003ea30: ldrd     r2, [r11, #28]                                                  # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+96
0x0003ea34: bl     0x156a4 <__aeabi_dadd>                                            # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+100
0x0003ea38: mov     r2, r0                                                           # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+104
0x0003ea3c: mov     r3, r1                                                           # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+108
0x0003ea40: mov     r0, r2                                                           # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+112
0x0003ea44: mov     r1, r3                                                           # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+116
0x0003ea48: ldrd     r2, [r11, #36]     ; 0x24                                           # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+120
0x0003ea4c: bl     0x156a4 <__aeabi_dadd>                                            # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+124
0x0003ea50: mov     r2, r0                                                           # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+128
0x0003ea54: mov     r3, r1                                                           # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+132
0x0003ea58: mov     r0, r2                                                           # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+136
0x0003ea5c: mov     r1, r3                                                           # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+140
0x0003ea60: ldrd     r2, [r11, #44]     ; 0x2c                                           # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+144
0x0003ea64: bl     0x156a4 <__aeabi_dadd>                                            # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+148
0x0003ea68: mov     r2, r0                                                           # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+152
0x0003ea6c: mov     r3, r1                                                           # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+156
0x0003ea70: mov     r0, r2                                                           # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+160
0x0003ea74: mov     r1, r3                                                           # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+164
0x0003ea78: ldrd     r2, [r11, #52]     ; 0x34                                           # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+168
0x0003ea7c: bl     0x156a4 <__aeabi_dadd>                                            # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+172
0x0003ea80: mov     r2, r0                                                           # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+176
0x0003ea84: mov     r3, r1                                                           # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+180
0x0003ea88: mov     r0, r2                                                           # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+184
0x0003ea8c: mov     r1, r3                                                           # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+188
0x0003ea90: ldrd     r2, [r11, #60]     ; 0x3c                                           # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+192
0x0003ea94: bl     0x156a4 <__aeabi_dadd>                                            # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+196
0x0003ea98: mov     r2, r0                                                           # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+200
0x0003ea9c: mov     r3, r1                                                           # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+204
0x0003eaa0: mov     r0, r2                                                           # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+208
0x0003eaa4: mov     r1, r3                                                           # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+212
0x0003eaa8: ldrd     r2, [r11, #68]     ; 0x44                                           # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+216
0x0003eaac: bl     0x156a4 <__aeabi_dadd>                                            # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+220
0x0003eab0: mov     r2, r0                                                           # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+224
0x0003eab4: mov     r3, r1                                                           # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+228
0x0003eab8: mov     r0, r2                                                           # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+232
0x0003eabc: mov     r1, r3                                                           # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+236
0x0003eac0: ldrd     r2, [r11, #76]     ; 0x4c                                           # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+240
0x0003eac4: bl     0x156a4 <__aeabi_dadd>                                            # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+244
0x0003eac8: mov     r2, r0                                                           # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+248
0x0003eacc: mov     r3, r1                                                           # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+252
0x0003ead0: mov     r0, r2                                                           # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+256
0x0003ead4: mov     r1, r3                                                           # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+260
0x0003ead8: ldrd     r2, [r11, #84]     ; 0x54                                           # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+264
0x0003eadc: bl     0x156a4 <__aeabi_dadd>                                            # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+268
0x0003eae0: mov     r2, r0                                                           # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+272
0x0003eae4: mov     r3, r1                                                           # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+276
0x0003eae8: mov     r0, r2                                                           # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+280
0x0003eaec: mov     r1, r3                                                           # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+284
0x0003eaf0: ldrd     r2, [r11, #92]     ; 0x5c                                           # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+288
0x0003eaf4: bl     0x156a4 <__aeabi_dadd>                                            # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+292
0x0003eaf8: mov     r2, r0                                                           # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+296
0x0003eafc: mov     r3, r1                                                           # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+300
0x0003eb00: strd     r2, [r11, #-12]       


dragon/test/dragon/lang/internal/arm/platformTest_arm.cc:241
0x0003eb04: ldrd     r2, [r11, #-12]                                                 # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+308
dragon/test/dragon/lang/internal/arm/platformTest_arm.cc:242
0x0003eb08: mov     r0, r2                                                           # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+312
0x0003eb0c: mov     r1, r3                                                           # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+316
0x0003eb10: sub     sp, r11, #4                                                      # invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)+320
0x0003eb14: pop     {r11, pc}     
 */
/*
double invoke_test_double_ret_invoke_01(void* pthis, double a1, double b1, double c1, double d1, double e1, double f1, double g1, double h1, double i1, double j1, double k1, double l1, double m1) {
	double a = a1 + b1 + c1 + d1 + e1 + f1 + g1 + h1 + i1 + j1 + k1 + l1 + m1;
	return a;
}
*/
/*

dragon/test/dragon/lang/internal/arm/platformTest_arm.cc:244
0x0003eb7c: str     r0, [r11, #-384]     ; 0x180                                         # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+20
dragon/test/dragon/lang/internal/arm/platformTest_arm.cc:245
0x0003eb80: ldr     r3, [pc, #1612]     ; 0x3f1d4 <Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+1644> # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+24
0x0003eb84: str     r3, [r11, #-28]                                                  # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+28
dragon/test/dragon/lang/internal/arm/platformTest_arm.cc:246
dragon/test/dragon/lang/internal/arm/platformTest_arm.cc:247
0x0003eb88: mov     r2, #0                                                           # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+32
0x0003eb8c: mov     r3, #1069547520     ; 0x3fc00000                                     # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+36
0x0003eb90: add     r3, r3, #3145728     ; 0x300000                                      # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+40
0x0003eb94: strd     r2, [r11, #-52]     ; 0xffffffcc                                    # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+44
dragon/test/dragon/lang/internal/arm/platformTest_arm.cc:248
0x0003eb98: mov     r2, #0                                                           # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+48
0x0003eb9c: mov     r3, #1073741824     ; 0x40000000                                     # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+52
0x0003eba0: strd     r2, [r11, #-60]     ; 0xffffffc4                                    # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+56
dragon/test/dragon/lang/internal/arm/platformTest_arm.cc:249
0x0003eba4: mov     r2, #0                                                           # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+60
0x0003eba8: mov     r3, #1073741824     ; 0x40000000                                     # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+64
0x0003ebac: add     r3, r3, #524288     ; 0x80000                                        # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+68
0x0003ebb0: strd     r2, [r11, #-68]     ; 0xffffffbc                                    # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+72
dragon/test/dragon/lang/internal/arm/platformTest_arm.cc:250
0x0003ebb4: mov     r2, #0                                                           # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+76
0x0003ebb8: mov     r3, #1073741824     ; 0x40000000                                     # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+80
0x0003ebbc: add     r3, r3, #1048576     ; 0x100000                                      # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+84
0x0003ebc0: strd     r2, [r11, #-76]     ; 0xffffffb4                                    # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+88
dragon/test/dragon/lang/internal/arm/platformTest_arm.cc:251
0x0003ebc4: mov     r2, #0                                                           # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+92
0x0003ebc8: mov     r3, #1073741824     ; 0x40000000                                     # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+96
0x0003ebcc: add     r3, r3, #1310720     ; 0x140000                                      # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+100
0x0003ebd0: strd     r2, [r11, #-84]     ; 0xffffffac                                    # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+104
dragon/test/dragon/lang/internal/arm/platformTest_arm.cc:252
0x0003ebd4: mov     r2, #0                                                           # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+108
0x0003ebd8: mov     r3, #1073741824     ; 0x40000000                                     # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+112
0x0003ebdc: add     r3, r3, #1572864     ; 0x180000                                      # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+116
0x0003ebe0: strd     r2, [r11, #-92]     ; 0xffffffa4                                    # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+120
dragon/test/dragon/lang/internal/arm/platformTest_arm.cc:253
0x0003ebe4: mov     r2, #0                                                           # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+124
0x0003ebe8: mov     r3, #1073741824     ; 0x40000000                                     # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+128
0x0003ebec: add     r3, r3, #1835008     ; 0x1c0000                                      # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+132
0x0003ebf0: strd     r2, [r11, #-100]     ; 0xffffff9c                                   # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+136
dragon/test/dragon/lang/internal/arm/platformTest_arm.cc:254
0x0003ebf4: mov     r2, #0                                                           # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+140
0x0003ebf8: mov     r3, #1073741824     ; 0x40000000                                     # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+144
0x0003ebfc: add     r3, r3, #2097152     ; 0x200000                                      # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+148
0x0003ec00: strd     r2, [r11, #-108]     ; 0xffffff94                                   # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+152
dragon/test/dragon/lang/internal/arm/platformTest_arm.cc:255
0x0003ec04: mov     r2, #0                                                           # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+156
0x0003ec08: mov     r3, #1073741824     ; 0x40000000                                     # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+160
0x0003ec0c: add     r3, r3, #2228224     ; 0x220000                                      # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+164
0x0003ec10: strd     r2, [r11, #-116]     ; 0xffffff8c                                   # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+168
dragon/test/dragon/lang/internal/arm/platformTest_arm.cc:256
0x0003ec14: mov     r2, #0                                                           # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+172
0x0003ec18: mov     r3, #1073741824     ; 0x40000000                                     # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+176
0x0003ec1c: add     r3, r3, #2359296     ; 0x240000                                      # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+180
0x0003ec20: strd     r2, [r11, #-124]     ; 0xffffff84                                   # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+184
dragon/test/dragon/lang/internal/arm/platformTest_arm.cc:257
0x0003ec24: mov     r2, #0                                                           # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+188
0x0003ec28: mov     r3, #1073741824     ; 0x40000000                                     # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+192
0x0003ec2c: add     r3, r3, #2490368     ; 0x260000                                      # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+196
0x0003ec30: strd     r2, [r11, #-132]     ; 0xffffff7c                                   # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+200
dragon/test/dragon/lang/internal/arm/platformTest_arm.cc:258
0x0003ec34: mov     r2, #0                                                           # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+204
0x0003ec38: mov     r3, #1073741824     ; 0x40000000                                     # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+208
0x0003ec3c: add     r3, r3, #2621440     ; 0x280000                                      # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+212
0x0003ec40: strd     r2, [r11, #-140]     ; 0xffffff74                                   # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+216
dragon/test/dragon/lang/internal/arm/platformTest_arm.cc:259
0x0003ec44: mov     r2, #0                                                           # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+220
0x0003ec48: mov     r3, #1073741824     ; 0x40000000                                     # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+224
0x0003ec4c: add     r3, r3, #2752512     ; 0x2a0000                                      # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+228
0x0003ec50: strd     r2, [r11, #-148]     ; 0xffffff6c                                   # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+232
dragon/test/dragon/lang/internal/arm/platformTest_arm.cc:260
dragon/test/dragon/lang/internal/arm/platformTest_arm.cc:261
0x0003ec54: ldrd     r2, [r11, #-60]     ; 0xffffffc4                                    # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+236
0x0003ec58: strd     r2, [sp]                                                        # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+240
0x0003ec5c: ldrd     r2, [r11, #-68]     ; 0xffffffbc                                    # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+244
0x0003ec60: strd     r2, [sp, #8]                                                    # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+248
0x0003ec64: ldrd     r2, [r11, #-76]     ; 0xffffffb4                                    # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+252
0x0003ec68: strd     r2, [sp, #16]                                                   # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+256
0x0003ec6c: ldrd     r2, [r11, #-84]     ; 0xffffffac                                    # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+260
0x0003ec70: strd     r2, [sp, #24]                                                   # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+264
0x0003ec74: ldrd     r2, [r11, #-92]     ; 0xffffffa4                                    # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+268
0x0003ec78: strd     r2, [sp, #32]                                                   # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+272
0x0003ec7c: ldrd     r2, [r11, #-100]     ; 0xffffff9c                                   # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+276
0x0003ec80: strd     r2, [sp, #40]     ; 0x28                                            # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+280
0x0003ec84: ldrd     r2, [r11, #-108]     ; 0xffffff94                                   # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+284
0x0003ec88: strd     r2, [sp, #48]     ; 0x30                                            # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+288
0x0003ec8c: ldrd     r2, [r11, #-116]     ; 0xffffff8c                                   # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+292
0x0003ec90: strd     r2, [sp, #56]     ; 0x38                                            # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+296
0x0003ec94: ldrd     r2, [r11, #-124]     ; 0xffffff84                                   # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+300
0x0003ec98: strd     r2, [sp, #64]     ; 0x40                                            # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+304
0x0003ec9c: ldrd     r2, [r11, #-132]     ; 0xffffff7c                                   # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+308
0x0003eca0: strd     r2, [sp, #72]     ; 0x48                                            # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+312
0x0003eca4: ldrd     r2, [r11, #-140]     ; 0xffffff74                                   # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+316
0x0003eca8: strd     r2, [sp, #80]     ; 0x50                                            # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+320
0x0003ecac: ldrd     r2, [r11, #-148]     ; 0xffffff6c                                   # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+324
0x0003ecb0: strd     r2, [sp, #88]     ; 0x58                                            # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+328
0x0003ecb4: ldr     r0, [r11, #-28]                                                  # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+332
0x0003ecb8: ldrd     r2, [r11, #-52]     ; 0xffffffcc                                    # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+336
0x0003ecbc: bl     0x3e9d0 <invoke_test_double_ret_invoke_01(void*, double, double, double, double, double, double, double, double, double, double, double, double, double)> # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+340
0x0003ecc0: mov     r2, r0                                                           # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+344
0x0003ecc4: mov     r3, r1                                                           # Dragon_Lang_Internal_platformTest_arm_Invoke_Multi_Args_double_ret_invoke_Test::TestBody()+348
0x0003ecc8: strd     r2, [r11, #-156]     ; 0xffffff64  
 */

/*
TEST(Dragon_Lang_Internal_platformTest_arm, Invoke_Multi_Args_double_ret_invoke) {
	void* pthis = (void*)(8888);

	double a1 = 1;
	double b1 = 2;
	double c1 = 3;
	double d1 = 4;
	double e1 = 5;
	double f1 = 6;
	double g1 = 7;
	double h1 = 8;
	double i1 = 9;
	double j1 = 10;
	double k1 = 11;
	double l1 = 12;
	double m1 = 13;

	double dd1 = invoke_test_double_ret_invoke_01(pthis, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1);

	ReturnInfo* ret = new ReturnInfo("double");

	ParamInfo* params = (ParamInfo*)malloc(sizeof(ParamInfo) * 13); 
    params[0] = ParamInfo(a1);
    params[1] = ParamInfo(b1);
    params[2] = ParamInfo(c1);
    params[3] = ParamInfo(d1);
    params[4] = ParamInfo(e1);
    params[5] = ParamInfo(f1);
    params[6] = ParamInfo(g1);
    params[7] = ParamInfo(h1);
    params[8] = ParamInfo(i1);
    params[9] = ParamInfo(j1);
    params[10] = ParamInfo(k1);
    params[11] = ParamInfo(l1);
    params[12] = ParamInfo(m1);

	Invoke(pthis, (void*)(&invoke_test_double_ret_invoke_01), ret, params, 13);

	double dd2 = ret->getValue<double>();
	dg_boolean is_true = (dd1 == dd2);
	EXPECT_EQ(dg_true, is_true);

	SafeDelete(ret);
	SafeFree(params);
*/ 
