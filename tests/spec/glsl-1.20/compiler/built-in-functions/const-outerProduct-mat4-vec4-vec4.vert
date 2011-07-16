/* [config]
 * expect_result: pass
 * glsl_version: 1.20
 * [end config]
 * Automatically generated by gen_constant_array_size_tests.py
 */
#version 120

float[length(vec4(2.7225, -2.1945, -3.1845, -1.254) - outerProduct(vec4(-1.65, 1.33, 1.93, 0.76), vec4(-1.65, 1.33, 1.93, 0.76))[0]) < 0.001 ? 1 : -1] array0;
float[length(vec4(-2.1945, 1.7689, 2.5669, 1.0108) - outerProduct(vec4(-1.65, 1.33, 1.93, 0.76), vec4(-1.65, 1.33, 1.93, 0.76))[1]) < 0.001 ? 1 : -1] array1;
float[length(vec4(-3.1845, 2.5669, 3.7249, 1.4668) - outerProduct(vec4(-1.65, 1.33, 1.93, 0.76), vec4(-1.65, 1.33, 1.93, 0.76))[2]) < 0.001 ? 1 : -1] array2;
float[length(vec4(-1.254, 1.0108, 1.4668, 0.5776) - outerProduct(vec4(-1.65, 1.33, 1.93, 0.76), vec4(-1.65, 1.33, 1.93, 0.76))[3]) < 0.001 ? 1 : -1] array3;
float[length(vec4(-1.32, 1.064, 1.544, 0.608) - outerProduct(vec4(-1.65, 1.33, 1.93, 0.76), vec4(0.8, -0.15, -0.51, 0.0))[0]) < 0.001 ? 1 : -1] array4;
float[length(vec4(0.2475, -0.1995, -0.2895, -0.114) - outerProduct(vec4(-1.65, 1.33, 1.93, 0.76), vec4(0.8, -0.15, -0.51, 0.0))[1]) < 0.001 ? 1 : -1] array5;
float[length(vec4(0.8415, -0.6783, -0.9843, -0.3876) - outerProduct(vec4(-1.65, 1.33, 1.93, 0.76), vec4(0.8, -0.15, -0.51, 0.0))[2]) < 0.001 ? 1 : -1] array6;
float[length(vec4(-0, 0.0, 0.0, 0.0) - outerProduct(vec4(-1.65, 1.33, 1.93, 0.76), vec4(0.8, -0.15, -0.51, 0.0))[3]) < 0.001 ? 1 : -1] array7;
float[length(vec4(-1.32, 0.2475, 0.8415, -0) - outerProduct(vec4(0.8, -0.15, -0.51, 0.0), vec4(-1.65, 1.33, 1.93, 0.76))[0]) < 0.001 ? 1 : -1] array8;
float[length(vec4(1.064, -0.1995, -0.6783, 0.0) - outerProduct(vec4(0.8, -0.15, -0.51, 0.0), vec4(-1.65, 1.33, 1.93, 0.76))[1]) < 0.001 ? 1 : -1] array9;
float[length(vec4(1.544, -0.2895, -0.9843, 0.0) - outerProduct(vec4(0.8, -0.15, -0.51, 0.0), vec4(-1.65, 1.33, 1.93, 0.76))[2]) < 0.001 ? 1 : -1] array10;
float[length(vec4(0.608, -0.114, -0.3876, 0.0) - outerProduct(vec4(0.8, -0.15, -0.51, 0.0), vec4(-1.65, 1.33, 1.93, 0.76))[3]) < 0.001 ? 1 : -1] array11;
float[length(vec4(0.64, -0.12, -0.408, 0.0) - outerProduct(vec4(0.8, -0.15, -0.51, 0.0), vec4(0.8, -0.15, -0.51, 0.0))[0]) < 0.001 ? 1 : -1] array12;
float[length(vec4(-0.12, 0.0225, 0.0765, -0) - outerProduct(vec4(0.8, -0.15, -0.51, 0.0), vec4(0.8, -0.15, -0.51, 0.0))[1]) < 0.001 ? 1 : -1] array13;
float[length(vec4(-0.408, 0.0765, 0.2601, -0) - outerProduct(vec4(0.8, -0.15, -0.51, 0.0), vec4(0.8, -0.15, -0.51, 0.0))[2]) < 0.001 ? 1 : -1] array14;
float[length(vec4(0.0, -0, -0, 0.0) - outerProduct(vec4(0.8, -0.15, -0.51, 0.0), vec4(0.8, -0.15, -0.51, 0.0))[3]) < 0.001 ? 1 : -1] array15;

main()
{
  gl_Position  = vec4(array0.length()
			+ array1.length()
			+ array2.length()
			+ array3.length()
			+ array4.length()
			+ array5.length()
			+ array6.length()
			+ array7.length()
			+ array8.length()
			+ array9.length()
			+ array10.length()
			+ array11.length()
			+ array12.length()
			+ array13.length()
			+ array14.length()
			+ array15.length());
}
