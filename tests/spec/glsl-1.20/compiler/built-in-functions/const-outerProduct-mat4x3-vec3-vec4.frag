/* [config]
 * expect_result: pass
 * glsl_version: 1.20
 * [end config]
 * Automatically generated by gen_constant_array_size_tests.py
 */
#version 120

float[length(vec3(0.0495, 1.4025, 1.551) - outerProduct(vec3(-0.03, -0.85, -0.94), vec4(-1.65, 1.33, 1.93, 0.76))[0]) < 0.001 ? 1 : -1] array0;
float[length(vec3(-0.0399, -1.1305, -1.2502) - outerProduct(vec3(-0.03, -0.85, -0.94), vec4(-1.65, 1.33, 1.93, 0.76))[1]) < 0.001 ? 1 : -1] array1;
float[length(vec3(-0.0579, -1.6405, -1.8142) - outerProduct(vec3(-0.03, -0.85, -0.94), vec4(-1.65, 1.33, 1.93, 0.76))[2]) < 0.001 ? 1 : -1] array2;
float[length(vec3(-0.0228, -0.646, -0.7144) - outerProduct(vec3(-0.03, -0.85, -0.94), vec4(-1.65, 1.33, 1.93, 0.76))[3]) < 0.001 ? 1 : -1] array3;
float[length(vec3(-0.024, -0.68, -0.752) - outerProduct(vec3(-0.03, -0.85, -0.94), vec4(0.8, -0.15, -0.51, 0.0))[0]) < 0.001 ? 1 : -1] array4;
float[length(vec3(0.0045, 0.1275, 0.141) - outerProduct(vec3(-0.03, -0.85, -0.94), vec4(0.8, -0.15, -0.51, 0.0))[1]) < 0.001 ? 1 : -1] array5;
float[length(vec3(0.0153, 0.4335, 0.4794) - outerProduct(vec3(-0.03, -0.85, -0.94), vec4(0.8, -0.15, -0.51, 0.0))[2]) < 0.001 ? 1 : -1] array6;
float[length(vec3(-0, -0, -0) - outerProduct(vec3(-0.03, -0.85, -0.94), vec4(0.8, -0.15, -0.51, 0.0))[3]) < 0.001 ? 1 : -1] array7;
float[length(vec3(-2.7555, -1.089, -3.0855) - outerProduct(vec3(1.67, 0.66, 1.87), vec4(-1.65, 1.33, 1.93, 0.76))[0]) < 0.001 ? 1 : -1] array8;
float[length(vec3(2.2211, 0.8778, 2.4871) - outerProduct(vec3(1.67, 0.66, 1.87), vec4(-1.65, 1.33, 1.93, 0.76))[1]) < 0.001 ? 1 : -1] array9;
float[length(vec3(3.2231, 1.2738, 3.6091) - outerProduct(vec3(1.67, 0.66, 1.87), vec4(-1.65, 1.33, 1.93, 0.76))[2]) < 0.001 ? 1 : -1] array10;
float[length(vec3(1.2692, 0.5016, 1.4212) - outerProduct(vec3(1.67, 0.66, 1.87), vec4(-1.65, 1.33, 1.93, 0.76))[3]) < 0.001 ? 1 : -1] array11;
float[length(vec3(1.336, 0.528, 1.496) - outerProduct(vec3(1.67, 0.66, 1.87), vec4(0.8, -0.15, -0.51, 0.0))[0]) < 0.001 ? 1 : -1] array12;
float[length(vec3(-0.2505, -0.099, -0.2805) - outerProduct(vec3(1.67, 0.66, 1.87), vec4(0.8, -0.15, -0.51, 0.0))[1]) < 0.001 ? 1 : -1] array13;
float[length(vec3(-0.8517, -0.3366, -0.9537) - outerProduct(vec3(1.67, 0.66, 1.87), vec4(0.8, -0.15, -0.51, 0.0))[2]) < 0.001 ? 1 : -1] array14;
float[length(vec3(0.0, 0.0, 0.0) - outerProduct(vec3(1.67, 0.66, 1.87), vec4(0.8, -0.15, -0.51, 0.0))[3]) < 0.001 ? 1 : -1] array15;

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
			+ array11.length()
			+ array12.length()
			+ array13.length()
			+ array14.length()
			+ array15.length());
}
