#ifndef _LINUX_INIT_H
#define _LINUX_INIT_H

/* These macros are used to mark some functions or 
 * initialized data (doesn't apply to uninitialized data)
 * as `initialization' functions. The kernel can take this
 * as hint that the function is used only during the initialization
 * phase and free up used memory resources after
 *
 * Usage:
 * For functions:
 * 
 * You should add __init immediately before the function name, like:
 *
 * static void __init initme(int x, int y)
 * {
 *    extern int z; z = x * y;
 * }
 *
 * Deprecated: you can surround the whole function declaration 
 * just before function body into __initfunc() macro, like:
 *
 * __initfunc (static void initme(int x, int y))
 * {
 *    extern int z; z = x * y;
 * }
 *
 * If the function has a prototype somewhere, you can also add
 * __init between closing brace of the prototype and semicolon:
 *
 * extern int initialize_foobar_device(int, int, int) __init;
 *
 * For initialized data:
 * You should insert __initdata between the variable name and equal
 * sign followed by value, e.g.:
 *
 * static int init_variable __initdata = 0;
 * static char linux_logo[] __initdata = { 0x32, 0x36, ... };
 *
 * For initialized data not at file scope, i.e. within a function,
 * you should use __initlocaldata instead, due to a bug in GCC 2.7.
 */

/*
 * Disable the __initfunc macros if a file that is a part of a
 * module attempts to use them. We do not want to interfere
 * with module linking.
 */

#if !defined(MODULE) && !defined(OSKIT)
#include <asm/init.h>
#else
#define __init
#define __initdata
#define __initfunc(__arginit) __arginit
/* For assembly routines */
#define __INIT
#define __FINIT
#define __INITDATA
#endif

#if (__GNUC__ > 2) || (__GNUC__ == 2 && __GNUC_MINOR__ >= 8)
#define __initlocaldata  __initdata
#else
#define __initlocaldata
#endif


#ifndef __ASSEMBLY__

/*
 * Used for kernel command line parameter setup
 */
struct new_kernel_param {
	const char *str;
	int (*setup_func)(char *);
};

extern struct new_kernel_param __setup_start, __setup_end;

#define __setup(str, fn)								\
	static char __setup_str_##fn[] __initdata = str;				\
	static struct new_kernel_param __setup_##fn __initsetup = { __setup_str_##fn, fn }

#define __initsetup	__attribute__ ((unused,__section__ (".setup.init")))


/*
 * Used for initialization calls..
 */
typedef int (*initcall_t)(void);
typedef void (*exitcall_t)(void);

#define __init_call	__attribute__ ((unused,__section__ (".initcall.init")))
#define __exit_call	__attribute__ ((unused,__section__ (".exitcall.exit")))

extern initcall_t __initcall_start, __initcall_end;

#define __initcall(fn)								\
	static initcall_t __initcall_##fn __init_call = fn
#define __exitcall(fn)								\
	static exitcall_t __exitcall_##fn __exit_call = fn

#ifdef MODULE
/* Not sure what version aliases were introduced in, but certainly in 2.91.66.  */
#if __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 91)
/* These macros create a dummy inline: gcc 2.9x does not count alias
 as usage, hence the `unused function' warning when __init functions
 are declared static. We use the dummy __*_module_inline functions
 both to kill the warning and check the type of the init/cleanup
 function. */
typedef int (*__init_module_func_t)(void);
typedef void (*__cleanup_module_func_t)(void);
#define module_init(x) \
	int init_module(void) __attribute__((alias(#x))); \
	extern inline __init_module_func_t __init_module_inline(void) \
	{ return x; }
#define module_exit(x) \
	void cleanup_module(void) __attribute__((alias(#x))); \
	extern inline __cleanup_module_func_t __cleanup_module_inline(void) \
	{ return x; }
#else
#define module_init(x)	int init_module(void) { return x(); }
#define module_exit(x)	void cleanup_module(void) { x(); }
#endif

#else 
#define module_init(x)	__initcall(x);
#define module_exit(x)	__exitcall(x);
#endif

#endif /* __ASSEMBLY __ */
#endif
