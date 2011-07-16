/* [config]
 * expect_result: pass
 * glsl_version: 1.20
 * [end config]
 * Automatically generated by gen_constant_array_size_tests.py
 */
#version 120

float[length(vec4(0.0495, -0.0399, -0.0579, -0.0228) - outerProduct(vec4(-1.65, 1.33, 1.93, 0.76), vec3(-0.03, -0.85, -0.94))[0]) < 0.001 ? 1 : -1] array0;
float[length(vec4(1.4025, -1.1305, -1.6405, -0.646) - outerProduct(vec4(-1.65, 1.33, 1.93, 0.76), vec3(-0.03, -0.85, -0.94))[1]) < 0.001 ? 1 : -1] array1;
float[length(vec4(1.551, -1.2502, -1.8142, -0.7144) - outerProduct(vec4(-1.65, 1.33, 1.93, 0.76), vec3(-0.03, -0.85, -0.94))[2]) < 0.001 ? 1 : -1] array2;
float[length(vec4(-2.7555, 2.2211, 3.2231, 1.2692) - outerProduct(vec4(-1.65, 1.33, 1.93, 0.76), vec3(1.67, 0.66, 1.87))[0]) < 0.001 ? 1 : -1] array3;
float[length(vec4(-1.089, 0.8778, 1.2738, 0.5016) - outerProduct(vec4(-1.65, 1.33, 1.93, 0.76), vec3(1.67, 0.66, 1.87))[1]) < 0.001 ? 1 : -1] array4;
float[length(vec4(-3.0855, 2.4871, 3.6091, 1.4212) - outerProduct(vec4(-1.65, 1.33, 1.93, 0.76), vec3(1.67, 0.66, 1.87))[2]) < 0.001 ? 1 : -1] array5;
float[length(vec4(-0.024, 0.0045, 0.0153, -0) - outerProduct(vec4(0.8, -0.15, -0.51, 0.0), vec3(-0.03, -0.85, -0.94))[0]) < 0.001 ? 1 : -1] array6;
float[length(vec4(-0.68, 0.1275, 0.4335, -0) - outerProduct(vec4(0.8, -0.15, -0.51, 0.0), vec3(-0.03, -0.85, -0.94))[1]) < 0.001 ? 1 : -1] array7;
float[length(vec4(-0.752, 0.141, 0.4794, -0) - outerProduct(vec4(0.8, -0.15, -0.51, 0.0), vec3(-0.03, -0.85, -0.94))[2]) < 0.001 ? 1 : -1] array8;
float[length(vec4(1.336, -0.2505, -0.8517, 0.0) - outerProduct(vec4(0.8, -0.15, -0.51, 0.0), vec3(1.67, 0.66, 1.87))[0]) < 0.001 ? 1 : -1] array9;
float[length(vec4(0.528, -0.099, -0.3366, 0.0) - outerProduct(vec4(0.8, -0.15, -0.51, 0.0), vec3(1.67, 0.66, 1.87))[1]) < 0.001 ? 1 : -1] array10;
float[length(vec4(1.496, -0.2805, -0.9537, 0.0) - outerProduct(vec4(0.8, -0.15, -0.51, 0.0), vec3(1.67, 0.66, 1.87))[2]) < 0.001 ? 1 : -1] array11;

main()
{
  gl_FragColor = vec4(array0.length()
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
			    + array11.length());
}