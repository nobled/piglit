/* [config]
 * expect_result: pass
 * glsl_version: 1.20
 * [end config]
 * Automatically generated by gen_constant_array_size_tests.py
 */
#version 120

float[any(bvec4(false, false, false, false)) ? -1 : 1] array0;
float[any(bvec4(false, false, false, true)) ? 1 : -1] array1;
float[any(bvec4(false, false, true, false)) ? 1 : -1] array2;
float[any(bvec4(false, false, true, true)) ? 1 : -1] array3;
float[any(bvec4(false, true, false, false)) ? 1 : -1] array4;
float[any(bvec4(false, true, false, true)) ? 1 : -1] array5;
float[any(bvec4(false, true, true, false)) ? 1 : -1] array6;
float[any(bvec4(false, true, true, true)) ? 1 : -1] array7;
float[any(bvec4(true, false, false, false)) ? 1 : -1] array8;
float[any(bvec4(true, false, false, true)) ? 1 : -1] array9;
float[any(bvec4(true, false, true, false)) ? 1 : -1] array10;
float[any(bvec4(true, false, true, true)) ? 1 : -1] array11;
float[any(bvec4(true, true, false, false)) ? 1 : -1] array12;
float[any(bvec4(true, true, false, true)) ? 1 : -1] array13;
float[any(bvec4(true, true, true, false)) ? 1 : -1] array14;
float[any(bvec4(true, true, true, true)) ? 1 : -1] array15;

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
